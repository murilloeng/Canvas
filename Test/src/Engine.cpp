//std
#include <stdexcept>

//canvas
#include "Canvas/Canvas/inc/API/Loader.hpp"

//test
#include "Canvas/Test/inc/Engine.hpp"

//constructor
Engine::Engine(void) : m_show_fps{true}, m_width{700}, m_height{700}
{
	setup_glfw();
	setup_scene();
	setup_callbacks();
}

//constructor
Engine::~Engine(void)
{
	delete m_scene;
	glfwTerminate();
}

//start
void Engine::start(void)
{
	glfwSetTime(0);
	float t1 = 0, t2;
	while(!glfwWindowShouldClose(m_window))
	{
		//time
		t2 = (float) glfwGetTime();
		//animations
		glfwPollEvents();
		m_scene->time(t2);
		m_scene->update_animations();
		if(m_user_idle) m_user_idle();
		//draw
		m_scene->draw();
		glfwSwapBuffers(m_window);
		//framerate
		if(m_show_fps)
		{
			printf("FPS: %d\n", uint32_t(1 / (t2 - t1)));
			t1 = t2;
		}
	}
}

//data
bool Engine::show_fps(void) const
{
	return m_show_fps;
}
bool Engine::show_fps(bool show_fps)
{
	return m_show_fps = show_fps;
}

uint32_t Engine::width(void) const
{
	return m_width;
}
uint32_t Engine::height(void) const
{
	return m_height;
}

canvas::Scene* Engine::scene(void) const
{
	return m_scene;
}

//user
void Engine::user_idle(std::function<void(void)> user_idle)
{
	m_user_idle = user_idle;
}
void Engine::user_key(std::function<void(int32_t, int32_t, int32_t)> user_key)
{
	m_user_key = user_key;
}
void Engine::user_button(std::function<void(int32_t, int32_t, int32_t, double, double)> user_button)
{
	m_user_button = user_button;
}

//setup
void Engine::setup_glfw(void)
{
	//library
	if(glfwInit() != GLFW_TRUE)
	{
		throw std::runtime_error("GLFW initialization failed!");
	}
	//window
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_window = glfwCreateWindow(700, 700, "Canvas", nullptr, nullptr);
	if(!m_window)
	{
		glfwTerminate();
		throw std::runtime_error("GLFW window initialization failed!");
	}
	//context
	glfwMakeContextCurrent(m_window);
	//v-sync
	glfwSwapInterval(0);
	//functions
	canvas::load_functions();
}
void Engine::setup_scene(void)
{
	int width, height;
	m_scene = new canvas::Scene;
	canvas::shaders::Shader::path("Canvas/shd/");
	glfwGetWindowSize(m_window, &width, &height);
	m_scene->camera().callback_reshape(width, height);
}
void Engine::setup_callbacks(void)
{
	glfwSetWindowUserPointer(m_window, this);
	glfwSetKeyCallback(m_window, callback_key);
	glfwSetScrollCallback(m_window, callback_wheel);
	glfwSetWindowSizeCallback(m_window, callback_size);
	glfwSetCursorPosCallback(m_window, callback_position);
	glfwSetMouseButtonCallback(m_window, callback_button);
}

//callbacks
void Engine::callback_position(GLFWwindow* window, double x1, double x2)
{
	Engine* engine = (Engine*) glfwGetWindowUserPointer(window);
	engine->m_scene->camera().callback_motion(int32_t(x1), int32_t(x2));
	glfwSwapBuffers(window);
}
void Engine::callback_size(GLFWwindow* window, int width, int height)
{
	//data
	Engine* engine = (Engine*) glfwGetWindowUserPointer(window);
	//engine
	engine->m_width = width;
	engine->m_height = height;
	//scene
	engine->m_scene->camera().callback_reshape(width, height);
	engine->m_scene->update(true);
	//update
	glfwSwapBuffers(window);
}
void Engine::callback_button(GLFWwindow* window, int button, int action, int modifiers)
{
	//data
	double x1, x2;
	glfwGetCursorPos(window, &x1, &x2);
	Engine* engine = (Engine*) glfwGetWindowUserPointer(window);
	//user
	if(engine->m_user_button) engine->m_user_button(button, action, modifiers, x1, x2);
	//callback
	engine->m_scene->camera().callback_mouse(canvas_button(button), action == GLFW_PRESS, int32_t(x1), int32_t(x2), canvas_modifiers(modifiers));
	//update
	glfwSwapBuffers(window);
}
void Engine::callback_wheel(GLFWwindow* window, double dx1, double dx2)
{
	//data
	Engine* engine = (Engine*) glfwGetWindowUserPointer(window);
	//camera
	engine->m_scene->camera().callback_wheel(dx2 < 0);
	//update
	glfwSwapBuffers(window);
}
void Engine::callback_key(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
{
	//master
	double x1, x2;
	if(action == GLFW_RELEASE) return;
	Engine* engine = (Engine*) glfwGetWindowUserPointer(window);
	glfwGetCursorPos(window, &x1, &x2);
	if(engine->m_user_key) engine->m_user_key(key, int32_t(x1), int32_t(x2));
	//Canvas
	if(key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if(key == GLFW_KEY_MINUS)
	{
		engine->m_scene->camera().callback_wheel(true);
	}
	if(key == GLFW_KEY_EQUAL && (mods & GLFW_MOD_SHIFT))
	{
		engine->m_scene->camera().callback_wheel(false);
	}
	else
	{
		const char* name = glfwGetKeyName(key, 0);
		if(name) engine->m_scene->camera().callback_key(*name);
		glfwSwapBuffers(window);
	}
}

//canvas
uint32_t Engine::canvas_modifiers(int32_t glfw_modifiers)
{
	//data
	int32_t glfw_list[] = {
		GLFW_MOD_ALT, GLFW_MOD_SHIFT, GLFW_MOD_CONTROL
	};
	canvas::modifier canvas_list[] = {
		canvas::modifier::alt, canvas::modifier::shift, canvas::modifier::control
	};
	//modifiers
	uint32_t canvas_modifiers = 0;
	for(uint32_t i = 0; i < 3; i++)
	{
		if(glfw_modifiers & glfw_list[i])
		{
			canvas_modifiers |= uint32_t(canvas_list[i]);
		}
	}
	//return
	return canvas_modifiers;
}
canvas::button Engine::canvas_button(int32_t glfw_button)
{
	//data
	int32_t glfw_list[] = {
		GLFW_MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_RIGHT, GLFW_MOUSE_BUTTON_MIDDLE
	};
	canvas::button canvas_list[] = {
		canvas::button::left, canvas::button::right, canvas::button::middle
	};
	//modifiers
	for(uint32_t i = 0; i < 3; i++)
	{
		if(glfw_button == glfw_list[i])
		{
			return canvas_list[i];
		}
	}
	//return
	return canvas::button::none;
}
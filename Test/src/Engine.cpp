//std
#include <stdexcept>

//canvas
#include "Canvas/Test/inc/Engine.hpp"

//constructor
Engine::Engine(void) : m_show_fps{true}, m_width{700}, m_height{700}
{
	setup_glfw();
	setup_glew();
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
	double t1 = 0, t2;
	while(!glfwWindowShouldClose(m_window))
	{
		//idle
		if(m_user_idle) m_user_idle();
		//draw
		glfwPollEvents();
		m_scene->draw();
		glfwSwapBuffers(m_window);
		//framerate
		if(m_show_fps)
		{
			t2 = glfwGetTime();
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
}
void Engine::setup_glew(void)
{
	if(glewInit() != GLEW_OK)
	{
		glfwTerminate();
		throw std::runtime_error("GLEW initialization failed!");
	}
}
void Engine::setup_scene(void)
{
	m_scene = new canvas::Scene("Canvas/shd/");
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
void Engine::callback_button(GLFWwindow* window, int button, int action, int mods)
{
	//data
	double x1, x2;
	glfwGetCursorPos(window, &x1, &x2);
	Engine* engine = (Engine*) glfwGetWindowUserPointer(window);
	if(engine->m_user_button) engine->m_user_button(button, action, mods, x1, x2);
	uint32_t glfw_buttons[] = {GLFW_MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_RIGHT, GLFW_MOUSE_BUTTON_MIDDLE};
	canvas::button canvas_buttons[] = {canvas::button::left, canvas::button::right, canvas::button::middle};
	//callback
	for(uint32_t i = 0; i < 3; i++)
	{
		if(uint32_t(button) == glfw_buttons[i])
		{
			engine->m_scene->camera().callback_mouse(canvas_buttons[i], action == GLFW_PRESS, int32_t(x1), int32_t(x2));
		}
	}
	glfwSwapBuffers(window);
}
void Engine::callback_wheel(GLFWwindow* window, double dx1, double dx2)
{
	double x1, x2;
	glfwGetCursorPos(window, &x1, &x2);
	Engine* engine = (Engine*) glfwGetWindowUserPointer(window);
	engine->m_scene->camera().callback_wheel(int32_t(dx2), int32_t(x1), int32_t(x2));
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
	if(key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, true);
	else
	{
		const char* name = glfwGetKeyName(key, 0);
		if(name) engine->m_scene->camera().callback_keyboard(*name);
		glfwSwapBuffers(window);
	}
}
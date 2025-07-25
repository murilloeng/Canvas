//std
#include <cmath>
#include <chrono>
#include <thread>
#include <stdexcept>

//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/Geometry.hpp"

//test
#include "Canvas/Managers/inc/GLFW.hpp"

//static data
static canvas::managers::GLFW* master;
static std::chrono::high_resolution_clock::time_point t1, t2;

namespace canvas
{
	namespace managers
	{
		//constructors
		GLFW::GLFW(int argc, char** argv, const char* shaders_dir) : 
			m_show_fps(true), m_callback_idle(nullptr), m_callback_keyboard(nullptr)
		{
			//setup
			master = this;
			if(!glfwInit())
			{
				throw std::runtime_error("GLFW initialization failed!");
			}
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			//window
			m_window = glfwCreateWindow(m_width, m_height, "Canvas", nullptr, nullptr);
			if(!m_window)
			{
				glfwTerminate();
				throw std::runtime_error("GLFW window initialization failed!");
			}
			glfwMakeContextCurrent(m_window);
			glfwSetWindowPos(m_window, 200, 200);
			//glew
			if(glewInit() != GLEW_OK)
			{
				glfwTerminate();
				throw std::runtime_error("GLEW initialization failed!");
			}
			m_scene = new canvas::Scene(shaders_dir);
			master->m_scene->camera().callback_reshape(m_width, m_height);
			//callbacks
			glfwSetKeyCallback(m_window, callback_key);
			glfwSetScrollCallback(m_window, callback_wheel);
			glfwSetWindowSizeCallback(m_window, callback_size);
			glfwSetCursorPosCallback(m_window, callback_motion);
			glfwSetMouseButtonCallback(m_window, callback_mouse);
		}

		//destructor
		GLFW::~GLFW(void)
		{
			//scene
			delete m_scene;
			//window
			glfwDestroyWindow(m_window);
			//library
			glfwTerminate();
		}

		//data
		bool GLFW::show_fps(void) const
		{
			return m_show_fps;
		}
		bool GLFW::show_fps(bool show_fps)
		{
			return m_show_fps = show_fps;
		}
		canvas::Scene* GLFW::scene(void) const
		{
			return m_scene;
		}
		void GLFW::callback_idle(std::function<void(void)> callback_idle)
		{
			m_callback_idle = callback_idle;
		}
		void GLFW::callback_key(std::function<void(int32_t, int32_t, int32_t)> callback_keyboard)
		{
			m_callback_keyboard = callback_keyboard;
		}

		//loop
		void GLFW::start(void)
		{
			t1 = std::chrono::high_resolution_clock::now();
			while(!glfwWindowShouldClose(m_window))
			{
				if(master->m_callback_idle)
				{
					master->m_callback_idle();
				}
				if(master->m_callback_idle || master->m_show_fps)
				{
					master->m_scene->draw();
					glfwSwapBuffers(m_window);
				}
				if(master->m_show_fps)
				{
					using namespace std::chrono;
					t2 = high_resolution_clock::now();
					const uint64_t td = duration_cast<microseconds>(t2 - t1).count();
					printf("FPS: %d\n", uint32_t(1e6 / td));
					t1 = t2;
				}
				glfwPollEvents();
			}
		}

		//callbacks
		void GLFW::callback_motion(GLFWwindow* window, double x1, double x2)
		{
			master->m_scene->camera().callback_motion(int32_t(x1), int32_t(x2));
			glfwSwapBuffers(window);
		}
		void GLFW::callback_size(GLFWwindow* window, int width, int height)
		{
			master->m_scene->camera().callback_reshape(width, height);
			master->m_scene->update(true);
			glfwSwapBuffers(window);
		}
		void GLFW::callback_mouse(GLFWwindow* window, int button, int action, int mods)
		{
			//data
			double x1, x2;
			uint32_t glfw_buttons[] = {GLFW_MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_RIGHT, GLFW_MOUSE_BUTTON_MIDDLE};
			canvas::button canvas_buttons[] = {canvas::button::left, canvas::button::right, canvas::button::middle};
			//callback
			for(uint32_t i = 0; i < 3; i++)
			{
				if(uint32_t(button) == glfw_buttons[i])
				{
					glfwGetCursorPos(window, &x1, &x2);
					master->m_scene->camera().callback_mouse(canvas_buttons[i], action == GLFW_PRESS, int32_t(x1), int32_t(x2));
				}
			}
			glfwSwapBuffers(window);
		}
		void GLFW::callback_wheel(GLFWwindow* window, double dx1, double dx2)
		{
			double x1, x2;
			glfwGetCursorPos(window, &x1, &x2);
			master->m_scene->camera().callback_wheel(int32_t(dx2), int32_t(x1), int32_t(x2));
			glfwSwapBuffers(window);
		}
		void GLFW::callback_key(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
		{
			//master
			double x1, x2;
			if(action == GLFW_RELEASE) return;
			glfwGetCursorPos(master->m_window, &x1, &x2);
			callback_special(window, key, scancode, action, mods);
			if(master->m_callback_keyboard) master->m_callback_keyboard(key, int32_t(x1), int32_t(x2));
			//Canvas
			if(key == GLFW_KEY_L) master->swap_lines();
			else if(key == GLFW_KEY_T) master->swap_triangles();
			else if(key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(master->m_window, true);
			else
			{
				const char* name = glfwGetKeyName(key, 0);
				if(name) master->m_scene->camera().callback_keyboard(*name);
				glfwSwapBuffers(master->m_window);
			}
		}
		void GLFW::callback_special(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
		{
			//data
			uint32_t canvas_mod = 0;
			const uint32_t glfw_mods[] = {GLFW_MOD_ALT, GLFW_MOD_CONTROL, GLFW_MOD_SHIFT};
			const uint32_t glfw_keys[] = {GLFW_KEY_LEFT, GLFW_KEY_RIGHT, GLFW_KEY_DOWN, GLFW_KEY_UP};
			const canvas::key canvas_keys[] = {canvas::key::left, canvas::key::right, canvas::key::down, canvas::key::up};
			const canvas::modifier canvas_mods[] = {canvas::modifier::alt, canvas::modifier::ctrl, canvas::modifier::shift};
			//callback
			for(uint32_t i = 0; i < 3; i++)
			{
				if(mods & glfw_mods[i])
				{
					canvas_mod |= 1 << uint32_t(canvas_mods[i]);
				}
			}
			for(uint32_t i = 0; i < 4; i++)
			{
				if(uint32_t(key) == glfw_keys[i])
				{
					double x1, x2;
					glfwGetCursorPos(window, &x1, &x2);
					master->m_scene->camera().callback_special(canvas_keys[i], canvas_mod, int32_t(x1), int32_t(x2));
				}
			}
			glfwSwapBuffers(window);
		}

		//misc
		void GLFW::swap_lines(void)
		{
			for(canvas::objects::Object* object : master->m_scene->objects())
			{
				//data
				canvas::objects::Geometry* geometry = dynamic_cast<canvas::objects::Geometry*>(object);
				//swap
				if(geometry)
				{
					geometry->stroke(!geometry->stroke());
				}
			}
			master->scene()->update(true);
			glfwSwapBuffers(master->m_window);
		}
		void GLFW::swap_triangles(void)
		{
			for(canvas::objects::Object* object : master->m_scene->objects())
			{
				//data
				canvas::objects::Geometry* geometry = dynamic_cast<canvas::objects::Geometry*>(object);
				//swap
				if(geometry)
				{
					geometry->fill(!geometry->fill());
				}
			}
			master->scene()->update(true);
			glfwSwapBuffers(master->m_window);
		}
	}
}
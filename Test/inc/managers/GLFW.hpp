#pragma once

//std
#include <cstdint>
#include <functional>

//external
#include "external/cpp/inc/GL/glew.h"
#include "external/cpp/inc/GLFW/glfw3.h"

//canvas
#include "Canvas/inc/Scene/Scene.hpp"

class GLFW
{
public:
	//constructors
	GLFW(int, char**, const char*);

	//destructor
	~GLFW(void);

	//data
	bool show_fps(bool);
	bool show_fps(void) const;
	canvas::Scene* scene(void) const;
	void callback_idle(std::function<void(void)>);
	void callback_keyboard(std::function<void(uint8_t, int, int)>);

	//loop
	void start(void);

	//callbacks
	static void callback_mouse(GLFWwindow*, int, int, int);
	static void callback_wheel(GLFWwindow*, double, double);
	static void callback_motion(GLFWwindow*, double, double);
	static void callback_size(GLFWwindow*, int32_t, int32_t);
	static void callback_key(GLFWwindow*, int32_t, int32_t, int32_t, int32_t);
	static void callback_special(GLFWwindow*, int32_t, int32_t, int32_t, int32_t);

protected:
	//misc
	void swap_lines(void);
	void swap_triangles(void);

	//data
	bool m_show_fps;
	GLFWwindow* m_window;
	canvas::Scene* m_scene;
	std::function<void(void)> m_callback_idle;
	std::function<void(uint8_t, int, int)> m_callback_keyboard;
};
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
	void callback_special(std::function<void(int, int, int)>);
	void callback_keyboard(std::function<void(uint8_t, int, int)>);

	//loop
	void start(void);

	//callbacks
	static void callback_idle(void);
	static void callback_display(void);
	static void callback_motion(int, int);
	static void callback_reshape(int, int);
	static void callback_special(int, int, int);
	static void callback_mouse(int, int, int, int);
	static void callback_wheel(int, int, int, int);
	static void callback_keyboard(uint8_t, int, int);

	//data
	static uint32_t key_up, key_down, key_left, key_right;

protected:
	//data
	bool m_show_fps;
	GLFWwindow* m_window;
	canvas::Scene* m_scene;
	std::function<void(void)> m_callback_idle;
	std::function<void(int, int, int)> m_callback_special;
	std::function<void(uint8_t, int, int)> m_callback_keyboard;
};
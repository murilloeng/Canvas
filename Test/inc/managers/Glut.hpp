#pragma once

//std
#include <cstdint>
#include <functional>

//canvas
#include "Canvas/inc/Scene/Scene.hpp"

class Glut
{
public:
	//constructors
	Glut(int, char**, const char*);

	//destructor
	~Glut(void);

	//data
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
	static uint32_t key_up;
	static uint32_t key_down;
	static uint32_t key_left;
	static uint32_t key_right;

protected:
	//data
	canvas::Scene* m_scene;
	std::function<void(void)> m_callback_idle;
	std::function<void(int, int, int)> m_callback_special;
	std::function<void(uint8_t, int, int)> m_callback_keyboard;
};
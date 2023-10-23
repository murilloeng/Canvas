#pragma once

//std
#include <functional>

namespace canvas
{
	class Scene;
}

namespace canvas
{
	class Glut
	{
	public:
		//constructors
		Glut(int, char**, const char*);

		//destructor
		~Glut(void);

		//data
		Scene* scene(void) const;

		//loop
		void start(void);

		//callbacks
		static void callback_display(void);
		static void callback_motion(int, int);
		static void callback_reshape(int, int);
		static void callback_special(int, int, int);
		static void callback_mouse(int, int, int, int);
		static void callback_wheel(int, int, int, int);
		static void callback_keyboard(unsigned char, int, int);

	private:
		//data
		Scene* m_scene;
	};
}
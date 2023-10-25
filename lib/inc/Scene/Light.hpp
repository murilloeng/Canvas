#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Colors/Color.hpp"

namespace canvas
{
	class Scene;
	class Program;
}

namespace canvas
{
	class Light
	{
	public:
		//constructors
		Light(void);

		//destructor
		~Light(void);

		//data
		bool ambient(bool);
		bool ambient(void) const;

		bool diffuse(bool);
		bool diffuse(void) const;

		bool specular(bool);
		bool specular(void) const;

		vec3 position(vec3);
		vec3 position(void) const;

		Color color_ambient(Color);
		Color color_ambient(void) const;

		Color color_diffuse(Color);
		Color color_diffuse(void) const;

		Color color_specular(Color);
		Color color_specular(void) const;

		//callbacks
		void callback_keyboard(char, int, int);

	private:
		//data
		bool m_ambient;
		bool m_diffuse;
		bool m_specular;
		vec3 m_position;
		Program* m_program;
		Color m_color_ambient;
		Color m_color_diffuse;
		Color m_color_specular;

		//friends
		friend class Scene;
	};
}
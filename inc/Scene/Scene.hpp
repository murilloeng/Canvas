#pragma once

//std
#include <string>
#include <vector>
#include <cstdint>

//FreeType
#include <freetype2/freetype/freetype.h>

//canvas
#include "Canvas/inc/Colors/Color.hpp"
#include "Canvas/inc/Lights/Lights.hpp"
#include "Canvas/inc/Cameras/Camera.hpp"

namespace canvas
{
	namespace buffers
	{
		class VBO;
	}
	namespace fonts
	{
		class Font;
	}
	namespace objects
	{
		class Object;
	}
	namespace animations
	{
		class Animation;
	}
}

namespace canvas
{
	class Scene
	{
	public:
		//constructors
		Scene(void);

		//destructor
		~Scene(void);

		//time
		float time(float);
		float time(void) const;

		//background
		Color background(Color);
		Color background(void) const;

		lights::Lights& light(void);
		const lights::Lights& light(void) const;

		cameras::Camera& camera(void);
		const cameras::Camera& camera(void) const;

		//fonts
		void add_font(const char*);
		fonts::Font* font(uint32_t) const;
		const std::vector<fonts::Font*>& fonts(void) const;

		//objects
		void clear_objects(bool);
		void add_object(objects::Object*);
		objects::Object* object(uint32_t) const;
		const std::vector<objects::Object*>& objects(void) const;

		//animations
		void add_animation(animations::Animation*);
		animations::Animation* animation(uint32_t) const;

		//update
		void draw(void);
		void setup(void);
		void update(void);
		void update_on_motion(void);
		void update_animations(void);

	protected:
		//setup
		void setup_OpenGL(void);
		void setup_FreeType(void);

		//data
		float m_time;
		Color m_background;
		FT_Library m_ft_library;
		lights::Lights m_lights;
		cameras::Camera m_camera;
		std::vector<fonts::Font*> m_fonts;
		std::vector<objects::Object*> m_objects;
		std::vector<animations::Animation*> m_animations;
	};
}
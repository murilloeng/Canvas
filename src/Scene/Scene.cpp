//std
#include <stdexcept>

//canvas
#include "Canvas/inc/Fonts/Font.hpp"
#include "Canvas/inc/Buffers/VBO.hpp"
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Objects/Object.hpp"
#include "Canvas/inc/Animations/Animation.hpp"

static void glClearColor(const canvas::Color& color)
{
	glClearColor(color[0], color[1], color[2], color[3]);
}

namespace canvas
{
	//constructors
	Scene::Scene(void) : m_background(0.12f, 0.12f, 0.12f, 1.00f), m_lights(this), m_camera(this)
	{
		setup_OpenGL();
		setup_FreeType();
		m_camera.m_scene = this;
	}

	//destructor
	Scene::~Scene(void)
	{
		//delete
		for(const fonts::Font* font : m_fonts) delete font;
		for(const objects::Object* object : m_objects) delete object;
		for(const animations::Animation* animation : m_animations) delete animation;
		//FreeType
		FT_Done_FreeType(m_ft_library);
	}

	//time
	float Scene::time(void) const
	{
		return m_time;
	}
	float Scene::time(float time)
	{
		return m_time = time;
	}

	//data
	Color Scene::background(void) const
	{
		return m_background;
	}
	Color Scene::background(Color background)
	{
		glClearColor(background);
		return m_background = background;
	}

	lights::Lights& Scene::light(void)
	{
		return m_lights;
	}
	const lights::Lights& Scene::light(void) const
	{
		return m_lights;
	}

	cameras::Camera& Scene::camera(void)
	{
		return m_camera;
	}
	const cameras::Camera& Scene::camera(void) const
	{
		return m_camera;
	}

	//fonts
	void Scene::add_font(const char* name)
	{
		m_fonts.push_back(new fonts::Font(m_ft_library, name));
	}
	fonts::Font* Scene::font(uint32_t index) const
	{
		return m_fonts[index];
	}
	const std::vector<fonts::Font*>& Scene::fonts(void) const
	{
		return m_fonts;
	}

	//objects
	void Scene::clear_objects(bool free)
	{
		if(free)
		{
			for(const objects::Object* object : m_objects)
			{
				delete object;
			}
		}
		m_objects.clear();
	}
	void Scene::add_object(objects::Object* object)
	{
		object->m_scene = this;
		m_objects.push_back(object);
	}
	objects::Object* Scene::object(uint32_t index) const
	{
		return m_objects[index];
	}
	const std::vector<objects::Object*>& Scene::objects(void) const
	{
		return m_objects;
	}

	//animations
	void Scene::add_animation(animations::Animation* animation)
	{
		animation->m_scene = this;
		if(animation->m_time_start == 0)
		{
			animation->m_time_start = m_time;
		}
		m_animations.push_back(animation);
	}
	animations::Animation* Scene::animation(uint32_t index) const
	{
		return m_animations[index];
	}

	//draw
	void Scene::draw(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for(objects::Object* object : m_objects) object->draw();
	}
	void Scene::setup(void)
	{
		for(objects::Object* object : m_objects) object->setup();
	}
	void Scene::update(void)
	{
		for(objects::Object* object : m_objects) object->update();
	}
	void Scene::update_on_motion(void)
	{
		for(objects::Object* object : m_objects)
		{
			object->update_on_motion();
		}
	}
	void Scene::update_animations(void)
	{
		std::vector<animations::Animation*>::iterator iterator;
		for(iterator = m_animations.begin(); iterator != m_animations.end();)
		{
			//data
			const float t0 = (*iterator)->m_time_start;
			const float dt = (*iterator)->m_time_duration;
			//update
			if(t0 <= m_time && m_time <= t0 + dt)
			{
				(*iterator)->animate(m_time);
				iterator++;
			}
			else if(m_time > t0 + dt)
			{
				(*iterator)->cleanup();
				delete *iterator;
				iterator = m_animations.erase(iterator);
			}
		}
	}

	//setup
	void Scene::setup_OpenGL(void)
	{
		//enable
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_POLYGON_OFFSET_FILL);
		//setup
		glPointSize(7);
		glClearColor(m_background);
		glPolygonOffset(1.0f, 1.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	void Scene::setup_FreeType(void)
	{
		if(FT_Init_FreeType(&m_ft_library))
		{
			throw std::runtime_error("FreeType initialization failed!");
		}
	}
}
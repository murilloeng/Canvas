//std
#include <omp.h>
#include <cmath>
#include <cfloat>
#include <algorithm>
#include <stdexcept>

//canvas
#include "Canvas/Canvas/inc/API/API.hpp"

#include "Canvas/Canvas/inc/Fonts/Font.hpp"

#include "Canvas/Canvas/inc/Buffers/VAO.hpp"
#include "Canvas/Canvas/inc/Buffers/VBO.hpp"
#include "Canvas/Canvas/inc/Buffers/IBO.hpp"
#include "Canvas/Canvas/inc/Buffers/UBO.hpp"

#include "Canvas/Canvas/inc/Scene/Scene.hpp"

#include "Canvas/Canvas/inc/Textures/Image.hpp"
#include "Canvas/Canvas/inc/Textures/Latex.hpp"

#include "Canvas/Canvas/inc/Shaders/Stage.hpp"
#include "Canvas/Canvas/inc/Shaders/Shader.hpp"

#include "Canvas/Canvas/inc/Textures/Texture.hpp"

#include "Canvas/Canvas/inc/Objects/Object.hpp"

#include "Canvas/Canvas/inc/Vertices/Text2D.hpp"
#include "Canvas/Canvas/inc/Vertices/Text3D.hpp"
#include "Canvas/Canvas/inc/Vertices/Model2D.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/Canvas/inc/Vertices/Image2D.hpp"
#include "Canvas/Canvas/inc/Vertices/Image3D.hpp"

#include "Canvas/Canvas/inc/Animations/Animation.hpp"

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
		setup_cameras();
		setup_freetype();
	}

	//destructor
	Scene::~Scene(void)
	{
		//delete
		for(const fonts::Font* font : m_fonts) delete font;
		for(const buffers::Buffer* vbo : m_vbos) delete vbo;
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

	//vbos
	void Scene::add_vbo(buffers::VBO* vbo)
	{
		return m_vbos.push_back(vbo);
	}
	buffers::VBO* Scene::vbo(uint32_t index) const
	{
		return m_vbos[index];
	}
	const std::vector<buffers::VBO*>& Scene::vbos(void) const
	{
		return m_vbos;
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
		for(const objects::Object* object : m_objects) object->draw();
	}
	void Scene::update(bool setup)
	{
		//setup
		if(setup)
		{
			setup_objects();
		}
		//update
		#pragma omp parallel for
		for(int32_t i = 0; i < (int32_t) m_objects.size(); i++)
		{
			m_objects[i]->setup();
		}
		//buffers
		for(const buffers::VBO* vbo : m_vbos) vbo->transfer();
	}
	void Scene::update_on_motion(void)
	{
		for(objects::Object* object : m_objects)
		{
			object->update_on_motion();
		}
		for(const buffers::VBO* vbo : m_vbos) vbo->transfer();
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
	void Scene::setup_cameras(void)
	{
		m_camera.m_scene = this;
	}
	void Scene::setup_objects(void)
	{
		for(buffers::VBO* vbo : m_vbos) vbo->m_vertex_count = 0;
		for(objects::Object* object : m_objects) object->setup();
		for(buffers::VBO* vbo : m_vbos) vbo->allocate();
	}
	void Scene::setup_freetype(void)
	{
		if(FT_Init_FreeType(&m_ft_library))
		{
			throw std::runtime_error("FreeType initialization failed!");
		}
	}
}
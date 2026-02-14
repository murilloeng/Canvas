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

namespace canvas
{
	//constructors
	Scene::Scene(std::string shaders_dir) : 
		m_background(0, 0, 0, 1), m_ubos(1),
		m_textures(3), m_lights(this), m_camera(this),m_shaders_dir(shaders_dir)
	{
		setup_ubos();
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
		for(const buffers::Buffer* ibo : m_ibos) delete ibo;
		for(const buffers::Buffer* ubo : m_ubos) delete ubo;
		for(const textures::Latex* latex : m_latex) delete latex;
		for(const textures::Image* image : m_images) delete image;
		for(const shaders::Shader* shader : m_shaders) delete shader;
		for(const objects::Object* object : m_objects) delete object;
		for(const textures::Texture* texture : m_textures) delete texture;
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

	//vaos
	void Scene::add_vao(buffers::VAO* vao)
	{
		m_vaos.push_back(vao);
	}
	buffers::VAO* Scene::vao(uint32_t index) const
	{
		return m_vaos[index];
	}
	buffers::VAO* Scene::vao(const char* label) const
	{
		for(buffers::VAO* vao : m_vaos)
		{
			if(strcmp(label, vao->label()) == 0) return vao;
		}
		return nullptr;
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
	buffers::VBO* Scene::vbo(const char* label) const
	{
		for(buffers::VBO* vbo : m_vbos)
		{
			if(strcmp(label, vbo->label()) == 0) return vbo;
		}
		return nullptr;
	}
	const std::vector<buffers::VBO*>& Scene::vbos(void) const
	{
		return m_vbos;
	}

	//ibos
	void Scene::add_ibo(buffers::IBO* ibo)
	{
		return m_ibos.push_back(ibo);
	}
	buffers::IBO* Scene::ibo(uint32_t index) const
	{
		return m_ibos[index];
	}
	buffers::IBO* Scene::ibo(const char* label) const
	{
		for(buffers::IBO* ibo : m_ibos)
		{
			if(strcmp(label, ibo->label()) == 0) return ibo;
		}
		return nullptr;
	}

	//ubos
	void Scene::add_ubo(buffers::UBO* ubo)
	{
		return m_ubos.push_back(ubo);
	}
	buffers::UBO* Scene::ubo(uint32_t index) const
	{
		return m_ubos[index];
	}
	buffers::UBO* Scene::ubo(const char* label) const
	{
		for(buffers::UBO* ubo : m_ubos)
		{
			if(strcmp(label, ubo->label()) == 0) return ubo;
		}
		return nullptr;
	}

	//shaders
	void Scene::add_shader(shaders::Shader* shader)
	{
		m_shaders.push_back(shader);
	}
	shaders::Shader* Scene::shader(uint32_t index) const
	{
		return m_shaders[index];
	}
	shaders::Shader* Scene::shader(const char* label) const
	{
		for(shaders::Shader* shader : m_shaders)
		{
			if(strcmp(label, shader->label()) == 0) return shader;
		}
		return nullptr;
	}

	//textures
	void Scene::add_texture(textures::Texture* texture)
	{
		m_textures.push_back(texture);
	}
	textures::Texture* Scene::texture(uint32_t index) const
	{
		return m_textures[index];
	}
	textures::Texture* Scene::texture(const char* label) const
	{
		for(textures::Texture* texture : m_textures)
		{
			if(strcmp(label, texture->label()) == 0) return texture;
		}
		return nullptr;
	}

	//fonts
	void Scene::add_font(const char* name)
	{
		m_fonts.push_back(new fonts::Font(this, name));
	}
	fonts::Font* Scene::font(uint32_t index) const
	{
		return m_fonts[index];
	}
	fonts::Font* Scene::font(const char* label) const
	{
		for(fonts::Font* font : m_fonts)
		{
			if(font->name().compare(label) == 0) return font;
		}
		return nullptr;
	}
	const std::vector<fonts::Font*>& Scene::fonts(void) const
	{
		return m_fonts;
	}

	//latex
	uint32_t Scene::add_latex(const char* source)
	{
		m_latex.push_back(new textures::Latex(source));
		return (uint32_t) m_latex.size() - 1;
	}
	textures::Latex* Scene::latex(uint32_t index) const
	{
		return m_latex[index];
	}
	textures::Latex* Scene::latex(const char* label) const
	{
		for(textures::Latex* latex : m_latex)
		{
			if(strcmp(label, latex->label()) == 0) return latex;
		}
		return nullptr;
	}
	const std::vector<textures::Latex*>& Scene::latexes(void) const
	{
		return m_latex;
	}

	//images
	void Scene::add_image(const char* path)
	{
		m_images.push_back(new textures::Image(path));
	}
	textures::Image* Scene::image(uint32_t index) const
	{
		return m_images[index];
	}
	textures::Image* Scene::image(const char* label) const
	{
		for(textures::Image* image : m_images)
		{
			if(strcmp(label, image->label()) == 0) return image;
		}
		return nullptr;
	}
	const std::vector<textures::Image*>& Scene::images(void) const
	{
		return m_images;
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
		//data
		const float* c = m_background.channels();
		//clear
		glClearColor(c[0], c[1], c[2], c[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//draw
		for(const objects::Object* object : m_objects)
		{
			object->draw();
		}
	}
	void Scene::update(bool setup)
	{
		//setup
		if(setup)
		{
			setup_fonts();
			setup_latex();
			setup_images();
			setup_objects();
		}
		//update
		#pragma omp parallel for
		for(int32_t i = 0; i < (int32_t) m_objects.size(); i++)
		{
			m_objects[i]->setup();
			m_objects[i]->apply_model_matrix();
		}
		//buffers
		for(const buffers::VBO* vbo : m_vbos) vbo->transfer();
		for(const buffers::IBO* ibo : m_ibos) ibo->transfer();
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
	void Scene::setup_ubos(void)
	{
		m_ubos[0] = new buffers::UBO("Camera");
		m_ubos[0]->bind_base(GL_UNIFORM_BUFFER, 0);
		m_ubos[0]->transfer(32 * sizeof(float), nullptr);
	}
	void Scene::setup_fonts(void)
	{
		//data
		bool update = false;
		uint32_t w = 0, h = 0;
		//fonts
		for(fonts::Font* font : m_fonts)
		{
			if((update = update || !font->m_status))
			{
				font->setup(w, h);
			}
		}
		if(!update) return;
		//texture
		fonts::Font::m_width = w;
		fonts::Font::m_height = h;
		m_textures[1]->width(w);
		m_textures[1]->height(h);
		m_textures[1]->format(GL_RED);
		//texture data
		m_textures[1]->allocate();
		for(fonts::Font* font : m_fonts)
		{
			font->setup_texture();
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	void Scene::setup_latex(void)
	{
		//data
		bool update = false;
		uint32_t w = 0, h = 0;
		//images
		for(textures::Latex* latex : m_latex)
		{
			if((update = update || !latex->m_status))
			{
				latex->load();
				latex->m_offset = w;
				w += latex->m_width;
				h = std::max(h, latex->m_height);
			}
		}
		//texture
		if(!update) return;
		m_textures[2]->width(w);
		m_textures[2]->height(h);
		m_textures[2]->format(GL_RED);
		textures::Latex::m_total_width = w;
		textures::Latex::m_total_height = h;
		//texture data
		m_textures[2]->allocate();
		for(textures::Latex* latex : m_latex)
		{
			const uint32_t w = latex->m_width;
			const uint32_t h = latex->m_height;
			const uint32_t x = latex->m_offset;
			const uint8_t* data = latex->m_data;
			m_textures[2]->transfer(x, 0, w, h, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	void Scene::setup_OpenGL(void)
	{
		//enable
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_POLYGON_OFFSET_FILL);
		//values
		glPointSize(7);
		glPolygonOffset(1.0f, 1.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	void Scene::setup_images(void)
	{
		//data
		bool update = false;
		uint32_t w = 0, h = 0;
		//images
		for(textures::Image* image : m_images)
		{
			if((update = update || !image->m_status))
			{
				image->load();
				image->m_offset = w;
				w += image->m_width;
				h = std::max(h, image->m_height);
			}
		}
		//texture
		if(!update) return;
		m_textures[0]->width(w);
		m_textures[0]->height(h);
		m_textures[0]->format(GL_RGBA);
		textures::Image::m_total_width = w;
		textures::Image::m_total_height = h;
		//texture data
		m_textures[0]->allocate();
		for(textures::Image* image : m_images)
		{
			const uint32_t w = image->m_width;
			const uint32_t h = image->m_height;
			const uint32_t x = image->m_offset;
			const uint8_t* data = image->m_data;
			m_textures[0]->transfer(x, 0, w, h, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	void Scene::setup_cameras(void)
	{
		m_camera.m_scene = this;
	}
	void Scene::setup_objects(void)
	{
		for(buffers::VBO* vbo : m_vbos) vbo->m_vertex_count = 0;
		for(buffers::IBO* ibo : m_ibos) ibo->m_vertex_count = 0;
		for(objects::Object* object : m_objects) object->setup();
		for(buffers::VBO* vbo : m_vbos) vbo->allocate();
		for(buffers::IBO* ibo : m_ibos) ibo->allocate();
	}
	void Scene::setup_freetype(void)
	{
		if(FT_Init_FreeType(&m_ft_library))
		{
			throw std::runtime_error("FreeType initialization failed!");
		}
	}
}
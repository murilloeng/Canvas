//std
#include <omp.h>
#include <cmath>
#include <cfloat>
#include <stdexcept>

//ext
#include "external/cpp/inc/GL/glew.h"

//canvas
#include "Canvas/Canvas/inc/Fonts/Font.hpp"

#include "Canvas/Canvas/inc/Scene/Scene.hpp"

#include "Canvas/Canvas/inc/Textures/Image.hpp"
#include "Canvas/Canvas/inc/Textures/Latex.hpp"

#include "Canvas/Canvas/inc/Shaders/Stage.hpp"
#include "Canvas/Canvas/inc/Shaders/Shader.hpp"

#include "Canvas/Canvas/inc/Objects/Object.hpp"

#include "Canvas/Canvas/inc/Vertices/Text2D.hpp"
#include "Canvas/Canvas/inc/Vertices/Text3D.hpp"
#include "Canvas/Canvas/inc/Vertices/Model2D.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/Canvas/inc/Vertices/Image2D.hpp"
#include "Canvas/Canvas/inc/Vertices/Image3D.hpp"

namespace canvas
{
	//constructors
	Scene::Scene(std::string shaders_dir) : 
		m_background(0, 0, 0, 1), m_vaos(12), m_vbos(6), m_ibos(12), m_ubos(1), m_shaders(9), 
		m_commands(12), m_textures(3), m_lights(this), m_camera(this),m_shaders_dir(shaders_dir)
	{
		setup_vbos();
		setup_ibos();
		setup_ubos();
		setup_vaos();
		setup_OpenGL();
		setup_shaders();
		setup_cameras();
		setup_freetype();
		setup_commands();
		setup_textures();
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
		for(const commands::Command* command : m_commands) delete command;
		for(const textures::Texture* texture : m_textures) delete texture;
		//freetype
		FT_Done_FreeType(m_ft_library);
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

	//vbos
	void Scene::add_vbo(buffers::VBO* vbo)
	{
		return m_vbos.push_back(vbo);
	}
	buffers::VBO* Scene::vbo(uint32_t index) const
	{
		return m_vbos[index];
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

	//shaders
	void Scene::add_shader(shaders::Shader* shader)
	{
		m_shaders.push_back(shader);
	}
	shaders::Shader* Scene::shader(uint32_t index) const
	{
		return m_shaders[index];
	}

	//commands
	void Scene::add_command(commands::Command* command)
	{
		return m_commands.push_back(command);
	}
	commands::Command* Scene::command(uint32_t index) const
	{
		return m_commands[index];
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

	//fonts
	void Scene::add_font(const char* name)
	{
		m_fonts.push_back(new fonts::Font(this, name));
	}
	fonts::Font* Scene::font(uint32_t index) const
	{
		return m_fonts[index];
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

	//images
	void Scene::add_image(const char* path)
	{
		m_images.push_back(new textures::Image(path));
	}
	textures::Image* Scene::image(uint32_t index) const
	{
		return m_images[index];
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

	//draw
	void Scene::draw(void)
	{
		//data
		const float* c = m_background.channels();
		//clear
		glClearColor(c[0], c[1], c[2], c[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//draw
		for(const commands::Command* command : m_commands)
		{
			command->draw(this);
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
		//buffers
		buffers_data();
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

	//setup
	void Scene::setup_vaos(void)
	{
		//create
		for(buffers::VAO*& vao : m_vaos)
		{
			vao = new buffers::VAO;
		}
		//setup
		setup_vao_text_2D();
		setup_vao_text_3D();
		setup_vao_latex_2D();
		setup_vao_latex_3D();
		setup_vao_image_2D();
		setup_vao_image_3D();
		setup_vao_model_2D_lines();
		setup_vao_model_3D_lines();
		setup_vao_model_2D_points();
		setup_vao_model_3D_points();
		setup_vao_model_2D_triangles();
		setup_vao_model_3D_triangles();
	}
	void Scene::setup_vbos(void)
	{
		const uint32_t vertex_sizes[] = {
			sizeof(vertices::Model3D), sizeof(vertices::Image3D), sizeof(vertices::Text3D), 
			sizeof(vertices::Model2D), sizeof(vertices::Image2D), sizeof(vertices::Text2D)
		};
		for(uint32_t i = 0; i < m_vbos.size(); i++)
		{
			m_vbos[i] = new buffers::VBO;
			m_vbos[i]->vertex_size(vertex_sizes[i]);
		}
	}
	void Scene::setup_ibos(void)
	{
		for(buffers::IBO*& ibo : m_ibos) ibo = new buffers::IBO;
	}
	void Scene::setup_ubos(void)
	{
		m_ubos[0] = new buffers::Buffer;
		m_ubos[0]->bind_base(GL_UNIFORM_BUFFER, 0);
		m_ubos[0]->transfer(32 * sizeof(float), nullptr);
	}
	void Scene::setup_data(void)
	{
		//data
		const size_t nv = m_vbos.size();
		const size_t ni = m_ibos.size();
		//objects
		for(objects::Object* object : m_objects)
		{
			object->m_vbo_size.resize(nv);
			object->m_ibo_size.resize(ni);
			object->m_vbo_index.resize(nv);
			object->m_ibo_index.resize(ni);
		}
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
	void Scene::setup_shaders(void)
	{
		setup_shader_light();
		setup_shader_text_2D();
		setup_shader_text_3D();
		setup_shader_model_2D();
		setup_shader_model_3D();
		setup_shader_image_2D();
		setup_shader_image_3D();
		setup_shader_latex_2D();
		setup_shader_latex_3D();
	}
	void Scene::setup_freetype(void)
	{
		if(FT_Init_FreeType(&m_ft_library))
		{
			throw std::runtime_error("FreeType initialization failed!");
		}
	}
	void Scene::setup_commands(void)
	{
		//create
		for(commands::Command*& command : m_commands) command = new commands::Command;
		//setup
		m_commands[ 1]->setup(GL_LINES, 1, 0);
		m_commands[ 7]->setup(GL_LINES, 7, 5);
		m_commands[ 0]->setup(GL_POINTS, 0, 0);
		m_commands[ 6]->setup(GL_POINTS, 6, 5);
		m_commands[ 2]->setup(GL_TRIANGLES,  2, 1);
		m_commands[ 3]->setup(GL_TRIANGLES,  3, 2);
		m_commands[ 4]->setup(GL_TRIANGLES,  4, 3);
		m_commands[ 5]->setup(GL_TRIANGLES,  5, 4);
		m_commands[ 8]->setup(GL_TRIANGLES,  8, 5);
		m_commands[ 9]->setup(GL_TRIANGLES,  9, 6);
		m_commands[10]->setup(GL_TRIANGLES, 10, 7);
		m_commands[11]->setup(GL_TRIANGLES, 11, 8);
	}
	void Scene::setup_textures(void)
	{
		const GLuint texture_units[] = {0, 1, 2};
		for(uint32_t i = 0; i < m_textures.size(); i++)
		{
			m_textures[i] = new textures::Texture;
			m_textures[i]->bind_unit(texture_units[i]);
		}
	}

	//setup vaos
	void Scene::setup_vao_text_2D(void)
	{
		m_vaos[10]->attribute_enable(0);
		m_vaos[10]->attribute_enable(1);
		m_vaos[10]->attribute_enable(2);
		m_vaos[10]->attribute_binding(0, 0);
		m_vaos[10]->attribute_binding(1, 0);
		m_vaos[10]->attribute_binding(2, 0);
		m_vaos[10]->element_buffer(m_ibos[10]->m_id);
		m_vaos[10]->attribute_format(0, 2, GL_FLOAT, 0 * sizeof(float));
		m_vaos[10]->attribute_format(1, 4, GL_FLOAT, 2 * sizeof(float));
		m_vaos[10]->attribute_format(2, 2, GL_FLOAT, 6 * sizeof(float));
		m_vaos[10]->vertex_buffer(0, m_vbos[5]->m_id, 0, 8 * sizeof(float));
	}
	void Scene::setup_vao_text_3D(void)
	{
		m_vaos[4]->attribute_enable(0);
		m_vaos[4]->attribute_enable(1);
		m_vaos[4]->attribute_enable(2);
		m_vaos[4]->attribute_binding(0, 0);
		m_vaos[4]->attribute_binding(1, 0);
		m_vaos[4]->attribute_binding(2, 0);
		m_vaos[4]->element_buffer(m_ibos[4]->m_id);
		m_vaos[4]->attribute_format(0, 3, GL_FLOAT, 0 * sizeof(float));
		m_vaos[4]->attribute_format(1, 4, GL_FLOAT, 3 * sizeof(float));
		m_vaos[4]->attribute_format(2, 2, GL_FLOAT, 7 * sizeof(float));
		m_vaos[4]->vertex_buffer(0, m_vbos[2]->m_id, 0, 9 * sizeof(float));
	}
	void Scene::setup_vao_latex_2D(void)
	{
		m_vaos[11]->attribute_enable(0);
		m_vaos[11]->attribute_enable(1);
		m_vaos[11]->attribute_enable(2);
		m_vaos[11]->attribute_binding(0, 0);
		m_vaos[11]->attribute_binding(1, 0);
		m_vaos[11]->attribute_binding(2, 0);
		m_vaos[11]->element_buffer(m_ibos[11]->m_id);
		m_vaos[11]->attribute_format(0, 2, GL_FLOAT, 0 * sizeof(float));
		m_vaos[11]->attribute_format(1, 4, GL_FLOAT, 2 * sizeof(float));
		m_vaos[11]->attribute_format(2, 2, GL_FLOAT, 6 * sizeof(float));
		m_vaos[11]->vertex_buffer(0, m_vbos[5]->m_id, 0, 8 * sizeof(float));
	}
	void Scene::setup_vao_latex_3D(void)
	{
		m_vaos[5]->attribute_enable(0);
		m_vaos[5]->attribute_enable(1);
		m_vaos[5]->attribute_enable(2);
		m_vaos[5]->attribute_binding(0, 0);
		m_vaos[5]->attribute_binding(1, 0);
		m_vaos[5]->attribute_binding(2, 0);
		m_vaos[5]->element_buffer(m_ibos[5]->m_id);
		m_vaos[5]->attribute_format(0, 3, GL_FLOAT, 0 * sizeof(float));
		m_vaos[5]->attribute_format(1, 4, GL_FLOAT, 3 * sizeof(float));
		m_vaos[5]->attribute_format(2, 2, GL_FLOAT, 7 * sizeof(float));
		m_vaos[5]->vertex_buffer(0, m_vbos[2]->m_id, 0, 9 * sizeof(float));
	}
	void Scene::setup_vao_image_2D(void)
	{
		m_vaos[9]->attribute_enable(0);
		m_vaos[9]->attribute_enable(1);
		m_vaos[9]->attribute_binding(0, 0);
		m_vaos[9]->attribute_binding(1, 0);
		m_vaos[9]->element_buffer(m_ibos[9]->m_id);
		m_vaos[9]->attribute_format(0, 2, GL_FLOAT, 0 * sizeof(float));
		m_vaos[9]->attribute_format(1, 2, GL_FLOAT, 2 * sizeof(float));
		m_vaos[9]->vertex_buffer(0, m_vbos[4]->m_id, 0, 4 * sizeof(float));
	}
	void Scene::setup_vao_image_3D(void)
	{
		m_vaos[3]->attribute_enable(0);
		m_vaos[3]->attribute_enable(1);
		m_vaos[3]->attribute_binding(0, 0);
		m_vaos[3]->attribute_binding(1, 0);
		m_vaos[3]->element_buffer(m_ibos[3]->m_id);
		m_vaos[3]->attribute_format(0, 3, GL_FLOAT, 0 * sizeof(float));
		m_vaos[3]->attribute_format(1, 2, GL_FLOAT, 3 * sizeof(float));
		m_vaos[3]->vertex_buffer(0, m_vbos[1]->m_id, 0, 5 * sizeof(float));
	}
	void Scene::setup_vao_model_2D_lines(void)
	{
		m_vaos[7]->attribute_enable(0);
		m_vaos[7]->attribute_enable(1);
		m_vaos[7]->attribute_binding(0, 0);
		m_vaos[7]->attribute_binding(1, 0);
		m_vaos[7]->element_buffer(m_ibos[7]->m_id);
		m_vaos[7]->attribute_format(0, 2, GL_FLOAT, 0 * sizeof(float));
		m_vaos[7]->attribute_format(1, 4, GL_FLOAT, 2 * sizeof(float));
		m_vaos[7]->vertex_buffer(0, m_vbos[3]->m_id, 0, 6 * sizeof(float));
	}
	void Scene::setup_vao_model_3D_lines(void)
	{
		m_vaos[1]->attribute_enable(0);
		m_vaos[1]->attribute_enable(1);
		m_vaos[1]->attribute_binding(0, 0);
		m_vaos[1]->attribute_binding(1, 0);
		m_vaos[1]->element_buffer(m_ibos[1]->m_id);
		m_vaos[1]->attribute_format(0, 3, GL_FLOAT, 0 * sizeof(float));
		m_vaos[1]->attribute_format(1, 4, GL_FLOAT, 3 * sizeof(float));
		m_vaos[1]->vertex_buffer(0, m_vbos[0]->m_id, 0, 7 * sizeof(float));
	}
	void Scene::setup_vao_model_2D_points(void)
	{
		m_vaos[6]->attribute_enable(0);
		m_vaos[6]->attribute_enable(1);
		m_vaos[6]->attribute_binding(0, 0);
		m_vaos[6]->attribute_binding(1, 0);
		m_vaos[6]->element_buffer(m_ibos[6]->m_id);
		m_vaos[6]->attribute_format(0, 2, GL_FLOAT, 0 * sizeof(float));
		m_vaos[6]->attribute_format(1, 4, GL_FLOAT, 2 * sizeof(float));
		m_vaos[6]->vertex_buffer(0, m_vbos[3]->m_id, 0, 6 * sizeof(float));
	}
	void Scene::setup_vao_model_3D_points(void)
	{
		m_vaos[0]->attribute_enable(0);
		m_vaos[0]->attribute_enable(1);
		m_vaos[0]->attribute_binding(0, 0);
		m_vaos[0]->attribute_binding(1, 0);
		m_vaos[0]->element_buffer(m_ibos[0]->m_id);
		m_vaos[0]->attribute_format(0, 3, GL_FLOAT, 0 * sizeof(float));
		m_vaos[0]->attribute_format(1, 4, GL_FLOAT, 3 * sizeof(float));
		m_vaos[0]->vertex_buffer(0, m_vbos[0]->m_id, 0, 7 * sizeof(float));
	}
	void Scene::setup_vao_model_2D_triangles(void)
	{
		m_vaos[8]->attribute_enable(0);
		m_vaos[8]->attribute_enable(1);
		m_vaos[8]->attribute_binding(0, 0);
		m_vaos[8]->attribute_binding(1, 0);
		m_vaos[8]->element_buffer(m_ibos[8]->m_id);
		m_vaos[8]->attribute_format(0, 2, GL_FLOAT, 0 * sizeof(float));
		m_vaos[8]->attribute_format(1, 4, GL_FLOAT, 2 * sizeof(float));
		m_vaos[8]->vertex_buffer(0, m_vbos[3]->m_id, 0, 6 * sizeof(float));
	}
	void Scene::setup_vao_model_3D_triangles(void)
	{
		m_vaos[2]->attribute_enable(0);
		m_vaos[2]->attribute_enable(1);
		m_vaos[2]->attribute_binding(0, 0);
		m_vaos[2]->attribute_binding(1, 0);
		m_vaos[2]->element_buffer(m_ibos[2]->m_id);
		m_vaos[2]->attribute_format(0, 3, GL_FLOAT, 0 * sizeof(float));
		m_vaos[2]->attribute_format(1, 4, GL_FLOAT, 3 * sizeof(float));
		m_vaos[2]->vertex_buffer(0, m_vbos[0]->m_id, 0, 7 * sizeof(float));
	}

	//setup shaders
	void Scene::setup_shader_light(void)
	{
		m_shaders[1] = (new shaders::Shader({
			new shaders::Stage(GL_VERTEX_SHADER, m_shaders_dir + "light.vert"),
			new shaders::Stage(GL_GEOMETRY_SHADER, m_shaders_dir + "light.geom"),
			new shaders::Stage(GL_FRAGMENT_SHADER, m_shaders_dir + "light.frag")
		}));
	}
	void Scene::setup_shader_text_2D(void)
	{
		m_shaders[7] = (new shaders::Shader({
			new shaders::Stage(GL_VERTEX_SHADER, m_shaders_dir + "text2D.vert"),
			new shaders::Stage(GL_FRAGMENT_SHADER, m_shaders_dir + "text2D.frag")
		}));
	}
	void Scene::setup_shader_text_3D(void)
	{
		m_shaders[3] = (new shaders::Shader({
			new shaders::Stage(GL_VERTEX_SHADER, m_shaders_dir + "text3D.vert"),
			new shaders::Stage(GL_FRAGMENT_SHADER, m_shaders_dir + "text3D.frag")
		}));
	}
	void Scene::setup_shader_model_2D(void)
	{
		m_shaders[5] = (new shaders::Shader({
			new shaders::Stage(GL_VERTEX_SHADER, m_shaders_dir + "model2D.vert"),
			new shaders::Stage(GL_FRAGMENT_SHADER, m_shaders_dir + "model2D.frag")
		}));
	}
	void Scene::setup_shader_model_3D(void)
	{
		m_shaders[0] = (new shaders::Shader({
			new shaders::Stage(GL_VERTEX_SHADER, m_shaders_dir + "model3D.vert"),
			new shaders::Stage(GL_FRAGMENT_SHADER, m_shaders_dir + "model3D.frag")
		}));
	}
	void Scene::setup_shader_image_2D(void)
	{
		m_shaders[6] = (new shaders::Shader({
			new shaders::Stage(GL_VERTEX_SHADER, m_shaders_dir + "image2D.vert"),
			new shaders::Stage(GL_FRAGMENT_SHADER, m_shaders_dir + "image2D.frag")
		}));
	}
	void Scene::setup_shader_image_3D(void)
	{
		m_shaders[2] = (new shaders::Shader({
			new shaders::Stage(GL_VERTEX_SHADER, m_shaders_dir + "image3D.vert"),
			new shaders::Stage(GL_FRAGMENT_SHADER, m_shaders_dir + "image3D.frag")
		}));
	}
	void Scene::setup_shader_latex_2D(void)
	{
		m_shaders[8] = (new shaders::Shader({
			new shaders::Stage(GL_VERTEX_SHADER, m_shaders_dir + "latex2D.vert"),
			new shaders::Stage(GL_FRAGMENT_SHADER, m_shaders_dir + "latex2D.frag")
		}));
	}
	void Scene::setup_shader_latex_3D(void)
	{
		m_shaders[4] = (new shaders::Shader({
			new shaders::Stage(GL_VERTEX_SHADER, m_shaders_dir + "latex3D.vert"),
			new shaders::Stage(GL_FRAGMENT_SHADER, m_shaders_dir + "latex3D.frag")
		}));
	}

	//buffers
	void Scene::buffers_data(void)
	{
		#pragma omp parallel for
		for(int32_t i = 0; i < (int32_t) m_objects.size(); i++)
		{
			m_objects[i]->buffers_data();
			m_objects[i]->apply_model_matrix();
		}
	}
}
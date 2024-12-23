//std
#include <omp.h>
#include <cmath>
#include <cfloat>

//ext
#include "external/cpp/inc/GL/glew.h"

//canvas
#include "Canvas/Canvas/inc/GPU/Shader.hpp"

#include "Canvas/Canvas/inc/Scene/Font.hpp"
#include "Canvas/Canvas/inc/Scene/Image.hpp"
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Scene/Latex.hpp"

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
		m_camera(this), m_lights(this), 
		m_vbos(6), m_ibos(12), m_textures(3), m_programs(7), 
		m_background(0, 0, 0, 1), m_shaders_dir(shaders_dir)
	{
		setup_gl();
		setup_buffers();
		setup_shaders();
		setup_freetype();
		setup_commands();
		m_camera.m_scene = this;
	}

	//destructor
	Scene::~Scene(void)
	{
		//delete
		for(const Font* font : m_fonts) delete font;
		for(const Latex* latex : m_latex) delete latex;
		for(const Image* image : m_images) delete image;
		for(uint32_t i = 0; i <  6; i++) delete m_vbos[i];
		for(uint32_t i = 0; i < 12; i++) delete m_ibos[i];
		for(uint32_t i = 0; i <  7; i++) delete m_programs[i];
		for(const objects::Object* object : m_objects) delete object;
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

	camera::Camera& Scene::camera(void)
	{
		return m_camera;
	}
	const camera::Camera& Scene::camera(void) const
	{
		return m_camera;
	}

	std::vector<Command>& Scene::commands(void)
	{
		return m_commands;
	}
	const std::vector<Command>& Scene::commands(void) const
	{
		return m_commands;
	}

	void Scene::clear_fonts(void)
	{
		for(const Font* font : m_fonts) delete font;
		m_fonts.clear();
	}
	Font* Scene::font(uint32_t index) const
	{
		return m_fonts[index];
	}
	void Scene::add_font(const char* name)
	{
		m_fonts.push_back(new Font(this, name));
	}
	const std::vector<Font*>& Scene::fonts(void) const
	{
		return m_fonts;
	}

	void Scene::clear_images(void)
	{
		for(const Image* image : m_images) delete image;
		m_images.clear();
	}
	void Scene::add_image(const char* path)
	{
		m_images.push_back(new Image(path));
	}
	Image* Scene::image(uint32_t index) const
	{
		return m_images[index];
	}
	const std::vector<Image*>& Scene::images(void) const
	{
		return m_images;
	}

	void Scene::clear_latex(void)
	{
		for(const Latex* latex : m_latex) delete latex;
		m_latex.clear();
	}
	Latex* Scene::latex(uint32_t index) const
	{
		return m_latex[index];
	}
	uint32_t Scene::add_latex(const char* source)
	{
		m_latex.push_back(new Latex(source));
		return (uint32_t) m_latex.size() - 1;
	}
	const std::vector<Latex*>& Scene::latex(void) const
	{
		return m_latex;
	}

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

	//buffers
	VBO* Scene::vbo(uint32_t index)
	{
		return m_vbos[index];
	}
	IBO* Scene::ibo(uint32_t index)
	{
		return m_ibos[index];
	}
	void Scene::add_vbo(VBO* vbo)
	{
		for(objects::Object* object : m_objects)
		{
			object->m_vbo_size.push_back(0);
			object->m_vbo_index.push_back(0);
		}
		return m_vbos.push_back(vbo);
	}
	void Scene::add_ibo(IBO* ibo)
	{
		for(objects::Object* object : m_objects)
		{
			object->m_ibo_size.push_back(0);
			object->m_ibo_index.push_back(0);
		}
		return m_ibos.push_back(ibo);
	}
	std::vector<VBO*>& Scene::vbos(void)
	{
		return m_vbos;
	}
	std::vector<IBO*>& Scene::ibos(void)
	{
		return m_ibos;
	}
	const VBO* Scene::vbo(uint32_t index) const
	{
		return m_vbos[index];
	}
	const IBO* Scene::ibo(uint32_t index) const
	{
		return m_ibos[index];
	}
	const std::vector<VBO*>& Scene::vbos(void) const
	{
		return m_vbos;
	}
	const std::vector<IBO*>& Scene::ibos(void) const
	{
		return m_ibos;
	}
	vertices::Text2D* Scene::vbo_data_text_2D(void) const
	{
		return (vertices::Text2D*) m_vbos[5]->data();
	}
	vertices::Text3D* Scene::vbo_data_text_3D(void) const
	{
		return (vertices::Text3D*) m_vbos[2]->data();
	}
	vertices::Model2D* Scene::vbo_data_model_2D(void) const
	{
		return (vertices::Model2D*) m_vbos[3]->data();
	}
	vertices::Model3D* Scene::vbo_data_model_3D(void) const
	{
		return (vertices::Model3D*) m_vbos[0]->data();
	}
	vertices::Image2D* Scene::vbo_data_image_2D(void) const
	{
		return (vertices::Image2D*) m_vbos[4]->data();
	}
	vertices::Image3D* Scene::vbo_data_image_3D(void) const
	{
		return (vertices::Image3D*) m_vbos[1]->data();
	}

	//programs
	Texture& Scene::texture(uint32_t index)
	{
		return m_textures[index];
	}
	std::vector<Texture>& Scene::textures(void)
	{
		return m_textures;
	}
	const Texture& Scene::texture(uint32_t index) const
	{
		return m_textures[index];
	}
	const std::vector<Texture>& Scene::textures(void) const
	{
		return m_textures;
	}

	//programs
	Program* Scene::program(uint32_t index)
	{
		return m_programs[index];
	}
	std::vector<Program*>& Scene::programs(void)
	{
		return m_programs;
	}
	const Program* Scene::program(uint32_t index) const
	{
		return m_programs[index];
	}
	const std::vector<Program*>& Scene::programs(void) const
	{
		return m_programs;
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
		for(const Command& command : m_commands)
		{
			//data
			VBO* vbo = m_vbos[command.m_vbo_index];
			IBO* ibo = m_ibos[command.m_ibo_index];
			Program* program = m_programs[command.m_program_index];
			Texture& texture = m_textures[command.has_texture() ? command.m_texture_index : 0];
			//draw
			if(ibo->m_size)
			{
				vbo->bind();
				ibo->bind();
				program->bind();
				if(command.has_texture()) texture.bind();
				glDrawElements(command.m_draw_mode, ibo->m_size, GL_UNSIGNED_INT, nullptr);
			}
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
		for(const VBO* vbo : m_vbos) vbo->transfer();
		for(const IBO* ibo : m_ibos) ibo->transfer();
	}
	void Scene::update_on_motion(void)
	{
		for(objects::Object* object : m_objects)
		{
			object->update_on_motion();
		}
		for(const VBO* vbo : m_vbos) vbo->transfer();
	}

	//setup
	void Scene::setup_gl(void)
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
	void Scene::setup_data(void)
	{
		//data
		const uint32_t nv = (uint32_t) m_vbos.size();
		const uint32_t ni = (uint32_t) m_ibos.size();
		//vbos
		for(uint32_t i = 6; i < nv; i++)
		{
			for(objects::Object* object : m_objects)
			{
				object->m_vbo_size.push_back(0);
				object->m_vbo_index.push_back(0);
			}
		}
		//ibos
		for(uint32_t i = 12; i < ni; i++)
		{
			for(objects::Object* object : m_objects)
			{
				object->m_ibo_size.push_back(0);
				object->m_ibo_index.push_back(0);
			}
		}
	}
	void Scene::setup_fonts(void)
	{
		//data
		bool update = false;
		uint32_t w = 0, h = 0;
		//fonts
		for(Font* font : m_fonts)
		{
			if((update = update || !font->m_status))
			{
				font->setup(w, h);
			}
		}
		if(!update) return;
		//texture
		Font::m_width = w;
		Font::m_height = h;
		m_textures[1].width(w);
		m_textures[1].height(h);
		m_textures[1].format(GL_RED);
		//texture data
		m_textures[1].allocate();
		for(Font* font : m_fonts)
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
		for(Latex* latex : m_latex)
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
		m_textures[2].width(w);
		m_textures[2].height(h);
		Latex::m_total_width = w;
		Latex::m_total_height = h;
		m_textures[2].format(GL_RED);
		//texture data
		m_textures[2].allocate();
		for(Latex* latex : m_latex)
		{
			const uint32_t w = latex->m_width;
			const uint32_t h = latex->m_height;
			const uint32_t x = latex->m_offset;
			const uint8_t* data = latex->m_data;
			m_textures[2].transfer(x, 0, w, h, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	void Scene::setup_images(void)
	{
		//data
		bool update = false;
		uint32_t w = 0, h = 0;
		//images
		for(Image* image : m_images)
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
		m_textures[0].width(w);
		m_textures[0].height(h);
		Image::m_total_width = w;
		Image::m_total_height = h;
		m_textures[0].format(GL_RGBA);
		//texture data
		m_textures[0].allocate();
		for(Image* image : m_images)
		{
			const uint32_t w = image->m_width;
			const uint32_t h = image->m_height;
			const uint32_t x = image->m_offset;
			const uint8_t* data = image->m_data;
			m_textures[0].transfer(x, 0, w, h, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	void Scene::setup_objects(void)
	{
		for(VBO* vbo : m_vbos) vbo->m_size = 0;
		for(IBO* ibo : m_ibos) ibo->m_size = 0;
		for(objects::Object* object : m_objects) object->setup();
		for(VBO* vbo : m_vbos) vbo->allocate();
		for(IBO* ibo : m_ibos) ibo->allocate();
	}
	void Scene::setup_buffers(void)
	{
		//setup
		for(VBO*& vbo : m_vbos) vbo = new VBO;
		for(IBO*& ibo : m_ibos) ibo = new IBO;
		//attributes
		vertices::Text3D::attributes(m_vbos[2]->m_attributes);
		vertices::Text2D::attributes(m_vbos[5]->m_attributes);
		vertices::Model3D::attributes(m_vbos[0]->m_attributes);
		vertices::Image3D::attributes(m_vbos[1]->m_attributes);
		vertices::Model2D::attributes(m_vbos[3]->m_attributes);
		vertices::Image2D::attributes(m_vbos[4]->m_attributes);
		//enable
		for(VBO* vbo : m_vbos) vbo->enable();
	}
	void Scene::setup_shaders(void)
	{
		//data
		for(Program*& program : m_programs) program = new Program;
		//path
		m_programs[1]->vertex_shader()->path(m_shaders_dir + "light.vert");
		m_programs[6]->vertex_shader()->path(m_shaders_dir + "text2D.vert");
		m_programs[3]->vertex_shader()->path(m_shaders_dir + "text3D.vert");
		m_programs[4]->vertex_shader()->path(m_shaders_dir + "model2D.vert");
		m_programs[0]->vertex_shader()->path(m_shaders_dir + "model3D.vert");
		m_programs[5]->vertex_shader()->path(m_shaders_dir + "image2D.vert");
		m_programs[2]->vertex_shader()->path(m_shaders_dir + "image3D.vert");
		m_programs[1]->geometry_shader()->path(m_shaders_dir + "light.geom");
		m_programs[1]->fragment_shader()->path(m_shaders_dir + "light.frag");
		m_programs[6]->fragment_shader()->path(m_shaders_dir + "text2D.frag");
		m_programs[3]->fragment_shader()->path(m_shaders_dir + "text3D.frag");
		m_programs[4]->fragment_shader()->path(m_shaders_dir + "model2D.frag");
		m_programs[0]->fragment_shader()->path(m_shaders_dir + "model3D.frag");
		m_programs[5]->fragment_shader()->path(m_shaders_dir + "image2D.frag");
		m_programs[2]->fragment_shader()->path(m_shaders_dir + "image3D.frag");
		//setup
		for(Program* program : m_programs) program->setup();
	}
	void Scene::setup_freetype(void)
	{
		if(FT_Init_FreeType(&m_ft_library))
		{
			fprintf(stderr, "Error: Unable to init FreeType Library!\n");
			exit(EXIT_FAILURE);
		}
	}
	void Scene::setup_commands(void)
	{
		//model 3D
		m_commands.push_back(Command(GL_POINTS, 0, 0, UINT32_MAX, 0));
		m_commands.push_back(Command(GL_LINES, 0, 1, UINT32_MAX, 0));
		m_commands.push_back(Command(GL_TRIANGLES, 0, 2, UINT32_MAX, 1));
		//image 3D
		m_commands.push_back(Command(GL_TRIANGLES, 1, 3, 0, 2));
		//text 3D
		m_commands.push_back(Command(GL_TRIANGLES, 2, 4, 1, 3));
		//latex 3D
		m_commands.push_back(Command(GL_TRIANGLES, 2, 5, 2, 3));
		//model 2D
		m_commands.push_back(Command(GL_POINTS, 3, 6, UINT32_MAX, 4));
		m_commands.push_back(Command(GL_LINES, 3, 7, UINT32_MAX, 4));
		m_commands.push_back(Command(GL_TRIANGLES, 3, 8, UINT32_MAX, 4));
		//image 2D
		m_commands.push_back(Command(GL_TRIANGLES, 4, 9, 0, 5));
		//text 2D
		m_commands.push_back(Command(GL_TRIANGLES, 5, 10, 1, 6));
		//latex 2D
		m_commands.push_back(Command(GL_TRIANGLES, 5, 11, 2, 6));
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
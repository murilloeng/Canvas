//os
#ifdef _WIN32
#include <Windows.h>
#endif

//std
#include <cmath>
#include <cfloat>

//ext
#include "external/cpp/inc/GL/glew.h"

//canvas
#include "Canvas/inc/GPU/Shader.hpp"

#include "Canvas/inc/Scene/Font.hpp"
#include "Canvas/inc/Scene/Image.hpp"
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Scene/Latex.hpp"

#include "Canvas/inc/Objects/Object.hpp"

#include "Canvas/inc/Vertices/Text3D.hpp"
#include "Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/inc/Vertices/Image3D.hpp"

// vbo
// (0) model:	position (3) color (4)
// (1) image:	position (3) texture (2)
// (2) text:	position (3) color (4) texture (2)

// ibo
// (0) points, (1) lines, (2) triangles, (3) images, (4) text, (5) latex

// programs
// (0) model, (1) light, (2) images, (3) text

namespace canvas
{
	//constructors
	Scene::Scene(std::string shaders_dir) : 
		m_vbo_size{0, 0, 0}, 
		m_ibo_size{0, 0, 0, 0, 0, 0}, 
		m_ibo_data{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, 
		m_vbo_data{nullptr, nullptr, nullptr}, m_background(0, 0, 0, 0), m_shaders_dir(shaders_dir)
	{
		setup_gl();
		setup_buffers();
		setup_shaders();
		setup_textures();
		setup_freetype();
		m_camera.m_scene = this;
		objects::Object::m_scene = this;
		m_camera.m_programs = m_programs;
		m_light.m_program = &m_programs[1];
	}

	//destructor
	Scene::~Scene(void)
	{
		//delete
		for(const Font* font : m_fonts) delete font;
		for(const Latex* latex : m_latex) delete latex;
		for(const Image* image : m_images) delete image;
		for(unsigned i = 0; i < 3; i++) delete[] m_vbo_data[i];
		for(unsigned i = 0; i < 6; i++) delete[] m_ibo_data[i];
		for(const objects::Object* object : m_objects) delete object;
		//opengl
		glUseProgram(0);
		glDeleteBuffers(3, m_vbo_id);
		glDeleteBuffers(6, m_ibo_id);
		glDeleteTextures(3, m_texture_id);
		glDeleteVertexArrays(3, m_vao_id);
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

	Light& Scene::light(void)
	{
		return m_light;
	}
	const Light& Scene::light(void) const
	{
		return m_light;
	}

	camera::Camera& Scene::camera(void)
	{
		return m_camera;
	}
	const camera::Camera& Scene::camera(void) const
	{
		return m_camera;
	}

	void Scene::clear_fonts(void)
	{
		for(const Font* font : m_fonts) delete font;
		m_fonts.clear();
	}
	Font* Scene::font(unsigned index) const
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
	Image* Scene::image(unsigned index) const
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
	void Scene::add_latex(const char* source)
	{
		m_latex.push_back(new Latex(source));
	}
	Latex* Scene::latex(unsigned index) const
	{
		return m_latex[index];
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
		m_objects.push_back(object);
	}
	objects::Object* Scene::object(unsigned index) const
	{
		return m_objects[index];
	}
	const std::vector<objects::Object*>& Scene::objects(void) const
	{
		return m_objects;
	}

	//buffers
	unsigned Scene::vbo_size(unsigned index) const
	{
		return m_vbo_size[index];
	}
	unsigned Scene::ibo_size(unsigned index) const
	{
		return m_ibo_size[index];
	}
	vertices::Vertex* Scene::vertex(unsigned type, unsigned index) const
	{
		if(type == 2) return (vertices::Text3D*) m_vbo_data[2] + index;
		else if(type == 0) return (vertices::Model3D*) m_vbo_data[0] + index;
		else if(type == 1) return (vertices::Image3D*) m_vbo_data[1] + index;
		else return nullptr;
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
		draw_text();
		draw_model();
		draw_image();
		draw_equation();
	}
	void Scene::update(bool setup)
	{
		//setup
		if(setup)
		{
			setup_vbo();
			setup_ibo();
			setup_fonts();
			setup_latex();
			setup_images();
			setup_objects();
		}
		//buffers
		buffers_data();
		buffers_transfer();
	}

	//draw
	void Scene::draw_text(void)
	{
		//model
		m_programs[3].use();
		glBindVertexArray(m_vao_id[2]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[2]);
		glBindTexture(GL_TEXTURE_2D, m_texture_id[1]);
		//draw triangles
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[4]);
		glDrawElements(GL_TRIANGLES, 3 * m_ibo_size[4], GL_UNSIGNED_INT, nullptr);
	}
	void Scene::draw_model(void)
	{
		//model
		m_programs[0].use();
		glBindVertexArray(m_vao_id[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[0]);
		//draw points
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[0]);
		glDrawElements(GL_POINTS, m_ibo_size[0], GL_UNSIGNED_INT, nullptr);
		//draw lines
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[1]);
		glDrawElements(GL_LINES, 2 * m_ibo_size[1], GL_UNSIGNED_INT, nullptr);
		//draw triangles
		m_programs[1].use();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[2]);
		glDrawElements(GL_TRIANGLES, 3 * m_ibo_size[2], GL_UNSIGNED_INT, nullptr);
	}
	void Scene::draw_image(void)
	{
		//model
		m_programs[2].use();
		glBindVertexArray(m_vao_id[1]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[1]);
		glBindTexture(GL_TEXTURE_2D, m_texture_id[0]);
		//draw triangles
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[3]);
		glDrawElements(GL_TRIANGLES, 3 * m_ibo_size[3], GL_UNSIGNED_INT, nullptr);
	}
	void Scene::draw_equation(void)
	{
		//model
		m_programs[3].use();
		glBindVertexArray(m_vao_id[2]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[2]);
		glBindTexture(GL_TEXTURE_2D, m_texture_id[2]);
		//draw triangles
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[5]);
		glDrawElements(GL_TRIANGLES, 3 * m_ibo_size[5], GL_UNSIGNED_INT, nullptr);
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
	void Scene::setup_vbo(void)
	{
		for(unsigned i = 0; i < 3; i++)
		{
			m_vbo_size[i] = 0;
			for(const objects::Object* object : m_objects)
			{
				m_vbo_size[i] += object->vbo_size(i);
			}
			delete[] m_vbo_data[i];
			if(i == 2) m_vbo_data[i] = new vertices::Text3D[m_vbo_size[i]];
			if(i == 0) m_vbo_data[i] = new vertices::Model3D[m_vbo_size[i]];
			if(i == 1) m_vbo_data[i] = new vertices::Image3D[m_vbo_size[i]];
		}
	}
	void Scene::setup_ibo(void)
	{
		//data
		const unsigned is[] = {1, 2, 3, 3, 3, 3};
		//ibo data
		for(unsigned i = 0; i < 6; i++)
		{
			m_ibo_size[i] = 0;
			for(const objects::Object* object : m_objects)
			{
				m_ibo_size[i] += object->ibo_size(i);
			}
			delete[] m_ibo_data[i];
			m_ibo_data[i] = new unsigned[is[i] * m_ibo_size[i]];
		}
	}
	void Scene::setup_fonts(void)
	{
		//data
		bool update = false;
		unsigned w = 0, h = 0;
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
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glBindTexture(GL_TEXTURE_2D, m_texture_id[1]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);
		//texture data
		for(Font* font : m_fonts)
		{
			font->setup_texture();
		}
	}
	void Scene::setup_latex(void)
	{
		//data
		bool update = false;
		unsigned w = 0, h = 0;
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
		Latex::m_total_width = w;
		Latex::m_total_height = h;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glBindTexture(GL_TEXTURE_2D, m_texture_id[2]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);
		//texture data
		for(Latex* latex : m_latex)
		{
			const unsigned w = latex->m_width;
			const unsigned h = latex->m_height;
			const unsigned x = latex->m_offset;
			const unsigned char* data = latex->m_data;
			glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, w, h, GL_RED, GL_UNSIGNED_BYTE, data);
		}
	}
	void Scene::setup_images(void)
	{
		//data
		bool update = false;
		unsigned w = 0, h = 0;
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
		Image::m_total_width = w;
		Image::m_total_height = h;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glBindTexture(GL_TEXTURE_2D, m_texture_id[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		//texture data
		for(Image* image : m_images)
		{
			const unsigned w = image->m_width;
			const unsigned h = image->m_height;
			const unsigned x = image->m_offset;
			const unsigned char* data = image->m_data;
			glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
	}
	void Scene::setup_objects(void)
	{
		//data
		unsigned vbo_counter[] = {0, 0, 0};
		unsigned ibo_counter[] = {0, 0, 0, 0, 0, 0};
		//objects
		for(objects::Object* object : m_objects)
		{
			object->setup(vbo_counter, ibo_counter);
		}
	}
	void Scene::setup_buffers(void)
	{
		//generate
		glGenBuffers(3, m_vbo_id);
		glGenBuffers(6, m_ibo_id);
		glGenVertexArrays(3, m_vao_id);
		//vao model
		glBindVertexArray(m_vao_id[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[0]);
		//attributes
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices::Model3D), (unsigned*) (0 * sizeof(float)));
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertices::Model3D), (unsigned*) (3 * sizeof(float)));
		//vao image
		glBindVertexArray(m_vao_id[1]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[1]);
		//attributes
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices::Image3D), (unsigned*) (0 * sizeof(float)));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices::Image3D), (unsigned*) (3 * sizeof(float)));
		//vao text
		glBindVertexArray(m_vao_id[2]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[2]);
		//attributes
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices::Text3D), (unsigned*) (0 * sizeof(float)));
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertices::Text3D), (unsigned*) (3 * sizeof(float)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices::Text3D), (unsigned*) (7 * sizeof(float)));
	}
	void Scene::setup_shaders(void)
	{
		//path
		m_programs[1].vertex_shader()->path(m_shaders_dir + "light.vert");
		m_programs[3].vertex_shader()->path(m_shaders_dir + "text3D.vert");
		m_programs[0].vertex_shader()->path(m_shaders_dir + "model3D.vert");
		m_programs[2].vertex_shader()->path(m_shaders_dir + "image3D.vert");
		m_programs[1].geometry_shader()->path(m_shaders_dir + "light.geom");
		m_programs[1].fragment_shader()->path(m_shaders_dir + "light.frag");
		m_programs[3].fragment_shader()->path(m_shaders_dir + "text3D.frag");
		m_programs[0].fragment_shader()->path(m_shaders_dir + "model3D.frag");
		m_programs[2].fragment_shader()->path(m_shaders_dir + "image3D.frag");
		//setup
		for(unsigned i = 0; i < 4; i++) m_programs[i].setup();
	}
	void Scene::setup_textures(void)
	{
		glGenTextures(3, m_texture_id);
		for(unsigned i = 0; i < 3; i++)
		{
			glBindTexture(GL_TEXTURE_2D, m_texture_id[i]);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
	}
	void Scene::setup_freetype(void)
	{
		if(FT_Init_FreeType(&m_ft_library))
		{
			fprintf(stderr, "Error: Unable to init FreeType Library!\n");
			exit(EXIT_FAILURE);
		}
	}

	//buffers
	void Scene::buffers_data(void)
	{
		for(const objects::Object* object : m_objects)
		{
			object->buffers_data(m_vbo_data, m_ibo_data);
			for(unsigned i = 0; i < 3; i++)
			{
				const unsigned is = object->vbo_size(i);
				const unsigned ib = object->m_vbo_index[i];
				for(unsigned iv = ib; iv < ib + is; iv++)
				{
					vertices::Vertex3D* vertex;
					if(i == 2) vertex = (vertices::Text3D*) m_vbo_data[i] + iv;
					if(i == 0) vertex = (vertices::Model3D*) m_vbo_data[i] + iv;
					if(i == 1) vertex = (vertices::Image3D*) m_vbo_data[i] + iv;
					vertex->m_position = object->model_matrix() * vertex->m_position;
				}
			}
		}
	}
	void Scene::buffers_transfer(void)
	{
		//data
		const unsigned is[] = {1, 2, 3, 3, 3, 3};
		const unsigned vs[] = {sizeof(vertices::Model3D), sizeof(vertices::Image3D), sizeof(vertices::Text3D)};
		//vbo data
		for(unsigned i = 0; i < 3; i++)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[i]);
			glBufferData(GL_ARRAY_BUFFER, m_vbo_size[i] * vs[i], m_vbo_data[i], GL_DYNAMIC_DRAW);
		}
		//ibo data
		for(unsigned i = 0; i < 6; i++)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[i]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, is[i] * m_ibo_size[i] * sizeof(unsigned), m_ibo_data[i], GL_DYNAMIC_DRAW);
		}
	}
}
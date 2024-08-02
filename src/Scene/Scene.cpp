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

#include "Canvas/inc/Vertices/Text2D.hpp"
#include "Canvas/inc/Vertices/Text3D.hpp"
#include "Canvas/inc/Vertices/Model2D.hpp"
#include "Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/inc/Vertices/Image2D.hpp"
#include "Canvas/inc/Vertices/Image3D.hpp"

// vbo
// (0) model3D:	position (3) color (4)
// (1) image3D:	position (3) texture (2)
// (2) text3D:	position (3) color (4) texture (2)
// (3) model2D:	position (2) color (4)
// (4) image2D:	position (2) texture (2)
// (5) text2D:	position (2) color (4) texture (2)

// ibo
// ( 0) points 3D, ( 1) lines 3D, ( 2) triangles 3D, ( 3) images 3D, ( 4) text 3D, ( 5) latex 3D
// ( 6) points 2D, ( 7) lines 2D, ( 8) triangles 2D, ( 9) images 2D, (10) text 2D, (11) latex 2D

// programs
// ( 0) model, (1) light, (2) images, (3) text

namespace canvas
{
	//constructors
	Scene::Scene(std::string shaders_dir) :
		m_vbo_size{0, 0, 0, 0, 0, 0}, m_ibo_size{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		m_ibo_data{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
		m_vbo_data{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, m_background(0, 0, 0, 1), m_shaders_dir(shaders_dir)
	{
		setup_gl();
		setup_buffers();
		setup_shaders();
		setup_textures();
		setup_freetype();
		m_camera.m_scene = this;
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
		for(uint32_t i = 0; i < 6; i++) delete[] m_vbo_data[i];
		for(uint32_t i = 0; i < 12; i++) delete[] m_ibo_data[i];
		for(const objects::Object* object : m_objects) delete object;
		//opengl
		glUseProgram(0);
		glDeleteBuffers(6, m_vbo_id);
		glDeleteBuffers(12, m_ibo_id);
		glDeleteTextures(3, m_texture_id);
		glDeleteVertexArrays(6, m_vao_id);
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
	void Scene::add_latex(const char* source)
	{
		m_latex.push_back(new Latex(source));
	}
	Latex* Scene::latex(uint32_t index) const
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
	uint32_t Scene::vbo_size(uint32_t index) const
	{
		return m_vbo_size[index];
	}
	uint32_t Scene::ibo_size(uint32_t index) const
	{
		return m_ibo_size[index];
	}
	vertices::Vertex* Scene::vertex(uint32_t type, uint32_t index) const
	{
		if(type == 5) return (vertices::Text2D*) m_vbo_data[5] + index;
		if(type == 2) return (vertices::Text3D*) m_vbo_data[2] + index;
		if(type == 3) return (vertices::Model2D*) m_vbo_data[3] + index;
		if(type == 0) return (vertices::Model3D*) m_vbo_data[0] + index;
		if(type == 4) return (vertices::Image2D*) m_vbo_data[4] + index;
		if(type == 1) return (vertices::Image3D*) m_vbo_data[1] + index;
		return nullptr;
	}

	//draw
	void Scene::draw(void)
	{
		//data
		const float* c = m_background.channels();
		//clear
		glClearColor(c[0], c[1], c[2], c[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//draw 3D
		draw_text_3D();
		draw_model_3D();
		draw_image_3D();
		draw_latex_3D();
		//draw 2D
		draw_text_2D();
		draw_model_2D();
		draw_image_2D();
		draw_latex_2D();
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
	void Scene::draw_text_2D(void)
	{
		//model
		m_programs[6].bind();
		glBindVertexArray(m_vao_id[5]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[5]);
		glBindTexture(GL_TEXTURE_2D, m_texture_id[1]);
		//draw triangles
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[10]);
		glDrawElements(GL_TRIANGLES, 3 * m_ibo_size[10], GL_UNSIGNED_INT, nullptr);
	}
	void Scene::draw_text_3D(void)
	{
		//model
		m_programs[3].bind();
		glBindVertexArray(m_vao_id[2]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[2]);
		glBindTexture(GL_TEXTURE_2D, m_texture_id[1]);
		//draw triangles
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[4]);
		glDrawElements(GL_TRIANGLES, 3 * m_ibo_size[4], GL_UNSIGNED_INT, nullptr);
	}
	void Scene::draw_model_2D(void)
	{
		//model
		m_programs[4].bind();
		glBindVertexArray(m_vao_id[3]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[3]);
		//draw points
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[6]);
		glDrawElements(GL_POINTS, m_ibo_size[6], GL_UNSIGNED_INT, nullptr);
		//draw lines
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[7]);
		glDrawElements(GL_LINES, 2 * m_ibo_size[7], GL_UNSIGNED_INT, nullptr);
		//draw triangles
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[8]);
		glDrawElements(GL_TRIANGLES, 3 * m_ibo_size[8], GL_UNSIGNED_INT, nullptr);
	}
	void Scene::draw_model_3D(void)
	{
		//model
		m_programs[0].bind();
		glBindVertexArray(m_vao_id[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[0]);
		//draw points
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[0]);
		glDrawElements(GL_POINTS, m_ibo_size[0], GL_UNSIGNED_INT, nullptr);
		//draw lines
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[1]);
		glDrawElements(GL_LINES, 2 * m_ibo_size[1], GL_UNSIGNED_INT, nullptr);
		//draw triangles
		m_programs[1].bind();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[2]);
		glDrawElements(GL_TRIANGLES, 3 * m_ibo_size[2], GL_UNSIGNED_INT, nullptr);
	}
	void Scene::draw_image_2D(void)
	{
		//model
		m_programs[5].bind();
		glBindVertexArray(m_vao_id[4]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[4]);
		glBindTexture(GL_TEXTURE_2D, m_texture_id[0]);
		//draw triangles
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[9]);
		glDrawElements(GL_TRIANGLES, 3 * m_ibo_size[9], GL_UNSIGNED_INT, nullptr);
	}
	void Scene::draw_image_3D(void)
	{
		//model
		m_programs[2].bind();
		glBindVertexArray(m_vao_id[1]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[1]);
		glBindTexture(GL_TEXTURE_2D, m_texture_id[0]);
		//draw triangles
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[3]);
		glDrawElements(GL_TRIANGLES, 3 * m_ibo_size[3], GL_UNSIGNED_INT, nullptr);
	}
	void Scene::draw_latex_2D(void)
	{
		//model
		m_programs[6].bind();
		glBindVertexArray(m_vao_id[5]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[5]);
		glBindTexture(GL_TEXTURE_2D, m_texture_id[2]);
		//draw triangles
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[11]);
		glDrawElements(GL_TRIANGLES, 3 * m_ibo_size[11], GL_UNSIGNED_INT, nullptr);
	}
	void Scene::draw_latex_3D(void)
	{
		//model
		m_programs[3].bind();
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
		for(uint32_t i = 0; i < 6; i++)
		{
			m_vbo_size[i] = 0;
			for(const objects::Object* object : m_objects)
			{
				m_vbo_size[i] += object->vbo_size(i);
			}
			delete[] m_vbo_data[i];
			if(i == 5) m_vbo_data[i] = new vertices::Text2D[m_vbo_size[i]];
			if(i == 2) m_vbo_data[i] = new vertices::Text3D[m_vbo_size[i]];
			if(i == 3) m_vbo_data[i] = new vertices::Model2D[m_vbo_size[i]];
			if(i == 0) m_vbo_data[i] = new vertices::Model3D[m_vbo_size[i]];
			if(i == 4) m_vbo_data[i] = new vertices::Image2D[m_vbo_size[i]];
			if(i == 1) m_vbo_data[i] = new vertices::Image3D[m_vbo_size[i]];
		}
	}
	void Scene::setup_ibo(void)
	{
		//data
		const uint32_t is[] = {1, 2, 3, 3, 3, 3, 1, 2, 3, 3, 3, 3};
		//ibo data
		for(uint32_t i = 0; i < 12; i++)
		{
			m_ibo_size[i] = 0;
			for(const objects::Object* object : m_objects)
			{
				m_ibo_size[i] += object->ibo_size(i);
			}
			delete[] m_ibo_data[i];
			m_ibo_data[i] = new uint32_t[is[i] * m_ibo_size[i]];
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
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glBindTexture(GL_TEXTURE_2D, m_texture_id[1]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);
		//texture data
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
		Latex::m_total_width = w;
		Latex::m_total_height = h;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glBindTexture(GL_TEXTURE_2D, m_texture_id[2]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);
		//texture data
		for(Latex* latex : m_latex)
		{
			const uint32_t w = latex->m_width;
			const uint32_t h = latex->m_height;
			const uint32_t x = latex->m_offset;
			const uint8_t* data = latex->m_data;
			glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, w, h, GL_RED, GL_UNSIGNED_BYTE, data);
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
		Image::m_total_width = w;
		Image::m_total_height = h;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glBindTexture(GL_TEXTURE_2D, m_texture_id[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		//texture data
		for(Image* image : m_images)
		{
			const uint32_t w = image->m_width;
			const uint32_t h = image->m_height;
			const uint32_t x = image->m_offset;
			const uint8_t* data = image->m_data;
			glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	void Scene::setup_objects(void)
	{
		//data
		uint32_t vbo_counter[] = {0, 0, 0, 0, 0, 0};
		uint32_t ibo_counter[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		//objects
		for(objects::Object* object : m_objects)
		{
			object->setup(vbo_counter, ibo_counter);
		}
	}
	void Scene::setup_buffers(void)
	{
		//generate
		glGenBuffers(6, m_vbo_id);
		glGenBuffers(12, m_ibo_id);
		glGenVertexArrays(6, m_vao_id);
		//buffers
		setup_buffers_2D();
		setup_buffers_3D();
	}
	void Scene::setup_shaders(void)
	{
		//path
		m_programs[1].vertex_shader()->path(m_shaders_dir + "light.vert");
		m_programs[6].vertex_shader()->path(m_shaders_dir + "text2D.vert");
		m_programs[3].vertex_shader()->path(m_shaders_dir + "text3D.vert");
		m_programs[4].vertex_shader()->path(m_shaders_dir + "model2D.vert");
		m_programs[0].vertex_shader()->path(m_shaders_dir + "model3D.vert");
		m_programs[5].vertex_shader()->path(m_shaders_dir + "image2D.vert");
		m_programs[2].vertex_shader()->path(m_shaders_dir + "image3D.vert");
		m_programs[1].geometry_shader()->path(m_shaders_dir + "light.geom");
		m_programs[1].fragment_shader()->path(m_shaders_dir + "light.frag");
		m_programs[6].fragment_shader()->path(m_shaders_dir + "text2D.frag");
		m_programs[3].fragment_shader()->path(m_shaders_dir + "text3D.frag");
		m_programs[4].fragment_shader()->path(m_shaders_dir + "model2D.frag");
		m_programs[0].fragment_shader()->path(m_shaders_dir + "model3D.frag");
		m_programs[5].fragment_shader()->path(m_shaders_dir + "image2D.frag");
		m_programs[2].fragment_shader()->path(m_shaders_dir + "image3D.frag");
		//setup
		for(uint32_t i = 0; i < 7; i++) m_programs[i].setup();
	}
	void Scene::setup_textures(void)
	{
		glGenTextures(3, m_texture_id);
		for(uint32_t i = 0; i < 3; i++)
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
	void Scene::setup_buffers_2D(void)
	{
		//vao model
		glBindVertexArray(m_vao_id[3]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[3]);
		//attributes
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertices::Model2D), (uint32_t*) (0 * sizeof(float)));
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertices::Model2D), (uint32_t*) (2 * sizeof(float)));
		//vao image
		glBindVertexArray(m_vao_id[4]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[4]);
		//attributes
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertices::Image2D), (uint32_t*) (0 * sizeof(float)));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices::Image2D), (uint32_t*) (2 * sizeof(float)));
		//vao text
		glBindVertexArray(m_vao_id[5]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[5]);
		//attributes
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertices::Text2D), (uint32_t*) (0 * sizeof(float)));
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertices::Text2D), (uint32_t*) (2 * sizeof(float)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices::Text2D), (uint32_t*) (6 * sizeof(float)));
	}
	void Scene::setup_buffers_3D(void)
	{
		//vao model
		glBindVertexArray(m_vao_id[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[0]);
		//attributes
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices::Model3D), (uint32_t*) (0 * sizeof(float)));
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertices::Model3D), (uint32_t*) (3 * sizeof(float)));
		//vao image
		glBindVertexArray(m_vao_id[1]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[1]);
		//attributes
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices::Image3D), (uint32_t*) (0 * sizeof(float)));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices::Image3D), (uint32_t*) (3 * sizeof(float)));
		//vao text
		glBindVertexArray(m_vao_id[2]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[2]);
		//attributes
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices::Text3D), (uint32_t*) (0 * sizeof(float)));
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertices::Text3D), (uint32_t*) (3 * sizeof(float)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices::Text3D), (uint32_t*) (7 * sizeof(float)));
	}

	//buffers
	void Scene::buffers_data(void)
	{
		for(const objects::Object* object : m_objects)
		{
			object->buffers_data(m_vbo_data, m_ibo_data);
			for(uint32_t i = 0; i < 3; i++)
			{
				const uint32_t is = object->vbo_size(i);
				const uint32_t ib = object->m_vbo_index[i];
				for(uint32_t iv = ib; iv < ib + is; iv++)
				{
					vertices::Vertex3D* vertex;
					if(i == 2) vertex = (vertices::Text3D*) m_vbo_data[i] + iv;
					if(i == 0) vertex = (vertices::Model3D*) m_vbo_data[i] + iv;
					if(i == 1) vertex = (vertices::Image3D*) m_vbo_data[i] + iv;
					if(object->m_has_model_matrix)
					{
						vertex->m_position = object->m_model_matrix * vertex->m_position;
					}
				}
			}
		}
	}
	void Scene::buffers_transfer(void)
	{
		//data
		const uint32_t is[] = {
			1, 2, 3, 3, 3, 3, 1, 2, 3, 3, 3, 3
		};
		const uint32_t vs[] = {
			sizeof(vertices::Model3D), sizeof(vertices::Image3D), sizeof(vertices::Text3D),
			sizeof(vertices::Model2D), sizeof(vertices::Image2D), sizeof(vertices::Text2D)
		};
		//vbo data
		for(uint32_t i = 0; i < 6; i++)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[i]);
			glBufferData(GL_ARRAY_BUFFER, m_vbo_size[i] * vs[i], m_vbo_data[i], GL_DYNAMIC_DRAW);
		}
		//ibo data
		for(uint32_t i = 0; i < 12; i++)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[i]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, is[i] * m_ibo_size[i] * sizeof(uint32_t), m_ibo_data[i], GL_DYNAMIC_DRAW);
		}
	}
}
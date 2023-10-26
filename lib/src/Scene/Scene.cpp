//os
#ifdef _WIN32
#include <Windows.h>
#endif

//ext
#include "ext/inc/GL/glew.h"

//canvas
#include "inc/GPU/Shader.hpp"

#include "inc/Scene/Font.hpp"
#include "inc/Scene/Image.hpp"
#include "inc/Scene/Scene.hpp"
#include "inc/Scene/Latex.hpp"

#include "inc/Objects/Object.hpp"

#include "inc/Vertices/Text.hpp"
#include "inc/Vertices/Model.hpp"
#include "inc/Vertices/Image.hpp"

namespace canvas
{
	//constructors
	Scene::Scene(std::string shaders_dir) : 
		m_shaders_dir(shaders_dir),
		m_ibo_data{nullptr, nullptr, nullptr, nullptr, nullptr}, 
		m_vbo_data{nullptr, nullptr, nullptr}, m_background(0, 0, 0, 0)
	{
		setup_gl();
		setup_buffers();
		setup_shaders();
		setup_textures();
		Font::setup_ft();
		m_camera.m_scene = this;
		objects::Object::m_scene = this;
		m_camera.m_programs = m_programs;
		m_light.m_program = &m_programs[1];
	}

	//destructor
	Scene::~Scene(void)
	{
		//delete
		Font::clean_ft();
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

	Camera& Scene::camera(void)
	{
		return m_camera;
	}
	const Camera& Scene::camera(void) const
	{
		return m_camera;
	}

	Font* Scene::font(unsigned index) const
	{
		return m_fonts[index];
	}
	void Scene::add_font(const char* name)
	{
		m_fonts.push_back(new Font(name));
	}
	const std::vector<Font*>& Scene::fonts(void) const
	{
		return m_fonts;
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

	void Scene::clear_objects(void)
	{
		for(const objects::Object* object : m_objects)
		{
			delete object;
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
	void Scene::bound(void)
	{
		m_camera.m_mode ? bound_orthogonal() : bound_perspective();
	}
	void Scene::update(void)
	{
		setup();
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
	void Scene::setup(void)
	{
		setup_vbo();
		setup_ibo();
		setup_fonts();
		setup_images();
		setup_objects();
		setup_equations();
	}
	void Scene::setup_gl(void)
	{
		//enable
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_POLYGON_OFFSET_FILL);
		//values
		glLineWidth(1);
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
			if(i == 2) m_vbo_data[i] = new vertices::Text[m_vbo_size[i]];
			if(i == 0) m_vbo_data[i] = new vertices::Model[m_vbo_size[i]];
			if(i == 1) m_vbo_data[i] = new vertices::Image[m_vbo_size[i]];
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
			if(update = update || !font->m_status)
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
	void Scene::setup_images(void)
	{
		//data
		bool update = false;
		unsigned w = 0, h = 0;
		//images
		for(Image* image : m_images)
		{
			if(update = update || !image->m_status)
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices::Model), (unsigned*) (0 * sizeof(float)));
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertices::Model), (unsigned*) (3 * sizeof(float)));
		//vao image
		glBindVertexArray(m_vao_id[1]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[1]);
		//attributes
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices::Image), (unsigned*) (0 * sizeof(float)));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices::Image), (unsigned*) (3 * sizeof(float)));
		//vao text
		glBindVertexArray(m_vao_id[2]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[2]);
		//attributes
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices::Text), (unsigned*) (0 * sizeof(float)));
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertices::Text), (unsigned*) (3 * sizeof(float)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices::Text), (unsigned*) (7 * sizeof(float)));
	}
	void Scene::setup_shaders(void)
	{
		//path
		m_programs[3].vertex_shader()->path(m_shaders_dir + "text.vert");
		m_programs[0].vertex_shader()->path(m_shaders_dir + "model.vert");
		m_programs[1].vertex_shader()->path(m_shaders_dir + "light.vert");
		m_programs[2].vertex_shader()->path(m_shaders_dir + "image.vert");
		m_programs[3].fragment_shader()->path(m_shaders_dir + "text.frag");
		m_programs[1].geometry_shader()->path(m_shaders_dir + "light.geom");
		m_programs[0].fragment_shader()->path(m_shaders_dir + "model.frag");
		m_programs[1].fragment_shader()->path(m_shaders_dir + "light.frag");
		m_programs[2].fragment_shader()->path(m_shaders_dir + "image.frag");
		//setup
		for(unsigned i = 0; i < 4; i++) m_programs[i].setup();
		//uniforms
		for(unsigned i = 0; i < 4; i++)
		{
			m_programs[i].use();
			glUniform1i(glGetUniformLocation(m_programs[i].id(), "camera_mode"), m_camera.m_mode);
			glUniform1f(glGetUniformLocation(m_programs[i].id(), "camera_far"), m_camera.m_plane_far);
			glUniform1f(glGetUniformLocation(m_programs[i].id(), "camera_near"), m_camera.m_plane_near);
			glUniform3fv(glGetUniformLocation(m_programs[i].id(), "camera_position"), 1, m_camera.m_position.memory());
			glUniform4fv(glGetUniformLocation(m_programs[i].id(), "camera_rotation"), 1, m_camera.m_rotation.memory());
		}
	}
	void Scene::setup_textures(void)
	{
		glGenTextures(3, m_texture_id);
		for(unsigned i = 0; i < 3; i++)
		{
			glBindTexture(GL_TEXTURE_2D, m_texture_id[i]);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}
	void Scene::setup_equations(void)
	{
		//data
		bool update = false;
		unsigned w = 0, h = 0;
		//images
		for(Latex* latex : m_latex)
		{
			if(update = update || !latex->m_status)
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

	//update
	void Scene::bound_orthogonal(void)
	{
		//data
		vec3 xw;
		const quat& qc = m_camera.m_rotation;
		const unsigned w = m_camera.m_screen[0];
		const unsigned h = m_camera.m_screen[1];
		vec3 x1 = {+FLT_MAX, +FLT_MAX, +FLT_MAX};
		vec3 x2 = {-FLT_MAX, -FLT_MAX, -FLT_MAX};
		//bound
		const float m = fminf(w, h);
		for(unsigned i = 0; i < 3; i++)
		{
			for(unsigned j = 0; j < m_vbo_size[i]; j++)
			{
				//position
				if(i == 2) xw = qc.conjugate(((vertices::Text*) m_vbo_data[i] + j)->m_position);
				if(i == 0) xw = qc.conjugate(((vertices::Model*) m_vbo_data[i] + j)->m_position);
				if(i == 1) xw = qc.conjugate(((vertices::Image*) m_vbo_data[i] + j)->m_position);
				//bouding box
				x1[2] = fminf(x1[2], xw[2]);
				x2[2] = fmaxf(x2[2], xw[2]);
				x1[0] = fminf(x1[0], m / w * xw[0]);
				x2[0] = fmaxf(x2[0], m / w * xw[0]);
				x1[1] = fminf(x1[1], m / h * xw[1]);
				x2[1] = fmaxf(x2[1], m / h * xw[1]);
			}
		}
		vec3 xm = (x1 + x2) / 2;
		const vec3 xs = (x2 - x1) / 2;
		const float dz = fmaxf(xs[0], fmaxf(xs[1], xs[2]));
		//apply
		xm[0] *= w / m;
		xm[1] *= h / m;
		m_camera.plane_near(dz);
		m_camera.plane_far(3 * dz);
		m_camera.position(qc.rotate(xm - 2 * dz * vec3(0, 0, 1)));
	}
	void Scene::bound_perspective(void)
	{

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
					vertices::Vertex* vertex;
					if(i == 2) vertex = (vertices::Text*) m_vbo_data[i] + iv;
					if(i == 0) vertex = (vertices::Model*) m_vbo_data[i] + iv;
					if(i == 1) vertex = (vertices::Image*) m_vbo_data[i] + iv;
					vertex->m_position = object->affine() * vertex->m_position;
				}
			}
		}
	}
	void Scene::buffers_transfer(void)
	{
		//data
		const unsigned is[] = {1, 2, 3, 3, 3, 3};
		const unsigned vs[] = {sizeof(vertices::Model), sizeof(vertices::Image), sizeof(vertices::Text)};
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
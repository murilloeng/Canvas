//os
#ifdef _WIN32
#include <Windows.h>
#endif

//ext
#include "../external/cpp/inc/GL/glew.h"

//canvas
#include "inc/Scene/Scene.hpp"

#include "inc/Objects/Object.hpp"

#include "inc/Vertices/Text.hpp"
#include "inc/Vertices/Model.hpp"
#include "inc/Vertices/Image.hpp"

namespace canvas
{
	//constructors
	Scene::Scene(void) : 
		m_ibo_data{nullptr, nullptr, nullptr, nullptr, nullptr}, 
		m_vbo_data{nullptr, nullptr, nullptr}, m_background(0, 0, 0, 0)
	{
		setup_gl();
		setup_buffers();
		setup_shaders();
		setup_textures();
		objects::Object::m_scene = this;
		m_camera.m_program_id = m_program_id;
	}

	//destructor
	Scene::~Scene(void)
	{
		//delete
		delete[] m_vbo_data[0];
		delete[] m_vbo_data[1];
		delete[] m_ibo_data[0];
		delete[] m_ibo_data[1];
		delete[] m_ibo_data[2];
		for(const objects::Object* object : m_objects)
		{
			delete object;
		}
		//opengl
		glUseProgram(0);
		glDeleteBuffers(2, m_vbo_id);
		glDeleteBuffers(3, m_ibo_id);
		glDeleteProgram(m_program_id[0]);
		glDeleteProgram(m_program_id[1]);
		glDeleteProgram(m_program_id[2]);
		glDeleteTextures(2, m_texture_id);
		glDeleteVertexArrays(2, m_vao_id);
		glDeleteShader(m_shaders_vertex_id[0]);
		glDeleteShader(m_shaders_vertex_id[1]);
		glDeleteShader(m_shaders_vertex_id[2]);
		glDeleteShader(m_shaders_fragment_id[0]);
		glDeleteShader(m_shaders_fragment_id[1]);
		glDeleteShader(m_shaders_fragment_id[2]);
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

	Camera& Scene::camera(void)
	{
		return m_camera;
	}
	const Camera& Scene::camera(void) const
	{
		return m_camera;
	}

	void Scene::add_image(const char* path)
	{
		Image image;
		image.m_path = path;
		m_images.push_back(image);
	}
	const Image& Scene::image(unsigned index) const
	{
		return m_images[index];
	}
	const std::vector<Image>& Scene::images(void) const
	{
		return m_images;
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
	}
	void Scene::bound(void)
	{
		//data
		vec3 box_min = {+FLT_MAX, +FLT_MAX, +FLT_MAX};
		vec3 box_max = {-FLT_MAX, -FLT_MAX, -FLT_MAX};
		//bound
		for(unsigned i = 0; i < 3; i++)
		{
			for(unsigned j = 0; j < m_vbo_size[i]; j++)
			{
				for(unsigned k = 0; k < 3; k++)
				{
					if(i == 2) box_min[k] = fminf(box_min[k], ((vertices::Text*) m_vbo_data[i] + j)->m_position[k]);
					if(i == 2) box_max[k] = fmaxf(box_max[k], ((vertices::Text*) m_vbo_data[i] + j)->m_position[k]);
					if(i == 0) box_min[k] = fminf(box_min[k], ((vertices::Model*) m_vbo_data[i] + j)->m_position[k]);
					if(i == 0) box_max[k] = fmaxf(box_max[k], ((vertices::Model*) m_vbo_data[i] + j)->m_position[k]);
					if(i == 1) box_min[k] = fminf(box_min[k], ((vertices::Image*) m_vbo_data[i] + j)->m_position[k]);
					if(i == 1) box_max[k] = fmaxf(box_max[k], ((vertices::Image*) m_vbo_data[i] + j)->m_position[k]);
				}
			}
		}
		//update
		m_camera.box_min(box_min);
		m_camera.box_max(box_max);
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
		glUseProgram(m_program_id[2]);
		glBindVertexArray(m_vao_id[2]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[2]);
		//draw triangles
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[4]);
		glDrawElements(GL_TRIANGLES, 3 * m_ibo_size[4], GL_UNSIGNED_INT, nullptr);
	}
	void Scene::draw_model(void)
	{
		//model
		glUseProgram(m_program_id[0]);
		glBindVertexArray(m_vao_id[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[0]);
		//draw points
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[0]);
		glDrawElements(GL_POINTS, m_ibo_size[0], GL_UNSIGNED_INT, nullptr);
		//draw lines
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[1]);
		glDrawElements(GL_LINES, 2 * m_ibo_size[1], GL_UNSIGNED_INT, nullptr);
		//draw triangles
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[2]);
		glDrawElements(GL_TRIANGLES, 3 * m_ibo_size[2], GL_UNSIGNED_INT, nullptr);
	}
	void Scene::draw_image(void)
	{
		//model
		glUseProgram(m_program_id[1]);
		glBindVertexArray(m_vao_id[1]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[1]);
		glBindTexture(GL_TEXTURE_2D, m_texture_id[0]);
		//draw triangles
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[3]);
		glDrawElements(GL_TRIANGLES, 3 * m_ibo_size[3], GL_UNSIGNED_INT, nullptr);
	}

	//setup
	void Scene::setup(void)
	{
		setup_vbo();
		setup_ibo();
		setup_images();
		setup_objects();
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
		const unsigned ibo_offset[] = {1, 2, 3, 3, 3};
		//buffers
		for(unsigned i = 0; i < 5; i++)
		{
			m_ibo_size[i] = 0;
			for(const objects::Object* object : m_objects)
			{
				m_ibo_size[i] += object->ibo_size(i);
			}
			delete[] m_ibo_data[i];
			m_ibo_data[i] = new unsigned[ibo_offset[i] * m_ibo_size[i]];
		}
	}
	void Scene::setup_images(void)
	{
		//data
		unsigned& w = Image::m_total_width = 0;
		unsigned& h = Image::m_total_height = 0;
		//images
		for(Image& image : m_images)
		{
			image.load();
			image.m_offset = w;
			w += image.m_width;
			h = std::max(h, image.m_height);
		}
		//texture
		glActiveTexture(GL_TEXTURE0);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glBindTexture(GL_TEXTURE_2D, m_texture_id[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		//texture data
		for(Image& image : m_images)
		{
			const unsigned w = image.m_width;
			const unsigned h = image.m_height;
			const unsigned x = image.m_offset;
			const unsigned char* data = image.m_data;
			glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
	}
	void Scene::setup_objects(void)
	{
		//data
		unsigned vbo_counter[] = {0, 0, 0};
		unsigned ibo_counter[] = {0, 0, 0, 0, 0};
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
		glGenBuffers(5, m_ibo_id);
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
		setup_program(m_program_id[2], m_shaders_vertex_id[2], m_shaders_fragment_id[2], "shd/text.vert", "shd/text.frag");
		setup_program(m_program_id[0], m_shaders_vertex_id[0], m_shaders_fragment_id[0], "shd/model.vert", "shd/model.frag");
		setup_program(m_program_id[1], m_shaders_vertex_id[1], m_shaders_fragment_id[1], "shd/image.vert", "shd/image.frag");
	}
	void Scene::setup_textures(void)
	{
		//generate
		glGenTextures(2, m_texture_id);
		//images texture
		glBindTexture(GL_TEXTURE_2D, m_texture_id[0]);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//text texture
		glBindTexture(GL_TEXTURE_2D, m_texture_id[1]);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
		const unsigned is[] = {1, 2, 3, 3, 3};
		const unsigned vs[] = {sizeof(vertices::Model), sizeof(vertices::Image), sizeof(vertices::Text)};
		//vbo data
		for(unsigned i = 0; i < 3; i++)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[i]);
			glBufferData(GL_ARRAY_BUFFER, m_vbo_size[i] * vs[i], m_vbo_data[i], GL_DYNAMIC_DRAW);
		}
		//ibo data
		for(unsigned i = 0; i < 5; i++)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[i]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, is[i] * m_ibo_size[i] * sizeof(unsigned), m_ibo_data[i], GL_DYNAMIC_DRAW);
		}
	}

	//misc
	bool Scene::load_file(std::string& source, const char* path)
	{
		//open
		FILE* file = fopen(path, "r");
		//check
		if(!file) return false;
		//read
		source.clear();
		while(!feof(file)) source += fgetc(file);
		source.back() = '\0';
		//close
		fclose(file);
		//return
		return true;
	}
	void Scene::setup_shader(unsigned& id, unsigned type, unsigned program, const char* path)
	{
		//source
		std::string source;
		if(!load_file(source, path))
		{
			fprintf(stderr, "Error loading shader source! (%d)\n", type);
			exit(EXIT_FAILURE);
		}
		//create
		id = glCreateShader(type);
		if(id == 0)
		{
			fprintf(stderr, "Error creating shader! (%d)\n", type);
			exit(EXIT_FAILURE);
		}
		//source
		const GLchar* p = source.c_str();
		glShaderSource(id, 1, &p, nullptr);
		//compile
		GLint status;
		GLchar log[1024];
		glCompileShader(id);
		glGetShaderiv(id, GL_COMPILE_STATUS, &status);
		if(status == 0)
		{
			glGetShaderInfoLog(id, sizeof(log), nullptr, log);
			fprintf(stderr, "Error compiling shader!\n");
			fprintf(stderr, "Shader type: %d\n", type);
			fprintf(stderr, "Shader path: %s\n", path);
			fprintf(stderr, "Error log: %hs\n", log);
			exit(EXIT_FAILURE);
		}
		//attach
		glAttachShader(program, id);
	}
	void Scene::setup_program(unsigned& id, unsigned& shader_1, unsigned& shader_2, const char* path_1, const char* path_2)
	{
		//create
		id = glCreateProgram();
		if(id == 0)
		{
			fprintf(stderr, "Error creating shader program!\n");
			exit(EXIT_FAILURE);
		}
		//shaders
		setup_shader(shader_1, GL_VERTEX_SHADER, id, path_1);
		setup_shader(shader_2, GL_FRAGMENT_SHADER, id, path_2);
		//link
		GLint status;
		GLchar log[1024];
		glLinkProgram(id);
		glGetProgramiv(id, GL_LINK_STATUS, &status);
		if(status == 0)
		{
			glGetProgramInfoLog(id, sizeof(log), nullptr, log);
			fprintf(stderr, "Error linking shader program: %s\n", log);
			exit(EXIT_FAILURE);
		}
		//validate
		glValidateProgram(id);
		glGetProgramiv(id, GL_VALIDATE_STATUS, &status);
		if(status == 0)
		{
			glGetProgramInfoLog(id, sizeof(log), nullptr, log);
			fprintf(stderr, "Error validating shader program: %s\n", log);
			exit(EXIT_FAILURE);
		}
	}
}
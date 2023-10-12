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
		m_vao_id{0, 0}, 
		m_vbo_id{0, 0}, 
		m_ibo_id{0, 0},
		m_vbo_size{0, 0}, 
		m_ibo_size{0, 0, 0}, 
		m_ibo_data{nullptr, nullptr, nullptr}, 
		m_vbo_data{nullptr, nullptr},
		m_background(0, 0, 0, 0),
		m_program_id{0, 0, 0},
		m_shaders_vertex_id{0, 0, 0}, 
		m_shaders_fragment_id{0, 0, 0}
	{
		setup_gl();
		setup_buffers();
		setup_shaders();
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
	void Scene::bound(void)
	{
		//check
		if(m_vbo_size[0] == 0) return;
		//data
		vec3 box_min = ((vertices::Model*) m_vbo_data[0])->m_position;
		vec3 box_max = ((vertices::Model*) m_vbo_data[0])->m_position;
		//bound
		for(unsigned i = 1; i < m_vbo_size[0]; i++)
		{
			for(unsigned j = 0; j < 3; j++)
			{
				box_min[j] = fminf(box_min[j], ((vertices::Model*) m_vbo_data[0] + i)->m_position[j]);
				box_max[j] = fmaxf(box_max[j], ((vertices::Model*) m_vbo_data[0] + i)->m_position[j]);
			}
		}
		m_camera.box_min(box_min);
		m_camera.box_max(box_max);
	}
	void Scene::update(bool bound)
	{
		//draw
		prepare();
		for(const objects::Object* object : m_objects)
		{
			const unsigned is = object->vbo_size(0);
			const unsigned ib = object->m_vbo_index[0];
			object->buffers_data(m_vbo_data[0], m_ibo_data);
			for(unsigned iv = ib; iv < ib + is; iv++)
			{
				vertices::Model* vertex = (vertices::Model*) m_vbo_data[0] + iv;
				vertex->m_position = object->affine() * vertex->m_position;
			}
		}
		if(bound) this->bound();
		//vbo data
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[0]);
		glBufferData(GL_ARRAY_BUFFER, m_vbo_size[0] * sizeof(vertices::Model), m_vbo_data[0], GL_STATIC_DRAW);
		//ibo data
		for(unsigned i = 0; i < 3; i++)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id[i]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, (i + 1) * m_ibo_size[i] * sizeof(unsigned), m_ibo_data[i], GL_STATIC_DRAW);
		}
	}
	void Scene::prepare(void)
	{
		//vbo size
		m_vbo_size[0] = 0;
		for(const objects::Object* object : m_objects)
		{
			m_vbo_size[0] += object->vbo_size(0);
		}
		delete[] m_vbo_data[0];
		m_vbo_data[0] = new vertices::Model[m_vbo_size[0]];
		//ibo size
		for(unsigned i = 0; i < 3; i++)
		{
			m_ibo_size[i] = 0;
			for(const objects::Object* object : m_objects)
			{
				m_ibo_size[i] += object->ibo_size(i);
			}
			delete[] m_ibo_data[i];
			m_ibo_data[i] = new unsigned[(i + 1) * m_ibo_size[i]];
		}
		//indexes
		unsigned vbo_counter = 0;
		unsigned ibo_counter[] = {0, 0, 0};
		for(objects::Object* object : m_objects)
		{
			object->buffers_index(vbo_counter, ibo_counter);
		}
	}

	//objects
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

	//setup
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
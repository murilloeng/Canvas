//os
#ifdef _WIN32
#include <Windows.h>
#endif

//ext
#include "../external/cpp/inc/GL/glew.h"

//canvas
#include "inc/Models/Model.hpp"

#include "inc/Vertices/Text.hpp"
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Arc.hpp"
#include "inc/Objects/Type.hpp"
#include "inc/Objects/Line.hpp"
#include "inc/Objects/Quad.hpp"
#include "inc/Objects/Point.hpp"
#include "inc/Objects/Circle.hpp"
#include "inc/Objects/Object.hpp"
#include "inc/Objects/Triangle.hpp"

namespace canvas
{
	//constructors
	Model::Model(void) : 
		m_vao_id{0, 0}, 
		m_vbo_id{0, 0}, 
		m_ibo_id{0, 0},
		m_vbo_size{0, 0}, 
		m_ibo_size{0, 0, 0}, 
		m_ibo_data{nullptr, nullptr, nullptr}, 
		m_vbo_data{nullptr, nullptr},
		m_program_id{0, 0},
		m_shaders_vertex_id{0, 0}, 
		m_shaders_fragment_id{0, 0}
	{
		setup_gl();
		setup_buffers();
		setup_shaders();
		setup_uniforms();
	}

	//destructor
	Model::~Model(void)
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
		glDeleteVertexArrays(2, m_vao_id);
		glDeleteShader(m_shaders_vertex_id[0]);
		glDeleteShader(m_shaders_vertex_id[1]);
		glDeleteShader(m_shaders_fragment_id[0]);
		glDeleteShader(m_shaders_fragment_id[1]);
	}

	//data
	void Model::screen(unsigned width, unsigned height)
	{
		glUniform2ui(glGetUniformLocation(m_program_id[0], "screen"), width, height);
	}

	void Model::box_min(float x1_min, float x2_min, float x3_min)
	{
		glUniform3f(glGetUniformLocation(m_program_id[0], "box_min"), x1_min, x2_min, x3_min);
	}
	void Model::box_max(float x1_max, float x2_max, float x3_max)
	{
		glUniform3f(glGetUniformLocation(m_program_id[0], "box_max"), x1_max, x2_max, x3_max);
	}

	void Model::zoom(float zoom)
	{
		glUniform1f(glGetUniformLocation(m_program_id[0], "zoom"), zoom);
	}
	void Model::pan(float x1, float x2, float x3)
	{
		glUniform3f(glGetUniformLocation(m_program_id[0], "pan"), x1, x2, x3);
	}
	void Model::quat(float q1, float q2, float q3, float q4)
	{
		glUniform4f(glGetUniformLocation(m_program_id[0], "quat"), q1, q2, q3, q4);
	}

	objects::Object* Model::object(unsigned index) const
	{
		return m_objects[index];
	}
	const std::vector<objects::Object*>& Model::objects(void) const
	{
		return m_objects;
	}

	//draw
	void Model::draw(void)
	{
		//clear
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
	void Model::update(void)
	{
		//draw
		prepare();
		for(const objects::Object* object : m_objects)
		{
			object->draw(m_vbo_data[0], m_ibo_data);
		}
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
	void Model::prepare(void)
	{
		//vbo size
		m_vbo_size[0] = 0;
		for(const objects::Object* object : m_objects)
		{
			m_vbo_size[0] += object->vbo_size();
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
			object->m_vbo_index = vbo_counter;
			vbo_counter += object->vbo_size();
			for(unsigned i = 0; i < 3; i++)
			{
				object->m_ibo_index[i] = ibo_counter[i];
				ibo_counter[i] += (i + 1) * object->ibo_size(i);
			}
		}
	}

	//objects
	void Model::clear_objects(void)
	{
		for(const objects::Object* object : m_objects)
		{
			delete object;
		}
		m_objects.clear();
	}
	void Model::add_object(objects::type type)
	{
		switch(type)
		{
		case objects::type::arc:
			m_objects.push_back(new objects::Arc);
			break;
		case objects::type::line:
			m_objects.push_back(new objects::Line);
			break;
		case objects::type::quad:
			m_objects.push_back(new objects::Quad);
			break;
		case objects::type::point:
			m_objects.push_back(new objects::Point);
			break;
		case objects::type::circle:
			m_objects.push_back(new objects::Circle);
			break;
		case objects::type::triangle:
			m_objects.push_back(new objects::Triangle);
			break;
		default:
			break;
		}
	}

	//setup
	void Model::setup_gl(void)
	{
		glLineWidth(2);
		glPointSize(7);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glPolygonOffset(1.0, 1.0);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	}
	void Model::setup_buffers(void)
	{
		//generate
		glGenBuffers(2, m_vbo_id);
		glGenBuffers(3, m_ibo_id);
		glGenVertexArrays(2, m_vao_id);
		//vao model
		glBindVertexArray(m_vao_id[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[0]);
		//attributes
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertices::Model), (unsigned*) (0 * sizeof(float)));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices::Model), (unsigned*) (4 * sizeof(float)));
		//vao text
		glBindVertexArray(m_vao_id[1]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id[1]);
		//attributes
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertices::Text), (unsigned*) (0 * sizeof(float)));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices::Text), (unsigned*) (4 * sizeof(float)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices::Text), (unsigned*) (7 * sizeof(float)));
	}
	void Model::setup_shaders(void)
	{
		setup_program(m_program_id[1], m_shaders_vertex_id[1], m_shaders_fragment_id[1], "shd/text.vert", "shd/text.frag");
		setup_program(m_program_id[0], m_shaders_vertex_id[0], m_shaders_fragment_id[0], "shd/model.vert", "shd/model.frag");
	}
	void Model::setup_uniforms(void)
	{
		int viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		glUniform1f(glGetUniformLocation(m_program_id[0], "zoom"), 1.0f);
		glUniform3f(glGetUniformLocation(m_program_id[0], "pan"), 0.0f, 0.0f, 0.0f);
		glUniform4f(glGetUniformLocation(m_program_id[0], "quat"), 1, 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(m_program_id[0], "box_min"), -1.0f, -1.0f, -1.0f);
		glUniform3f(glGetUniformLocation(m_program_id[0], "box_max"), +1.0f, +1.0f, +1.0f);
		glUniform2ui(glGetUniformLocation(m_program_id[0], "screen"), viewport[2], viewport[3]);
	}

	//misc
	bool Model::load_file(std::string& source, const char* path)
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
	void Model::setup_shader(unsigned& id, unsigned type, unsigned program, const char* path)
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
			fprintf(stderr, "Error log: %S\n", log);
			exit(EXIT_FAILURE);
		}
		//attach
		glAttachShader(program, id);
	}
	void Model::setup_program(unsigned& id, unsigned& shader_1, unsigned& shader_2, const char* path_1, const char* path_2)
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
//os
#ifdef _WIN32
#include <Windows.h>
#endif

//ext
#include "../external/cpp/inc/GL/glew.h"

//canvas
#include "inc/Scene/Scene.hpp"

#include "inc/Vertices/Text.hpp"
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Type.hpp"
#include "inc/Objects/Path.hpp"
#include "inc/Objects/Object.hpp"
#include "inc/Objects/Curves/Arc.hpp"
#include "inc/Objects/Curves/Line.hpp"
#include "inc/Objects/Volumes/Cube.hpp"
#include "inc/Objects/Points/Point.hpp"
#include "inc/Objects/Surfaces/Quad.hpp"
#include "inc/Objects/Curves/Spline.hpp"
#include "inc/Objects/Volumes/Sphere.hpp"
#include "inc/Objects/Surfaces/Circle.hpp"
#include "inc/Objects/Volumes/Cylinder.hpp"
#include "inc/Objects/Surfaces/Grid_2D.hpp"
#include "inc/Objects/Surfaces/Grid_3D.hpp"
#include "inc/Objects/Surfaces/Triangle.hpp"

namespace canvas
{
	//constructors
	Scene::Scene(void) : 
		m_zoom(1.0f),
		m_vao_id{0, 0}, 
		m_vbo_id{0, 0}, 
		m_ibo_id{0, 0},
		m_vbo_size{0, 0}, 
		m_ibo_size{0, 0, 0}, 
		m_ibo_data{nullptr, nullptr, nullptr}, 
		m_vbo_data{nullptr, nullptr},
		m_background(0, 0, 0, 0),
		m_program_id{0, 0},
		m_shaders_vertex_id{0, 0}, 
		m_shaders_fragment_id{0, 0}
	{
		setup_gl();
		setup_buffers();
		setup_shaders();
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
		glDeleteVertexArrays(2, m_vao_id);
		glDeleteShader(m_shaders_vertex_id[0]);
		glDeleteShader(m_shaders_vertex_id[1]);
		glDeleteShader(m_shaders_fragment_id[0]);
		glDeleteShader(m_shaders_fragment_id[1]);
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

	void Scene::box_min(float x1_min, float x2_min, float x3_min)
	{
		glUniform3f(glGetUniformLocation(m_program_id[0], "box_min"), x1_min, x2_min, x3_min);
	}
	void Scene::box_max(float x1_max, float x2_max, float x3_max)
	{
		glUniform3f(glGetUniformLocation(m_program_id[0], "box_max"), x1_max, x2_max, x3_max);
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
		m_box_min = ((vertices::Model*) m_vbo_data[0])->m_position;
		m_box_max = ((vertices::Model*) m_vbo_data[0])->m_position;
		//bound
		for(unsigned i = 1; i < m_vbo_size[0]; i++)
		{
			for(unsigned j = 0; j < 3; j++)
			{
				m_box_min[j] = fminf(m_box_min[j], ((vertices::Model*) m_vbo_data[0] + i)->m_position[j]);
				m_box_max[j] = fmaxf(m_box_max[j], ((vertices::Model*) m_vbo_data[0] + i)->m_position[j]);
			}
		}
		//shader
		glUniform3f(glGetUniformLocation(m_program_id[0], "box_min"), m_box_min[0], m_box_min[1], m_box_min[2]);
		glUniform3f(glGetUniformLocation(m_program_id[0], "box_max"), m_box_max[0], m_box_max[1], m_box_max[2]);
	}
	void Scene::update(bool bound)
	{
		//draw
		prepare();
		for(const objects::Object* object : m_objects)
		{
			const unsigned is = object->vbo_size();
			const unsigned ib = object->m_vbo_index;
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
	void Scene::add_object(objects::type type)
	{
		switch(type)
		{
		case objects::type::arc:
			m_objects.push_back(new objects::Arc);
			break;
		case objects::type::cube:
			m_objects.push_back(new objects::Cube);
			break;
		case objects::type::line:
			m_objects.push_back(new objects::Line);
			break;
		case objects::type::quad:
			m_objects.push_back(new objects::Quad);
			break;
		case objects::type::path:
			m_objects.push_back(new objects::Path);
			break;
		case objects::type::point:
			m_objects.push_back(new objects::Point);
			break;
		case objects::type::circle:
			m_objects.push_back(new objects::Circle);
			break;
		case objects::type::sphere:
			m_objects.push_back(new objects::Sphere);
			break;
		case objects::type::spline:
			m_objects.push_back(new objects::Spline);
			break;
		case objects::type::grid_2D:
			m_objects.push_back(new objects::Grid_2D);
			break;
		case objects::type::grid_3D:
			m_objects.push_back(new objects::Grid_3D);
			break;
		case objects::type::triangle:
			m_objects.push_back(new objects::Triangle);
			break;
		case objects::type::cylinder:
			m_objects.push_back(new objects::Cylinder);
			break;
		default:
			break;
		}
	}
	void Scene::add_object(objects::Object* object)
	{
		m_objects.push_back(object);
	}

	//callbacks
	void Scene::callback_motion(int x1, int x2)
	{
		//data
		const float z = m_zoom;
		const int w = m_screen[0];
		const int h = m_screen[1];
		const quat& q = m_rotation;
		const float m = w < h ? w : h;
		const int z1 = m_click.position(0);
		const int z2 = m_click.position(1);
		const vec3 xs = (m_box_max - m_box_min) / 2;
		const float s = fmaxf(xs[0], fmaxf(xs[1], xs[2]));
		const vec3 xp((2 * x1 - w) / m, (h - 2 * x2) / m, 0);
		const vec3 xc((2 * z1 - w) / m, (h - 2 * z2) / m, 0);
		//shift
		if(m_click.button() == button::middle)
		{
			shift(m_click.shift() + s / z * q.conjugate().rotate(xc - xp));
		}
		//rotation
		if(m_click.button() == button::left)
		{
			const quat qc = m_click.rotation();
			const vec3 v1 = Click::arcball(xc[0], xc[1]);
			const vec3 v2 = Click::arcball(xp[0], xp[1]);
			rotation((acosf(v1.inner(v2)) * v1.cross(v2).unit()).quaternion() * m_click.rotation());
			shift(m_click.shift() + s / z * (qc.conjugate().rotate(xc) - q.conjugate().rotate(xc)));
		}
	}
	void Scene::callback_reshape(int width, int height)
	{
		m_screen[0] = width;
		m_screen[1] = height;
		glViewport(0, 0, width, height);
		glUniform2ui(glGetUniformLocation(m_program_id[0], "screen"), width, height);
	}
	void Scene::callback_wheel(int direction, int x1, int x2)
	{
		//box
		const vec3 xc = (m_box_min + m_box_max) / 2;
		const vec3 xs = (m_box_max - m_box_min) / 2;
		//zoom
		const float dz = 0.05;
		const float z_old = m_zoom;
		const float z_new = (1 + direction * dz) * m_zoom;
		//screen
		const int w = m_screen[0];
		const int h = m_screen[1];
		const float m = w < h ? w : h;
		const vec3 xp((2 * x1 - w) / m, (h - 2 * x2) / m, 0);
		//shift
		zoom(z_new);
		const vec3 xs_old = shift();
		const float s = fmax(xs[0], fmaxf(xs[1], xs[2]));
		shift(xs_old + s * (z_new - z_old) / z_new / z_old * m_rotation.conjugate().rotate(xp));
	}
	void Scene::callback_keyboard(char key, int x1, int x2)
	{
		if(key == 'd')
		{
			for(objects::Object* object : m_objects)
			{
				object->dot(!object->dot());
			}
		}
		else if(key == 's')
		{
			for(objects::Object* object : m_objects)
			{
				object->stroke(!object->stroke());
			}
		}
		else if(key == 'f')
		{
			for(objects::Object* object : m_objects)
			{
				object->fill(!object->fill());
			}
		}
		else if(key == 'r')
		{
			zoom(1.0f);
			shift(vec3());
			rotation(quat());
		}
		else if(key == 'x' || key == 'y' || key == 'z' || key == 'i') rotation(key);
	}
	void Scene::callback_mouse(canvas::button button, bool pressed, int x1, int x2)
	{
		if(pressed)
		{
			m_click.shift(m_shift);
			m_click.button(button);
			m_click.position(0, x1);
			m_click.position(1, x2);
			m_click.rotation(m_rotation);
		}
		else
		{
			m_click.button(canvas::button::none);
		}
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
	void Scene::setup_shaders(void)
	{
		setup_program(m_program_id[1], m_shaders_vertex_id[1], m_shaders_fragment_id[1], "shd/text.vert", "shd/text.frag");
		setup_program(m_program_id[0], m_shaders_vertex_id[0], m_shaders_fragment_id[0], "shd/model.vert", "shd/model.frag");
		glUseProgram(m_program_id[0]);
	}

	//camera
	float Scene::zoom(void) const
	{
		return m_zoom;
	}
	float Scene::zoom(float zoom)
	{
		glUniform1f(glGetUniformLocation(m_program_id[0], "zoom"), zoom);
		return m_zoom = zoom;
	}

	vec3 Scene::shift(void) const
	{
		return m_shift;
	}
	vec3 Scene::shift(const vec3& shift)
	{
		glUniform3f(glGetUniformLocation(m_program_id[0], "shift"), shift[0], shift[1], shift[2]);
		return m_shift = shift;
	}

	unsigned Scene::width(void) const
	{
		return m_screen[0];
	}
	unsigned Scene::height(void) const
	{
		return m_screen[1];
	}

	quat Scene::rotation(char mode)
	{
		if(mode == 'x')
		{
			return rotation(quat::view_x1());
		}
		else if(mode == 'y')
		{
			return rotation(quat::view_x2());
		}
		else if(mode == 'z')
		{
			return rotation(quat::view_x3());
		}
		else if(mode == 'i')
		{
			static unsigned index = 1;
			return rotation(quat::view_iso(index = (index + 1) % 3));
		}
		else
		{
			return quat();
		}
	}
	quat Scene::rotation(void) const
	{
		return m_rotation;
	}
	quat Scene::rotation(const quat& rotation)
	{
		glUniform4f(glGetUniformLocation(m_program_id[0], "rotation"), rotation[0], rotation[1], rotation[2], rotation[3]);
		return m_rotation = rotation;
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
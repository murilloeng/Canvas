#pragma once

//std
#include <string>
#include <vector>

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Math/quat.hpp"
#include "inc/Scene/Click.hpp"
#include "inc/Colors/Color.hpp"

namespace canvas
{
	namespace objects
	{
		class Object;
	}
	namespace vertices
	{
		class Vertex;
	}
}

namespace canvas
{
	class Scene
	{
	public:
		//constructors
		Scene(void);

		//destructor
		~Scene(void);

		//data
		Color background(Color);
		Color background(void) const;

		void box_min(float, float, float);
		void box_max(float, float, float);

		objects::Object* object(unsigned) const;
		const std::vector<objects::Object*>& objects(void) const;

		//draw
		void draw(void);
		void bound(void);
		void update(bool);
		void prepare(void);

		//objects
		void clear_objects(void);
		void add_object(objects::Object*);

		//callbacks
		void callback_motion(int, int);
		void callback_reshape(int, int);
		void callback_wheel(int, int, int);
		void callback_keyboard(char, int, int);
		void callback_mouse(button, bool, int, int);
		void callback_special(key, unsigned, int, int);

	private:
		//setup
		void setup_gl(void);
		void setup_buffers(void);
		void setup_shaders(void);

		//camera
		float zoom(float);
		float zoom(void) const;

		vec3 shift(void) const;
		vec3 shift(const vec3&);

		quat rotation(char);
		quat rotation(void) const;
		quat rotation(const quat&);

		unsigned width(void) const;
		unsigned height(void) const;

		//misc
		static bool load_file(std::string&, const char*);
		static void setup_shader(unsigned&, unsigned, unsigned, const char*);
		static void setup_program(unsigned&, unsigned&, unsigned&, const char*, const char*);

		//data
		float m_zoom;
		vec3 m_shift;
		vec3 m_box_min;
		vec3 m_box_max;
		quat m_rotation;
		unsigned m_screen[2];

		unsigned m_vao_id[2];
		unsigned m_vbo_id[2];
		unsigned m_ibo_id[3];
		unsigned m_vbo_size[2];
		unsigned m_ibo_size[3];
		unsigned* m_ibo_data[3];
		vertices::Vertex* m_vbo_data[2];

		Color m_background;
		unsigned m_program_id[2];
		unsigned m_shaders_vertex_id[2];
		unsigned m_shaders_fragment_id[2];

		Click m_click;
		std::vector<objects::Object*> m_objects;
	};
}
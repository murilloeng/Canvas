#pragma once

//std
#include <string>
#include <vector>

//canvas
#include "inc/Scene/Camera.hpp"
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

		Camera& camera(void);
		const Camera& camera(void) const;

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

	private:
		//setup
		void setup_gl(void);
		void setup_buffers(void);
		void setup_shaders(void);

		//misc
		static bool load_file(std::string&, const char*);
		static void setup_shader(unsigned&, unsigned, unsigned, const char*);
		static void setup_program(unsigned&, unsigned&, unsigned&, const char*, const char*);

		//data
		Camera m_camera;

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

		std::vector<objects::Object*> m_objects;
	};
}
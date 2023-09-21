#pragma once

//std
#include <string>
#include <vector>

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
	class Canvas
	{
	public:
		//constructors
		Canvas(void);

		//destructor
		~Canvas(void);

		//setup
		void setup_buffers(void);
		void setup_shaders(void);

		//draw
		void draw(void);
		void update(void);
		void prepare(void);

		//misc
		static bool load_file(std::string&, const char*);
		static void setup_shader(unsigned&, unsigned, unsigned, const char*);
		static void setup_program(unsigned&, unsigned&, unsigned&, const char*, const char*);

		//data
		unsigned m_vao_id[2];
		unsigned m_vbo_id[2];
		unsigned m_ibo_id[3];
		unsigned m_vbo_size[2];
		unsigned m_ibo_size[3];
		unsigned* m_ibo_data[3];
		vertices::Vertex* m_vbo_data[2];

		unsigned m_program_id[2];
		unsigned m_shaders_vertex_id[2];
		unsigned m_shaders_fragment_id[2];

		std::vector<objects::Object*> m_objects;
	};
}
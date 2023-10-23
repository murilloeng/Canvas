#pragma once

//ext
#include "ext/inc/GL/glew.h"

namespace canvas
{
	class Shader;
}

namespace canvas
{
	class Program
	{
	public:
		//constructors
		Program(void);

		//destructor
		~Program(void);

		//setup
		void setup(void);

	private:
		//data
		GLuint m_id;
		Shader* m_vertex_shader;
		Shader* m_compute_shader;
		Shader* m_geometry_shader;
		Shader* m_fragment_shader;
		Shader* m_tess_control_shader;
		Shader* m_tess_evaluation_shader;
	};
}
#pragma once

//std
#include <cstdint>

//ext
#include "external/cpp/inc/GL/glew.h"

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

		//data
		GLuint id(void) const;
		Shader* vertex_shader(void) const;
		Shader* compute_shader(void) const;
		Shader* geometry_shader(void) const;
		Shader* fragment_shader(void) const;
		Shader* tess_control_shader(void) const;
		Shader* tess_evaluation_shader(void) const;

		//setup
		void setup(void);
		void bind(void) const;
		static void unbind(void);

		//uniforms
		GLint uniform_location(const char*);
		
		void set_uniform(const char*, float);
		void set_uniform(const char*, float, float);
		void set_uniform(const char*, float, float, float);
		void set_uniform(const char*, float, float, float, float);

		void set_uniform(const char*, int32_t);
		void set_uniform(const char*, int32_t, int32_t);
		void set_uniform(const char*, int32_t, int32_t, int32_t);
		void set_uniform(const char*, int32_t, int32_t, int32_t, int32_t);

		void set_uniform(const char*, uint32_t);
		void set_uniform(const char*, uint32_t, uint32_t);
		void set_uniform(const char*, uint32_t, uint32_t, uint32_t);
		void set_uniform(const char*, uint32_t, uint32_t, uint32_t, uint32_t);

		void set_uniform(const char*, const float*, uint32_t);
		void set_uniform(const char*, const int32_t*, uint32_t);
		void set_uniform(const char*, const uint32_t*, uint32_t);
		void set_uniform_matrix(const char*, const float*, uint32_t);

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
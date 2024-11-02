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
		GLint uniform_location(const char*) const;

		void set_uniform(const char*, float) const;
		void set_uniform(const char*, float, float) const;
		void set_uniform(const char*, float, float, float) const;
		void set_uniform(const char*, float, float, float, float) const;

		void set_uniform(const char*, int32_t) const;
		void set_uniform(const char*, int32_t, int32_t) const;
		void set_uniform(const char*, int32_t, int32_t, int32_t) const;
		void set_uniform(const char*, int32_t, int32_t, int32_t, int32_t) const;

		void set_uniform(const char*, uint32_t) const;
		void set_uniform(const char*, uint32_t, uint32_t) const;
		void set_uniform(const char*, uint32_t, uint32_t, uint32_t) const;
		void set_uniform(const char*, uint32_t, uint32_t, uint32_t, uint32_t) const;

		void set_uniform(const char*, const float*, uint32_t) const;
		void set_uniform(const char*, const int32_t*, uint32_t) const;
		void set_uniform(const char*, const uint32_t*, uint32_t) const;
		void set_uniform_matrix(const char*, const float*, uint32_t) const;

	private:
		//check
		void check_uniform(const char*) const;
		void check_uniform_location(const char*, int32_t) const;

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
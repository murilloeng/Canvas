#pragma once

//std
#include <cstdint>

//ext
#include "external/cpp/inc/GL/glew.h"

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"
#include "Canvas/Canvas/inc/Math/mat4.hpp"

namespace canvas
{
	class Stage;
}

namespace canvas
{
	class Shader
	{
	public:
		//constructors
		Shader(void);

		//destructor
		~Shader(void);

		//data
		GLuint id(void) const;
		Stage* vertex_shader(void) const;
		Stage* compute_shader(void) const;
		Stage* geometry_shader(void) const;
		Stage* fragment_shader(void) const;
		Stage* tess_control_shader(void) const;
		Stage* tess_evaluation_shader(void) const;

		//GPU
		void setup(void);
		void bind(void) const;

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

		void set_uniform(const char*, vec3) const;
		void set_uniform(const char*, mat4) const;
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
		Stage* m_vertex_shader;
		Stage* m_compute_shader;
		Stage* m_geometry_shader;
		Stage* m_fragment_shader;
		Stage* m_tess_control_shader;
		Stage* m_tess_evaluation_shader;
	};
}
#pragma once

//std
#include <vector>
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
		Shader(std::vector<Stage*>);

		//destructor
		~Shader(void);

		//data
		GLuint id(void) const;

		//bind
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
	};
}
#pragma once

//std
#include <vector>
#include <cstdint>

//OpenGL
#ifdef _WIN32
#include <Windows.h>
#endif
#include <GL/gl.h>

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"
#include "Canvas/Canvas/inc/Math/mat4.hpp"

namespace canvas
{
	namespace shaders
	{
		class Stage;
	}
}

namespace canvas
{
	namespace shaders
	{
		class Shader
		{
		public:
			//constructors
			Shader(std::vector<Stage*>, const char* = "");

			//destructor
			~Shader(void);

			//bind
			void bind(void) const;

			//data
			GLuint id(void) const;

			const char* label(void) const;
			const char* label(const char*);

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
			char m_label[64];
		};
	}
}
#pragma once

//std
#include <cstdint>

namespace canvas
{
	class vec3;
	class vec4;
	class quat;
}

namespace canvas
{
	class mat4
	{
	public:
		//constructors
		mat4(void);
		mat4(float*);
		mat4(const mat4&);
		mat4(const float*);

		//destructor
		~mat4(void);

		//data
		float* data(void);
		const float* data(void) const;

		//linear
		void clear(void);
		void zeros(void);
		float norm(void) const;

		//print
		void print(const char* = "") const;

		//operators
		float& operator()(uint32_t);
		float& operator[](uint32_t);
		float& operator()(uint32_t, uint32_t);

		const float& operator()(uint32_t) const;
		const float& operator[](uint32_t) const;
		const float& operator()(uint32_t, uint32_t) const;

		mat4& operator=(const mat4&);

		mat4 operator+(void) const;
		mat4 operator-(void) const;
		vec3 operator*(const vec3&) const;
		vec4 operator*(const vec4&) const;
		mat4 operator*(const mat4&) const;
		mat4 operator+(const mat4&) const;
		mat4 operator-(const mat4&) const;

		mat4& operator*=(float);
		friend mat4 operator*(float, const mat4&);

		//affine
		static mat4 scaling(float);
		static mat4 scaling(const vec3&);
		static mat4 shifting(const vec3&);
		static mat4 rotation(const vec3&);
		static mat4 rotation(const quat&);
		static mat4 rotation(const vec3&, const vec3&);
		static mat4 rotation(const vec3&, const quat&);

	private:
		//data
		float m_data_mem[16];

		float* m_data_ptr;
		const float* m_data_ref;
	};
}
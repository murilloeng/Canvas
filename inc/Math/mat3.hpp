#pragma once

//std
#include <cstdint>

namespace canvas
{
	class vec2;
	class vec3;
}

namespace canvas
{
	class mat3
	{
	public:
		//constructors
		mat3(void);
		mat3(float*);
		mat3(const mat3&);
		mat3(const float*);

		//destructor
		~mat3(void);

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

		mat3& operator=(const mat3&);

		mat3 operator+(void) const;
		mat3 operator-(void) const;
		vec2 operator*(const vec2&) const;
		vec3 operator*(const vec3&) const;
		mat3 operator*(const mat3&) const;
		mat3 operator+(const mat3&) const;
		mat3 operator-(const mat3&) const;

		mat3& operator*=(float);
		friend mat3 operator*(float, const mat3&);

		//affine
		static mat3 scaling(float);
		static mat3 rotation(float);
		static mat3 scaling(const vec2&);
		static mat3 shifting(const vec2&);

	private:
		//data
		float m_data_mem[9];

		float* m_data_ptr;
		const float* m_data_ref;
	};
}
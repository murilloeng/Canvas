#pragma once

//std
#include <cstdint>

namespace canvas
{
	class vec2;
}

namespace canvas
{
	class mat2
	{
	public:
		//constructors
		mat2(void);
		mat2(float*);
		mat2(const mat2&);
		mat2(const float*);
		mat2(float, float, float, float);

		//destructor
		~mat2(void);

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

		mat2& operator=(const mat2&);

		mat2 operator+(void) const;
		mat2 operator-(void) const;
		vec2 operator*(const vec2&) const;
		mat2 operator*(const mat2&) const;
		mat2 operator+(const mat2&) const;
		mat2 operator-(const mat2&) const;

		mat2& operator*=(float);
		friend mat2 operator*(float, const mat2&);

		//affine
		static mat2 scaling(float);
		static mat2 rotation(float);
		static mat2 scaling(const vec2&);

	private:
		//data
		float m_data_mem[4];

		float* m_data_ptr;
		const float* m_data_ref;
	};
}
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
	class vec4
	{
	public:
		//constructors
		vec4(void);
		vec4(float);
		vec4(const float*);
		vec4(const vec3&, float = 1);
		vec4(float, float, float, float);

		//destructor
		~vec4(void);

		//reduction
		vec3 reduce(void) const;

		//data
		float* data(void);
		const float* data(void) const;
		
		//linear
		float norm(void) const;
		float inner(const vec4&) const;

		//print
		void print(const char* = "") const;

		//operators
		vec4& operator*=(float);
		vec4& operator/=(float);
		vec4& operator+=(const vec4&);
		vec4& operator-=(const vec4&);

		vec4& operator=(const vec2&);
		vec4& operator=(const vec3&);
		vec4& operator=(const vec4&);
		vec4& operator=(const float*);

		vec4 operator+(void) const;
		vec4 operator-(void) const;
		vec4 operator/(float) const;
		vec4 operator+(const vec4&) const;
		vec4 operator-(const vec4&) const;

		float& operator()(uint32_t);
		float& operator[](uint32_t);
		const float& operator()(uint32_t) const;
		const float& operator[](uint32_t) const;

		//friends
		friend vec4 operator*(float, const vec4&);

	private:
		//data
		float m_data[4];
	};
}
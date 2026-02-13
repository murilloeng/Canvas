#pragma once

//std
#include <cstdint>

namespace canvas
{
	class vec2;
	class vec4;
	class quat;
	class mat4;
}

namespace canvas
{
	class vec3
	{
	public:
		//constructors
		vec3(void);
		vec3(const float*);
		vec3(const double*);
		vec3(float, float, float);

		//destructor
		~vec3(void);

		//data
		float* data(void);
		const float* data(void) const;

		//linear
		float norm(void) const;
		float inner(const vec3&) const;
		float min(uint32_t*, bool) const;
		float max(uint32_t*, bool) const;

		vec3 unit(void) const;
		mat4 shift(void) const;
		vec3 normal(void) const;
		quat quaternion(void) const;
		vec3 cross(const vec3&) const;
		void triad(vec3&, vec3&) const;

		//operators
		vec3& operator*=(float);
		vec3& operator/=(float);
		vec3& operator+=(const vec3&);
		vec3& operator-=(const vec3&);
		vec3& operator*=(const mat4&);

		vec3& operator=(const vec2&);
		vec3& operator=(const vec3&);
		vec3& operator=(const float*);

		vec3 operator+(void) const;
		vec3 operator-(void) const;
		vec3 operator/(float) const;
		vec3 operator+(const vec3&) const;
		vec3 operator-(const vec3&) const;

		float& operator()(uint32_t);
		float& operator[](uint32_t);
		const float& operator()(uint32_t) const;
		const float& operator[](uint32_t) const;

		//print
		void print(const char* = "", bool = false) const;

		//friends
		friend vec3 operator*(float, const vec3&);

	private:
		//data
		float m_data[3];

		//friends
		friend class vec4;
	};
}
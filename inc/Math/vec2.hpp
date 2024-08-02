#pragma once

//std
#include <cstdint>

namespace canvas
{
	class vec2
	{
	public:
		//constructors
		vec2(void);
		vec2(const float*);
		vec2(float, float);

		//destructor
		~vec2(void);

		//data
		float* data(void);
		const float* data(void) const;

		//print
		void print(const char* = "") const;

		//linear
		vec2 unit(void) const;
		float norm(void) const;
		float inner(const vec2&) const;
		float cross(const vec2&) const;
		float min(uint32_t*, bool) const;
		float max(uint32_t*, bool) const;

		//operators
		vec2& operator*=(float);
		vec2& operator/=(float);
		vec2& operator+=(const vec2&);
		vec2& operator-=(const vec2&);

		vec2& operator=(const vec2&);
		vec2& operator=(const float*);

		vec2 operator+(void) const;
		vec2 operator-(void) const;
		vec2 operator/(float) const;
		vec2 operator+(const vec2&) const;
		vec2 operator-(const vec2&) const;

		float& operator()(uint32_t);
		float& operator[](uint32_t);
		const float& operator()(uint32_t) const;
		const float& operator[](uint32_t) const;

		//friends
		friend vec2 operator*(float, const vec2&);

	private:
		//data
		float m_data[2];
	};
}
#pragma once

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
		float* memory(void);
		const float* memory(void) const;

		//linear
		vec2 unit(void) const;
		float norm(void) const;
		float inner(const vec2&) const;
		float min(unsigned*, bool) const;
		float max(unsigned*, bool) const;

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

		float& operator()(unsigned);
		float& operator[](unsigned);
		const float& operator()(unsigned) const;
		const float& operator[](unsigned) const;

		//friends
		friend vec2 operator*(float, const vec2&);

	private:
		//data
		float m_data[2];
	};
}
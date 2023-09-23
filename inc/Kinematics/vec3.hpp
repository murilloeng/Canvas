#pragma once

namespace canvas
{
	class vec3
	{
	public:
		//constructors
		vec3(void);
		vec3(const float*);
		vec3(float, float, float);

		//destructor
		~vec3(void);

		//data
		float* memory(void);
		const float* memory(void) const;

		//operators
		vec3& operator*=(float);
		vec3& operator/=(float);
		vec3& operator+=(const vec3&);
		vec3& operator-=(const vec3&);

		vec3 operator+(void) const;
		vec3 operator-(void) const;
		vec3 operator/(float) const;
		vec3 operator+(const vec3&) const;
		vec3 operator-(const vec3&) const;

		float& operator()(unsigned);
		float& operator[](unsigned);
		const float& operator()(unsigned) const;
		const float& operator[](unsigned) const;

	private:
		//data
		float m_data[3];
	};
}
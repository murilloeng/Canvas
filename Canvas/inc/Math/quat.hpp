#pragma once

//std
#include <cstdint>

namespace canvas
{
	class vec3;
	class mat4;
}

namespace canvas
{
	class quat
	{
	public:
		//constructors
		quat(void);
		quat(const float*);
		quat(const double*);
		quat(vec3, vec3, vec3);
		quat(float, float, float, float);
		quat(double, double, double, double);

		//destructor
		~quat(void);

		//data
		float* data(void);
		const float* data(void) const;

		//print
		void print(const char* = "") const;

		//views
		static quat view_x1(void);
		static quat view_x2(void);
		static quat view_x3(void);
		static quat view_iso(uint32_t);

		//operators
		quat& operator*=(const quat&);
		quat operator*(const quat&) const;

		float& operator()(uint32_t);
		float& operator[](uint32_t);
		const float& operator()(uint32_t) const;
		const float& operator[](uint32_t) const;

		//algebra
		float angle(void) const;
		vec3 vector(void) const;

		//group
		mat4 rotation(void) const;
		quat conjugate(void) const;
		vec3 rotate(const vec3&) const;
		vec3 conjugate(const vec3&) const;
		quat conjugate(const quat&) const;
		quat slerp(const quat&, float) const;

	private:
		//data
		float m_data[4];
	};
}
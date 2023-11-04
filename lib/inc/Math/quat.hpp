#pragma once

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
		quat(float, float, float, float);

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
		static quat view_iso(unsigned);

		//operators
		quat& operator*=(const quat&);
		quat operator*(const quat&) const;

		float& operator()(unsigned);
		float& operator[](unsigned);
		const float& operator()(unsigned) const;
		const float& operator[](unsigned) const;

		//affine
		mat4 rotation(void) const;
		quat conjugate(void) const;
		vec3 rotate(const vec3&) const;
		vec3 conjugate(const vec3&) const;

	private:
		//data
		float m_data[4];
	};
}
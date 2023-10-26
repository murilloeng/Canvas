#pragma once

namespace canvas
{
	class vec3;
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
		float* memory(void);
		const float* memory(void) const;

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
		quat conjugate(void) const;
		vec3 rotate(const vec3&) const;
		vec3 conjugate(const vec3&) const;

	private:
		//data
		float m_data[4];
	};
}
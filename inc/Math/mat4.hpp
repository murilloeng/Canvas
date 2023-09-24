#pragma once

namespace canvas
{
	class vec3;
	class quat;
}

namespace canvas
{
	class mat4
	{
	public:
		//constructors
		mat4(void);

		//destructor
		~mat4(void);

		//operators
		float& operator()(unsigned);
		float& operator[](unsigned);
		float& operator()(unsigned, unsigned);

		const float& operator()(unsigned) const;
		const float& operator[](unsigned) const;
		const float& operator()(unsigned, unsigned) const;

		vec3 operator*(const vec3&) const;
		mat4 operator*(const mat4&) const;

		//affine
		static mat4 scaling(float);
		static mat4 scaling(const vec3&);
		static mat4 rotation(const vec3&);
		static mat4 rotation(const quat&);
		static mat4 translation(const vec3&);

		static mat4 rotation(const vec3&, const vec3&);
		static mat4 rotation(const vec3&, const quat&);

	private:
		//data
		float m_data[16];
	};
}
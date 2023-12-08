//std
#include <cmath>
#include <cstdio>
#include <cstring>

//canvas
#include "Canvas/lib/inc/Math/vec3.hpp"
#include "Canvas/lib/inc/Math/quat.hpp"
#include "Canvas/lib/inc/Math/mat4.hpp"

namespace canvas
{
	//constructors
	quat::quat(void) : m_data{1.0f, 0.0f, 0.0f, 0.0f}
	{
		return;
	}
	quat::quat(const float* q) : m_data{q[0], q[1], q[2], q[3]}
	{
		return;
	}
	quat::quat(float q0, float q1, float q2, float q3) : m_data{q0, q1, q2, q3}
	{
		return;
	}

	//destructor
	quat::~quat(void)
	{
		return;
	}

	//data
	float* quat::data(void)
	{
		return m_data;
	}
	const float* quat::data(void) const
	{
		return m_data;
	}

	//print
	void quat::print(const char* label) const
	{
		if(strlen(label) != 0)
		{
			printf("%s\n", label);
		}
		for(unsigned i = 0; i < 4; i++)
		{
			printf("%+.2e\n", m_data[i]);
		}
	}

	//views
	quat quat::view_x1(void)
	{
		return vec3(0, 0, -M_PI_2).quaternion() * vec3(0, -M_PI_2, 0).quaternion();
	}
	quat quat::view_x2(void)
	{
		return vec3(0, 0, +M_PI_2).quaternion() * vec3(+M_PI_2, 0, 0).quaternion();
	}
	quat quat::view_x3(void)
	{
		return quat();
	}
	quat quat::view_iso(unsigned index)
	{
		switch(index)
		{
			case 0:
				return vec3(atan(M_SQRT1_2), 0, 0).quaternion() * vec3(0, -M_PI_4, 0).quaternion() * view_x2();
			case 1:
				return vec3(atan(M_SQRT1_2), 0, 0).quaternion() * vec3(0, -M_PI_4, 0).quaternion() * view_x3();
			case 2:
				return vec3(atan(M_SQRT1_2), 0, 0).quaternion() * vec3(0, -M_PI_4, 0).quaternion() * view_x1();
			default:
				return quat();
		}
	}

	//operators
	quat& quat::operator*=(const quat& q)
	{
		return *this = q * *this;
	}
	quat quat::operator*(const quat& q) const
	{
		quat r;
		r.m_data[0] = m_data[0] * q.m_data[0] - m_data[1] * q.m_data[1] - m_data[2] * q.m_data[2] - m_data[3] * q.m_data[3];
		r.m_data[1] = m_data[0] * q.m_data[1] + m_data[1] * q.m_data[0] + m_data[2] * q.m_data[3] - m_data[3] * q.m_data[2];
		r.m_data[2] = m_data[0] * q.m_data[2] + m_data[2] * q.m_data[0] + m_data[3] * q.m_data[1] - m_data[1] * q.m_data[3];
		r.m_data[3] = m_data[0] * q.m_data[3] + m_data[3] * q.m_data[0] + m_data[1] * q.m_data[2] - m_data[2] * q.m_data[1];
		return r;
	}

	float& quat::operator()(unsigned index)
	{
		return m_data[index];
	}
	float& quat::operator[](unsigned index)
	{
		return m_data[index];
	}
	const float& quat::operator()(unsigned index) const
	{
		return m_data[index];
	}
	const float& quat::operator[](unsigned index) const
	{
		return m_data[index];
	}

	//affine
	mat4 quat::rotation(void) const
	{
		//data
		mat4 M;
		const vec3 x(m_data + 1);
		const float s = m_data[0];
		const float a = s * s - x.inner(x);
		//rotation
		M[0 + 4 * 0] = a + 2 * x[0] * x[0];
		M[1 + 4 * 1] = a + 2 * x[1] * x[1];
		M[2 + 4 * 2] = a + 2 * x[2] * x[2];
		M[0 + 4 * 1] = 2 * x[0] * x[1] - 2 * s * x[2];
		M[0 + 4 * 2] = 2 * x[0] * x[2] + 2 * s * x[1];
		M[1 + 4 * 0] = 2 * x[0] * x[1] + 2 * s * x[2];
		M[1 + 4 * 2] = 2 * x[1] * x[2] - 2 * s * x[0];
		M[2 + 4 * 0] = 2 * x[0] * x[2] - 2 * s * x[1];
		M[2 + 4 * 1] = 2 * x[1] * x[2] + 2 * s * x[0];
		//return
		return M;
	}
	quat quat::conjugate(void) const
	{
		return quat(m_data[0], -m_data[1], -m_data[2], -m_data[3]);
	}
	vec3 quat::rotate(const vec3& v) const
	{
		vec3 r;
		const vec3 x(m_data + 1);
		const float s = m_data[0];
		const float b = 2 * x.inner(v);
		const float a = s * s - x.inner(x);
		r[0] = a * v[0] + b * x[0] + 2 * s * (x[1] * v[2] - x[2] * v[1]);
		r[1] = a * v[1] + b * x[1] + 2 * s * (x[2] * v[0] - x[0] * v[2]);
		r[2] = a * v[2] + b * x[2] + 2 * s * (x[0] * v[1] - x[1] * v[0]);
		return r;
	}
	vec3 quat::conjugate(const vec3& v) const
	{
		return conjugate().rotate(v);
	}
}
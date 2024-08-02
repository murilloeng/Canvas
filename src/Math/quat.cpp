//std
#include <cmath>
#include <cstdio>
#include <cstring>

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Math/quat.hpp"
#include "Canvas/inc/Math/mat4.hpp"

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
	quat::quat(const double* q) : m_data{(float) q[0], (float) q[1], (float) q[2], (float) q[3]}
	{
		return;
	}
	quat::quat(vec3 s1, vec3 s2, vec3 s3)
	{
		const float d0 = s1[0];
		const float d1 = s2[1];
		const float d2 = s3[2];
		const float tr = d0 + d1 + d2;
		if(tr >= d0 && tr >= d1 && tr >= d2)
		{
			m_data[0] = sqrtf(1 + tr) / 2;
			m_data[1] = (s2[2] - s3[1]) / (4 * m_data[0]);
			m_data[2] = (s3[0] - s1[2]) / (4 * m_data[0]);
			m_data[3] = (s1[1] - s2[0]) / (4 * m_data[0]);
		}
		else if(d0 >= d1 && d0 >= d2)
		{
			m_data[1] = sqrtf(1 - tr + 2 * d0) / 2;
			m_data[0] = (s2[2] - s3[1]) / (4 * m_data[1]);
			m_data[2] = (s2[0] + s1[1]) / (4 * m_data[1]);
			m_data[3] = (s3[0] + s1[2]) / (4 * m_data[1]);
		}
		else if(d1 >= d2)
		{
			m_data[2] = sqrtf(1 - tr + 2 * d1) / 2;
			m_data[0] = (s3[0] - s1[2]) / (4 * m_data[2]);
			m_data[1] = (s2[0] + s1[1]) / (4 * m_data[2]);
			m_data[3] = (s3[1] + s2[2]) / (4 * m_data[2]);
		}
		else
		{
			m_data[3] = sqrtf(1 - tr + 2 * d2) / 2;
			m_data[0] = (s1[1] - s2[0]) / (4 * m_data[3]);
			m_data[1] = (s3[0] + s1[2]) / (4 * m_data[3]);
			m_data[2] = (s3[1] + s2[2]) / (4 * m_data[3]);
		}
	}
	quat::quat(float q0, float q1, float q2, float q3) : m_data{q0, q1, q2, q3}
	{
		return;
	}
	quat::quat(double q0, double q1, double q2, double q3) : m_data{(float) q0, (float) q1, (float) q2, (float) q3}
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
		return vec3(0, 0, -float(M_PI_2)).quaternion() * vec3(0, -float(M_PI_2), 0).quaternion();
	}
	quat quat::view_x2(void)
	{
		return vec3(0, 0, +float(M_PI_2)).quaternion() * vec3(+float(M_PI_2), 0, 0).quaternion();
	}
	quat quat::view_x3(void)
	{
		return quat();
	}
	quat quat::view_iso(unsigned index)
	{
		//data
		const float t = float(M_PI_4);
		const float a = float(M_SQRT1_2);
		//view
		switch(index)
		{
			case 0:
				return vec3(atanf(a), 0, 0).quaternion() * vec3(0, -t, 0).quaternion() * view_x2();
			case 1:
				return vec3(atanf(a), 0, 0).quaternion() * vec3(0, -t, 0).quaternion() * view_x3();
			case 2:
				return vec3(atanf(a), 0, 0).quaternion() * vec3(0, -t, 0).quaternion() * view_x1();
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
	vec3 quat::vector(void) const
	{
		//data
		const float t = 2 * acosf(m_data[0]);
		//vector
		if(t == 0)
		{
			return vec3(0, 0, 0);
		}
		else
		{
			return t / sinf(t / 2) * vec3(m_data[1], m_data[2], m_data[3]);
		}
	}
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
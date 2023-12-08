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
	mat4::mat4(void) : m_data{
			1.0f, 0.0f, 0.0f, 0.0f, 
			0.0f, 1.0f, 0.0f, 0.0f, 
			0.0f, 0.0f, 1.0f, 0.0f, 
			0.0f, 0.0f, 0.0f, 1.0f}
	{
		return;
	}

	//destructor
	mat4::~mat4(void)
	{
		return;
	}

	//data
	float* mat4::data(void)
	{
		return m_data;
	}
	const float* mat4::data(void) const
	{
		return m_data;
	}

	//linear
	float mat4::norm(void) const
	{
		float v = 0;
		for(unsigned i = 0; i < 16; i++)
		{
			v += m_data[i] * m_data[i];
		}
		return sqrtf(v);
	}

	//print
	void mat4::print(const char* label) const
	{
		if(strlen(label) != 0)
		{
			printf("%s\n", label);
		}
		for(unsigned i = 0; i < 4; i++)
		{
			for(unsigned j = 0; j < 4; j++)
			{
				printf("%+.2e ", m_data[i + 4 * j]);
			}
			printf("\n");
		}
	}

	//operators
	float& mat4::operator()(unsigned i)
	{
		return m_data[i];
	}
	float& mat4::operator[](unsigned i)
	{
		return m_data[i];
	}
	float& mat4::operator()(unsigned i, unsigned j)
	{
		return m_data[i + 4 * j];
	}
	const float& mat4::operator()(unsigned i) const
	{
		return m_data[i];
	}
	const float& mat4::operator[](unsigned i) const
	{
		return m_data[i];
	}
	const float& mat4::operator()(unsigned i, unsigned j) const
	{
		return m_data[i + 4 * j];
	}

	mat4 mat4::operator+(void) const
	{
		return *this;
	}
	mat4 mat4::operator-(void) const
	{
		return mat4(*this) *= -1;
	}
	vec3 mat4::operator*(const vec3& v) const
	{
		vec3 r;
		for(unsigned i = 0; i < 3; i++)
		{
			r[i] = m_data[i + 4 * 3];
			for(unsigned j = 0; j < 3; j++)
			{
				r[i] += m_data[i + 4 * j] * v[j];
			}
		}
		return r;
	}
	mat4 mat4::operator*(const mat4& M) const
	{
		mat4 r;
		for(unsigned i = 0; i < 4; i++)
		{
			for(unsigned j = 0; j < 4; j++)
			{
				r.m_data[i + 4 * j] = 0;
				for(unsigned k = 0; k < 4; k++)
				{
					r.m_data[i + 4 * j] += m_data[i + 4 * k] * M.m_data[k + 4 * j];
				}
			}
		}
		return r;
	}
	mat4 mat4::operator+(const mat4& M) const
	{
		mat4 A;
		for(unsigned i = 0; i < 16; i++)
		{
			A.m_data[i] = m_data[i] + M.m_data[i];
		}
		return A;
	}
	mat4 mat4::operator-(const mat4& M) const
	{
		mat4 A;
		for(unsigned i = 0; i < 16; i++)
		{
			A.m_data[i] = m_data[i] - M.m_data[i];
		}
		return A;
	}

	mat4& mat4::operator*=(float s)
	{
		for(unsigned i = 0; i < 16; i++)
		{
			m_data[i] *= s;
		}
		return *this;
	}
	mat4 operator*(float s, const mat4& M)
	{
		return mat4(M) *= s;
	}

	//affine
	mat4 mat4::scaling(float s)
	{
		return scaling({s, s, s});
	}
	mat4 mat4::scaling(const vec3& s)
	{
		mat4 A;
		A.m_data[0 + 4 * 0] = s[0];
		A.m_data[1 + 4 * 1] = s[1];
		A.m_data[2 + 4 * 2] = s[2];
		return A;
	}
	mat4 mat4::rotation(const vec3& v)
	{
		return rotation(v.quaternion());
	}
	mat4 mat4::rotation(const quat& q)
	{
		mat4 A;
		A.m_data[1 + 4 * 2] = 2 * (q[2] * q[3] - q[0] * q[1]);
		A.m_data[2 + 4 * 1] = 2 * (q[2] * q[3] + q[0] * q[1]);
		A.m_data[2 + 4 * 0] = 2 * (q[1] * q[3] - q[0] * q[2]);
		A.m_data[0 + 4 * 2] = 2 * (q[1] * q[3] + q[0] * q[2]);
		A.m_data[0 + 4 * 1] = 2 * (q[1] * q[2] - q[0] * q[3]);
		A.m_data[1 + 4 * 0] = 2 * (q[1] * q[2] + q[0] * q[3]);
		A.m_data[0 + 4 * 0] = q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3];
		A.m_data[1 + 4 * 1] = q[0] * q[0] - q[1] * q[1] + q[2] * q[2] - q[3] * q[3];
		A.m_data[2 + 4 * 2] = q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3];
		return A;
	}
	mat4 mat4::shifting(const vec3& v)
	{
		mat4 A;
		A.m_data[0 + 4 * 3] = v[0];
		A.m_data[1 + 4 * 3] = v[1];
		A.m_data[2 + 4 * 3] = v[2];
		return A;
	}

	mat4 mat4::rotation(const vec3& xc, const vec3& tr)
	{
		return rotation(xc, tr.quaternion());
	}
	mat4 mat4::rotation(const vec3& xc, const quat& qr)
	{
		return mat4::shifting(+xc) * mat4::rotation(qr) * mat4::shifting(-xc);
	}
}
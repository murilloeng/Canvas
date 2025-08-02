//std
#include <cmath>
#include <cstdio>
#include <cfloat>
#include <cstring>

//canvas
#include "Canvas/Canvas/inc/Math/vec2.hpp"
#include "Canvas/Canvas/inc/Math/vec3.hpp"
#include "Canvas/Canvas/inc/Math/vec4.hpp"

namespace canvas
{
	//constructors
	vec4::vec4(void) : m_data{0.0f, 0.0f, 0.0f, 0.0f}
	{
		return;
	}
	vec4::vec4(float s) : m_data{s, s, s, s}
	{
		return;
	}
	vec4::vec4(const float* x) : m_data{x[0], x[1], x[2], x[3]}
	{
		return;
	}
	vec4::vec4(float x1, float x2, float x3, float x4) : m_data{x1, x2, x3, x4}
	{
		return;
	}

	//destructor
	vec4::~vec4(void)
	{
		return;
	}

	//data
	float* vec4::data(void)
	{
		return m_data;
	}
	const float* vec4::data(void) const
	{
		return m_data;
	}

	//print
	void vec4::print(const char* label) const
	{
		if(strlen(label) != 0)
		{
			printf("%s\n", label);
		}
		for(uint32_t i = 0; i < 4; i++)
		{
			printf("%+.2e\n", m_data[i]);
		}
	}

	//linear
	float vec4::norm(void) const
	{
		return sqrtf(inner(*this));
	}
	float vec4::inner(const vec4& v) const
	{
		return
			m_data[0] * v.m_data[0] +
			m_data[1] * v.m_data[1] +
			m_data[2] * v.m_data[2] +
			m_data[3] * v.m_data[3];
	}

	//operators
	vec4& vec4::operator*=(float s)
	{
		m_data[0] *= s;
		m_data[1] *= s;
		m_data[2] *= s;
		m_data[3] *= s;
		return *this;
	}
	vec4& vec4::operator/=(float s)
	{
		m_data[0] /= s;
		m_data[1] /= s;
		m_data[2] /= s;
		m_data[3] /= s;
		return *this;
	}
	vec4& vec4::operator+=(const vec4& p)
	{
		m_data[0] += p.m_data[0];
		m_data[1] += p.m_data[1];
		m_data[2] += p.m_data[2];
		m_data[3] += p.m_data[3];
		return *this;
	}
	vec4& vec4::operator-=(const vec4& p)
	{
		m_data[0] -= p.m_data[0];
		m_data[1] -= p.m_data[1];
		m_data[2] -= p.m_data[2];
		m_data[3] -= p.m_data[3];
		return *this;
	}

	vec4& vec4::operator=(const vec2& v)
	{
		m_data[2] = 0;
		m_data[3] = 1;
		m_data[0] = v.m_data[0];
		m_data[1] = v.m_data[1];
		return *this;
	}
	vec4& vec4::operator=(const vec3& v)
	{
		m_data[3] = 1;
		m_data[0] = v.m_data[0];
		m_data[1] = v.m_data[1];
		m_data[2] = v.m_data[2];
		return *this;
	}
	vec4& vec4::operator=(const vec4& v)
	{
		memcpy(m_data, v.m_data, 4 * sizeof(float));
		return *this;
	}
	vec4& vec4::operator=(const float* data)
	{
		memcpy(m_data, data, 3 * sizeof(float));
		return *this;
	}

	vec4 vec4::operator+(void) const
	{
		return vec4(m_data);
	}
	vec4 vec4::operator-(void) const
	{
		return vec4(m_data) *= -1;
	}
	vec4 vec4::operator/(float s) const
	{
		return vec4(m_data) /= s;
	}
	vec4 vec4::operator+(const vec4& p) const
	{
		return vec4(m_data) += p;
	}
	vec4 vec4::operator-(const vec4& p) const
	{
		return vec4(m_data) -= p;
	}

	float& vec4::operator()(uint32_t index)
	{
		return m_data[index];
	}
	float& vec4::operator[](uint32_t index)
	{
		return m_data[index];
	}
	const float& vec4::operator()(uint32_t index) const
	{
		return m_data[index];
	}
	const float& vec4::operator[](uint32_t index) const
	{
		return m_data[index];
	}

	//friends
	vec4 operator*(float s, const vec4& v)
	{
		return vec4(v.m_data) *= s;
	}
}
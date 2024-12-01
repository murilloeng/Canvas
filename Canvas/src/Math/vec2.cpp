//std
#include <cmath>
#include <cfloat>
#include <cstdio>
#include <cstring>

//canvas
#include "Canvas/Canvas/inc/Math/vec2.hpp"

namespace canvas
{
	//constructors
	vec2::vec2(void) : m_data{0.0f, 0.0f}
	{
		return;
	}
	vec2::vec2(const float* x) : m_data{x[0], x[1]}
	{
		return;
	}
	vec2::vec2(float x1, float x2) : m_data{x1, x2}
	{
		return;
	}

	//destructor
	vec2::~vec2(void)
	{
		return;
	}

	//data
	float* vec2::data(void)
	{
		return m_data;
	}
	const float* vec2::data(void) const
	{
		return m_data;
	}

	//print
	void vec2::print(const char* label) const
	{
		if(strlen(label) != 0)
		{
			printf("%s\n", label);
		}
		for(uint32_t i = 0; i < 2; i++)
		{
			printf("%+.2e\n", m_data[i]);
		}
	}

	//linear
	vec2 vec2::unit(void) const
	{
		return *this / norm();
	}
	float vec2::norm(void) const
	{
		return sqrtf(inner(*this));
	}
	float vec2::inner(const vec2& v) const
	{
		return m_data[0] * v.m_data[0] + m_data[1] * v.m_data[1];
	}
	float vec2::cross(const vec2& v) const
	{
		return m_data[0] * v.m_data[1] - m_data[1] * v.m_data[0];
	}
	float vec2::min(uint32_t* index, bool abs) const
	{
		float min = +FLT_MAX;
		for(uint32_t i = 0; i < 2; i++)
		{
			if(min > (abs ? fabsf(m_data[i]) : m_data[i]))
			{
				if(index) *index = i;
				min = abs ? fabsf(m_data[i]) : m_data[i];
			}
		}
		return min;
	}
	float vec2::max(uint32_t* index, bool abs) const
	{
		float max = -FLT_MAX;
		for(uint32_t i = 0; i < 2; i++)
		{
			if(max < (abs ? fabsf(m_data[i]) : m_data[i]))
			{
				if(index) *index = i;
				max = abs ? fabsf(m_data[i]) : m_data[i];
			}
		}
		return max;
	}

	//operators
	vec2& vec2::operator*=(float s)
	{
		m_data[0] *= s;
		m_data[1] *= s;
		return *this;
	}
	vec2& vec2::operator/=(float s)
	{
		m_data[0] /= s;
		m_data[1] /= s;
		return *this;
	}
	vec2& vec2::operator+=(const vec2& p)
	{
		m_data[0] += p.m_data[0];
		m_data[1] += p.m_data[1];
		return *this;
	}
	vec2& vec2::operator-=(const vec2& p)
	{
		m_data[0] -= p.m_data[0];
		m_data[1] -= p.m_data[1];
		return *this;
	}

	vec2& vec2::operator=(const vec2& v)
	{
		m_data[0] = v.m_data[0];
		m_data[1] = v.m_data[1];
		return *this;
	}
	vec2& vec2::operator=(const float* data)
	{
		m_data[0] = data[0];
		m_data[1] = data[1];
		return *this;
	}

	vec2 vec2::operator+(void) const
	{
		return vec2(m_data);
	}
	vec2 vec2::operator-(void) const
	{
		return vec2(m_data) *= -1;
	}
	vec2 vec2::operator/(float s) const
	{
		return vec2(m_data) /= s;
	}
	vec2 vec2::operator+(const vec2& p) const
	{
		return vec2(m_data) += p;
	}
	vec2 vec2::operator-(const vec2& p) const
	{
		return vec2(m_data) -= p;
	}

	float& vec2::operator()(uint32_t index)
	{
		return m_data[index];
	}
	float& vec2::operator[](uint32_t index)
	{
		return m_data[index];
	}
	const float& vec2::operator()(uint32_t index) const
	{
		return m_data[index];
	}
	const float& vec2::operator[](uint32_t index) const
	{
		return m_data[index];
	}

	//friends
	vec2 operator*(float s, const vec2& v)
	{
		return vec2(v.m_data) *= s;
	}
}
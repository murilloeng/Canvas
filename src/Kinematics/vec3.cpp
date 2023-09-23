//std
#include <cstring>

//canvas
#include "inc/Kinematics/vec3.hpp"

namespace canvas
{
	//constructors
	vec3::vec3(void) : m_data{0.0f, 0.0f, 0.0f}
	{
		return;
	}
	vec3::vec3(const float* x) : m_data{x[0], x[1], x[2]}
	{
		return;
	}
	vec3::vec3(float x1, float x2, float x3) : m_data{x1, x2, x3}
	{
		return;
	}

	//destructor
	vec3::~vec3(void)
	{
		return;
	}

	//data
	float* vec3::memory(void)
	{
		return m_data;
	}
	const float* vec3::memory(void) const
	{
		return m_data;
	}

	//operators
	vec3& vec3::operator*=(float s)
	{
		m_data[0] *= s;
		m_data[1] *= s;
		m_data[2] *= s;
		return *this;
	}
	vec3& vec3::operator/=(float s)
	{
		m_data[0] /= s;
		m_data[1] /= s;
		m_data[2] /= s;
		return *this;
	}
	vec3& vec3::operator+=(const vec3& p)
	{
		m_data[0] += p.m_data[0];
		m_data[1] += p.m_data[1];
		m_data[2] += p.m_data[2];
		return *this;
	}
	vec3& vec3::operator-=(const vec3& p)
	{
		m_data[0] -= p.m_data[0];
		m_data[1] -= p.m_data[1];
		m_data[2] -= p.m_data[2];
		return *this;
	}

	vec3 vec3::operator+(void) const
	{
		return vec3(m_data);
	}
	vec3 vec3::operator-(void) const
	{
		return vec3(m_data) *= -1;
	}
	vec3 vec3::operator/(float s) const
	{
		return vec3(m_data) /= s;
	}
	vec3 vec3::operator+(const vec3& p) const
	{
		return vec3(m_data) += p;
	}
	vec3 vec3::operator-(const vec3& p) const
	{
		return vec3(m_data) -= p;
	}

	float& vec3::operator()(unsigned index)
	{
		return m_data[index];
	}
	float& vec3::operator[](unsigned index)
	{
		return m_data[index];
	}
	const float& vec3::operator()(unsigned index) const
	{
		return m_data[index];
	}
	const float& vec3::operator[](unsigned index) const
	{
		return m_data[index];
	}
}
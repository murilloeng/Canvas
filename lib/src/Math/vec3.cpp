//std
#include <cmath>
#include <cfloat>
#include <cstring>

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Math/quat.hpp"
#include "inc/Math/mat4.hpp"

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

	//linear
	float vec3::norm(void) const
	{
		return sqrtf(inner(*this));
	}
	float vec3::inner(const vec3& v) const
	{
		return 
			m_data[0] * v.m_data[0] + 
			m_data[1] * v.m_data[1] + 
			m_data[2] * v.m_data[2];
	}
	float vec3::min(unsigned* index, bool abs) const
	{
		double min = +FLT_MAX;
		for(unsigned i = 0; i < 3; i++)
		{
			if(min > (abs ? fabsf(m_data[i]) : m_data[i]))
			{
				if(index) *index = i;
				min = abs ? fabsf(m_data[i]) : m_data[i];
			}
		}
		return min;
	}
	float vec3::max(unsigned* index, bool abs) const
	{
		double max = -FLT_MAX;
		for(unsigned i = 0; i < 3; i++)
		{
			if(max < (abs ? fabsf(m_data[i]) : m_data[i]))
			{
				if(index) *index = i;
				max = abs ? fabsf(m_data[i]) : m_data[i];
			}
		}
		return max;
	}

	vec3 vec3::unit(void) const
	{
		return *this / norm();
	}
	mat4 vec3::shift(void) const
	{
		//data
		mat4 M;
		//shift
		M[0 + 4 * 3] = m_data[0];
		M[1 + 4 * 3] = m_data[1];
		M[2 + 4 * 3] = m_data[2];
		//return
		return M;
	}
	quat vec3::quaternion(void) const
	{
		//angle
		const float t = norm();
		const float c = cosf(t / 2);
		const float s = t ? sinf(t / 2) / t : 0.5;
		//setup
		quat q;
		q[0] = c;
		q[1] = s * m_data[0];
		q[2] = s * m_data[1];
		q[3] = s * m_data[2];
		return q;
	}
	vec3 vec3::cross(const vec3& v) const
	{
		return {
			m_data[1] * v.m_data[2] - m_data[2] * v.m_data[1],
			m_data[2] * v.m_data[0] - m_data[0] * v.m_data[2],
			m_data[0] * v.m_data[1] - m_data[1] * v.m_data[0]
		};
	}
	void vec3::triad(vec3& t2, vec3& t3) const
	{
		//data
		unsigned index;
		min(&index, true);
		const unsigned k1 = (index + 1) % 3;
		const unsigned k2 = (index + 2) % 3;
		const unsigned k3 = (index + 0) % 3;
		//triad
		t2[k3] = 0;
		t2[k1] = -m_data[k2] / sqrtf(m_data[k1] * m_data[k1] + m_data[k2] * m_data[k2]);
		t2[k2] = +m_data[k1] / sqrtf(m_data[k1] * m_data[k1] + m_data[k2] * m_data[k2]);
		//cross
		t3 = cross(t2);
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
	vec3& vec3::operator*=(const mat4& A)
	{
		return *this = A * *this;
	}

	vec3& vec3::operator=(const vec3& v)
	{
		memcpy(m_data, v.m_data, 3 * sizeof(float));
		return *this;
	}
	vec3& vec3::operator=(const float* data)
	{
		memcpy(m_data, data, 3 * sizeof(float));
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

	//friends
	vec3 operator*(float s, const vec3& v)
	{
		return vec3(v.m_data) *= s;
	}
}
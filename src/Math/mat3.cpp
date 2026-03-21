//std
#include <cmath>
#include <cstdio>
#include <cstring>

//canvas
#include "Canvas/inc/Math/vec2.hpp"
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Math/vec4.hpp"
#include "Canvas/inc/Math/quat.hpp"
#include "Canvas/inc/Math/mat3.hpp"

namespace canvas
{
	//constructors
	mat3::mat3(void) : m_data_mem{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f}, m_data_ptr{m_data_mem}, m_data_ref{m_data_mem}
	{
		return;
	}
	mat3::mat3(float* data_ptr) : m_data_ptr{data_ptr}, m_data_ref{data_ptr}
	{
		return;
	}
	mat3::mat3(const mat3& M) : m_data_ptr{m_data_mem}, m_data_ref{m_data_mem}
	{
		memcpy(m_data_ptr, M.m_data_ref, 9 * sizeof(float));
	}
	mat3::mat3(const float* data_ref) : m_data_ptr{nullptr}, m_data_ref{data_ref}
	{
		return;
	}

	//destructor
	mat3::~mat3(void)
	{
		return;
	}

	//data
	float* mat3::data(void)
	{
		return m_data_ptr;
	}
	const float* mat3::data(void) const
	{
		return m_data_ref;
	}

	//linear
	void mat3::clear(void)
	{
		for(uint32_t i = 0; i < 3; i++)
		{
			for(uint32_t j = 0; j < 3; j++)
			{
				m_data_ptr[i + 3 * j] = i == j;
			}
		}
	}
	void mat3::zeros(void)
	{
		memset(m_data_ptr, 0, 9 * sizeof(float));
	}
	float mat3::norm(void) const
	{
		float v = 0;
		for(uint32_t i = 0; i < 9; i++)
		{
			v += m_data_ref[i] * m_data_ref[i];
		}
		return sqrtf(v);
	}

	//print
	void mat3::print(const char* label) const
	{
		if(strlen(label) != 0)
		{
			printf("%s\n", label);
		}
		for(uint32_t i = 0; i < 3; i++)
		{
			for(uint32_t j = 0; j < 3; j++)
			{
				printf("%+.2e ", m_data_ref[i + 3 * j]);
			}
			printf("\n");
		}
	}

	//operators
	float& mat3::operator()(uint32_t i)
	{
		return m_data_ptr[i];
	}
	float& mat3::operator[](uint32_t i)
	{
		return m_data_ptr[i];
	}
	float& mat3::operator()(uint32_t i, uint32_t j)
	{
		return m_data_ptr[i + 3 * j];
	}
	const float& mat3::operator()(uint32_t i) const
	{
		return m_data_ref[i];
	}
	const float& mat3::operator[](uint32_t i) const
	{
		return m_data_ref[i];
	}
	const float& mat3::operator()(uint32_t i, uint32_t j) const
	{
		return m_data_ref[i + 3 * j];
	}

	mat3& mat3::operator=(const mat3& M)
	{
		memcpy(m_data_ptr, M.m_data_ref, 9 * sizeof(float));
		return *this;
	}

	mat3 mat3::operator+(void) const
	{
		return *this;
	}
	mat3 mat3::operator-(void) const
	{
		return mat3(*this) *= -1;
	}
	vec2 mat3::operator*(const vec2& v) const
	{
		vec2 r;
		for(uint32_t i = 0; i < 2; i++)
		{
			r[i] = m_data_ref[i + 3 * 2];
			for(uint32_t j = 0; j < 2; j++)
			{
				r[i] += m_data_ref[i + 3 * j] * v[j];
			}
		}
		return r;
	}
	vec3 mat3::operator*(const vec3& v) const
	{
		vec3 r;
		for(uint32_t i = 0; i < 3; i++)
		{
			r[i] = 0;
			for(uint32_t j = 0; j < 3; j++)
			{
				r[i] += m_data_ref[i + 3 * j] * v[j];
			}
		}
		return r;
	}
	mat3 mat3::operator*(const mat3& M) const
	{
		mat3 r;
		for(uint32_t i = 0; i < 3; i++)
		{
			for(uint32_t j = 0; j < 3; j++)
			{
				r.m_data_ptr[i + 3 * j] = 0;
				for(uint32_t k = 0; k < 3; k++)
				{
					r.m_data_ptr[i + 3 * j] += m_data_ref[i + 3 * k] * M.m_data_ref[k + 3 * j];
				}
			}
		}
		return r;
	}
	mat3 mat3::operator+(const mat3& M) const
	{
		mat3 A;
		for(uint32_t i = 0; i < 9; i++)
		{
			A.m_data_ptr[i] = m_data_ref[i] + M.m_data_ref[i];
		}
		return A;
	}
	mat3 mat3::operator-(const mat3& M) const
	{
		mat3 A;
		for(uint32_t i = 0; i < 9; i++)
		{
			A.m_data_ptr[i] = m_data_ref[i] - M.m_data_ref[i];
		}
		return A;
	}

	mat3& mat3::operator*=(float s)
	{
		for(uint32_t i = 0; i < 9; i++)
		{
			m_data_ptr[i] *= s;
		}
		return *this;
	}
	mat3 operator*(float s, const mat3& M)
	{
		return mat3(M) *= s;
	}

	//affine
	mat3 mat3::scaling(float s)
	{
		return scaling({s, s});
	}
	mat3 mat3::rotation(float t)
	{
		mat3 A;
		A.m_data_ptr[0 + 3 * 0] = +cosf(t);
		A.m_data_ptr[1 + 3 * 0] = +sinf(t);
		A.m_data_ptr[0 + 3 * 1] = -sinf(t);
		A.m_data_ptr[1 + 3 * 1] = +cosf(t);
		return A;
	}
	mat3 mat3::scaling(const vec2& s)
	{
		mat3 A;
		A.m_data_ptr[0 + 3 * 0] = s[0];
		A.m_data_ptr[1 + 3 * 1] = s[1];
		return A;
	}
	mat3 mat3::shifting(const vec2& v)
	{
		mat3 A;
		A.m_data_ptr[0 + 3 * 2] = v[0];
		A.m_data_ptr[1 + 3 * 2] = v[1];
		return A;
	}
}
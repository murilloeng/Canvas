//std
#include <cmath>
#include <cstdio>
#include <cstring>

//canvas
#include "Canvas/inc/Math/vec2.hpp"
#include "Canvas/inc/Math/mat2.hpp"

namespace canvas
{
	//constructors
	mat2::mat2(void) : m_data_mem{1.0f, 0.0f, 0.0f, 1.0f}, m_data_ptr{m_data_mem}, m_data_ref{m_data_mem}
	{
		return;
	}
	mat2::mat2(float* data_ptr) : m_data_ptr{data_ptr}, m_data_ref{data_ptr}
	{
		return;
	}
	mat2::mat2(const mat2& M) : m_data_ptr{m_data_mem}, m_data_ref{m_data_mem}
	{
		memcpy(m_data_ptr, M.m_data_ref, 4 * sizeof(float));
	}
	mat2::mat2(const float* data_ref) : m_data_ptr{nullptr}, m_data_ref{data_ref}
	{
		return;
	}
	mat2::mat2(float a1, float a2, float a3, float a4) : m_data_mem{a1, a2, a3, a4}, m_data_ptr{m_data_mem}, m_data_ref{m_data_mem}
	{
		return;
	}

	//destructor
	mat2::~mat2(void)
	{
		return;
	}

	//data
	float* mat2::data(void)
	{
		return m_data_ptr;
	}
	const float* mat2::data(void) const
	{
		return m_data_ref;
	}

	//linear
	void mat2::clear(void)
	{
		for(uint32_t i = 0; i < 2; i++)
		{
			for(uint32_t j = 0; j < 2; j++)
			{
				m_data_ptr[i + 2 * j] = i == j;
			}
		}
	}
	void mat2::zeros(void)
	{
		memset(m_data_ptr, 0, 4 * sizeof(float));
	}
	float mat2::norm(void) const
	{
		float v = 0;
		for(uint32_t i = 0; i < 4; i++)
		{
			v += m_data_ref[i] * m_data_ref[i];
		}
		return sqrtf(v);
	}

	//print
	void mat2::print(const char* label) const
	{
		if(strlen(label) != 0)
		{
			printf("%s\n", label);
		}
		for(uint32_t i = 0; i < 2; i++)
		{
			for(uint32_t j = 0; j < 2; j++)
			{
				printf("%+.2e ", m_data_ref[i + 2 * j]);
			}
			printf("\n");
		}
	}

	//operators
	float& mat2::operator()(uint32_t i)
	{
		return m_data_ptr[i];
	}
	float& mat2::operator[](uint32_t i)
	{
		return m_data_ptr[i];
	}
	float& mat2::operator()(uint32_t i, uint32_t j)
	{
		return m_data_ptr[i + 2 * j];
	}
	const float& mat2::operator()(uint32_t i) const
	{
		return m_data_ref[i];
	}
	const float& mat2::operator[](uint32_t i) const
	{
		return m_data_ref[i];
	}
	const float& mat2::operator()(uint32_t i, uint32_t j) const
	{
		return m_data_ref[i + 2 * j];
	}

	mat2& mat2::operator=(const mat2& M)
	{
		memcpy(m_data_ptr, M.m_data_ref, 4 * sizeof(float));
		return *this;
	}

	mat2 mat2::operator+(void) const
	{
		return *this;
	}
	mat2 mat2::operator-(void) const
	{
		return mat2{*this} *= -1;
	}
	vec2 mat2::operator*(const vec2& v) const
	{
		vec2 r;
		for(uint32_t i = 0; i < 2; i++)
		{
			r[i] = 0;
			for(uint32_t j = 0; j < 2; j++)
			{
				r[i] += m_data_ref[i + 2 * j] * v[j];
			}
		}
		return r;
	}
	mat2 mat2::operator*(const mat2& M) const
	{
		mat2 r;
		for(uint32_t i = 0; i < 2; i++)
		{
			for(uint32_t j = 0; j < 2; j++)
			{
				r.m_data_ptr[i + 2 * j] = 0;
				for(uint32_t k = 0; k < 2; k++)
				{
					r.m_data_ptr[i + 2 * j] += m_data_ref[i + 2 * k] * M.m_data_ref[k + 2 * j];
				}
			}
		}
		return r;
	}
	mat2 mat2::operator+(const mat2& M) const
	{
		mat2 A;
		for(uint32_t i = 0; i < 4; i++)
		{
			A.m_data_ptr[i] = m_data_ref[i] + M.m_data_ref[i];
		}
		return A;
	}
	mat2 mat2::operator-(const mat2& M) const
	{
		mat2 A;
		for(uint32_t i = 0; i < 4; i++)
		{
			A.m_data_ptr[i] = m_data_ref[i] - M.m_data_ref[i];
		}
		return A;
	}

	mat2& mat2::operator*=(float s)
	{
		for(uint32_t i = 0; i < 4; i++)
		{
			m_data_ptr[i] *= s;
		}
		return *this;
	}
	mat2 operator*(float s, const mat2& M)
	{
		return mat2(M) *= s;
	}

	//affine
	mat2 mat2::scaling(float s)
	{
		return {s, 0, 0, s};
	}
	mat2 mat2::rotation(float t)
	{
		return {+cosf(t), +sinf(t), -sinf(t), +cosf(t)};
	}
	mat2 mat2::scaling(const vec2& s)
	{
		return {s[0], 0, 0, s[1]};
	}
}
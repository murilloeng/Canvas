//std
#include <cstring>

//canvas
#include "Canvas/Canvas/inc/Objects/Graph/Curve2D.hpp"

namespace canvas
{
	namespace objects
	{
		namespace graphs
		{
			//constructor
			Curve2D::Curve2D(void) : 
				m_data{nullptr, nullptr}, m_graph(nullptr), m_samples(0),
				m_points(false), m_points_size(0.1f), m_points_type(0),
				m_lines(false), m_lines_type(0), m_lines_thickness(0.1f),
				m_range{0, 1}, m_function_1(nullptr), m_function_2(nullptr)
			{
				return;
			}

			//destructor
			Curve2D::~Curve2D(void)
			{
				delete[] m_data[0];
				delete[] m_data[1];
			}

			//data
			uint32_t Curve2D::samples(void) const
			{
				return m_samples;
			}
			uint32_t Curve2D::samples(uint32_t samples)
			{
				return m_samples = samples;
			}
			const float* Curve2D::data(uint32_t index) const
			{
				return m_data[index];
			}
			void Curve2D::data(uint32_t samples, const float* data_1, const float* data_2)
			{
				delete[] m_data[0];
				delete[] m_data[1];
				m_samples = samples;
				m_data[0] = new float[samples];
				m_data[1] = new float[samples];
				memcpy(m_data[0], data_1, samples * sizeof(float));
				memcpy(m_data[1], data_2, samples * sizeof(float));
			}

			bool Curve2D::points(void) const
			{
				return m_points;
			}
			bool Curve2D::points(bool points)
			{
				return m_points = points;
			}

			float Curve2D::points_size(void) const
			{
				return m_points_size;
			}
			float Curve2D::points_size(float points_size)
			{
				return m_points_size = points_size;
			}

			Color Curve2D::points_color(void) const
			{
				return m_points_color;
			}
			Color Curve2D::points_color(Color points_color)
			{
				return m_points_color = points_color;
			}

			uint32_t Curve2D::points_type(void) const
			{
				return m_points_type;
			}
			uint32_t Curve2D::points_type(uint32_t points_type)
			{
				return m_points_type = points_type;
			}

			bool Curve2D::lines(void) const
			{
				return m_lines;
			}
			bool Curve2D::lines(bool lines)
			{
				return m_lines = lines;
			}

			Color Curve2D::lines_color(void) const
			{
				return m_lines_color;
			}
			Color Curve2D::lines_color(Color lines_color)
			{
				return m_lines_color = lines_color;
			}

			uint32_t Curve2D::lines_type(void) const
			{
				return m_lines_type;
			}
			uint32_t Curve2D::lines_type(uint32_t lines_type)
			{
				return m_lines_type = lines_type;
			}

			float Curve2D::lines_thickness(void) const
			{
				return m_lines_thickness;
			}
			float Curve2D::lines_thickness(float lines_thickness)
			{
				return m_lines_thickness = lines_thickness;
			}

			float Curve2D::range(uint32_t index) const
			{
				return m_range[index];
			}
			float Curve2D::range(uint32_t index, float range)
			{
				return m_range[index] = range;
			}

			void Curve2D::function_1(float(*function_1)(float))
			{
				m_function_1 = function_1;
			}
			void Curve2D::function_2(float(*function_2)(float))
			{
				m_function_2 = function_2;
			}

			//points
			void Curve2D::point(uint32_t index, float& x1, float& x2) const
			{
				if(m_function_1)
				{
					const float t1 = m_range[0];
					const float t2 = m_range[1];
					const uint32_t ns = m_samples;
					const float ti = t1 + (t2 - t1) * index / (ns - 1);
					x1 = m_function_2 ? m_function_1(ti) : ti;
					x2 = m_function_2 ? m_function_2(t1) : m_function_1(ti);
				}
				else
				{
					x1 = m_data[0][index];
					x2 = m_data[1][index];
				}
			}
		}
	}
}
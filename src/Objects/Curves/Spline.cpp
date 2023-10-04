//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Type.hpp"
#include "inc/Objects/Curves/Spline.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Spline::Spline(void)
		{
			m_stroke_colors.resize(1);
			m_points.push_back({0, 0, 0});
			m_points.push_back({0, 0, 0});
			m_controls.push_back({0, 0, 0});
			m_controls.push_back({0, 0, 0});
		}

		//destructor
		Spline::~Spline(void)
		{
			return;
		}

		//data
		unsigned Spline::mesh(void)
		{
			return m_mesh;
		}
		unsigned Spline::mesh(unsigned mesh)
		{
			return m_mesh = mesh;
		}

		vec3 Spline::point(unsigned index) const
		{
			return m_points[index];
		}
		vec3 Spline::point(unsigned index, const vec3& position)
		{
			return m_points[index] = position;
		}

		vec3 Spline::control(unsigned index, unsigned side) const
		{
			return m_controls[2 * index + side - 1];
		}
		vec3 Spline::control(unsigned index, unsigned side, const vec3& position)
		{
			return m_controls[2 * index + side - 1] = position;
		}

		void Spline::add_point(const vec3& position)
		{
			//data
			const vec3& xp = m_points.back();
			const vec3& xc = m_controls.back();
			//points
			m_points.push_back(position);
			m_controls.push_back(2 * xp - xc);
			m_controls.push_back(2 * xp - xc);
		}
		const std::vector<vec3>& Spline::points(void) const
		{
			return m_points;
		}
		const std::vector<vec3>& Spline::controls(void) const
		{
			return m_controls;
		}

		//path
		vec3 Spline::hessian(float s) const
		{
			return {0, 0, 0};
		}
		vec3 Spline::position(float s) const
		{
			vec3 p;
			const unsigned np = m_points.size();
			const unsigned ic = s * (np - 1);
			const float t2 = s * (np - 1) - ic;
			const float t1 = 1 - s * (np - 1) + ic;
			p += t1 * t1 * t1 * m_points[ic - 1];
			p += t2 * t2 * t2 * m_points[ic + 0];
			p += t1 * t1 * t2 * m_points[2 * ic - 2];
			p += t1 * t2 * t2 * m_points[2 * ic - 1];
			return p;
		}
		vec3 Spline::gradient(float) const
		{
			return {0, 0, 0};
		}

		//type
		objects::type Spline::type(void) const
		{
			return objects::type::spline;
		}

		//buffers
		unsigned Spline::vbo_size(void) const
		{
			const unsigned nm = m_mesh;
			const unsigned np = m_points.size();
			return (np * nm - nm + 1) * m_stroke;
		}
		unsigned Spline::ibo_size(unsigned index) const
		{
			const unsigned nm = m_mesh;
			const unsigned np = m_points.size();
			return nm * (np - 1) * (index == 1) * m_stroke;
		}

		//draw
		void Spline::ibo_stroke_data(unsigned** ibo_data) const
		{
			//data
			const unsigned nm = m_mesh;
			const unsigned np = m_points.size();
			unsigned* ibo_ptr = ibo_data[1] + m_ibo_index[1];
			//ibo data
			for(unsigned i = 0; i < nm * (np - 1); i++)
			{
				ibo_ptr[2 * i + 0] = m_vbo_index + i + 0;
				ibo_ptr[2 * i + 1] = m_vbo_index + i + 1;
			}
		}
		void Spline::vbo_stroke_data(vertices::Vertex* vbo_data) const
		{
			//data
			const unsigned nm = m_mesh;
			const unsigned np = m_points.size();
			vertices::Model* vbo_stroke_ptr = (vertices::Model*) vbo_data + m_vbo_index;
			//vbo data
			for(unsigned i = 1; i < np; i++)
			{
				for(unsigned j = 1; j <= nm; j++)
				{
					const float t2 = float(j) / nm;
					const float t1 = 1 - float(j) / nm;
					(vbo_stroke_ptr + nm * (i - 1) + j)->m_position = {0, 0, 0};
					(vbo_stroke_ptr + nm * (i - 1) + j)->m_color = m_stroke_colors[0];
					(vbo_stroke_ptr + nm * (i - 1) + j)->m_position += t1 * t1 * t1 * m_points[i - 1];
					(vbo_stroke_ptr + nm * (i - 1) + j)->m_position += t2 * t2 * t2 * m_points[i + 0];
					(vbo_stroke_ptr + nm * (i - 1) + j)->m_position += 3 * t1 * t1 * t2 * m_controls[2 * i - 2];
					(vbo_stroke_ptr + nm * (i - 1) + j)->m_position += 3 * t1 * t2 * t2 * m_controls[2 * i - 1];
				}
			}
			vbo_stroke_ptr->m_position = m_points[0];
			vbo_stroke_ptr->m_color = m_stroke_colors[0];
		}
		void Spline::buffers_data(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			if(m_stroke) vbo_stroke_data(vbo_data);
			if(m_stroke) ibo_stroke_data(ibo_data);
		}

		//static
		unsigned Spline::m_mesh = 60;
	}
}
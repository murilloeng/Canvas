//canvas
#include "Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/inc/Objects/1D/Spline.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Spline::Spline(void)
		{
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
		uint32_t Spline::mesh(void)
		{
			return m_mesh;
		}
		uint32_t Spline::mesh(uint32_t mesh)
		{
			return m_mesh = mesh;
		}

		vec3 Spline::point(uint32_t index) const
		{
			return m_points[index];
		}
		vec3 Spline::point(uint32_t index, const vec3& position)
		{
			return m_points[index] = position;
		}

		vec3 Spline::control(uint32_t index, uint32_t side) const
		{
			return m_controls[2 * index + side - 1];
		}
		vec3 Spline::control(uint32_t index, uint32_t side, const vec3& position)
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

		//draw
		void Spline::draw(void)
		{
			m_vao.bind();
			m_shader.bind();
			const uint32_t np = m_points.size();
			glDrawArrays(GL_LINE_STRIP, 0, (np - 1) * (m_mesh + 1));
		}
		void Spline::setup(void)
		{
			const uint32_t np = m_points.size();
			m_vbo.allocate((np - 1) * (m_mesh + 1));
		}
		void Spline::update(void)
		{
			//data
			const uint32_t np = m_points.size();
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) m_vbo.data();
			//vbo data
			for(uint32_t i = 0; i < np - 1; i++)
			{
				const vec3& x1 = m_points[i + 0];
				const vec3& x2 = m_points[i + 1];
				const vec3& c1 = m_controls[2 * i + 0];
				const vec3& c2 = m_controls[2 * i + 1];
				for(uint32_t j = 0; j < m_mesh + 1; j++)
				{
					//data
					const float t = float(j) / m_mesh;
					const float s = 1 - float(j) / m_mesh;
					//vertex
					vbo_ptr[i * (m_mesh + 1) + j].m_color = m_color_stroke;
					vbo_ptr[i * (m_mesh + 1) + j].m_position = s * s * s * x1 + 3 * s * s * t * c1 + 3 * s * t * t * c2 + t * t * t * x2;
				}
			}
			//transfer
			apply_model();
			m_vbo.transfer();
		}

		//static
		uint32_t Spline::m_mesh = 60;
	}
}
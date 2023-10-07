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
		vec3 Spline::path_hessian(float s) const
		{
			vec3 h;
			const float t2 = s - unsigned(s);
			const float t1 = 1 + unsigned(s) - s;
			h += 6 * t1 * m_points[unsigned(s) + 0];
			h += 6 * t2 * m_points[unsigned(s) + 1];
			h -= 2 * (2 * t1 - t2) * m_controls[2 * unsigned(s) + 0];
			h -= 2 * (2 * t2 - t1) * m_controls[2 * unsigned(s) + 1];
			return h;
		}
		vec3 Spline::path_position(float s) const
		{
			vec3 p;
			const float t2 = s - unsigned(s);
			const float t1 = 1 +unsigned(s) - s;
			p += t1 * t1 * t1 * m_points[unsigned(s) + 0];
			p += t2 * t2 * t2 * m_points[unsigned(s) + 1];
			p += t1 * t1 * t2 * m_controls[2 * unsigned(s) + 0];
			p += t1 * t2 * t2 * m_controls[2 * unsigned(s) + 1];
			return p;
		}
		vec3 Spline::path_gradient(float s) const
		{
			vec3 g;
			const float t2 = s - unsigned(s);
			const float t1 = 1 + unsigned(s) - s;
			g -= 3 * t1 * t1 * m_points[unsigned(s) + 0];
			g += 3 * t2 * t2 * m_points[unsigned(s) + 1];
			g -= (2 * t2 - t1) * t1 * m_controls[2 * unsigned(s) + 0];
			g += (2 * t1 - t2) * t2 * m_controls[2 * unsigned(s) + 1];
			return g;
		}

		//type
		objects::type Spline::type(void) const
		{
			return objects::type::spline;
		}
	}
}
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
		float Spline::path_max(void) const
		{
			return m_points.size() - 1;
		}
		vec3 Spline::path_hessian(float s) const
		{
			//data
			vec3 h;
			unsigned k = unsigned(s);
			if(k + 1 == m_points.size()) k--;
			//hessian
			const float t2 = s - k;
			const float t1 = 1 + k - s;
			h += 6 * t1 * m_points[k + 0];
			h += 6 * t2 * m_points[k + 1];
			h -= 6 * (2 * t1 - t2) * m_controls[2 * k + 0];
			h -= 6 * (2 * t2 - t1) * m_controls[2 * k + 1];
			//return
			return h;
		}
		vec3 Spline::path_position(float s) const
		{
			//data
			vec3 p;
			unsigned k = unsigned(s);
			if(k + 1 == m_points.size()) k--;
			//position
			const float t2 = s - k;
			const float t1 = 1 + k - s;
			p += t1 * t1 * t1 * m_points[k + 0];
			p += t2 * t2 * t2 * m_points[k + 1];
			p += 3 * t1 * t1 * t2 * m_controls[2 * k + 0];
			p += 3 * t1 * t2 * t2 * m_controls[2 * k + 1];
			//return
			return p;
		}
		vec3 Spline::path_gradient(float s) const
		{
			//data
			vec3 g;
			unsigned k = unsigned(s);
			if(k + 1 == m_points.size()) k--;
			//gradient
			const float t2 = s - k;
			const float t1 = 1 + k - s;
			g -= 3 * t1 * t1 * m_points[k + 0];
			g += 3 * t2 * t2 * m_points[k + 1];
			g -= 3 * (2 * t2 - t1) * t1 * m_controls[2 * k + 0];
			g += 3 * (2 * t1 - t2) * t2 * m_controls[2 * k + 1];
			//return
			return g;
		}

		//type
		objects::type Spline::type(void) const
		{
			return objects::type::spline;
		}
	}
}
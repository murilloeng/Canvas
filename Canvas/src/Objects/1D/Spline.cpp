//canvas
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Spline.hpp"

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

		//path
		float Spline::path_max(void) const
		{
			return m_points.size() - 1.0f;
		}
		vec3 Spline::path_hessian(float s) const
		{
			//data
			vec3 h;
			uint32_t k = uint32_t(s);
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
			uint32_t k = uint32_t(s);
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
			uint32_t k = uint32_t(s);
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
	}
}
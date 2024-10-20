//ext
#include "external/cpp/inc/GL/glew.h"

//canvas
#include "Canvas/inc/GPU/Program.hpp"
#include "Canvas/inc/Light/Light.hpp"
#include "Canvas/inc/Light/Point.hpp"
#include "Canvas/inc/Light/Ambient.hpp"
#include "Canvas/inc/Light/Direction.hpp"

namespace canvas
{
	namespace lights
	{
		//constructor
		Light::Light(void) : m_ambient(new Ambient)
		{
			return;
		}

		//destructor
		Light::~Light(void)
		{
			delete m_ambient;
			for(Point* point : m_points) delete point;
			for(Direction* direction : m_directions) delete direction;
		}
		
		//data
		Ambient* Light::ambient(void) const
		{
			return m_ambient;
		}
		Point* Light::point(uint32_t index) const
		{
			return m_points[index];
		}
		Direction* Light::direction(uint32_t index) const
		{
			return m_directions[index];
		}

		const std::vector<Point*> Light::points(void) const
		{
			return m_points;
		}
		const std::vector<Direction*> Light::directions(void) const
		{
			return m_directions;
		}

		//lists
		void Light::add_point(void)
		{
			m_points.push_back(new Point);
		}
		void Light::add_direction(void)
		{
			m_directions.push_back(new Direction);
		}
		void Light::remove_point(uint32_t index)
		{
			delete m_points[index];
			m_points.erase(m_points.begin() + index);
		}
		void Light::remove_direction(uint32_t index)
		{
			delete m_directions[index];
			m_directions.erase(m_directions.begin() + index);
		}

		//shaders
		void Light::update_shaders(void) const
		{
			//bind
			m_program->bind();
			//ambient
			const Color ca = m_ambient->color();
			m_program->set_uniform("ambient.m_color", ca[0], ca[1], ca[2]);
			//points
			char format[200];
			for(uint32_t i = 0; i < m_points.size(); i++)
			{
				const Color cp = m_points[i]->color();
				const vec3 xp = m_points[i]->position();
				sprintf(format, "points[%d].m_color", i);
				m_program->set_uniform(format, cp[0], cp[1], cp[2]);
				sprintf(format, "points[%d].m_position", i);
				m_program->set_uniform(format, xp[0], xp[1], xp[2]);
			}
			m_program->set_uniform("n_points", uint32_t(m_points.size()));
			//directions
			for(uint32_t i = 0; i < m_directions.size(); i++)
			{
				const Color cd = m_directions[i]->color();
				const vec3 vd = m_directions[i]->direction();
				sprintf(format, "directions[%d].m_color", i);
				m_program->set_uniform(format, cd[0], cd[1], cd[2]);
				sprintf(format, "directions[%d].m_direction", i);
				m_program->set_uniform(format, vd[0], vd[1], vd[2]);
			}
			m_program->set_uniform("n_directions", uint32_t(m_directions.size()));
		}
	}
}
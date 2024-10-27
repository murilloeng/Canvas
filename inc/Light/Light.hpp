#pragma once

//std
#include <vector>

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Colors/Color.hpp"

namespace canvas
{
	class Scene;
	class Program;
	namespace lights
	{
		class Point;
		class Ambient;
		class Direction;
	}
}

namespace canvas
{
	namespace lights
	{
		class Light
		{
		public:
			//constructors
			Light(void);

			//destructor
			~Light(void);

			//data
			Point* point(uint32_t) const;
			Ambient* ambient(void) const;
			Direction* direction(uint32_t) const;

			const std::vector<Point*> points(void) const;
			const std::vector<Direction*> directions(void) const;

			//lists
			void add_point(void);
			void add_direction(void);
			void remove_point(uint32_t);
			void remove_direction(uint32_t);

			//shaders
			void update_shaders(void) const;

		private:
			//data
			Program* m_program;
			Ambient* m_ambient;
			std::vector<Point*> m_points;
			std::vector<Direction*> m_directions;

			//friends
			friend class canvas::Scene;
		};
	}
}
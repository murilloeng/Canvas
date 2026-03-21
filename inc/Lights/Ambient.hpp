#pragma once

//canvas
#include "Canvas/inc/Colors/Color.hpp"

namespace canvas
{
	namespace lights
	{
		class Ambient
		{
		public:
			//constructor
			Ambient(void);

			//destructor
			~Ambient(void);

			//data
			Color color(Color);
			Color color(void) const;

		private:
			//data
			Color m_color;
		};
	}
}
#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Volume : public Object
		{
		public:
			//constructors
			Volume(void);

			//destructor
			~Volume(void);

			//path
			virtual float area(void) const = 0;
			virtual float volume(void) const = 0;
		};
	}
}
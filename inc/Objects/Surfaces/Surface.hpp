#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Surface : public Object
		{
		public:
			//constructors
			Surface(void);

			//destructor
			~Surface(void);

			//path
			virtual float area(void) const = 0;
			virtual float length(void) const = 0;
		};
	}
}
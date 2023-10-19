#pragma once

//canvas
#include "inc/Objects/Group.hpp"

namespace canvas
{
	namespace objects
	{
		class Curve;
	}
}

namespace canvas
{
	namespace objects
	{
		class Path : public Group
		{
		public:
			//constructors
			Path(void);

			//destructor
			~Path(void);

			//curves
			void add_curve(Curve*);
			void remove_curve(unsigned);
			unsigned curves(void) const;
			Curve* curve(unsigned) const;
		};
	}
}
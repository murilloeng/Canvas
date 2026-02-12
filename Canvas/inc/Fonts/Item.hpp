#pragma once

//std
#include <cstdint>

namespace canvas
{
	namespace objects
	{
		class Object;
	}
}

namespace canvas
{
	namespace fonts
	{
		class Item
		{
		public:
			//constructor
			Item(void);

			//destructor
			virtual ~Item(void);

			//types
			enum class Type{Line, Conic, Cubic};
			
			//type
			virtual Type type(void) const = 0;
			
			//print
			virtual void print(void) const = 0;
			
			//object
			virtual objects::Object* object(void) const = 0;

			//intersection
			virtual uint32_t hit(const float*) const = 0;
			virtual float point(uint32_t, float) const = 0;
		};
	}
}
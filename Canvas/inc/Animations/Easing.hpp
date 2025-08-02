#pragma once

//std
#include <cstdint>

namespace canvas
{
	namespace animations
	{
		class Easing
		{
		public:
			//constructor
			Easing(void);
	
			//destructor
			~Easing(void);
	
			//types
			enum class type : uint32_t
			{
				linear, sin, back, elastic
			};
			enum class subtype : uint32_t
			{
				in, out, in_out
			};
	
			//value
			float value(float) const;
	
			//data
			type m_type;
			subtype m_subtype;
		};
	}
}
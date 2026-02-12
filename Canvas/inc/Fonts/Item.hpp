#pragma once

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

			//print
			virtual void print(void) const = 0;
		};
	}
}
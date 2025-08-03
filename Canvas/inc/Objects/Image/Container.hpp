#pragma once

//canvas
#include "Canvas/Canvas/inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Container : public Object
		{
		public:
			//constructor
			Container(void);

			//destructor
			~Container(void);

		private:
			//setup
			void setup(void) override;

			//buffers
			void buffers_size(void) override;
			void buffers_data(void) const override;

			//objects
			Object* m_object;
		};
	}
}
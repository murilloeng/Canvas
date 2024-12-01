#pragma once

//std
#include <vector>

//canvas
#include "Canvas/Canvas/inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Group : public Object
		{
		public:
			//constructors
			Group(void);

			//destructor
			virtual ~Group(void);

			//data
			std::vector<Object*>& objects(void);
			const std::vector<Object*>& objects(void) const;

		protected:
			//setup
			void setup(void) override;

			//buffers
			void buffers_size(void) override;
			void buffers_data(void) const override;

			//model matrix
			void apply_model_matrix(void) const override;

			//data
			std::vector<Object*> m_objects;
		};
	}
}
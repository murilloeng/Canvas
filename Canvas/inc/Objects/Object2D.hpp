#pragma once

//Canvas
#include "Canvas/Canvas/inc/Math/mat3.hpp"
#include "Canvas/Canvas/inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Object2D : public Object
		{
		public:
			//constructors
			Object2D(void);

			//destructor
			virtual ~Object2D(void);

			//data
			mat3 model_matrix(mat3);
			mat3 model_matrix(void) const;
			mat3 apply_matrix(mat3, bool = true);

			//transformations
			void reset(void);
			void scale(float);
			void rotate(float, bool = true);
			void scale(const vec2&, bool = true);
			void shift(const vec2&, bool = true);

		protected:
			//data
			mat3 m_model_matrix;
			bool m_has_model_matrix;
		};
	}
}
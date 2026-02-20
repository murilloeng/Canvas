#pragma once

//Canvas
#include "Canvas/Canvas/inc/Math/mat4.hpp"
#include "Canvas/Canvas/inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Object3D : public Object
		{
		public:
			//constructors
			Object3D(void);

			//destructor
			virtual ~Object3D(void);

			//data
			mat4 model_matrix(mat4);
			mat4 model_matrix(void) const;
			mat4 apply_matrix(mat4, bool = true);

			//transformations
			void reset(void);
			void scale(float);
			void scale(const vec3&, bool = true);
			void shift(const vec3&, bool = true);
			void rotate(const vec3&, bool = true);
			void rotate(const quat&, bool = true);
			void rotate(const vec3&, const vec3&, bool = true);
			void rotate(const vec3&, const quat&, bool = true);

		protected:
			//data
			mat4 m_model_matrix;
			bool m_has_model_matrix;
		};
	}
}
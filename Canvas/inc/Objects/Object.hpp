#pragma once

//std
#include <vector>
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Math/mat4.hpp"

namespace canvas
{
	class Scene;
	namespace vertices
	{
		class Text2D;
		class Text3D;
		class Model2D;
		class Model3D;
		class Image2D;
		class Image3D;
	}
	namespace objects
	{
		class Group;
		class Container;
	}
}

namespace canvas
{
	namespace objects
	{
		class Object
		{
		public:
			//constructors
			Object(void);

			//destructor
			virtual ~Object(void);

			//data
			Scene* scene(void) const;

			mat4 model_matrix(mat4);
			mat4 model_matrix(void) const;
			mat4 apply_matrix(mat4, bool = true);

			//affine
			void reset(void);
			void scale(float);
			void scale(const vec3&, bool = true);
			void shift(const vec3&, bool = true);
			void rotate(const vec3&, bool = true);
			void rotate(const quat&, bool = true);
			void rotate(const vec3&, const vec3&, bool = true);
			void rotate(const vec3&, const quat&, bool = true);

		protected:
			//draw
			virtual void setup(void);
			virtual void draw(void) const;

			//update
			virtual void update_on_motion(void) const;

			//model matrix
			virtual void apply_model_matrix(void) const;

			//data
			Scene* m_scene;

			mat4 m_model_matrix;
			bool m_has_model_matrix;

			//friends
			friend class canvas::Scene;
			friend class objects::Group;
			friend class objects::Container;
		};
	}
}
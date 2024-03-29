#pragma once

//canvas
#include "Canvas/inc/Math/mat4.hpp"

namespace canvas
{
	class Scene;
	namespace vertices
	{
		class Vertex;
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

			const unsigned* ibo_index(void) const;
			const unsigned* vbo_index(void) const;

			//affine
			void scale(float);
			void scale(const vec3&, bool = true);
			void shift(const vec3&, bool = true);
			void rotate(const vec3&, bool = true);
			void rotate(const quat&, bool = true);
			void rotate(const vec3&, const vec3&, bool = true);
			void rotate(const vec3&, const quat&, bool = true);

		protected:
			//size
			virtual unsigned vbo_size(unsigned) const = 0;
			virtual unsigned ibo_size(unsigned) const = 0;

			//buffers
			virtual void setup(unsigned[], unsigned[]);
			virtual void buffers_data(vertices::Vertex**, unsigned**) const = 0;

			//data
			Scene* m_scene;
			mat4 m_model_matrix;
			unsigned m_vbo_index[6];
			unsigned m_ibo_index[12];

			//friends
			friend class canvas::Scene;
		};
	}
}
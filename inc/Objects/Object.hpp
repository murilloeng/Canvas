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

			const uint32_t* ibo_index(void) const;
			const uint32_t* vbo_index(void) const;

			//affine
			void scale(float);
			void scale(const vec3&, bool = true);
			void shift(const vec3&, bool = true);
			void rotate(const vec3&, bool = true);
			void rotate(const quat&, bool = true);
			void rotate(const vec3&, const vec3&, bool = true);
			void rotate(const vec3&, const quat&, bool = true);

		protected:
			//setup
			virtual void setup(void);

			//buffers
			virtual void buffers_size(void) = 0;
			virtual void buffers_data(void) const = 0;

			//data
			Scene* m_scene;

			mat4 m_model_matrix;
			bool m_has_model_matrix;

			uint32_t m_vbo_size[6];
			uint32_t m_vbo_index[6];

			uint32_t m_ibo_size[12];
			uint32_t m_ibo_index[12];

			//friends
			friend class canvas::Scene;
		};
	}
}
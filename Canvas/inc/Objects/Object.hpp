#pragma once

//std
#include <vector>
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Math/mat4.hpp"

namespace canvas
{
	class Scene;
	namespace objects
	{
		class Group;
	}
	namespace vertices
	{
		class Text2D;
		class Text3D;
		class Model2D;
		class Model3D;
		class Image2D;
		class Image3D;
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

			//buffers
			uint32_t* ibo_data(uint32_t) const;
			vertices::Text2D* vbo_data_text_2D(void) const;
			vertices::Text3D* vbo_data_text_3D(void) const;
			vertices::Model2D* vbo_data_model_2D(void) const;
			vertices::Model3D* vbo_data_model_3D(void) const;
			vertices::Image2D* vbo_data_image_2D(void) const;
			vertices::Image3D* vbo_data_image_3D(void) const;

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

			//update
			virtual void update_on_motion(void) const;

			//model matrix
			virtual void apply_model_matrix(void) const;

			//data
			Scene* m_scene;

			mat4 m_model_matrix;
			bool m_has_model_matrix;

			std::vector<uint32_t> m_vbo_size;
			std::vector<uint32_t> m_ibo_size;
			std::vector<uint32_t> m_vbo_index;
			std::vector<uint32_t> m_ibo_index;

			//friends
			friend class canvas::Scene;
			friend class objects::Group;
		};
	}
}
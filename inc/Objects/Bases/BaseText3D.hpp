#pragma once

//Canvas
#include "Canvas/inc/Buffers/IBO.hpp"
#include "Canvas/inc/Buffers/VAO.hpp"
#include "Canvas/inc/Buffers/VBO.hpp"
#include "Canvas/inc/Shaders/Shader.hpp"
#include "Canvas/inc/Objects/Bases/BaseObject3D.hpp"

namespace canvas
{
	namespace objects
	{
		class BaseText3D : public BaseObject3D
		{
		public:
			//constructor
			BaseText3D(void);

			//destructor
			~BaseText3D(void);

		protected:
			//model
			void apply_model(void) const override;

			//update
			void update_bounding_box(cameras::BoundingBox&) const override;

			//data
			buffers::IBO m_ibo;
			buffers::VAO m_vao;
			buffers::VBO m_vbo;
			shaders::Shader m_shader;
		};
	}
}
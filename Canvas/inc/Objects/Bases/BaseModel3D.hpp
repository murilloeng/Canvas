#pragma once

//Canvas
#include "Canvas/Canvas/inc/Buffers/IBO.hpp"
#include "Canvas/Canvas/inc/Buffers/VAO.hpp"
#include "Canvas/Canvas/inc/Buffers/VBO.hpp"
#include "Canvas/Canvas/inc/Colors/Color.hpp"
#include "Canvas/Canvas/inc/Shaders/Shader.hpp"
#include "Canvas/Canvas/inc/Objects/Bases/BaseObject3D.hpp"

namespace canvas
{
	namespace objects
	{
		class BaseModel3D : public BaseObject3D
		{
		public:
			//constructor
			BaseModel3D(void);

			//destructor
			~BaseModel3D(void);

			//data
			Color color_fill(void) const;
			Color color_fill(const Color&);

			Color color_stroke(void) const;
			Color color_stroke(const Color&);

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
			Color m_color_fill, m_color_stroke;
		};
	}
}
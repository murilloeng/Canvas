#pragma once

//Canvas
#include "Canvas/Canvas/inc/Buffers/IBO.hpp"
#include "Canvas/Canvas/inc/Buffers/VAO.hpp"
#include "Canvas/Canvas/inc/Buffers/VBO.hpp"
#include "Canvas/Canvas/inc/Colors/Color.hpp"
#include "Canvas/Canvas/inc/Objects/Object.hpp"
#include "Canvas/Canvas/inc/Shaders/Shader.hpp"

namespace canvas
{
	namespace objects
	{
		class Model3D : public Object
		{
		public:
			//constructor
			Model3D(void);

			//destructor
			~Model3D(void);

			//data
			Color color_fill(void) const;
			Color color_fill(const Color&);

			Color color_stroke(void) const;
			Color color_stroke(const Color&);

		protected:
			//data
			buffers::IBO m_ibo;
			buffers::VAO m_vao;
			buffers::VBO m_vbo;
			shaders::Shader m_shader;
			Color m_color_fill, m_color_stroke;
		};
	}
}
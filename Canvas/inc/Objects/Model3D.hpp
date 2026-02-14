#pragma once

//Canvas
#include "Canvas/Canvas/inc/Buffers/IBO.hpp"
#include "Canvas/Canvas/inc/Buffers/VAO.hpp"
#include "Canvas/Canvas/inc/Buffers/VBO.hpp"
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

		protected:
			//data
			buffers::IBO m_ibo;
			buffers::VAO m_vao;
			buffers::VBO m_vbo;
			shaders::Shader m_shader;
		};
	}
}
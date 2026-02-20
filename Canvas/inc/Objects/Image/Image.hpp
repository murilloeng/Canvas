#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Buffers/VAO.hpp"
#include "Canvas/Canvas/inc/Buffers/VBO.hpp"
#include "Canvas/Canvas/inc/Shaders/Shader.hpp"
#include "Canvas/Canvas/inc/Textures/Image.hpp"
#include "Canvas/Canvas/inc/Objects/Object3D.hpp"
#include "Canvas/Canvas/inc/Objects/Image/Anchor.hpp"

namespace canvas
{
	namespace objects
	{
		class Image : public Object3D
		{
		public:
			//constructors
			Image(void);

			//destructor
			~Image(void);

			//data
			Anchor anchor(Anchor);
			Anchor anchor(void) const;

			textures::Image& image(void);

		protected:
			//draw
			void setup(void) override;
			void draw(void) const override;

			//data
			Anchor m_anchor;
			buffers::VAO m_vao;
			buffers::VBO m_vbo;
			textures::Image m_image;
			shaders::Shader m_shader;
		};
	}
}
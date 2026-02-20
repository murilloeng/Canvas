#pragma once

//std
#include <string>
#include <vector>
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Buffers/VAO.hpp"
#include "Canvas/Canvas/inc/Buffers/VBO.hpp"
#include "Canvas/Canvas/inc/Buffers/IBO.hpp"
#include "Canvas/Canvas/inc/Colors/Color.hpp"
#include "Canvas/Canvas/inc/Shaders/Shader.hpp"
#include "Canvas/Canvas/inc/Vertices/Text2D.hpp"
#include "Canvas/Canvas/inc/Objects/Object2D.hpp"
#include "Canvas/Canvas/inc/Objects/Image/Anchor.hpp"

namespace canvas
{
	namespace objects
	{
		class Text2D : public Object2D
		{
		public:
			//constructors
			Text2D(void);

			//destructor
			~Text2D(void);

			//data
			uint32_t font(uint32_t);
			uint32_t font(void) const;

			Color color(void) const;
			Color color(const Color&);

			Anchor anchor(Anchor);
			Anchor anchor(void) const;

			std::string text(void) const;
			std::string text(std::string);

		protected:
			//text
			uint32_t width(void) const;
			uint32_t height(void) const;
			uint32_t length(void) const;

			//buffers
			void ibo_data(uint32_t, uint32_t*) const;
			void vbo_data(uint32_t, vertices::Text2D*) const;

			//draw
			void setup(void) override;
			void draw(void) const override;

			//data
			Color m_color;
			Anchor m_anchor;
			uint32_t m_font;
			std::string m_text;
			buffers::VAO m_vao;
			buffers::VBO m_vbo;
			buffers::IBO m_ibo;
			shaders::Shader m_shader;
		};
	}
}
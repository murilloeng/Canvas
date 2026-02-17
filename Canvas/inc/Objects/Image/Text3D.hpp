#pragma once

//std
#include <string>
#include <vector>
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Buffers/IBO.hpp"
#include "Canvas/Canvas/inc/Buffers/VAO.hpp"
#include "Canvas/Canvas/inc/Buffers/VBO.hpp"
#include "Canvas/Canvas/inc/Colors/Color.hpp"
#include "Canvas/Canvas/inc/Shaders/Shader.hpp"
#include "Canvas/Canvas/inc/Objects/Object.hpp"
#include "Canvas/Canvas/inc/Objects/Image/Anchor.hpp"

namespace canvas
{
	namespace objects
	{
		class Text3D : public Object
		{
		public:
			//constructors
			Text3D(void);

			//destructor
			~Text3D(void);

			//data
			float size(float);
			float size(void) const;

			bool normal(bool);
			bool normal(void) const;
			
			uint32_t font(uint32_t);
			uint32_t font(void) const;
			
			Color color(void) const;
			Color color(const Color&);

			Anchor anchor(Anchor);
			Anchor anchor(void) const;

			std::string text(void) const;
			std::string text(std::string);
			
			float line_spacing(float);
			float line_spacing(void) const;

		protected:
			//text
			uint32_t width(void) const;
			uint32_t height(void) const;
			uint32_t length(void) const;

			//setup
			// void setup(void) override;

			//data
			void vbo_fill_data(void) const;
			void ibo_fill_data(void) const;

			//draw
			void setup(void) override;
			void draw(void) const override;

			//update
			void update_on_motion(void) const override;

			//data
			float m_size;
			bool m_normal;
			Color m_color;
			uint32_t m_font;
			Anchor m_anchor;
			std::string m_text;
			buffers::IBO m_ibo;
			buffers::VBO m_vbo;
			buffers::VAO m_vao;
			float m_line_spacing;
			shaders::Shader m_shader;
			std::vector<uint32_t> m_lines;
		};
	}
}
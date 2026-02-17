#pragma once

//std
#include <string>
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
			
		protected:
			//text
			uint32_t width(void) const;
			uint32_t height(void) const;
			uint32_t length(void) const;

			//buffers
			void ibo_data(uint32_t, uint32_t*) const;
			void vbo_data(uint32_t, vertices::Text3D*) const;

			//draw
			void setup(void) override;
			void draw(void) const override;

			//update
			void update_on_motion(void) const override;

			//data
			bool m_normal;
			Color m_color;
			uint32_t m_font;
			Anchor m_anchor;
			std::string m_text;
			buffers::IBO m_ibo;
			buffers::VBO m_vbo;
			buffers::VAO m_vao;
			shaders::Shader m_shader;
		};
	}
}
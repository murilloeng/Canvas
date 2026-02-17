#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Buffers/IBO.hpp"
#include "Canvas/Canvas/inc/Buffers/VAO.hpp"
#include "Canvas/Canvas/inc/Buffers/VBO.hpp"
#include "Canvas/Canvas/inc/Shaders/Shader.hpp"
#include "Canvas/Canvas/inc/Objects/Object.hpp"
#include "Canvas/Canvas/inc/Palettes/Palette.hpp"

namespace canvas
{
	namespace objects
	{
		class Palette : public Object
		{
		public:
			//constructors
			Palette(void);

			//destructor
			~Palette(void);

			//data
			float min(float);
			float min(void) const;

			float max(float);
			float max(void) const;

			float width(float);
			float width(void) const;

			float height(float);
			float height(void) const;

			float offset(float);
			float offset(void) const;

			uint32_t font(uint32_t);
			uint32_t font(void) const;

			uint32_t marks(uint32_t);
			uint32_t marks(void) const;

			palettes::Palette& palette(void);

		protected:
			//text
			uint32_t text_width(const char*) const;

			//data
			void ibo_data_text(uint32_t*) const;
			void ibo_data_model(uint32_t*) const;
			void vbo_data_text(vertices::Text2D*) const;
			void vbo_data_model(vertices::Model2D*) const;

			//buffers
			void setup(void) override;
			void draw(void) const override;

			//data
			float m_min;
			float m_max;
			float m_width;
			float m_height;
			float m_offset;
			uint32_t m_font;
			uint32_t m_marks;
			buffers::VAO m_vaos[2];
			buffers::VBO m_vbos[2];
			buffers::IBO m_ibos[2];
			palettes::Palette m_palette;
			shaders::Shader m_shaders[2];
		};
	}
}
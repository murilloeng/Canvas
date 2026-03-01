#pragma once

//Canvas
#include "Canvas/Canvas/inc/Buffers/VAO.hpp"
#include "Canvas/Canvas/inc/Buffers/VBO.hpp"
#include "Canvas/Canvas/inc/Buffers/IBO.hpp"
#include "Canvas/Canvas/inc/Colors/Color.hpp"
#include "Canvas/Canvas/inc/Objects/Object.hpp"
#include "Canvas/Canvas/inc/Shaders/Shader.hpp"
#include "Canvas/Canvas/inc/Vertices/Line2D.hpp"
#include "Canvas/Canvas/inc/Vertices/Glyph2D.hpp"
#include "Canvas/Canvas/inc/Objects/Graph/Axis.hpp"

namespace canvas
{
	namespace objects
	{
		class Graph;
		namespace graphs
		{
			class Curve;
		}
	}
}

namespace canvas
{
	namespace objects
	{
		namespace graphs
		{
			class Frame : public Object
			{
			private:
				//constructor
				Frame(const Graph*);

				//destructor
				~Frame(void);

			public:
				//data
				Axis& axis(uint32_t);

				Color color(void) const;
				Color color(const Color&);

				uint32_t thickness(uint32_t);
				uint32_t thickness(void) const;

				float grid_opacity(float);
				float grid_opacity(void) const;

			private:
				//compute
				void compute_glyphs(void);
				void compute_offset(void);

				//position
				vec2 ndc(const vec2&) const;
				vec2 pixel(const vec2&) const;

				//draw
				void setup(void) override;
				void draw(void) const override;

				//text
				float text_width(float, std::string) const;
				float text_width(float, float, const char*) const;

				float text_height(float, std::string) const;
				float text_height(float, float, const char*) const;

				void text_height(float, std::string, float&, float&) const;
				void text_height(float, float, const char*, float&, float&) const;

				//bufers
				void vbo_data_frame(vertices::Line2D*&) const;
				void vbo_data_frame_grid(vertices::Line2D*&) const;
				void vbo_data_frame_vertical(vertices::Line2D*&) const;
				void vbo_data_frame_horizontal(vertices::Line2D*&) const;

				void vbo_data_label_vertical(vertices::Glyph2D*&) const;
				void vbo_data_ticks_vertical(vertices::Glyph2D*&) const;
				void vbo_data_label_horizontal(vertices::Glyph2D*&) const;
				void vbo_data_ticks_horizontal(vertices::Glyph2D*&) const;

				//data
				Color m_color;
				Axis m_axis[2];
				float m_offset[4];
				float m_grid_opacity;
				uint32_t m_thickness;
				const Graph* m_graph;
				buffers::VAO m_vaos[2];
				buffers::VBO m_vbos[2];
				uint32_t m_glyphs_count;
				shaders::Shader m_shaders[2];

				//friends
				friend class objects::Graph;
				friend class objects::graphs::Curve;
			};
		}
	}
}
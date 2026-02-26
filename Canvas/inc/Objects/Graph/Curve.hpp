#pragma once

//std
#include <vector>

//canvas
#include "Canvas/Canvas/inc/Math/vec2.hpp"
#include "Canvas/Canvas/inc/Buffers/VAO.hpp"
#include "Canvas/Canvas/inc/Buffers/SSBO.hpp"
#include "Canvas/Canvas/inc/Colors/Color.hpp"
#include "Canvas/Canvas/inc/Objects/Object.hpp"
#include "Canvas/Canvas/inc/Shaders/Shader.hpp"

namespace canvas
{
	namespace objects
	{
		class Graph;
		namespace graphs
		{
			class Frame;
		}
	}
}

namespace canvas
{
	namespace objects
	{
		namespace graphs
		{
			class Curve : public Object
			{
			public:
				//constructor
				Curve(void);

				//destructor
				~Curve(void);

				//data
				bool line(bool);
				bool line(void) const;

				Color line_color(void) const;
				Color line_color(const Color&);

				uint32_t line_width(uint32_t);
				uint32_t line_width(void) const;

				bool point(bool);
				bool point(void) const;

				Color point_color(void) const;
				Color point_color(const Color&);

				uint32_t point_size(uint32_t);
				uint32_t point_size(void) const;

				uint32_t point_type(uint32_t);
				uint32_t point_type(void) const;

				std::vector<vec2>& data(void);
				const std::vector<vec2>& data(void) const;

			protected:
				//draw
				void setup(void) override;
				void draw(void) const override;

				//data
				bool m_line;
				Color m_line_color;
				uint32_t m_line_width;

				bool m_point;
				Color m_point_color;
				uint32_t m_point_size;
				uint32_t m_point_type;
				
				buffers::VAO m_vao;
				buffers::SSBO m_ssbo;
				shaders::Shader m_shader;
				std::vector<vec2> m_data;
				const graphs::Frame* m_frame;

				//friends
				friend class objects::Graph;
			};
		}
	}
}
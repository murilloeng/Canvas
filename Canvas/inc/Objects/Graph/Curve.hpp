#pragma once

//std
#include <vector>

//canvas
#include "Canvas/Canvas/inc/Math/vec2.hpp"
#include "Canvas/Canvas/inc/Buffers/VAO.hpp"
#include "Canvas/Canvas/inc/Buffers/UBO.hpp"
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
				bool lines(bool);
				bool lines(void) const;

				Color lines_color(void) const;
				Color lines_color(const Color&);

				uint32_t lines_width(uint32_t);
				uint32_t lines_width(void) const;

				bool points(bool);
				bool points(void) const;

				Color points_color(void) const;
				Color points_color(const Color&);

				uint32_t points_size(uint32_t);
				uint32_t points_size(void) const;

				uint32_t points_skip(uint32_t);
				uint32_t points_skip(void) const;

				uint32_t points_type(uint32_t);
				uint32_t points_type(void) const;

				std::vector<vec2>& data(void);
				const std::vector<vec2>& data(void) const;

			protected:
				//draw
				void setup(void) override;
				void draw(void) const override;

				//data
				bool m_lines;
				Color m_lines_color;
				uint32_t m_lines_width;
				buffers::UBO m_ubo_lines;
				shaders::Shader m_shader_lines;

				bool m_points;
				Color m_points_color;
				uint32_t m_points_size;
				uint32_t m_points_skip;
				uint32_t m_points_type;
				buffers::UBO m_ubo_points;
				shaders::Shader m_shader_points;
				
				buffers::VAO m_vao;
				buffers::SSBO m_ssbo;
				std::vector<vec2> m_data;
				const graphs::Frame* m_frame;

				//friends
				friend class objects::Graph;
			};
		}
	}
}
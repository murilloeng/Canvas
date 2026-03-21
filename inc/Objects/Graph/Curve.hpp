#pragma once

//std
#include <vector>

//canvas
#include "Canvas/inc/Math/vec2.hpp"
#include "Canvas/inc/Buffers/VAO.hpp"
#include "Canvas/inc/Buffers/UBO.hpp"
#include "Canvas/inc/Buffers/SSBO.hpp"
#include "Canvas/inc/Objects/Object.hpp"
#include "Canvas/inc/Shaders/Shader.hpp"
#include "Canvas/inc/Objects/Graph/Lines.hpp"
#include "Canvas/inc/Objects/Graph/Points.hpp"

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
				Lines& lines(void);
				Points& points(void);

				std::vector<vec2>& data(void);
				const std::vector<vec2>& data(void) const;

			protected:
				//draw
				void setup(void) override;
				void draw(void) const override;

				//compute
				void compute_lengths(void) const;

				//data
				buffers::VAO m_vao;
				buffers::SSBO m_ssbo;
				std::vector<vec2> m_data;
				const graphs::Frame* m_frame;

				Lines m_lines;
				Points m_points;
				buffers::UBO m_ubo_lines;
				buffers::UBO m_ubo_points;
				shaders::Shader m_shader_lines;
				shaders::Shader m_shader_points;

				//friends
				friend class objects::Graph;
			};
		}
	}
}
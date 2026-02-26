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
				Color color(void) const;
				Color color(const Color&);

				float thickness(float);
				float thickness(void) const;

				std::vector<vec2>& points(void);
				const std::vector<vec2>& points(void) const;

			protected:
				//draw
				void setup(void) override;
				void draw(void) const override;

				//data
				Color m_color;
				float m_thickness;
				buffers::VAO m_vao;
				buffers::SSBO m_ssbos[2];
				std::vector<vec2> m_points;
				shaders::Shader m_shaders[2];
				const graphs::Frame* m_frame;

				//friends
				friend class objects::Graph;
			};
		}
	}
}
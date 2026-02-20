#pragma once

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"
#include "Canvas/Canvas/inc/Buffers/VAO.hpp"
#include "Canvas/Canvas/inc/Buffers/VBO.hpp"
#include "Canvas/Canvas/inc/Colors/Color.hpp"
#include "Canvas/Canvas/inc/Objects/Object.hpp"
#include "Canvas/Canvas/inc/Shaders/Shader.hpp"

namespace canvas
{
	namespace objects
	{
		namespace graphs
		{
			class Line : public objects::Object
			{
			public:
				//constructor
				Line(void);

				//destructor
				~Line(void);

				//data
				Color color(void) const;
				Color color(const Color&);

				float thickness(float);
				float thickness(void) const;

				vec3 point(uint32_t) const;
				vec3 point(uint32_t, const vec3&);

			protected:
				//draw
				void setup(void) override;
				void draw(void) const override;

				//data
				Color m_color;
				vec3 m_points[2];
				float m_thickness;
				buffers::VAO m_vao;
				buffers::VBO m_vbo;
				shaders::Shader m_shader;
			};
		}
	}
}
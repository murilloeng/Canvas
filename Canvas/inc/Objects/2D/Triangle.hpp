#pragma once

//std
#include <cstdint>

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
		class Triangle : public Object
		{
		public:
			//constructors
			Triangle(void);

			//destructor
			~Triangle(void);

			//data
			Color color(void) const;
			Color color(const Color&);

			vec3 position(uint32_t) const;
			vec3 position(uint32_t, const vec3&);

		protected:
			//draw
			void setup(void) override;
			void draw(void) const override;

			//data
			Color m_color;
			buffers::VAO m_vao;
			buffers::VBO m_vbo;
			vec3 m_positions[3];
			shaders::Shader m_shader;
		};
	}
}
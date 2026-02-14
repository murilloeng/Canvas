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
		class Point : public Object
		{
		public:
			//constructors
			Point(void);

			//destructor
			~Point(void);

			//data
			Color color(void) const;
			Color color(const Color&);

			vec3 position(void) const;
			vec3 position(const vec3&);

		protected:
			//draw
			void setup(void) override;
			void draw(void) const override;

			//data
			Color m_color;
			vec3 m_position;
			buffers::VAO* m_vao;
			buffers::VBO* m_vbo;
			shaders::Shader* m_shader;
		};
	}
}
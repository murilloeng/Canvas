#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Buffers/VAO.hpp"
#include "Canvas/Canvas/inc/Buffers/VBO.hpp"
#include "Canvas/Canvas/inc/Colors/Color.hpp"
#include "Canvas/Canvas/inc/Shaders/Shader.hpp"
#include "Canvas/Canvas/inc/Textures/Latex.hpp"
#include "Canvas/Canvas/inc/Objects/Image/Anchor.hpp"
#include "Canvas/Canvas/inc/Objects/Bases/BaseObject3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Latex : public BaseObject3D
		{
		public:
			//constructors
			Latex(void);

			//destructor
			~Latex(void);

			//data
			Anchor anchor(Anchor);
			Anchor anchor(void) const;

			Color color(void) const;
			Color color(const Color&);

			textures::Latex& latex(void);

		protected:
			//draw
			void setup(void) override;
			void draw(void) const override;

			//model
			void apply_model(void) const override;

			//data
			Color m_color;
			Anchor m_anchor;
			buffers::VAO m_vao;
			buffers::VBO m_vbo;
			textures::Latex m_latex;
			shaders::Shader m_shader;
		};
	}
}
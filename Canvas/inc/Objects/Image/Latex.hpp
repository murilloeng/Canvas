#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Colors/Color.hpp"
#include "Canvas/Canvas/inc/Textures/Latex.hpp"
#include "Canvas/Canvas/inc/Objects/Image/Anchor.hpp"
#include "Canvas/Canvas/inc/Objects/Bases/BaseText3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Latex : public BaseText3D
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

			//data
			Color m_color;
			Anchor m_anchor;
			textures::Latex m_latex;
		};
	}
}
#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Textures/Image.hpp"
#include "Canvas/Canvas/inc/Objects/Image/Anchor.hpp"
#include "Canvas/Canvas/inc/Objects/Bases/BaseImage3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Image : public BaseImage3D
		{
		public:
			//constructors
			Image(void);

			//destructor
			~Image(void);

			//data
			Anchor anchor(Anchor);
			Anchor anchor(void) const;

			textures::Image& image(void);

		protected:
			//draw
			void setup(void) override;
			void draw(void) const override;

			//data
			Anchor m_anchor;
			textures::Image m_image;
		};
	}
}
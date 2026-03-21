#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/inc/Textures/Image.hpp"
#include "Canvas/inc/Objects/Image/Anchor.hpp"
#include "Canvas/inc/Objects/Bases/BaseImage3D.hpp"

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
			void draw(void) override;
			void update(void) override;

			//data
			Anchor m_anchor;
			textures::Image m_image;
		};
	}
}
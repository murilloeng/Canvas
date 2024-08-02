//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Objects/Image/Image.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

namespace examples
{
	namespace objects
	{
		void images(canvas::Scene* scene)
		{
			//data
			char path[200];
			const uint32_t ni = 10;
			canvas::objects::Image* image;
			//images
			for(uint32_t i = 0; i < 12; i++)
			{
				sprintf(path, "data/images/wizard-%d.png", i % ni);
				scene->add_image(path);
			}
			//objects
			for(uint32_t i = 0; i < 4; i++)
			{
				for(uint32_t j = 0; j < 3; j++)
				{
					image = new canvas::objects::Image;
					image->size(0.5);
					image->anchor("CC");
					image->index(3 * i + j);
					image->shift({(2 * float(i) + 1) / 4 - 1, (2 * float(j) + 1) / 3 - 1, 0});
					scene->add_object(image);
				}
			}
		}
	}
}
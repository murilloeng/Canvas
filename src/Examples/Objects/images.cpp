//canvas
#include "inc/Scene/Scene.hpp"
#include "inc/Objects/Image/Image.hpp"

//examples
#include "inc/Examples/examples.hpp"

namespace examples
{
	namespace objects
	{
		void images(canvas::Scene* scene)
		{
			//data
			char path[200];
			canvas::objects::Image* image;
			//images
			for(unsigned i = 0; i < 12; i++)
			{
				sprintf(path, "data/images/eldrazi-%d.png", i);
				scene->add_image(path);
			}
			//objects
			for(unsigned i = 0; i < 4; i++)
			{
				for(unsigned j = 0; j < 3; j++)
				{
					image = new canvas::objects::Image;
					image->size(0.5);
					image->image(3 * i + j);
					image->position({2 * float(i) / 4 - 1, 2 * float(j) / 3 - 1, 0});
					scene->add_object(image);
				}
			}
		}
	}
}
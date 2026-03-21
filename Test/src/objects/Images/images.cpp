//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Objects/Image/Image.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::images(canvas::Scene* scene)
{
	char path[200];
	for(uint32_t i = 0; i < 4; i++)
	{
		for(uint32_t j = 0; j < 6; j++)
		{
			//data
			canvas::objects::Image* image = new canvas::objects::Image;
			sprintf(path, "Test/data/images/wizard-%02d.png", 6 * i + j + 1);
			//setup
			image->anchor("SW");
			image->scale(1.0f / 3);
			image->image().path(path);
			image->shift({float(j) / 3 - 1, float(i) / 2 - 1, 0});
			//scene
			image->image().load();
			scene->add_object(image);
		}
	}
}
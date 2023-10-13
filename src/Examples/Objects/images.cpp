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
			scene->add_image("data/mtg.jpg");
			canvas::objects::Image* image = new canvas::objects::Image;
			scene->add_object(image);
		}
	}
}
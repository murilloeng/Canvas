//canvas
#include "inc/Scene/Scene.hpp"
#include "inc/Objects/2D/Surface.hpp"

//examples
#include "inc/Examples/examples.hpp"

namespace examples
{
	namespace objects
	{
		void surfaces(canvas::Scene* scene)
		{
			//data
			canvas::objects::Surface* surface = new canvas::objects::Surface;
			//surface
			surface->mesh(0, 100);
			surface->mesh(1, 100);
			surface->domain(0, 0, -1);
			surface->domain(0, 1, +1);
			surface->domain(1, 0, -1);
			surface->domain(1, 1, +1);
			surface->color_fill({0, 0, 1});
			surface->position([] (float s1, float s2) { return canvas::vec3(s1, s2, s1 * s1 + s2 * s2); });
			//scene
			scene->add_object(surface);
		}
	}
}
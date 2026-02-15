//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/0D/Point.hpp"
#include "Canvas/Canvas/inc/Palettes/Palette.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::points(canvas::Scene* scene)
{
	//data
	const uint32_t n = 10;
	const float r = 1.0f / n;
	canvas::palettes::Palette palette;
	//objects
	for(uint32_t i = 0; i < n; i++)
	{
		for(uint32_t j = 0; j < n; j++)
		{
			scene->add_object(new canvas::objects::Point);
			((canvas::objects::Point*) scene->object(n * i + j))->color_fill(palette.color(i * n + j, 0, n * n - 1));
			((canvas::objects::Point*) scene->object(n * i + j))->position({2 * r * j + r - 1, 2 * r * i + r - 1, 0});
		}
	}
}
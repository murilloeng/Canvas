//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Palettes/Palette.hpp"
#include "Canvas/Canvas/inc/Objects/2D/Circle.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::circles(canvas::Scene* scene)
{
	//data
	const uint32_t n = 10;
	const float r = 1.0f / n;
	const canvas::palettes::Palette palette;
	//objects
	for(uint32_t i = 0; i < n; i++)
	{
		for(uint32_t j = 0; j < n; j++)
		{
			scene->add_object(new canvas::objects::Circle);
			((canvas::objects::Circle*) scene->object(n * i + j))->scale(r);
			((canvas::objects::Circle*) scene->object(n * i + j))->color_stroke({1, 1, 1});
			((canvas::objects::Circle*) scene->object(n * i + j))->shift({2 * r * j + r - 1, 2 * r * i + r - 1, 0});
			((canvas::objects::Circle*) scene->object(n * i + j))->color_fill(palette.color(i * n + j, 0, n * n - 1));
		}
	}
}
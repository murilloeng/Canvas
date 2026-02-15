//std
#include <cmath>

//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Arc.hpp"
#include "Canvas/Canvas/inc/Palettes/Palette.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::arcs(canvas::Scene* scene)
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
			//objects
			canvas::objects::Arc* arc = new canvas::objects::Arc;
			//arc
			arc->scale(r);
			arc->angle(2 * float(M_PI) * (i * n + j) / n / n);
			arc->shift({2 * r * j + r - 1, 2 * r * i + r - 1, 0});
			arc->color_stroke(palette.color(i * n + j, 0, n * n - 1));
			//scene
			scene->add_object(arc);
		}
	}
}
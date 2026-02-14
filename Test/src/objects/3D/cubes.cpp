//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/3D/Cube.hpp"
#include "Canvas/Canvas/inc/Palettes/Palette.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::cubes(canvas::Scene* scene)
{
	//data
	const uint32_t n = 10;
	const float s = 1.0f / n;
	const canvas::palettes::Palette palette;
	//objects
	for(uint32_t i = 0; i < n; i++)
	{
		for(uint32_t j = 0; j < n; j++)
		{
			const float x1 = 2 * j * s - 1 + s;
			const float x2 = 2 * i * s - 1 + s;
			scene->add_object(new canvas::objects::Cube);
			((canvas::objects::Cube*) scene->object(n * i + j))->scale(s / 2);
			((canvas::objects::Cube*) scene->object(n * i + j))->shift({x1, x2, 0});
			((canvas::objects::Cube*) scene->object(n * i + j))->color_stroke({1.0f, 1.0f, 1.0f});
			((canvas::objects::Cube*) scene->object(n * i + j))->color_fill(palette.color(i * n + j, 0, n * n - 1));
		}
	}
}
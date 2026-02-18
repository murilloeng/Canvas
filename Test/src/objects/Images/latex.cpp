//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Palettes/Palette.hpp"
#include "Canvas/Canvas/inc/Objects/Image/Latex.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::latex(canvas::Scene* scene)
{
	//data
	char source[256];
	canvas::palettes::Palette palette;
	const char* anchors[] = {"SW", "SE", "NW", "NE"};
	//objects
	for(uint32_t i = 0; i < 2; i++)
	{
		for(uint32_t j = 0; j < 2; j++)
		{
			//data
			const uint32_t k = 2 * i + j;
			sprintf(source, "$ \\int_{0}^{L} %c_{%d} dx $", k + 65, k);
			canvas::objects::Latex* latex = new canvas::objects::Latex;
			//object
			latex->anchor(anchors[i]);
			latex->latex().source(source);
			latex->color(palette.color(k, 0, 2 * 2 - 1));
			latex->shift({2 * float(i) - 1, 2 * float(j) - 1, 0});
			latex->latex().load();
			//scene
			scene->add_object(latex);
		}
	}
}
//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/Image/Latex.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::latex(canvas::Scene* scene)
{
	//data
	char source[200];
	canvas::objects::Latex* latex;
	//images
	for(uint32_t i = 0; i < 4; i++)
	{
		sprintf(source, "$ \\int_{0}^{L} %c_{%d} dx $", i + 65, i);
		scene->add_latex(source);
	}
	//objects
	for(uint32_t i = 0; i < 2; i++)
	{
		for(uint32_t j = 0; j < 2; j++)
		{
			latex = new canvas::objects::Latex;
			latex->size(0.25f);
			latex->anchor("SW");
			latex->index(2 * i + j);
			latex->shift({2 * float(i) / 2 - 1, 2 * float(j) / 2 - 1, 0});
			scene->add_object(latex);
		}
	}
}
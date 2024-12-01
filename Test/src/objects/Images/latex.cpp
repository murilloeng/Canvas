//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/Image/Latex.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

namespace examples
{
	namespace objects
	{
		void latex(canvas::Scene* scene)
		{
			//data
			char source[200];
			canvas::objects::Latex* latex;
			//images
			for(uint32_t i = 0; i < 12; i++)
			{
				sprintf(source, "$ \\int_{0}^{L} %c_{%d} dx $", i + 65, i);
				scene->add_latex(source);
			}
			//objects
			for(uint32_t i = 0; i < 4; i++)
			{
				for(uint32_t j = 0; j < 3; j++)
				{
					latex = new canvas::objects::Latex;
					latex->size(0.15f);
					latex->anchor("SW");
					latex->index(3 * i + j);
					latex->shift({2 * float(i) / 4 - 1, 2 * float(j) / 3 - 1, 0});
					scene->add_object(latex);
				}
			}
		}
	}
}
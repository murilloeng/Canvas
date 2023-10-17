//canvas
#include "inc/Scene/Scene.hpp"
#include "inc/Objects/Image/Equation.hpp"

//examples
#include "inc/Examples/examples.hpp"

namespace examples
{
	namespace objects
	{
		void equations(canvas::Scene* scene)
		{
			//data
			char source[200];
			canvas::objects::Equation* equation;
			//images
			for(unsigned i = 0; i < 12; i++)
			{
				sprintf(source, "$ \\int_{0}^{L} %c_{%d} dx $", i + 65, i);
				scene->add_equation(source);
			}
			//objects
			for(unsigned i = 0; i < 4; i++)
			{
				for(unsigned j = 0; j < 3; j++)
				{
					equation = new canvas::objects::Equation;
					equation->size(0.5);
					equation->anchor("SW");
					equation->index(3 * i + j);
					equation->shift({2 * float(i) / 4 - 1, 2 * float(j) / 3 - 1, 0});
					scene->add_object(equation);
				}
			}
		}
	}
}
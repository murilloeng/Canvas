//canvas
#include "inc/Examples/examples.hpp"
#include "inc/Examples/defs/Beam.hpp"
#include "inc/Examples/defs/Support_1.hpp"
#include "inc/Examples/defs/Support_2.hpp"
#include "inc/Examples/defs/Support_3.hpp"

namespace examples
{
	namespace scenes
	{
		void beam_1(canvas::Scene* scene)
		{
			//objects
			Beam* beam = new Beam(0.90f, 0.10f);
			Support_1* support_1 = new Support_1(0.10f);
			Support_2* support_2 = new Support_2(0.10f);
			Support_3* support_3 = new Support_3(0.25f, 0.05f);
			//affine
			support_1->shift({0.0f, 0.0f, 0.1f});
			support_2->shift({0.9f, 0.0f, 0.1f});
			support_3->shift({0.0f, 0.0f, 0.1f});
			//scene
			scene->add_object(beam);
			// scene->add_object(support_1);
			scene->add_object(support_2);
			scene->add_object(support_3);
			scene->background({1, 1, 1, 1});
		}
	}
}
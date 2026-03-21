//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Objects/Image/Palette.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::palettes(canvas::Scene* scene)
{
	scene->add_font("times");
	scene->add_object(new canvas::objects::Palette);
}
//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Objects/2D/Quad.hpp"
#include "Canvas/inc/Objects/Image/Palette.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::palettes(canvas::Scene* scene)
{
	//fonts
	scene->add_font("times");
	//objects
	canvas::objects::Palette* palette = new canvas::objects::Palette;
	//scene
	scene->add_object(palette);
}
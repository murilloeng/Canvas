//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"

#include "Canvas/Canvas/inc/Objects/2D/Square.hpp"
#include "Canvas/Canvas/inc/Objects/Image/Text3D.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

//static
static const float x[] = {-1, -1, +1, -1, +1, +1, -1, +1};
static const char* c[] = {"A", "B", "C", "D", "E", "F", "G", "H"};
static const char* a[] = {"NE", "NW", "SW", "SE", "SW", "SE", "NE", "NW"};

void examples::objects::text3D(canvas::Scene* scene)
{
	//fonts
	scene->add_font("times");
	//objects
	canvas::objects::Square* square;
	canvas::objects::Text3D* text[9];
	for(uint32_t i = 0; i < 9; i++)
	{
		scene->add_object(text[i] = new canvas::objects::Text3D);
	}
	scene->add_object(square = new canvas::objects::Square);
	//square
	square->color_fill({0, 0, 0, 0});
	//text
	for(uint32_t i = 0; i < 4; i++)
	{
		text[i + 0]->scale(0.25f);
		text[i + 5]->scale(0.25f);
		text[i + 0]->normal(true);
		text[i + 5]->normal(true);
		text[i + 0]->color("red");
		text[i + 5]->color("blue");
		text[i + 0]->text(c[i + 0]);
		text[i + 5]->text(c[i + 4]);
		text[i + 0]->anchor(a[i + 0]);
		text[i + 5]->anchor(a[i + 4]);
		text[i + 0]->shift({x[2 * i + 0], x[2 * i + 1], 0});
		text[i + 5]->shift({x[2 * i + 0], x[2 * i + 1], 0});
	}
	text[4]->scale(0.25f);
	text[4]->anchor("CC");
	text[4]->color("green");
	text[4]->text("This is a\nmulti-\vline\ntext\twith tab.");
}
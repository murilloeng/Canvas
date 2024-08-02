//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Objects/2D/Quad.hpp"
#include "Canvas/inc/Objects/Image/Text.hpp"

//examples
#include "Canvas/Test/inc/examples.hpp"

//static
static const float x[] = {-1, -1, +1, -1, +1, +1, -1, +1};
static const char* c[] = {"A", "B", "C", "D", "E", "F", "G", "H"};
static const char* a[] = {"NE", "NW", "SW", "SE", "SW", "SE", "NE", "NW"};

namespace examples
{
	namespace objects
	{
		void text(canvas::Scene* scene)
		{
			//fonts
			scene->add_font("times");
			//objects
			canvas::objects::Quad* quad;
			canvas::objects::Text* text[9];
			for(uint32_t i = 0; i < 9; i++)
			{
				scene->add_object(text[i] = new canvas::objects::Text);
			}
			scene->add_object(quad = new canvas::objects::Quad);
			//quad
			quad->fill(false);
			quad->point(0, {-1, -1, 0});
			quad->point(1, {+1, -1, 0});
			quad->point(2, {+1, +1, 0});
			quad->point(3, {-1, +1, 0});
			//text
			text[4]->size(0.2f);
			text[4]->anchor("CC");
			text[4]->position({0, 0, 0});
			text[4]->color_fill({0, 1, 0});
			for(uint32_t i = 0; i < 4; i++)
			{
				text[i + 0]->size(0.2f);
				text[i + 5]->size(0.2f);
				text[i + 0]->text(c[i + 0]);
				text[i + 5]->text(c[i + 4]);
				text[i + 0]->anchor(a[i + 0]);
				text[i + 5]->anchor(a[i + 4]);
				text[i + 0]->color_fill({0, 0, 1});
				text[i + 5]->color_fill({1, 0, 0});
				text[i + 0]->position({x[2 * i + 0], x[2 * i + 1], 0});
				text[i + 5]->position({x[2 * i + 0], x[2 * i + 1], 0});
			}
			text[4]->text("this is a\nmulti-\vline\ntext\twith tab");
		}
	}
}
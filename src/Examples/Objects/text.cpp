//canvas
#include "inc/Scene/Scene.hpp"
#include "inc/Objects/2D/Quad.hpp"
#include "inc/Objects/Image/Text.hpp"

//examples
#include "inc/Examples/examples.hpp"

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
			canvas::objects::Text* text[5];
			for(unsigned i = 0; i < 5; i++)
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
			text[0]->text("A");
			text[1]->text("B");
			text[2]->text("C");
			text[3]->text("D");
			text[0]->size(0.2f);
			text[1]->size(0.2f);
			text[2]->size(0.2f);
			text[3]->size(0.2f);
			text[0]->anchor("NE");
			text[1]->anchor("NW");
			text[2]->anchor("SW");
			text[3]->anchor("SE");
			text[4]->anchor("CC");
			text[4]->position({0, 0, 0});
			text[0]->position({-1, -1, 0});
			text[1]->position({+1, -1, 0});
			text[2]->position({+1, +1, 0});
			text[3]->position({-1, +1, 0});
			text[4]->text("this is a\nmulti-\vline\ntext\twith tab");
		}
	}
}
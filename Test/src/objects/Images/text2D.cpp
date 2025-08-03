//canvas
#include "Canvas/Canvas/inc/Objects/Image/Text2D.hpp"

//test
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::text2D(canvas::Scene* scene)
{
	//data
	canvas::objects::Text2D* text[5];
	const canvas::vec2 positions[] = {
		{0.0f, 0.0f}, {-1.0f, -1.0f}, {+1.0f, -1.0f}, {+1.0f, +1.0f}, {-1.0f, +1.0f}
	};
	const canvas::Anchor anchors[] = {"CC", "SW", "SE", "NE", "NW"};
	const char* strings[] = {"little test\nwith a little text", "A", "B", "C", "D"};
	//text
	scene->add_font("times");
	for(uint32_t i = 0; i < 5; i++)
	{
		//create
		text[i] = new canvas::objects::Text2D;
		//setup
		text[i]->font(0);
		text[i]->size(0.1f);
		text[i]->string(strings[i]);
		text[i]->anchor(anchors[i]);
		text[i]->position(positions[i]);
		//scene
		scene->add_object(text[i]);
	}
}
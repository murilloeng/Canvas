//canvas
#include "Canvas/Canvas/inc/Objects/1D/Polyline.hpp"
#include "Canvas/Canvas/inc/Objects/Image/Text2D.hpp"

//test
#include "Canvas/Test/inc/examples.hpp"

void examples::objects::text2D(canvas::Scene* scene)
{
	//data
	canvas::objects::Text2D* text[5];
	const canvas::vec2 positions[] = {
		{0.0f, 0.0f}, {-0.5f, -0.5f}, {+0.5f, -0.5f}, {+0.5f, +0.5f}, {-0.5f, +0.5f}
	};
	canvas::objects::Polyline* line = new canvas::objects::Polyline;
	const canvas::Anchor anchors[] = {"CC", "NE", "NW", "SW", "SW"};
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
	//line
	scene->add_object(line);
	line->vertices().push_back({positions[1][0], positions[1][1], 0});
	line->vertices().push_back({positions[2][0], positions[2][1], 0});
	line->vertices().push_back({positions[3][0], positions[3][1], 0});
	line->vertices().push_back({positions[4][0], positions[4][1], 0});
	line->vertices().push_back({positions[1][0], positions[1][1], 0});
}
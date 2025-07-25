//canvas
#include "Canvas/Canvas/inc/Objects/0D/Point.hpp"

//Test
#include "Canvas/Test/inc/Engine.hpp"
#include "Canvas/Test/inc/examples.hpp"

static Engine* engine;

static void user_button(int button, int action, int mods, double s1, double s2)
{
	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		const float w = (float) engine->width();
		const float h = (float) engine->height();
		const float x1 = 2 * float(s1) / w - 1;
		const float x2 = 1 - 2 * float(s2) / h;
		canvas::objects::Point* point = new canvas::objects::Point;
		point->position({x1, x2, 0});
		point->color_dot({1, 0, 0});
		engine->scene()->add_object(point);
	}
}

void examples::scenes::user_interaction(void)
{
	//data
	engine = new Engine;
	//setup
	engine->show_fps(false);
	//user
	engine->user_button(user_button);
	//start
	engine->start();
	//delete
	delete engine;
}
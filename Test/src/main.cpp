//std
#include <cstdlib>
#include <stdexcept>

//test
#include "Canvas/Test/inc/Engine.hpp"
#include "Canvas/Test/inc/examples.hpp"

//Canvas
#include "Canvas/Canvas/inc/Objects/0D/Point.hpp"

int main(void)
{
	try
	{
		//data
		Engine engine;
		canvas::objects::Point* point = new canvas::objects::Point;
		//point
		point->color("blue");
		point->position({0, 0, 0});
		//objects
		engine.scene()->add_object(point);
		engine.scene()->update(true);
		//start
		engine.start();
	}
	catch(const std::exception& e)
	{
		fprintf(stderr, "%s\n", e.what());
	}
	//return
	return EXIT_SUCCESS;
}
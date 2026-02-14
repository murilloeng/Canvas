//std
#include <cstdlib>
#include <stdexcept>

//test
#include "Canvas/Test/inc/Engine.hpp"
#include "Canvas/Test/inc/examples.hpp"

//Canvas
#include "Canvas/Canvas/inc/Objects/1D/Line.hpp"
#include "Canvas/Canvas/inc/Objects/0D/Point.hpp"
#include "Canvas/Canvas/inc/Objects/2D/Triangle.hpp"

int main(void)
{
	try
	{
		//data
		Engine engine;
		engine.show_fps(false);
		examples::objects::cubes(engine.scene());
		//update
		engine.scene()->update(true);
		engine.scene()->camera().update();
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
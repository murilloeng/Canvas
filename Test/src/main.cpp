//std
#include <cstdlib>
#include <stdexcept>

//test
#include "Canvas/Test/inc/Engine.hpp"
#include "Canvas/Test/inc/examples.hpp"

int32_t main(void)
{
	try
	{
		//data
		Engine engine;
		engine.show_fps(true);
		//scene
		examples::objects::graphs(engine.scene());
		//scene
		engine.scene()->update();
		engine.scene()->camera().bound();
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
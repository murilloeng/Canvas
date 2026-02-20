//std
#include <cstdlib>
#include <stdexcept>

//test
#include "Canvas/Test/inc/Engine.hpp"
#include "Canvas/Test/inc/examples.hpp"

//Canvas
#include "Canvas/Canvas/inc/Objects/Graph/Line.hpp"

int32_t main(void)
{
	try
	{
		//data
		Engine engine;
		engine.show_fps(true);
		// examples::objects::latex(engine.scene());
		canvas::objects::graphs::Line* line = new canvas::objects::graphs::Line;
		line->point(0, {0, 0, 0});
		line->point(1, {1, 1, 0});
		engine.scene()->add_object(line);
		//update
		engine.scene()->update();
		engine.scene()->camera().update();
		//start
		engine.start();
		// examples::scenes::examples();
	}
	catch(const std::exception& e)
	{
		fprintf(stderr, "%s\n", e.what());
	}
	//return
	return EXIT_SUCCESS;
}
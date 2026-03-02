//std
#include <cmath>
#include <cstdlib>
#include <stdexcept>

//test
#include "Canvas/Test/inc/Engine.hpp"
#include "Canvas/Test/inc/examples.hpp"

#include "Canvas/Canvas/inc/API/API.hpp"
#include "Canvas/Canvas/inc/Buffers/SSBO.hpp"
#include "Canvas/Canvas/inc/Shaders/Stage.hpp"
#include "Canvas/Canvas/inc/Shaders/Shader.hpp"

int32_t main(void)
{
	try
	{
		//data
		Engine engine;
		engine.show_fps(false);
		//scene
		examples::objects::graphs(engine.scene());
		//scene
		engine.scene()->update();
		engine.scene()->camera().bound();
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
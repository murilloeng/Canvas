//std
#include <cmath>
#include <cstdlib>
#include <stdexcept>

//test
#include "Canvas/Test/inc/Engine.hpp"
#include "Canvas/Test/inc/examples.hpp"

//Canvas
#include "Canvas/Canvas/inc/Objects/Graph/Curve.hpp"

int32_t main(void)
{
	try
	{
		//data
		examples::scenes::tensegrity_chair();
	}
	catch(const std::exception& e)
	{
		fprintf(stderr, "%s\n", e.what());
	}
	//return
	return EXIT_SUCCESS;
}
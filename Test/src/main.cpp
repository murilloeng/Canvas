//std
#include <cstdlib>
#include <stdexcept>

//test
#include "Canvas/Test/inc/examples.hpp"

int32_t main(void)
{
	try
	{
		examples::scenes::examples();
	}
	catch(const std::exception& e)
	{
		fprintf(stderr, "%s\n", e.what());
	}
	//return
	return EXIT_SUCCESS;
}
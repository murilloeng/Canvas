//std
#include <cstdlib>

//test
#include "Canvas/Test/inc/examples.hpp"

int main(void)
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
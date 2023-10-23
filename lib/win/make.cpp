//maker
#include "../../Maker/inc/Maker.hpp"

int main(int argc, char** argv)
{
	//setup
	Maker maker;
	maker.m_lib = true;
	maker.m_out = "canvas";
	maker.setup(argc, argv);
	maker.m_incs += "/I ext/inc ";
	//build
	if(!maker.m_clean)
	{
		maker.build_src();
		maker.build_lib();
	}
	if(maker.m_clean)
	{
		maker.build_clean();
	}
	//return
	return EXIT_SUCCESS;
}
//maker
#include "../../Maker/inc/Maker.hpp"

void build_lib(const Maker& maker)
{
	std::filesystem::current_path("../lib");
	if(system(maker.m_mode.compare("debug") == 0 ? "make.exe" : "make.exe m=r"))
	{
		fprintf(stderr, "Error building lib!\n");
		exit(EXIT_FAILURE);
	}
	std::filesystem::current_path("../test");
}
void setup_dlls(Maker& maker)
{
	maker.m_path_dll.clear();
	maker.m_path_dll.push_back(maker.m_edll + "glew32.dll");
	maker.m_path_dll.push_back(maker.m_edll + "freeglut.dll");
	maker.m_path_dll.push_back(maker.m_edll + "freetype.dll");
}
void setup_libs(Maker& maker)
{
	maker.m_libs.clear();
	maker.m_libs += "glu32.lib ";
	maker.m_libs += "opengl32.lib ";
	maker.m_libs += maker.m_elib + "glew32.lib ";
	maker.m_libs += maker.m_elib + "freeglut.lib ";
	maker.m_libs += maker.m_elib + "freetype.lib ";
	maker.m_libs += "../lib/dist/" + maker.m_mode + "/libcanvas.lib ";
}

int main(int argc, char** argv)
{
	//setup
	Maker maker;
	maker.m_out = "test";
	maker.setup(argc, argv);
	maker.m_incs += "/I ../lib/ ";
	maker.m_elib = "../lib/ext/lib/";
	maker.m_edll = "../lib/ext/dll/";
	//build
	if(!maker.m_clean)
	{
		build_lib(maker);
		setup_libs(maker);
		setup_dlls(maker);
		maker.build_src();
		maker.build_dll();
		maker.build_exe();
		maker.build_run();
		maker.build_debug();
	}
	if(maker.m_clean)
	{
		maker.build_clean();
	}
	//return
	return EXIT_SUCCESS;
}
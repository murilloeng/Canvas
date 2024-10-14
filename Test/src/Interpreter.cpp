//canvas
#include "Canvas/test/inc/Interpreter.hpp"

//constructor
Interpreter::Interpreter(canvas::Scene* scene) : m_scene(scene)
{
	return;
}

//destructor
Interpreter::~Interpreter(void)
{
	return;
}

//run
void Interpreter::run(void) const
{
	//data
	char cmd[200];
	//loop
	while(true)
	{
		fgets(cmd, 200, stdin);
		printf("%s", cmd);
		if(strncmp(cmd, "exit", 4) == 0) break;
	}
}
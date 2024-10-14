#pragma once

//canvas
#include "Canvas/inc/Scene/Scene.hpp"

class Interpreter
{
public:
	//constructor
	Interpreter(canvas::Scene*);

	//destructor
	~Interpreter(void);

	//run
	void run(void) const;

private:
	//data
	canvas::Scene* m_scene;
};
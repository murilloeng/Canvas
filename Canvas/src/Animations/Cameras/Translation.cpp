//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"

#include "Canvas/Canvas/inc/Animations/Cameras/Translation.hpp"

namespace canvas
{
	namespace animations
	{
		namespace cameras
		{
			//constructor
			Translation::Translation(canvas::cameras::Camera* camera, vec3 xt, float dt) : 
				Camera(camera), m_xt{xt}, m_dt{dt}
			{
				return;
			}

			//destructor
			Translation::~Translation(void)
			{
				return;
			}

			//update
			void Translation::setup(void)
			{
				Animation::setup();
			}
			void Translation::cleanup(void)
			{
				Animation::cleanup();
			}
			void Translation::animate(float t)
			{
				Animation::animate(t);
			}
		}
	}
}
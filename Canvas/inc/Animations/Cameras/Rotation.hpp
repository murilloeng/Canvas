#pragma once

//canvas
#include "Canvas/Canvas/inc/Math/quat.hpp"

#include "Canvas/Canvas/inc/Animations/Cameras/Camera.hpp"

namespace canvas
{
	namespace animations
	{
		namespace cameras
		{
			class Rotation : public Camera
			{
			public:
				//constructor
				Rotation(canvas::cameras::Camera*, quat);

				//destructor
				~Rotation(void);

				//update
				void setup(void) override;
				void cleanup(void) override;
				void animate(float) override;

			private:
				//data
				quat m_q0;
				quat m_qr;
				quat m_qt;
			};
		}
	}
}
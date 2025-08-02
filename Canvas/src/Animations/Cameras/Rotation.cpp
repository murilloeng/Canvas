//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"

#include "Canvas/Canvas/inc/Animations/Cameras/Rotation.hpp"

namespace canvas
{
	namespace animations
	{
		namespace cameras
		{
			//constructor
			Rotation::Rotation(canvas::cameras::Camera* camera, quat qt) : Camera(camera), m_qt{qt}
			{
				return;
			}

			//destructor
			Rotation::~Rotation(void)
			{
				return;
			}

			//update
			void Rotation::setup(void)
			{
				//data
				Animation::setup();
				const vec3 up = m_camera->up();
				const vec3 ur = m_camera->right();
				const vec3 uf = m_camera->front();
				//setup
				m_q0 = quat(ur, up, -uf);
				m_qr = m_q0.conjugate() * m_qt;
			}
			void Rotation::cleanup(void)
			{
				Animation::cleanup();
			}
			void Rotation::animate(float t)
			{
				//data
				Animation::animate(t);
				const float t0 = m_time_start;
				const float dt = m_time_duration;
				const float vt = m_easing.value((t - t0) / dt);
				const quat qt = m_q0 * (vt * m_qr.vector()).quaternion();
				//animate
				m_camera->direction(qt);
				//update
				m_camera->update();
			}
		}
	}
}
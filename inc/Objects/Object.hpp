#pragma once

namespace canvas
{
	class Scene;
	namespace cameras
	{
		class BoundingBox;
	}
}

namespace canvas
{
	namespace objects
	{
		class Object
		{
		public:
			//constructors
			Object(void);

			//destructor
			virtual ~Object(void);

			//data
			Scene* scene(void) const;

		protected:
			//draw
			virtual void setup(void);
			virtual void draw(void) const;

			//update
			virtual void update_on_motion(void) const;
			virtual void update_bounding_box(cameras::BoundingBox&) const;

			//data
			Scene* m_scene;

			//friends
			friend class canvas::Scene;
			friend class canvas::cameras::BoundingBox;
		};
	}
}
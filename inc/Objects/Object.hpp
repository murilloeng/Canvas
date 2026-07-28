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
			void show(void);
			void hide(void);
			bool visible(bool);
			bool visible(void) const;
			Scene* scene(void) const;

		protected:
			//draw
			virtual void draw(void);
			virtual void setup(void);
			virtual void update(void);

			//update
			virtual void update_on_motion(void) const;
			virtual void update_bounding_box(cameras::BoundingBox&) const;

			//data
			Scene* m_scene;
			bool m_visible;

			//friends
			friend class canvas::Scene;
			friend class canvas::cameras::BoundingBox;
		};
	}
}
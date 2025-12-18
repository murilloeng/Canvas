#pragma once

namespace canvas
{
	class Scene;
}

namespace canvas
{
	namespace cameras
	{
		class BoundingBox
		{
		public:
			//constructor
			BoundingBox(void);

			//destructor
			~BoundingBox(void);

			//status
			bool status(void) const;

			//compute
			void compute(const Scene*);
			void insert_vertex(const float*);

			//combine
			void combine(const BoundingBox&);
			static BoundingBox combine(const BoundingBox&, const BoundingBox&);

		private:
			//data
			float m_min[3];
			float m_max[3];
		};
	}
}
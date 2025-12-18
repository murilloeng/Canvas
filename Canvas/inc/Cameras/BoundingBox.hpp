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

			//data
			const float* min(void) const;
			const float* max(void) const;

			//status
			bool status(void) const;

			//compute
			void reset(void);
			void repair(void);
			void insert_vertex(const float*);
			void compute(const Scene*, bool, bool);

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
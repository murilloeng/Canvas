#pragma once

//std
#include <vector>
#include <cstdint>

//Canvas
#include "Canvas/inc/Objects/Object.hpp"
#include "Canvas/inc/Objects/Graph/Curve.hpp"
#include "Canvas/inc/Objects/Graph/Frame.hpp"

namespace canvas
{
	namespace objects
	{
		class Graph : public Object
		{
		public:
			//constructor
			Graph(void);

			//destructor
			~Graph(void);

			//data
			uint32_t font(uint32_t);
			uint32_t font(void) const;

			graphs::Frame& frame(void);
			const graphs::Frame& frame(void) const;

			std::vector<graphs::Curve*>& curves(void);
			const std::vector<graphs::Curve*>& curves(void) const;

		private:
			//draw
			void draw(void) override;
			void setup(void) override;
			void update(void) override;

			//data
			uint32_t m_font;
			graphs::Frame m_frame;
			std::vector<graphs::Curve*> m_curves;
		};
	}
}
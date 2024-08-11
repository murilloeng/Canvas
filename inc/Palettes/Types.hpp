#pragma once

//std
#include <cstdint>

namespace canvas
{
	namespace palettes
	{
		enum class type : uint32_t
		{
			jet,
			greys,
			plasma,
			whylrd,
			viridis,
			moreland,
			spectral,
			last
		};
	}
}
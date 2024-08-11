//std
#include <cstdio>
#include <cstdint>

//canvas
#include "Canvas/inc/Math/vec2.hpp"
#include "Canvas/inc/Objects/Tessellator.hpp"

//test
#include "Canvas/Test/inc/tessellation.hpp"

void examples::tessellation::non_convex_ccw_4(void)
{
	//data
	const uint32_t validator[] = {
		1, 2, 3,
		0, 1, 3
	};
	const uint32_t loops[] = {0, 4};
	const canvas::vec2 vertices[] = {
		{0, 0}, {1, 0.1f}, {2, 0}, {0, 2}
	};
	const uint32_t nl = sizeof(loops) / sizeof(uint32_t) - 1;
	const uint32_t nv = sizeof(vertices) / sizeof(canvas::vec2);
	uint32_t* triangles = (uint32_t*) alloca(3 * (nv - 2) * sizeof(uint32_t));
	//tessellation
	canvas::objects::Tessellator(vertices, loops, nl, triangles).tessellate();
	//validation
	for(uint32_t i = 0; i < 3 * (nv - 2); i++)
	{
		if(triangles[i] != validator[i])
		{
			printf("Test non convex ccw 4: not ok!\n");
			return;
		}
	}
	printf("Test non convex ccw 4: ok!\n");
}
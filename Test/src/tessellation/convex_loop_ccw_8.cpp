//std
#include <cstdio>
#include <cstdint>
#include <algorithm>

//canvas
#include "Canvas/Canvas/inc/Math/vec2.hpp"
#include "Canvas/Canvas/inc/Objects/Tessellator.hpp"

//test
#include "Canvas/Test/inc/examples.hpp"

void examples::tessellation::convex_loop_ccw_8(void)
{
	//data
	const uint32_t validator[] = {
		0, 4, 5,
		7, 4, 0,
		7, 0, 1,
		6, 7, 1,
		6, 1, 2,
		5, 6, 2,
		5, 2, 3,
		0, 5, 3
	};
	const uint32_t loops[] = {0, 4, 8};
	const canvas::vec2 vertices[] = {
		{0, 0}, {3, 0}, {3, 3}, {0, 3}, {1, 1}, {1, 2}, {2, 2}, {2, 1}
	};
	const uint32_t nl = sizeof(loops) / sizeof(uint32_t) - 1;
	const uint32_t nv = sizeof(vertices) / sizeof(canvas::vec2);
	uint32_t* triangles = (uint32_t*) alloca(3 * (nv - 2 + 2 * (nl - 1)) * sizeof(uint32_t));
	//tessellation
	canvas::objects::Tessellator(vertices, loops, nl, triangles).tessellate();
	//validation
	for(uint32_t i = 0; i < 3 * (nv - 2 + 2 * (nl - 1)); i++)
	{
		if(triangles[i] != validator[i])
		{
			printf("Test convex loop ccw 8: not ok!\n");
			return;
		}
	}
	printf("Test convex loop ccw 8: ok!\n");
}
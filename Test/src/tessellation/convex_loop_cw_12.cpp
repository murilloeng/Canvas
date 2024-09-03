//std
#include <cstdio>
#include <cstdint>
#include <algorithm>

//canvas
#include "Canvas/inc/Math/vec2.hpp"
#include "Canvas/inc/Objects/Tessellator.hpp"

//test
#include "Canvas/Test/inc/tessellation.hpp"

void examples::tessellation::convex_loop_cw_12(void)
{
	//data
	const uint32_t validator[] = {
		0,  4,  5,
		7,  4,  0,
		7,  0,  1,
		6,  7,  1,
		6,  1,  2,
		2, 10, 11,
		6,  2, 11,
		5,  6, 11,
		5, 11,  8,
		0,  5,  8,
		0,  8,  9,
		9, 10,  2,
		9,  2,  3,
		0,  9,  3
	};
	const uint32_t loops[] = {0, 4, 8, 12};
	const canvas::vec2 vertices[] = {
		{0, 0}, {0, 3}, {5, 3}, {5, 0}, {1, 1}, {2, 1}, {2, 2}, {1, 2}, {3, 1}, {4, 1}, {4, 2}, {3, 2}
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
			printf("Test convex loop cw 12: not ok!\n");
			return;
		}
	}
	printf("Test convex loop cw 12: ok!\n");
}
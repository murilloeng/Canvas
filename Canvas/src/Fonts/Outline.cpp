//std
#include <cstdint>

//FreeType
#include <freetype2/freetype/ftoutln.h>

//Canvas
#include "Canvas/Canvas/inc/Fonts/Line.hpp"
#include "Canvas/Canvas/inc/Fonts/Conic.hpp"
#include "Canvas/Canvas/inc/Fonts/Cubic.hpp"
#include "Canvas/Canvas/inc/Fonts/Outline.hpp"

//callbacks
static uint64_t xr[2];
static int callback_move(const FT_Vector* to, void* data)
{
	//contour
	((canvas::fonts::Outline*) data)->m_contours.push_back(new canvas::fonts::Contour());
	//update
	xr[0] = to->x;
	xr[1] = to->y;
	//return
	return 0;
}
static int callback_line(const FT_Vector* to, void* data)
{
	//data
	canvas::fonts::Line* line = new canvas::fonts::Line;
	//line
	line->m_points[0][0] = xr[0];
	line->m_points[0][1] = xr[1];
	line->m_points[1][0] = to->x;
	line->m_points[1][1] = to->y;
	//contour
	((canvas::fonts::Outline*) data)->m_contours.back()->m_items.push_back(line);
	//update
	xr[0] = to->x;
	xr[1] = to->y;
	//return
	return 0;
}
static int callback_conic(const FT_Vector* control, const FT_Vector* to, void* data)
{
	//data
	canvas::fonts::Conic* conic = new canvas::fonts::Conic;
	//conic
	conic->m_points[0][0] = xr[0];
	conic->m_points[0][1] = xr[1];
	conic->m_points[1][0] = to->x;
	conic->m_points[1][1] = to->y;
	conic->m_control[0] = control->x;
	conic->m_control[1] = control->y;
	//contour
	((canvas::fonts::Outline*) data)->m_contours.back()->m_items.push_back(conic);
	//update
	xr[0] = to->x;
	xr[1] = to->y;
	//return
	return 0;
}
static int callback_cubic(const FT_Vector* control_1, const FT_Vector* control_2, const FT_Vector* to, void* data)
{
	//data
	canvas::fonts::Cubic* cubic = new canvas::fonts::Cubic;
	//conic
	cubic->m_points[0][0] = xr[0];
	cubic->m_points[0][1] = xr[1];
	cubic->m_points[1][0] = to->x;
	cubic->m_points[1][1] = to->y;
	cubic->m_controls[0][0] = control_1->x;
	cubic->m_controls[0][1] = control_1->y;
	cubic->m_controls[1][0] = control_2->x;
	cubic->m_controls[1][1] = control_2->y;
	//contour
	((canvas::fonts::Outline*) data)->m_contours.back()->m_items.push_back(cubic);
	//update
	xr[0] = to->x;
	xr[1] = to->y;
	//return
	return 0;
}

namespace canvas
{
	namespace fonts
	{
		//constructor
		Outline::Outline(void)
		{
			return;
		}

		//destructor
		Outline::~Outline(void)
		{
			for(const Contour* contour : m_contours) delete contour;
		}

		//setup
		void Outline::setup(FT_Face face)
		{
			//data
			FT_BBox box;
			FT_Outline_Funcs callbacks;
			//setup
			callbacks.delta = 0;
			callbacks.shift = 0;
			callbacks.move_to = callback_move;
			callbacks.line_to = callback_line;
			callbacks.conic_to = callback_conic;
			callbacks.cubic_to = callback_cubic;
			//decompose
			FT_Outline_Get_CBox(&face->glyph->outline, &box);
			FT_Outline_Decompose(&face->glyph->outline, &callbacks, this);
			//bounding box
			m_bounding_box = BoundingBox(box);
		}

		//print
		void Outline::print(void) const
		{
			uint32_t counter = 0;
			for(const Contour* contour : m_contours)
			{
				printf("Contour: %d\n", counter++);
				contour->print();
			}
			m_bounding_box.print();
		}
	}
}
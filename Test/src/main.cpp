//std
#include <cstdlib>
#include <stdexcept>

//freetype
#include <freetype2/freetype/ftglyph.h>
#include <freetype2/freetype/ftoutln.h>

//canvas
#include "Canvas/Canvas/inc/Objects/1D/Line.hpp"
#include "Canvas/Canvas/inc/Objects/0D/Point.hpp"

//test
#include "Canvas/Test/inc/Engine.hpp"
#include "Canvas/Test/inc/examples.hpp"

static int callback_move(const FT_Vector* to, void* user)
{
	printf("move: %zd %zd\n", to->x, to->y);
	return 0;
}
static int callback_line(const FT_Vector* to, void* user)
{
	printf("line: %zd %zd\n", to->x, to->y);
	return 0;
}
static int callback_conic(const FT_Vector* control, const FT_Vector* to, void* user)
{
	printf("conic: %zd %zd %zd %zd\n", control->x, control->y, to->x, to->y);
	return 0;
}
static int callback_cubic(const FT_Vector* control1, const FT_Vector* control2, const FT_Vector* to, void* user)
{
	printf("cubic: %zd %zd %zd %zd %zd %zd\n", control1->x, control1->y, control2->x, control2->y, to->x, to->y);
	return 0;
}

int main(void)
{
	try
	{
		examples::scenes::examples();
		return EXIT_SUCCESS;
		//path
		const char* path = "/usr/share/fonts/truetype/msttcorefonts/times.ttf";
		//library
		FT_Library m_ft_library;
		if(FT_Init_FreeType(&m_ft_library))
		{
			throw std::runtime_error("FreeType initialization failed!");
		}
		//face
		FT_Face m_face;
		if(FT_New_Face(m_ft_library, path, 0, &m_face))
		{
			throw std::runtime_error("FreeType face loading failed!");
		}
		//glyph
		FT_Outline_Funcs callbacks;
		callbacks.shift = 0;
		callbacks.delta = 0;
		callbacks.move_to = callback_move;
		callbacks.line_to = callback_line;
		callbacks.conic_to = callback_conic;
		callbacks.cubic_to = callback_cubic;
		FT_Load_Char(m_face, 'P', FT_LOAD_DEFAULT);
		FT_Outline_Decompose(&m_face->glyph->outline, &callbacks, nullptr);
		//engine
		Engine engine;
		canvas::Scene* scene = engine.scene();
		for(uint8_t i = 0; i < m_face->glyph->outline.n_points; i++)
		{
			canvas::objects::Point* point = new canvas::objects::Point;
			point->position({
				(float) m_face->glyph->outline.points[i].x, (float) m_face->glyph->outline.points[i].y, 0
			});
			scene->add_object(point);
		}
		for(uint8_t i = 0; i < m_face->glyph->outline.n_contours; i++)
		{
			const uint8_t b = m_face->glyph->outline.contours[i];
			const uint8_t a = i ? m_face->glyph->outline.contours[i - 1] + 1 : 0;
			for(uint8_t j = a; j <= b; j++)
			{
				const float x1 = (float) m_face->glyph->outline.points[a + (j - a + 0) % (b - a + 1)].x;
				const float y1 = (float) m_face->glyph->outline.points[a + (j - a + 0) % (b - a + 1)].y;
				const float x2 = (float) m_face->glyph->outline.points[a + (j - a + 1) % (b - a + 1)].x;
				const float y2 = (float) m_face->glyph->outline.points[a + (j - a + 1) % (b - a + 1)].y;
				canvas::objects::Line* line = new canvas::objects::Line;
				line->point(0, {x1, y1, 0});
				line->point(1, {x2, y2, 0});
				scene->add_object(line);
			}
		}
		scene->update(true);
		scene->camera().bound();
		scene->camera().update();
		engine.show_fps(false);
		engine.start();
		//cleanup
		FT_Done_Face(m_face);
		FT_Done_FreeType(m_ft_library);
	}
	catch(const std::exception& e)
	{
		fprintf(stderr, "%s\n", e.what());
	}
	//return
	return EXIT_SUCCESS;
}
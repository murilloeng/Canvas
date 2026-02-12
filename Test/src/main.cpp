//std
#include <cstdlib>
#include <stdexcept>

//test
#include "Canvas/Test/inc/Engine.hpp"
#include "Canvas/Test/inc/examples.hpp"

#include "Canvas/Canvas/inc/Fonts/Font.hpp"
#include "Canvas/Canvas/inc/Objects/2D/Circle.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Polyline.hpp"

int main(void)
{
	try
	{
		//engine
		Engine engine;
		engine.show_fps(true);
		const uint32_t mesh[] = {100, 100};
		//font
		engine.scene()->add_font("times");
		engine.scene()->update(true);
		//outline
		const canvas::fonts::Outline& outline = engine.scene()->font(0)->glyph('q').outline();
		const float x_min = (float) outline.m_bounding_box.m_min[0];
		const float y_min = (float) outline.m_bounding_box.m_min[1];
		const float x_max = (float) outline.m_bounding_box.m_max[0];
		const float y_max = (float) outline.m_bounding_box.m_max[1];
		//bounding box
		canvas::objects::Polyline* bounding_box = new canvas::objects::Polyline;
		bounding_box->vertices().push_back({x_min, y_min, 0});
		bounding_box->vertices().push_back({x_max, y_min, 0});
		bounding_box->vertices().push_back({x_max, y_max, 0});
		bounding_box->vertices().push_back({x_min, y_max, 0});
		bounding_box->vertices().push_back({x_min, y_min, 0});
		//objects
		engine.scene()->add_object(bounding_box);
		for(const canvas::fonts::Contour* contour : outline.m_contours)
		{
			for(const canvas::fonts::Item* item : contour->m_items)
			{
				engine.scene()->add_object(item->object());
			}
		}
		const float dx = float(x_max - x_min) / mesh[0];
		const float dy = float(y_max - y_min) / mesh[1];
		for(uint32_t i = 0; i < mesh[0]; i++)
		{
			for(uint32_t j = 0; j < mesh[1]; j++)
			{
				uint32_t hit_counter = 0;
				const float position[] = {x_min + (i + 0.5f) * dx, y_min + (j + 0.5f) * dy, 0};
				canvas::objects::Circle* circle = new canvas::objects::Circle;
				circle->radius(0.5f);
				circle->stroke(false);
				circle->scale({dx, dy, 1});
				circle->shift({x_min + (i + 0.5f) * dx, y_min + (j + 0.5f) * dy, 0});
				engine.scene()->add_object(circle);
				for(const canvas::fonts::Contour* contour : outline.m_contours)
				{
					for(const canvas::fonts::Item* item : contour->m_items)
					{
						hit_counter += item->hit(position);
					}
				}
				circle->color_fill(hit_counter % 2 == 0 ? canvas::Color(0.5f, 0.5f, 0.5f, 0.5f) : canvas::Color(0.0f, 0.0f, 1.0f, 0.5f));
			}
		}
		//update
		engine.scene()->update(true);
		engine.scene()->camera().bound();
		engine.scene()->camera().update();
		//start
		engine.start();
		//examples::scenes::examples();
	}
	catch(const std::exception& e)
	{
		fprintf(stderr, "%s\n", e.what());
	}
	//return
	return EXIT_SUCCESS;
}
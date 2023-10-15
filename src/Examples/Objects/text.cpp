//canvas
#include "inc/Scene/Scene.hpp"
#include "inc/Objects/Image/Text.hpp"

//examples
#include "inc/Examples/examples.hpp"

namespace examples
{
	namespace objects
	{
		void text(canvas::Scene* scene)
		{
			scene->add_font("times");
			canvas::objects::Text* text;
			text = new canvas::objects::Text;
			text->text("my long long test string");
			scene->add_object(text);
		}
	}
}
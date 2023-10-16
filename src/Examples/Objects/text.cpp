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
			canvas::objects::Text* text = new canvas::objects::Text;
			text->text("this is a\nmulti-line\ntext\twith tab");
			scene->add_object(text);
		}
	}
}
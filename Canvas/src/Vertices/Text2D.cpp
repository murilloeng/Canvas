//ext
#include "external/cpp/inc/GL/glew.h"

//canvas
#include "Canvas/Canvas/inc/GPU/Attribute.hpp"
#include "Canvas/Canvas/inc/Vertices/Text2D.hpp"

namespace canvas
{
	namespace vertices
	{
		//constructor
		Text2D::Text2D(void)
		{
			return;
		}

		//destructor
		Text2D::~Text2D(void)
		{
			return;
		}

		//attributes
		void Text2D::attributes(std::vector<Attribute>& attributes)
		{
			Vertex2D::attributes(attributes);
			attributes.push_back(Attribute(GL_FLOAT, 4));
			attributes.push_back(Attribute(GL_FLOAT, 2));
		}
	}
}
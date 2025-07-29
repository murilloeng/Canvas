//ext
#include "external/cpp/inc/GL/glew.h"

//canvas
#include "Canvas/Canvas/inc/Vertices/Text3D.hpp"

#include "Canvas/Canvas/inc/Buffers/Attribute.hpp"

namespace canvas
{
	namespace vertices
	{
		//constructor
		Text3D::Text3D(void)
		{
			return;
		}

		//destructor
		Text3D::~Text3D(void)
		{
			return;
		}

		//attributes
		void Text3D::attributes(std::vector<Attribute>& attributes)
		{
			Vertex3D::attributes(attributes);
			attributes.push_back(Attribute(GL_FLOAT, 4));
			attributes.push_back(Attribute(GL_FLOAT, 2));
		}
	}
}
//ext
#include "external/cpp/inc/GL/glew.h"

//canvas
#include "Canvas/Canvas/inc/GPU/Attribute.hpp"
#include "Canvas/Canvas/inc/Vertices/Image2D.hpp"

namespace canvas
{
	namespace vertices
	{
		//constructor
		Image2D::Image2D(void)
		{
			return;
		}

		//destructor
		Image2D::~Image2D(void)
		{
			return;
		}

		//attributes
		void Image2D::attributes(std::vector<Attribute>& attributes)
		{
			Vertex2D::attributes(attributes);
			attributes.push_back(Attribute(GL_FLOAT, 2));
		}
	}
}
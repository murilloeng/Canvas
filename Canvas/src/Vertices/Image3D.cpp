//ext
#include "external/cpp/inc/GL/glew.h"

//canvas
#include "Canvas/Canvas/inc/GPU/Attribute.hpp"
#include "Canvas/Canvas/inc/Vertices/Image3D.hpp"

namespace canvas
{
	namespace vertices
	{
		//constructor
		Image3D::Image3D(void)
		{
			return;
		}

		//destructor
		Image3D::~Image3D(void)
		{
			return;
		}

		//attributes
		void Image3D::attributes(std::vector<Attribute>& attributes)
		{
			Vertex3D::attributes(attributes);
			attributes.push_back(Attribute(GL_FLOAT, 2));
		}
	}
}
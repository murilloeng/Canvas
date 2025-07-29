//ext
#include "external/cpp/inc/GL/glew.h"

//canvas
#include "Canvas/Canvas/inc/Renderer/Attribute.hpp"
#include "Canvas/Canvas/inc/Vertices/Vertex2D.hpp"

namespace canvas
{
	namespace vertices
	{
		//constructor
		Vertex2D::Vertex2D(void)
		{
			return;
		}

		//destructor
		Vertex2D::~Vertex2D(void)
		{
			return;
		}

		//attributes
		void Vertex2D::attributes(std::vector<Attribute>& attributes)
		{
			attributes.push_back(Attribute(GL_FLOAT, 2));
		}
	}
}
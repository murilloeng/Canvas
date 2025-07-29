//ext
#include "external/cpp/inc/GL/glew.h"

//canvas
#include "Canvas/Canvas/inc/Renderer/Attribute.hpp"
#include "Canvas/Canvas/inc/Vertices/Vertex3D.hpp"

namespace canvas
{
	namespace vertices
	{
		//constructor
		Vertex3D::Vertex3D(void)
		{
			return;
		}

		//destructor
		Vertex3D::~Vertex3D(void)
		{
			return;
		}

		//attributes
		void Vertex3D::attributes(std::vector<Attribute>& attributes)
		{
			attributes.push_back(Attribute(GL_FLOAT, 3));
		}
	}
}
//ext
#include "external/cpp/inc/GL/glew.h"

//canvas
#include "Canvas/Canvas/inc/GPU/Attribute.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"

namespace canvas
{
	namespace vertices
	{
		//constructor
		Model3D::Model3D(void)
		{
			return;
		}

		//destructor
		Model3D::~Model3D(void)
		{
			return;
		}

		//attributes
		void Model3D::attributes(std::vector<Attribute>& attributes)
		{
			Vertex3D::attributes(attributes);
			attributes.push_back(Attribute(GL_FLOAT, 4));
		}
	}
}
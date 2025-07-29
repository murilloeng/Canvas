//ext
#include "external/cpp/inc/GL/glew.h"

//canvas
#include "Canvas/Canvas/inc/Renderer/Attribute.hpp"
#include "Canvas/Canvas/inc/Vertices/Model2D.hpp"

namespace canvas
{
	namespace vertices
	{
		//constructor
		Model2D::Model2D(void)
		{
			return;
		}

		//destructor
		Model2D::~Model2D(void)
		{
			return;
		}

		//attributes
		void Model2D::attributes(std::vector<Attribute>& attributes)
		{
			Vertex2D::attributes(attributes);
			attributes.push_back(Attribute(GL_FLOAT, 4));
		}
	}
}
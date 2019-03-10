#include "Mesh.h"
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_NO_IMPLEMENTATION
#define TINYGLTF_NO_STB_IMAGE_WRITE
#include "tiny_gltf.h"

Mesh::Mesh(const char * filename)
{
	std::string err, warn;
	tinygltf::TinyGLTF loader;
	bool ret = loader.LoadBinaryFromFile(&m_model, &err, &warn, filename);
	if (ret)
	{

	}
	else
	{
		m_VAO = 0;
		m_VBO = 0;
		m_EBO = 0;
	}
}

Mesh::~Mesh()
{
}

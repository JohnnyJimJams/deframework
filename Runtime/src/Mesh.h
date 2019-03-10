#ifndef __MESH_H_
#define __MESH_H_

#define TINYGLTF_NO_IMPLEMENTATION
#define STB_IMAGE_NO_IMPLEMENTATION
#define TINYGLTF_NO_STB_IMAGE_WRITE
#include "tiny_gltf.h"

class Mesh
{
public:

	Mesh(const char * filename);
	~Mesh();
private:
	tinygltf::Model m_model;
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_EBO;
};

#endif // __MESH_H_
#ifndef __MESH_H_
#define __MESH_H_

#define TINYGLTF_NO_IMPLEMENTATION
#define STB_IMAGE_NO_IMPLEMENTATION
#define TINYGLTF_NO_STB_IMAGE_WRITE
#include "tiny_gltf.h"
#include <GL/gl3w.h> 

class Mesh
{
public:
	Mesh();
	Mesh(const char * filename);
	~Mesh();
	void Draw();
	std::string GetLog() { return m_log; }
	void Load(const char * filename);
private:
	void BindModel();
	void BindModelNodes(std::map<int, GLuint> vbos, tinygltf::Node &node);
	void BindMesh(std::map<int, GLuint> vbos, tinygltf::Mesh &mesh);
	void DrawModelNodes(tinygltf::Node &node);
	void DrawMesh(tinygltf::Mesh &mesh);
	tinygltf::Model m_model;
	unsigned int m_VAO;
	std::string m_log;
	bool hasMesh;
};

#endif // __MESH_H_
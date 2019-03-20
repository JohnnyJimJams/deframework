#include "Mesh.h"
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_NO_IMPLEMENTATION
#define TINYGLTF_NO_STB_IMAGE_WRITE
#include "tiny_gltf.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

Mesh::Mesh()
{
	hasMesh = false;
}

Mesh::Mesh(const char * filename)
{
	hasMesh = false;
	std::string err, warn;
	tinygltf::TinyGLTF loader;
	bool ret = loader.LoadBinaryFromFile(&m_model, &err, &warn, filename);
	if (ret)
	{
		BindModel();
		hasMesh = true;
	}
	else
	{
		m_VAO = 0;
	}
}

Mesh::~Mesh()
{
}

void Mesh::Load(const char * filename)
{
	hasMesh = false;
	std::string err, warn;
	tinygltf::TinyGLTF loader;
	bool ret = loader.LoadBinaryFromFile(&m_model, &err, &warn, filename);
	if (ret)
	{
		BindModel();
		hasMesh = true;
	}
	else
	{
		m_VAO = 0;
	}
}

void Mesh::BindModel()
{
	std::map<int, GLuint> vbos;
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	const tinygltf::Scene &scene = m_model.scenes[m_model.defaultScene];
	m_log += "Number of scene nodes: ";
	m_log += std::to_string(scene.nodes.size());
	m_log += "\n";
	for (size_t i = 0; i < scene.nodes.size(); ++i) {
		BindModelNodes(vbos, m_model.nodes[scene.nodes[i]]);
	}

	glBindVertexArray(0);
	for (size_t i = 0; i < vbos.size(); ++i) {
		glDeleteBuffers(1, &vbos[i]);
	}
}

void Mesh::BindModelNodes(std::map<int, GLuint> vbos, tinygltf::Node &node)
{
	BindMesh(vbos, m_model.meshes[node.mesh]);
	for (size_t i = 0; i < node.children.size(); i++) {
		BindModelNodes(vbos, m_model.nodes[node.children[i]]);
	}
}

void Mesh::BindMesh(std::map<int, GLuint> vbos, tinygltf::Mesh &mesh)
{
	for (size_t i = 0; i < m_model.bufferViews.size(); ++i) {
		const tinygltf::BufferView &bufferView = m_model.bufferViews[i];
		if (bufferView.target == 0) { // unsupported target 
			continue;  
		}

		tinygltf::Buffer buffer = m_model.buffers[bufferView.buffer];

		GLuint vbo;
		glGenBuffers(1, &vbo);
		vbos[i] = vbo;
		glBindBuffer(bufferView.target, vbo);
		glBufferData(bufferView.target, bufferView.byteLength, &buffer.data.at(0) + bufferView.byteOffset, GL_STATIC_DRAW);
	}

	for (size_t i = 0; i < mesh.primitives.size(); ++i) {
		tinygltf::Primitive primitive = mesh.primitives[i];
		tinygltf::Accessor indexAccessor = m_model.accessors[primitive.indices];

		for (auto &attrib : primitive.attributes) {
			tinygltf::Accessor accessor = m_model.accessors[attrib.second];
			int byteStride =
				accessor.ByteStride(m_model.bufferViews[accessor.bufferView]);
			glBindBuffer(GL_ARRAY_BUFFER, vbos[accessor.bufferView]);

			int size = 1;
			if (accessor.type != TINYGLTF_TYPE_SCALAR) {
				size = accessor.type;
			}

			int vaa = -1;
			if (attrib.first.compare("POSITION") == 0) vaa = 0;
			if (attrib.first.compare("NORMAL") == 0) vaa = 1;
			if (attrib.first.compare("TEXCOORD_0") == 0) vaa = 2;
			if (vaa > -1) {
				glEnableVertexAttribArray(vaa);
				glVertexAttribPointer(vaa, size, accessor.componentType,
					accessor.normalized ? GL_TRUE : GL_FALSE,
					byteStride, BUFFER_OFFSET(accessor.byteOffset));
			}
		}
	}
}

void Mesh::DrawMesh(tinygltf::Mesh &mesh) {
	for (size_t i = 0; i < mesh.primitives.size(); ++i) {
		tinygltf::Primitive primitive = mesh.primitives[i];
		tinygltf::Accessor indexAccessor = m_model.accessors[primitive.indices];

		glDrawElements(primitive.mode, indexAccessor.count, indexAccessor.componentType, BUFFER_OFFSET(indexAccessor.byteOffset));
	}
}

// recursively draw node and children nodes of model
void Mesh::DrawModelNodes(tinygltf::Node &node) {
	DrawMesh(m_model.meshes[node.mesh]);
	for (size_t i = 0; i < node.children.size(); i++) {
		DrawModelNodes(m_model.nodes[node.children[i]]);
	}
}
void Mesh::Draw() {
	if (hasMesh)
	{
		glBindVertexArray(m_VAO);

		const tinygltf::Scene &scene = m_model.scenes[m_model.defaultScene];
		for (size_t i = 0; i < scene.nodes.size(); ++i) {
			DrawModelNodes(m_model.nodes[scene.nodes[i]]);
		}

		glBindVertexArray(0);
	}
}

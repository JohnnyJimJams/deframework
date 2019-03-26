#include "Layer.h"
#include "Demo.h"
#include <string>

using namespace std;

Demo::Demo(unsigned int width, unsigned int height)
{
	m_width = width;
	m_height = height;
	PrepareFullScreenQuad();
}

Demo::~Demo()
{
	for (auto m : m_materials)
		RemoveMaterial(m.first);
	for (auto m : m_meshes)
		RemoveMesh(m.first);
	for (auto t : m_textures)
		RemoveTexture2D(t.first);
	for (auto s : m_shaders)
		RemoveShader(s.first);
}

unsigned int Demo::GetWidth()
{
	return m_width;
}

unsigned int Demo::GetHeight()
{
	return m_height;
}

void Demo::DrawFullScreenQuad()
{
	glBindVertexArray(m_fullscreenQuadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

Texture2D * Demo::GetCurrentFrame()
{
	return nullptr;
}

Layer *Demo::AddLayer(std::string name)
{
	// check if layer exists with this name
	for (auto l : m_layers)
	{
		if (l->name == name)
		{
			return l;
		}
	}
	m_layers.push_back(new Layer(m_width, m_height, name));
	
	return m_layers.back();
}

Layer * Demo::AddLayer()
{
	int layerNum = 1;
	string name = "layer" + to_string(layerNum);

	bool nameExists;
	do 
	{
		if (nameExists = LayerNameExists(name))
		{
			layerNum++;
			name = "layer" + to_string(layerNum);
		}
	} while (nameExists);

	return AddLayer(name);
}

void Demo::DeleteLayers(std::vector<Layer*>* layersToDelete)
{
	for (auto layerToDelete : *layersToDelete)
	{
		string nameToDelete = layerToDelete->name;
		int index = GetLayerIndex(nameToDelete);
		if (index > -1)
		{
			m_layers.erase(m_layers.begin() + index);
		}
		delete(layerToDelete);
	}
}

int Demo::GetLayerIndex(string name)
{
	int index = -1;
	for (unsigned int i = 0; i < m_layers.size(); i++)
	{
		if (m_layers[i]->name == name)
		{
			index = i;
			break;
		}
	}
	return index;
}

void Demo::AddMesh(Mesh *meshToAdd)
{
}

std::string Demo::AddMesh()
{
	// create a unique mesh name
	int meshNum = 1;
	string name = "mesh" + to_string(meshNum);

	bool nameExists;
	do
	{
		if (nameExists = MeshNameExists(name))
		{
			meshNum++;
			name = "mesh" + to_string(meshNum);
		}
	} while (nameExists);

	// Create new mesh
	Mesh *newMesh = new Mesh();

	m_meshes[name] = newMesh;

	return name;
}

void Demo::RemoveMesh(std::string meshToRemove)
{
	if (MeshNameExists(meshToRemove))
	{
		Mesh *meshToDelete = m_meshes[meshToRemove];
		m_meshes.erase(meshToRemove);
		delete(meshToDelete);
	}
}

bool Demo::MeshNameExists(std::string name)
{
	return (!(m_meshes.find(name) == m_meshes.end()));
}

std::string Demo::AddMaterial()
{
	// create a unique mat name
	int matNum = 1;
	string name = "material" + to_string(matNum);

	bool nameExists;
	do
	{
		if (nameExists = MaterialNameExists(name))
		{
			matNum++;
			name = "material" + to_string(matNum);
		}
	} while (nameExists);

	// Create new mat
	Material *newMaterial= new Material();

	m_materials[name] = newMaterial;

	return name;
}

void Demo::RemoveMaterial(std::string materialToRemove)
{
	if (MaterialNameExists(materialToRemove))
	{
		Material *matToDelete = m_materials[materialToRemove];
		m_materials.erase(materialToRemove);
		delete(matToDelete);
	}
}

bool Demo::MaterialNameExists(std::string name)
{
	return (!(m_materials.find(name) == m_materials.end()));
}

std::string Demo::AddTexture2D()
{
	// create a unique tex name
	int texNum = 1;
	string name = "texture" + to_string(texNum);

	bool nameExists;
	do
	{
		if (nameExists = Texture2DNameExists(name))
		{
			texNum++;
			name = "texture" + to_string(texNum);
		}
	} while (nameExists);

	// Create new tex
	Texture2D *newTexture = new Texture2D(1024, 1024, 4);

	m_textures[name] = newTexture;

	return name;
}

bool Demo::Texture2DNameExists(std::string name)
{
	return (!(m_textures.find(name) == m_textures.end()));
}

void Demo::AddShader(ShaderProgram * shaderToAdd)
{
}

void Demo::RemoveShader(std::string shaderToRemove)
{
	if (ShaderNameExists(shaderToRemove))
	{
		ShaderProgram *shaderToDelete = m_shaders[shaderToRemove];
		m_shaders.erase(shaderToRemove);
		delete(shaderToDelete);
	}
}

bool Demo::ShaderNameExists(std::string name)
{
	return (!(m_shaders.find(name) == m_shaders.end()));
}

void Demo::RemoveTexture2D(std::string texToRemove)
{
	if (Texture2DNameExists(texToRemove))
	{
		Texture2D *textureToDelete = m_textures[texToRemove];
		m_textures.erase(texToRemove);
		delete(textureToDelete);
	}
}

bool Demo::LayerNameExists(string name)
{
	for (auto l : m_layers)
	{
		if (l->name == name)
		{
			return true;
		}
	}
	return false;
}

void Demo::PrepareFullScreenQuad()
{
	float quad[] =
	{
		-1.0f,-1.0f, 0.0f, 0.0f, 1.0f,
		 1.0f,-1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

		-1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f,-1.0f, 0.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	};
	glGenVertexArrays(1, &m_fullscreenQuadVAO);
	glBindVertexArray(m_fullscreenQuadVAO);
	glGenBuffers(1, &m_fullscreenQuadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_fullscreenQuadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 5 * 6, quad, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, ((char*)0) + 12);
	glBindVertexArray(0);
}


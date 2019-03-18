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


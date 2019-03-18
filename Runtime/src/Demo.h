#ifndef __DEMO_H_
#define __DEMO_H_

#include <GL/gl3w.h> 
#include "Texture2D.h"
#include "Layer.h"
#include <vector>

class Demo
{
public:
	Demo(unsigned int width, unsigned int height);
	virtual ~Demo();

	unsigned int GetWidth();
	unsigned int GetHeight();
	void DrawFullScreenQuad();
	Texture2D *GetCurrentFrame();
	std::vector<Layer *> &GetLayers() { return m_layers; }
	Layer *AddLayer(std::string name);
	Layer *AddLayer();
	void DeleteLayers(std::vector<Layer *> *layersToDelete);
	bool LayerNameExists(std::string name);
	int GetLayerIndex(std::string name);
private:
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_fullscreenQuadVAO;
	unsigned int m_fullscreenQuadVBO;

	std::vector<Layer *> m_layers;

	void PrepareFullScreenQuad();

};

#endif // __DEMO_H_
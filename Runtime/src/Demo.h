#ifndef __DEMO_H_
#define __DEMO_H_

#include <GL/gl3w.h> 
#include "Texture2D.h"
#include "Layer.h"
#include "Material.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include <vector>
#include <map>
#include <string>

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

	void AddMeshes(std::map<std::string, Mesh *> meshesToAdd);
	void AddMesh(std::string name);
	void RemoveMeshes(std::vector<std::string>  meshesToRemove);
private:
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_fullscreenQuadVAO;
	unsigned int m_fullscreenQuadVBO;

	std::vector<Layer *> m_layers;

	std::map<std::string, Material *> m_materials;
	std::map<std::string, Texture2D *> m_textures;
	std::map<std::string, ShaderProgram *> m_shaders;
	std::map<std::string, Mesh *> m_meshes;

	void PrepareFullScreenQuad();

};

#endif // __DEMO_H_
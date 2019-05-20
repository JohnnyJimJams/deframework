#ifndef __DEMO_H_
#define __DEMO_H_

#include <GL/gl3w.h> 
#include "Layer.h"

#include "Texture2D.h"
#include "Material.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Animation.h"
#include "MP3.h"

#include <vector>
#include <map>
#include <string>

class Demo
{
public:
	Demo(unsigned int width, unsigned int height, LPCWSTR musicPath);
	virtual ~Demo();

	void Tick(double time);
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

	std::string AddMesh(Mesh *meshToAdd);
	void AddMesh(std::string name, Mesh *meshToAdd);
	std::string AddMesh();
	void RemoveMesh(std::string meshToRemove);
	bool MeshNameExists(std::string name);
	std::map<std::string, Mesh *> &GetMeshes() { return m_meshes; }
	std::string GetMeshName(Mesh *mesh);
	
	std::string AddMaterial();
	void AddMaterial(std::string name, Material *material);
	void RemoveMaterial(std::string materialToRemove);
	bool MaterialNameExists(std::string name);
	std::map<std::string, Material *> &GetMaterials() { return m_materials; }
	std::string GetMaterialName(Material *material);

	std::string AddTexture2D();
	void AddTexture2D(std::string name, Texture2D *texture);
	void RemoveTexture2D(std::string texToRemove);
	bool Texture2DNameExists(std::string name);
	std::map<std::string, Texture2D *> &GetTextures() { return m_textures; }
	std::string GetTexture2DName(Texture2D *texture);

	void AddShader(ShaderProgram *shaderToAdd);
	void AddShader(std::string name, ShaderProgram *shaderToAdd);
	void RemoveShader(std::string shaderToRemove);
	bool ShaderNameExists(std::string name);
	std::map<std::string, ShaderProgram *> &GetShaders() { return m_shaders; }
	std::string GetShaderName(ShaderProgram *shader);

	std::vector<Animation> Animations;
	
	Mp3* GetAudio();
	void Play();
	void Stop();
	double GetMusicSecondsNow();
	double GetMusicSecondsTotal();
	bool IsKeyed(std::string prop);
	Animation* AnimationByID(std::string id);

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
	Mp3* audio;

};

#endif // __DEMO_H_
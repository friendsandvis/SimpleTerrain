#pragma once

#define GLEW_STATIC

#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include"SOMath.h"
#include"shaderprogram.h"
#include"socamera.h"

#include<vector>
#include<iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>




struct Vertex
{
	float data[11];
};

class Texture
{
public:
	Texture();
	~Texture() {};

	void setTextue(GLuint texid);
	void setTextureType(aiTextureType type);
	aiTextureType getTextureType();
	GLuint getTexture();
	GLuint64 getBindLessTexture();
	void setBindLess();
private:
	GLuint texid;
	GLuint64 texidbindless;
	aiTextureType textype;
};

class Mesh
{
public:
	Mesh();
	~Mesh() {};
	void setMesh(std::vector<Vertex> verticies, std::vector<unsigned> indicies, std::vector<Texture> textures);
	void makeBuffers();
	void render(soprogram::Program& progid);

private:
	std::vector<Vertex> verticies;
	std::vector<unsigned> indicies;
	std::vector<Texture> textures;

	GLuint vaoid, eboid, vboid;
};

class Model
{
public:
	Model(const char* textureloc);
	~Model() {};

	int setModel(const char* modelpath);
	void render(soprogram::Program& progid);
	void makeBuffers();

private:

	char textureloc[50];
	std::vector<Mesh> meshes;
	Model(const Model&);
	Model();

	void setAllData(aiNode *node, const aiScene *scene);
	Mesh setMeshData(aiMesh *mesh, const aiScene *scene);
	void setTextures(aiMaterial* material, std::vector<Texture>& textures, aiTextureType textype);

};
#pragma once

#define GLEW_STATIC


#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include"SOMath.h"
#include"shaderprogram.h"

#include<iostream>
#include<vector>
#include<random>


struct ImageData
{
	int width;
	int height;
	unsigned char* data;
};

void getImageData(const char* imageloc, ImageData& datapack);
GLuint getTexture(const char* texturename,int mipmaplevel);
GLuint getTextureGreyScale(const char* texturename, int mipmaplevel);
void freeImageData(ImageData& imagedata);

class Plane
{
	public:
		somath::mat4 model;

		Plane();
		~Plane() {}


		void destroy();
		GLuint setPlane();
		void render();
	private:
		GLuint vboid,vaoid;

		
		Plane(const Plane&) {}
};


/*
*Window Creation return code:      -1 == window creation Failed
*/
class Window
{
	public:
		Window();
		~Window() {};
		

		int setWindow(int width, int height, const char* windowname);
		int destroyWindow();
		int getWidth();
		int getHeight();
		GLFWwindow* getWindowID();

	private:
		GLFWwindow* windowid;
		int width, height;

		Window(Window&) {};
		
};

class Skybox
{
	public:
		Skybox();
		~Skybox() {};
		void setSkybox(const char** texturename);
		void render();
		void destroy();
		GLuint64 getSkyboxTexBindLess();

	private:
		GLuint skyboxid;
		GLuint64 skyboxbindlessid;
		GLuint vao, vbo;

		Skybox(const Skybox&) {}
		
};


class FrameBuffer
{
	public:
		FrameBuffer();
		~FrameBuffer() {}
		void makeFrameBuffer(int width, int height, bool depthbufferneeded);
		void bind();
		GLuint getFBOid();
		GLuint getTexture();
		GLuint64 getTextureBindLess();
		GLuint getDepthTexture();
		GLuint64 getDepthTextureBindLess();
		
	private:
		GLuint fboid, depthtexid,texid;
		GLuint64 texidbindless,depthtexidbindless;

		
		FrameBuffer(const FrameBuffer&) {}
};



class TerrainMesh
{

public:
	TerrainMesh();
	~TerrainMesh() {}

	void TerrainMesh::setTerrainMesh(int nofx, int noofy, float sizex , float sizey , int randseed ,float terrainareareduction);
	void setHeightMap(double heightofterrain);
	void render();
	void destroyTerrain();
	GLuint64 getHmapBindless();
	somath::vec2 getWorldSize();
	somath::vec2 getWorldScale();
	
private:
	GLuint terrainvao;
	GLuint terrainvbo;
	GLuint heightmap;
	GLuint64 heightmapbindlessid;

	int noofxblocks, noofyblocks;
	float sizeofxblock, sizeofyblock;
	int randomsp;
	float terrainareadeduction;


	std::vector<GLfloat>* translatepos;

	
	TerrainMesh(const TerrainMesh&) {}
	void setTranslates();
};
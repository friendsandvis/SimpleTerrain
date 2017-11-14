#define STB_IMAGE_IMPLEMENTATION

#include"support.h"
#include<iostream>
#include<stb_image.h>
#include<fstream>


int saveHMAP(float* arr, long long size)
{
	std::ofstream hmapout;
	hmapout.open("textures/Hmap1.soi", std::ios::binary | std::ios::out);

	if (!hmapout.is_open())
		return -1;

	long long datawritten = 0;

	while (datawritten<size)
	{
		hmapout.write((char*)arr, size);
		datawritten = hmapout.tellp();
	}
	std::cout << '\n' << size << '\t' << datawritten << '\n';
	hmapout.close();

	return 0;

}

int getHMAP(float *arr, long long size)
{
	std::ifstream hmapout;
	hmapout.open("textures/Hmap1.soi", std::ios::binary | std::ios::in);

	if (!hmapout.is_open())
		return -1;

	long long datawritten = 0;

	while (datawritten<size)
	{
		hmapout.read((char*)arr, size);
		datawritten = hmapout.tellg();
	}

	hmapout.close();

	return 0;
}

void getImageData(const char* imageloc, ImageData& datapack)
{
	int width, height, cannels;

	stbi_set_flip_vertically_on_load(false);
	unsigned char* data = stbi_load(imageloc, &width, &height, &cannels, 3);

	if (!data)
		std::cout << "problem loading image" << '\n';

	datapack.width = width;
	datapack.height = height;
	datapack.data = data;
}


void freeImageData(ImageData& imagedata)
{
	stbi_image_free((void*)imagedata.data);


}

GLuint getTexture(const char* texturename, int mipmaplevel)
{
	GLuint texid;
	int width, height, cannels;

	stbi_set_flip_vertically_on_load(false);
	unsigned char* data = stbi_load(texturename, &width, &height, &cannels, 4);

	if (!data)
	{
		std::cout << "problem loading image" << '\n';
		return 0;
	}

	glCreateTextures(GL_TEXTURE_2D, 1, &texid);
	glTextureImage2DEXT(texid,GL_TEXTURE_2D,0,GL_RGBA, width, height,0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTextureParameteri(texid, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(texid, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(texid, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(texid, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	stbi_image_free((void*)data);
	return texid;

}

GLuint getTextureGreyScale(const char* texturename, int mipmaplevel)
{
	GLuint texid;
	int width, height, cannels;

	stbi_set_flip_vertically_on_load(false);
	unsigned char* data = stbi_load(texturename, &width, &height, &cannels, 3);

	std::cout << cannels;

	if (!data)
	{
		std::cout << "problem loading image" << '\n';
		return 0;
	}

	glCreateTextures(GL_TEXTURE_2D, 1, &texid);
	//glTextureStorage2D(texid, 1, GL_RGB8, width, height);
	//glTextureSubImage2D(texid, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTextureImage2DEXT(texid, GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTextureParameteri(texid, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(texid, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(texid, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(texid, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free((void*)data);
	return texid;
}






Window::Window()
{
	windowid = 0;
	width = height = 0;
}



int Window::setWindow(int width, int height, const char* windowname)
{
	windowid = glfwCreateWindow(width, height, windowname, nullptr, nullptr);

	this->width = width;
	this->height = height;

	if (windowid == 0)
	{		
		std::cout << "\nfailed to create Window\n";
		return -1;
	}
	return 0;
}

int Window::destroyWindow()
{
	glfwDestroyWindow(windowid);
	return 0;
}

int Window::getWidth()
{
	return width;
}

int Window::getHeight()
{
	return height;
}

GLFWwindow* Window::getWindowID()
{
	return windowid;
}









GLfloat cubedata[] = {
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f,  1.0f
};






Skybox::Skybox()
{
	skyboxid = 0;
	vao = vbo = 0;
}

void Skybox::setSkybox(const char** texturename)
{
	ImageData imagedata;

	glCreateTextures(GL_TEXTURE_CUBE_MAP,1,&skyboxid);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxid);
	glTextureParameteri(skyboxid, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(skyboxid, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(skyboxid, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(skyboxid, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureParameteri(skyboxid, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (int z = 0;z<6;z++)
	{
		getImageData(texturename[z], imagedata);
		glTextureImage2DEXT(skyboxid, GL_TEXTURE_CUBE_MAP_POSITIVE_X + z, 0, GL_RGB, imagedata.width, imagedata.height, 0, GL_RGB, GL_UNSIGNED_BYTE, imagedata.data);
		freeImageData(imagedata);
	}
	
	GLint par[4];
	glGetTexLevelParameteriv(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_TEXTURE_INTERNAL_FORMAT, par);

	skyboxbindlessid = glGetTextureHandleARB(skyboxid);
	glMakeTextureHandleResidentARB(skyboxbindlessid);


	glCreateBuffers(1, &vbo);
	glNamedBufferStorage(vbo, sizeof(cubedata), cubedata, GL_DYNAMIC_STORAGE_BIT);

	glCreateVertexArrays(1, &vao);

	glEnableVertexArrayAttrib(vao, 0);
	glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vao, 0, 0);
	glVertexArrayVertexBuffer(vao, 0, vbo, 0, 3 * sizeof(GLfloat));

}


void Skybox::destroy()
{
	glDeleteTextures(1, &skyboxid);
}

void Skybox::render()
{
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

GLuint64 Skybox::getSkyboxTexBindLess()
{
	return skyboxbindlessid;
}




GLfloat planedata[]
{
	1.0f,1.0f,0.0f,  1.0,1.0,   0.0,0.0,1.0,
	-1.0f,-1.0f,0.0f,  0.0,0.0,   0.0,0.0,1.0,
	1.0f,-1.0f,0.0f,  1.0,0.0,   0.0,0.0,1.0,

	1.0f,1.0f,0.0f,  1.0,1.0,   0.0,0.0,1.0,
	-1.0f,1.0f,0.0f,  0.0,1.0,   0.0,0.0,1.0,
	-1.0f,-1.0f,0.0f,  0.0,0.0,   0.0,0.0,1.0
};




Plane::Plane()
{
	vaoid = vboid = 0;
}

void Plane::destroy()
{
	glDeleteBuffers(1, &vboid);
	glDeleteVertexArrays(1, &vaoid);
}

GLuint Plane::setPlane()
{
	glCreateBuffers(1, &vboid);
	glNamedBufferStorage(vboid, sizeof(planedata), planedata, GL_DYNAMIC_STORAGE_BIT);


	glCreateVertexArrays(1, &vaoid);

	glEnableVertexArrayAttrib(vaoid, 0);
	glEnableVertexArrayAttrib(vaoid, 1);
	glEnableVertexArrayAttrib(vaoid, 2);
	glVertexArrayAttribFormat(vaoid, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(vaoid, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));
	glVertexArrayAttribFormat(vaoid, 2, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat));
	glVertexArrayAttribBinding(vaoid, 0, 0);
	glVertexArrayAttribBinding(vaoid, 1, 0);
	glVertexArrayAttribBinding(vaoid, 2, 0);
	glVertexArrayVertexBuffer(vaoid, 0, vboid, 0, 8 * sizeof(GLfloat));

	return 0;
}

void Plane::render()
{
	glBindVertexArray(vaoid);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}




GLfloat terrainplanedata[]
{
	1.0f,0.0f,1.0f,  1.0,1.0,   0.0,0.0,1.0,
	-1.0f,0.0f,-1.0f,  0.0,0.0,   0.0,0.0,1.0,
	1.0f,0.0f,-1.0f,  1.0,0.0,   0.0,0.0,1.0,

	1.0f,0.0f,1.0f,  1.0,1.0,   0.0,0.0,1.0,
	-1.0f,0.0f,1.0f,  0.0,1.0,   0.0,0.0,1.0,
	-1.0f,0.0f,-1.0f,  0.0,0.0,   0.0,0.0,1.0
};

//temperary procedure
void vec3ToFloatArr(somath::vec3& vec, float* arr)
{
	arr[0] = vec.x;
	arr[1] = vec.y;
	arr[2] = vec.z;
}



TerrainMesh::TerrainMesh()
{
	terrainvao = terrainvbo = 0;
	translatepos = nullptr;
}

void TerrainMesh::destroyTerrain()
{
	delete translatepos;
	glDeleteBuffers(1, &terrainvbo);
	glDeleteVertexArrays(1, &terrainvao);
}


void TerrainMesh::setTerrainMesh(int nofx, int noofy, float sizex, float sizey, int randseed,float terrainareadeduction)
{
	noofxblocks = nofx;noofyblocks = noofy;
	sizeofxblock=sizex, sizeofyblock=sizey;
	randomsp = randseed;
	this->terrainareadeduction = terrainareadeduction;

	setTranslates();

	glCreateBuffers(1, &terrainvbo);
	glCreateVertexArrays(1,&terrainvao); 

	glNamedBufferStorage(terrainvbo, sizeof(terrainplanedata)+(sizeof(float)*translatepos->size()), nullptr, GL_DYNAMIC_STORAGE_BIT);
	glNamedBufferSubData(terrainvbo, 0, sizeof(terrainplanedata), terrainplanedata);
	glNamedBufferSubData(terrainvbo, sizeof(terrainplanedata), (sizeof(float)*translatepos->size()), &(*translatepos)[0]);
	


	glEnableVertexArrayAttrib(terrainvao, 0);
	glEnableVertexArrayAttrib(terrainvao, 1);
	glEnableVertexArrayAttrib(terrainvao, 2);
	glEnableVertexArrayAttrib(terrainvao, 3);
	glVertexArrayAttribFormat(terrainvao, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(terrainvao, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));
	glVertexArrayAttribFormat(terrainvao, 2, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat));
	glVertexArrayAttribFormat(terrainvao, 3, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(terrainvao, 0, 0);
	glVertexArrayAttribBinding(terrainvao, 1, 0);
	glVertexArrayAttribBinding(terrainvao, 2, 0);
	glVertexArrayAttribBinding(terrainvao, 3, 1);
	glVertexArrayVertexBuffer(terrainvao, 0, terrainvbo, 0, 8 * sizeof(GLfloat));
	glVertexArrayVertexBuffer(terrainvao, 1, terrainvbo, sizeof(terrainplanedata), 3 * sizeof(GLfloat));
	glVertexArrayBindingDivisor(terrainvao, 1, 1);
}

void TerrainMesh::setHeightMap(double heightofterrain)
{

	float *heightData = new float[noofxblocks*noofyblocks];
	int noofoctaves = 8;
	somath::vec2 samplearea = somath::vec2(40, 40);
	somath::vec2 resolution = somath::vec2(noofxblocks, noofyblocks);


	if (getHMAP(heightData, noofxblocks*noofyblocks * sizeof(float)) == -1)
	{

		//more diviser means smaller area of map lesser variation
		somath::vec2 step = samplearea / resolution;
		float amp = 1.0;

		for (int zo = 1;zo < 4*noofoctaves;zo*=4)
		{
			for (int z = 0;z < resolution.y;z++)
				for (int z1 = 0;z1 < resolution.x;z1++)
					if (zo == 1)
						heightData[z*int(resolution.x) + z1] = somath::getNoise(z*step.x*zo, z1*step.y*zo, 0.1)*amp;
					else
						heightData[z*int(resolution.x) + z1] += somath::getNoise(z*step.x / zo, z1*step.y / zo, 0.1 + zo)*zo;
			amp /= 2.0;
		}

		saveHMAP(heightData, resolution.x*resolution.y * sizeof(float));
	}

	//creating the texture
	glCreateTextures(GL_TEXTURE_2D, 1, &heightmap);
	glTextureStorage2D(heightmap, 1, GL_R32F,	noofxblocks,noofyblocks);
	glTextureSubImage2D(heightmap, 0, 0, 0, noofxblocks, noofyblocks, GL_RED, GL_FLOAT, &(heightData[0]));

	glTextureParameteri(heightmap, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(heightmap, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(heightmap, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(heightmap, GL_TEXTURE_WRAP_T, GL_REPEAT);

	heightmapbindlessid = glGetTextureHandleARB(heightmap);
	glMakeTextureHandleResidentARB(heightmapbindlessid);

	
}

void TerrainMesh::setTranslates()
{
	
	translatepos = new std::vector<float>();

	float tem[3];
	double totalsizex = noofxblocks*2.0*sizeofxblock;
	double totalsizey = noofyblocks*2.0*sizeofyblock;

	for (int z = 0;z < noofxblocks;z++)
	{
		for (int z1 = 0;z1 < noofyblocks;z1++)
		{
			somath::vec3 translate(z*2.0*sizeofxblock, 0.0, z1*2.0*sizeofyblock);
			translate = translate - somath::vec3(totalsizex / 2.0, 0.0, totalsizey / 2.0);
			vec3ToFloatArr(translate, tem);

			translatepos->push_back(tem[0]);translatepos->push_back(tem[1]);translatepos->push_back(tem[2]);
		}
	}

	
}

void TerrainMesh::render()
{
	glBindVertexArray(terrainvao);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, noofxblocks*noofyblocks);
}

GLuint64 TerrainMesh::getHmapBindless()
{
	return heightmapbindlessid;
}

somath::vec2 TerrainMesh::getWorldSize()
{
	return somath::vec2(sizeofxblock*noofxblocks*2.0,sizeofyblock*noofyblocks*2.0);
}

somath::vec2 TerrainMesh::getWorldScale()
{
	return somath::vec2(sizeofxblock, sizeofyblock);
}





FrameBuffer::FrameBuffer()
{
	fboid = depthrbuffid = 0;
}
void FrameBuffer::makeFrameBuffer(int width, int height, bool depthbufferneeded)
{
	glCreateFramebuffers(1, &fboid);

	glCreateTextures(GL_TEXTURE_2D,1, &texid);
	glTextureStorage2D(texid, 1, GL_RGBA8, width, height);
	glTextureParameteri(texid, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(texid, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(texid, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(texid, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	
	glNamedFramebufferTexture(fboid, GL_COLOR_ATTACHMENT0, texid, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (depthbufferneeded)
	{
		glCreateRenderbuffers(1, &depthrbuffid);
		glNamedRenderbufferStorage(depthrbuffid, GL_DEPTH_COMPONENT32F, width, height);
		glNamedFramebufferRenderbuffer(fboid, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrbuffid);
	}

	texidbindless=glGetTextureHandleARB(texid);
	glMakeTextureHandleResidentARB(texidbindless);
}
GLuint FrameBuffer::getFBOid()
{
	return fboid;
}
GLuint FrameBuffer::getTexture()
{
	return texid;
}
void FrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fboid);
}
GLuint64 FrameBuffer::getTextureBindLess()
{
	return texidbindless;
}
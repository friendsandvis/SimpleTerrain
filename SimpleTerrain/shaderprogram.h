#pragma once

#include<stdio.h>
#include<iostream>
#include<vector>
#define GLEW_STATIC
#include<GL/glew.h>
#include"SOMath.h"

namespace sodatautils
{
	struct Entry
	{
		GLuint index;
		char str[50];

	};


	class Buffers
	{
		std::vector<Entry*> bufferpool;

	public:
		Buffers();
		~Buffers();

		int addBuffer(char* buffername);
		int getIndex(char* buffname);
		GLuint getBuffer(int);
		GLuint getBuffer(char* buffername);
		void deleteBuffer(int);
		void deleteBuffer(char* buffername);
	};

	class VertexArraies
	{
		std::vector<Entry*> bufferpool;

	public:
		VertexArraies();
		~VertexArraies();

		int addVertexArraies(char* vertexarrayname);
		int getIndex(char* vertexarrayname);
		GLuint getVertexArraies(int);
		GLuint getVertexArraies(char* vertexarrayname);
		void deleteVertexArraies(int);
		void deleteVertexArraies(char* vertexarrayname);
	};

};

namespace soprogram
{

	//hold a file as string data array 
	//here used for holding the source code of shaders
	class Source
	{
		char* str;

		void readFile(FILE* file);

	public:
		bool readfaliure;


		Source();
		Source(const char* sourcefilepath);
		~Source();

		void setSource(const char* sourcefilepath);
		const char* getSource();

	};



	class Shader
	{
		GLuint shaderid;
		GLuint type;

	public:
		bool readfaliure;

		Shader();
		Shader(const char* const* source, GLuint type);
		~Shader();
		GLuint& getShader();
		void setShader(const char* const* source, GLuint type);
		void checkShader();
	};

	class Program
	{
		GLuint programid;
		GLint linkstatus;

	public:
		Program();
		~Program();

		GLuint getProgram();
		void showSucessText();

		void makeProgram(const char* shadersourcepath);
		void makeProgram(const char* vertexshadersourcepath, const char* fragmentshadersourcepath);
		void makeProgram(const char* vertexshadersourcepath, const char* geometryshadersourcepath, const char* fragmentshadersourcepath);

		void useProgram();

		void setUniformInteger(const char* variablename, int value)const;
		void setUniformFloat(const char* variablename, float value)const;
		void setUniformVec2(const char* variablename, somath::vec2 value)const;
		void setUniformVec3(const char* variablename, somath::vec3 value)const;
		void setUniformVec4(const char* variablename, somath::vec4 value)const;
		void setUniformMat4(const char* variablename, somath::mat4 value)const;
		void setUniformMat3(const char* variablename, somath::mat3 value)const;
	};


};
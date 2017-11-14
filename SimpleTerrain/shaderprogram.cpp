
#define _CRT_SECURE_NO_WARNINGS
#include "shaderprogram.h"





soprogram::Source::Source()
{
	str = nullptr;
	readfaliure = false;
}

soprogram::Source::~Source()
{
	delete[] str;
}

soprogram::Source::Source(const char* sourcefile)
{
	readfaliure = false;

	FILE* file = fopen(sourcefile, "r");

	if (file == nullptr)
	{
		std::cout << "\n Cannot open the file-" << sourcefile << '\n';
		readfaliure = true;
		return;
	}

	std::fseek(file, 0, SEEK_END);
	long filesize = std::ftell(file);
	std::fseek(file, 0, SEEK_SET);

	str = new char[filesize];
	readFile(file);
}

const char* soprogram::Source::getSource()
{
	return str;
}

void soprogram::Source::readFile(FILE* file)
{
	char ch = fgetc(file);
	int z = 0;
	while (ch != EOF)
	{
		str[z++] = ch;
		ch = fgetc(file);
	}
	str[z] = '\0';

	fclose(file);
}


void soprogram::Source::setSource(const char* sourcefile)
{
	delete[] str;

	FILE* file = fopen(sourcefile, "r");

	if (file == nullptr)
	{
		std::cout << "\n Cannot open the file-" << sourcefile << '\n';
		return;
	}

	std::fseek(file, 0, SEEK_END);
	long filesize = std::ftell(file);
	std::fseek(file, 0, SEEK_SET);

	str = new char[filesize];
	readFile(file);
}









soprogram::Shader::Shader()
{
	shaderid = -1;type = -1;
	readfaliure = false;
}

soprogram::Shader::Shader(const char* const* source, GLuint type)
{
	readfaliure = false;

	if (type != GL_VERTEX_SHADER && type != GL_FRAGMENT_SHADER && type != GL_GEOMETRY_SHADER && type != GL_COMPUTE_SHADER)
	{
		std::cout << "\nUnsupported type of shader\n";
		readfaliure = true;
		return;
	}

	shaderid = glCreateShader(type);
	glShaderSource(shaderid, 1, source, NULL);
	this->type = type;
	checkShader();
}

void soprogram::Shader::checkShader()
{
	glCompileShader(shaderid);

	int sucess, sizeofinfolog;
	glGetShaderiv(shaderid, GL_COMPILE_STATUS, &sucess);
	glGetShaderiv(shaderid, GL_INFO_LOG_LENGTH, &sizeofinfolog);

	if (!sucess)
	{
		std::cout << "\nShader failed to compile";
		readfaliure = true;

		switch (type)
		{
		case GL_VERTEX_SHADER: std::cout << ":vertex shader\n";break;
		case GL_FRAGMENT_SHADER: std::cout << ":fragment shader\n";break;
		case GL_GEOMETRY_SHADER: std::cout << ":geometry shader\n";break;
		case GL_COMPUTE_SHADER: std::cout << ":compute shader\n";break;
		default: std::cout << ":-1\n";break;
		}


		char* ch = new char[sizeofinfolog];
		glGetShaderInfoLog(shaderid, sizeofinfolog, NULL, ch);
		std::cout << '\n' << ch << '\n';
		delete[] ch;
	}
}

soprogram::Shader::~Shader()
{
	glDeleteShader(shaderid);
}

GLuint& soprogram::Shader::getShader()
{
	return shaderid;
}

void soprogram::Shader::setShader(const char* const* source, GLuint type)
{
	if (shaderid != -1)
		glDeleteShader(shaderid);

	readfaliure = false;

	if (type != GL_VERTEX_SHADER && type != GL_FRAGMENT_SHADER && type != GL_GEOMETRY_SHADER  && type != GL_COMPUTE_SHADER)
	{
		std::cout << "\nUnsupported type of shader\n";
		readfaliure = true;
		return;
	}

	shaderid = glCreateShader(type);
	glShaderSource(shaderid, 1, source, NULL);
	this->type = type;
	checkShader();
}







soprogram::Program::Program()
{
	programid = -1;
	linkstatus = 0;
}

soprogram::Program::~Program()
{
	glDeleteProgram(programid);
}

void soprogram::Program::useProgram()
{
	if (programid == -1)
		return;
	glUseProgram(programid);
}

GLuint soprogram::Program::getProgram()
{
	return programid;
}

void soprogram::Program::showSucessText()
{
	if (linkstatus)
		std::cout << "\nLinked successfully\n";
}

void soprogram::Program::makeProgram(const char* vertexpath, const char* fragmentpath)
{
	if (programid != -1)
		glDeleteProgram(programid);

	Source vertexsrc(vertexpath);
	Source fragmentsrc(fragmentpath);

	if (vertexsrc.readfaliure || fragmentsrc.readfaliure)
		return;

	const char* vertexsrcptr = vertexsrc.getSource();
	const char* fragmentsrcptr = fragmentsrc.getSource();

	Shader vertexshader(&vertexsrcptr, GL_VERTEX_SHADER);
	Shader fragmentshader(&fragmentsrcptr, GL_FRAGMENT_SHADER);

	if (vertexshader.readfaliure || fragmentshader.readfaliure)
		return;

	programid = glCreateProgram();

	glAttachShader(programid, vertexshader.getShader());
	glAttachShader(programid, fragmentshader.getShader());
	glLinkProgram(programid);


	glGetProgramiv(programid, GL_LINK_STATUS, &linkstatus);

	if (!linkstatus)
	{
		std::cout << "\nLinking failed\n";

		char* ch = new char[500];
		glGetProgramInfoLog(programid, 500, NULL, ch);
		std::cout << '\n' << ch << '\n';
		delete[] ch;

		glDeleteProgram(programid);
	}
}

void soprogram::Program::makeProgram(const char* shadersourcepath)
{
	if (programid != -1)
		glDeleteProgram(programid);

	Source computesrc(shadersourcepath);

	if (computesrc.readfaliure)
		return;

	const char* computesrcptr = computesrc.getSource();

	Shader computeshader(&computesrcptr, GL_COMPUTE_SHADER);

	if (computeshader.readfaliure)
		return;

	programid = glCreateProgram();

	glAttachShader(programid, computeshader.getShader());
	glLinkProgram(programid);


	glGetProgramiv(programid, GL_LINK_STATUS, &linkstatus);

	if (!linkstatus)
	{
		std::cout << "\nLinking failed\n";

		char* ch = new char[500];
		glGetProgramInfoLog(programid, 500, NULL, ch);
		std::cout << '\n' << ch << '\n';
		delete[] ch;

		glDeleteProgram(programid);
	}
}


void soprogram::Program::makeProgram(const char* vertexpath, const char* geometrypath, const char* fragmentpath)
{
	if (programid != -1)
		glDeleteProgram(programid);

	Source vertexsrc(vertexpath);
	Source geometrysrc(geometrypath);
	Source fragmentsrc(fragmentpath);

	if (vertexsrc.readfaliure || fragmentsrc.readfaliure || geometrysrc.readfaliure)
		return;

	const char* vertexsrcptr = vertexsrc.getSource();
	const char* geometrysrcptr = geometrysrc.getSource();
	const char* fragmentsrcptr = fragmentsrc.getSource();

	Shader vertexshader(&vertexsrcptr, GL_VERTEX_SHADER);
	Shader geometryshader(&geometrysrcptr, GL_GEOMETRY_SHADER);
	Shader fragmentshader(&fragmentsrcptr, GL_FRAGMENT_SHADER);

	if (vertexshader.readfaliure || fragmentshader.readfaliure || geometryshader.readfaliure)
		return;

	programid = glCreateProgram();

	glAttachShader(programid, vertexshader.getShader());
	glAttachShader(programid, geometryshader.getShader());
	glAttachShader(programid, fragmentshader.getShader());
	glLinkProgram(programid);


	glGetProgramiv(programid, GL_LINK_STATUS, &linkstatus);

	if (!linkstatus)
	{
		std::cout << "\nLinking failed\n";

		char* ch = new char[500];
		glGetProgramInfoLog(programid, 500, NULL, ch);
		std::cout << '\n' << ch << '\n';
		delete[] ch;

		glDeleteProgram(programid);
	}

}

void soprogram::Program::setUniformInteger(const char* variablename, int value) const
{
	glUniform1i(glGetUniformLocation(programid, variablename), value);
}
void soprogram::Program::setUniformFloat(const char* variablename, float value)const
{
	glUniform1f(glGetUniformLocation(programid, variablename), value);
}
void soprogram::Program::setUniformVec2(const char* variablename, somath::vec2 value)const
{
	glUniform2f(glGetUniformLocation(programid, variablename), value.x, value.y);
}
void soprogram::Program::setUniformVec3(const char* variablename, somath::vec3 value)const
{
	glUniform3f(glGetUniformLocation(programid, variablename), value.x, value.y, value.z);
}
void soprogram::Program::setUniformVec4(const char* variablename, somath::vec4 value)const
{
	glUniform4f(glGetUniformLocation(programid, variablename), value.x, value.y, value.z, value.w);
}
void soprogram::Program::setUniformMat4(const char* variablename, somath::mat4 value)const
{
	somath::linearFormation tem_linearformation(value);
	glUniformMatrix4fv(glGetUniformLocation(programid, variablename), 1, GL_FALSE, tem_linearformation.getArray());
}
void soprogram::Program::setUniformMat3(const char* variablename, somath::mat3 value)const
{
	somath::linearFormation tem_linearformation(value);
	glUniformMatrix3fv(glGetUniformLocation(programid, variablename), 1, GL_FALSE, tem_linearformation.getArray());
}












sodatautils::Buffers::Buffers()
{

}

sodatautils::Buffers::~Buffers()
{
	for (int z = 0;z < bufferpool.size();z++)
	{
		glDeleteBuffers(1, &bufferpool[z]->index);
		delete bufferpool[z];
	}
}

int sodatautils::Buffers::addBuffer(char* str)
{
	Entry *e = new Entry();
	glCreateBuffers(1, &(e->index));
	strcpy(e->str, str);

	for (int z = 0;z < bufferpool.size();z++)
		if (bufferpool[z] == nullptr)
		{
			bufferpool[z] = e;return z;
		}

	bufferpool.push_back(e);
	return bufferpool.size() - 1;
}
int sodatautils::Buffers::getIndex(char* buffname)
{
	for (int z = 0;z < bufferpool.size();z++)
		if (!strcmp(buffname, bufferpool[z]->str))
			return z;
}
GLuint sodatautils::Buffers::getBuffer(int index)
{
	if (bufferpool.size() >= index)
		return 0;
	return bufferpool[index]->index;
}
GLuint sodatautils::Buffers::getBuffer(char* buffername)
{
	for (int z = 0;z < bufferpool.size();z++)
		if (!strcmp(buffername, bufferpool[z]->str))
			return bufferpool[z]->index;
}
void sodatautils::Buffers::deleteBuffer(int index)
{
	if (bufferpool.size() >= index)
		return;
	glDeleteBuffers(1, &bufferpool[index]->index);
	delete bufferpool[index];
	bufferpool[index] = nullptr;
}
void sodatautils::Buffers::deleteBuffer(char* buffername)
{
	for (int z = 0;z < bufferpool.size();z++)
		if (!strcmp(buffername, bufferpool[z]->str))
		{
			glDeleteBuffers(1, &bufferpool[z]->index);
			delete bufferpool[z];
			bufferpool[z] = nullptr;
		}
}

sodatautils::VertexArraies::VertexArraies()
{

}
sodatautils::VertexArraies::~VertexArraies()
{
	for (int z = 0;z < bufferpool.size();z++)
	{
		glDeleteVertexArrays(1, &bufferpool[z]->index);
		delete bufferpool[z];
	}
}

int sodatautils::VertexArraies::addVertexArraies(char* str)
{
	Entry *e = new Entry();
	glCreateVertexArrays(1, &(e->index));
	strcpy(e->str, str);

	for (int z = 0;z < bufferpool.size();z++)
		if (bufferpool[z] == nullptr)
		{
			bufferpool[z] = e;return z;
		}

	bufferpool.push_back(e);
	return bufferpool.size() - 1;
}

int sodatautils::VertexArraies::getIndex(char* buffname)
{
	for (int z = 0;z < bufferpool.size();z++)
		if (!strcmp(buffname, bufferpool[z]->str))
			return z;
}
GLuint sodatautils::VertexArraies::getVertexArraies(int index)
{
	if (bufferpool.size() >= index)
		return 0;
	return bufferpool[index]->index;
}
GLuint sodatautils::VertexArraies::getVertexArraies(char* buffername)
{
	for (int z = 0;z < bufferpool.size();z++)
		if (!strcmp(buffername, bufferpool[z]->str))
			return bufferpool[z]->index;
}
void sodatautils::VertexArraies::deleteVertexArraies(int index)
{
	if (bufferpool.size() >= index)
		return;

	glDeleteVertexArrays(1, &bufferpool[index]->index);
	delete bufferpool[index];
	bufferpool[index] = nullptr;
}
void sodatautils::VertexArraies::deleteVertexArraies(char* buffername)
{
	for (int z = 0;z < bufferpool.size();z++)
		if (!strcmp(buffername, bufferpool[z]->str))
		{
			glDeleteVertexArrays(1, &bufferpool[z]->index);
			delete bufferpool[z];
			bufferpool[z] = nullptr;
		}
}

#include"modelloader.h"


extern GLuint getTexture(const char* texturename);




Model::Model(const char* texloc)
{
	strcpy_s(textureloc, texloc);
}

int Model::setModel(const char* modelpath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(modelpath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
	{
		std::cout << "Error loading model:\n" << importer.GetErrorString() << '\n';

		return -1;
	}

	setAllData(scene->mRootNode, scene);
	return 0;

}

void Model::setAllData(aiNode *node, const aiScene *scene)
{
	for (unsigned z = 0;z<node->mNumMeshes;z++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[z]];
		meshes.push_back(setMeshData(mesh, scene));
	}

	for (unsigned z = 0;z < node->mNumChildren;z++)
		setAllData(node->mChildren[z], scene);
}


Mesh Model::setMeshData(aiMesh *mesh, const aiScene *scene)
{
	Mesh *meshdata = new Mesh();

	std::vector<Vertex> verticies;

	for (unsigned z = 0;z < mesh->mNumVertices;z++)
	{
		Vertex temvertex;
		temvertex.data[0] = mesh->mVertices[z].x;
		temvertex.data[1] = mesh->mVertices[z].y;
		temvertex.data[2] = mesh->mVertices[z].z;


		temvertex.data[3] = mesh->mNormals[z].x;
		temvertex.data[4] = mesh->mNormals[z].y;
		temvertex.data[5] = mesh->mNormals[z].z;

		if (mesh->mTextureCoords[0])
		{
			temvertex.data[6] = mesh->mTextureCoords[0][z].x;
			temvertex.data[7] = mesh->mTextureCoords[0][z].y;
		}
		else
		{
			temvertex.data[6] = 0.0;
			temvertex.data[7] = 0.0;
		}

		temvertex.data[8] = mesh->mTangents[z].x;
		temvertex.data[9] = mesh->mTangents[z].y;
		temvertex.data[10] = mesh->mTangents[z].z;


		verticies.push_back(temvertex);
	}


	std::vector<unsigned> indicies;

	for (unsigned z = 0;z < mesh->mNumFaces;z++)
	{
		aiFace face = mesh->mFaces[z];
		for (unsigned z1 = 0;z1 < face.mNumIndices;z1++)
			indicies.push_back(face.mIndices[z1]);
	}



	std::vector<Texture> textures;

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		setTextures(material, textures, aiTextureType_DIFFUSE);
		setTextures(material, textures, aiTextureType_SPECULAR);
		setTextures(material, textures, aiTextureType_HEIGHT);
	}

	meshdata->setMesh(verticies, indicies, textures);
	return *meshdata;
}

void Model::setTextures(aiMaterial* material, std::vector<Texture>& textures, aiTextureType textype)
{
	for (unsigned z = 0;z < material->GetTextureCount(textype);z++)
	{
		Texture tex;
		aiString str;
		material->GetTexture(textype, z, &str);
		char texpath[100];
		strcpy_s(texpath, textureloc);
		strcat_s(texpath, str.C_Str());
		tex.setTextue(getTexture(texpath));
		tex.setBindLess();
		tex.setTextureType(textype);
		textures.push_back(tex);
	}
}

void Model::render(soprogram::Program& progid)
{
	for (int z = 0;z<meshes.size();z++)
		meshes[z].render(progid);
}
void Model::makeBuffers()
{
	for (int z = 0;z<meshes.size();z++)
		meshes[z].makeBuffers();
}

void Model::destroy()
{
	for (Mesh& mesh : meshes)
		mesh.destroy();

}








Mesh::Mesh()
{
	vboid = eboid = vaoid;
}
void Mesh::setMesh(std::vector<Vertex> verticies, std::vector<unsigned> indicies, std::vector<Texture> textures)
{
	this->verticies = verticies;
	this->indicies = indicies;
	this->textures = textures;
}
void Mesh::makeBuffers()
{
	glGenBuffers(1, &vboid);glGenBuffers(1, &eboid);
	glGenVertexArrays(1, &vaoid);

	glBindVertexArray(vaoid);
	glBindBuffer(GL_ARRAY_BUFFER, vboid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*verticies.size(), &(verticies[0].data[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboid);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned)*indicies.size(), &indicies[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 6));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 8));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glBindVertexArray(0);

	std::cout << indicies.size() << '\n';

}
void Mesh::render(soprogram::Program& progid)
{
	for (Texture& tex : textures)
	{
		if (tex.getTextureType() == aiTextureType_DIFFUSE)
			glUniformHandleui64ARB(glGetUniformLocation(progid.getProgram(), "tex_diffuse"), tex.getBindLessTexture());
	}
	for (Texture& tex : textures)
	{
		if (tex.getTextureType() == aiTextureType_SPECULAR)
			glUniformHandleui64ARB(glGetUniformLocation(progid.getProgram(), "tex_specular"), tex.getBindLessTexture());
	}
	for (Texture& tex : textures)
	{
		if (tex.getTextureType() == aiTextureType_HEIGHT)
			glUniformHandleui64ARB(glGetUniformLocation(progid.getProgram(), "tex_normal"), tex.getBindLessTexture());
	}

	glBindVertexArray(vaoid);
	glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::destroy()
{
	glDeleteBuffers(1, &vboid);
	glDeleteBuffers(1, &eboid);
	glDeleteVertexArrays(1, &vaoid);

	for (Texture& tex : textures)
		tex.destroy();
}






Texture::Texture()
{
	texid = 0; texidbindless = 0;
}

void Texture::setTextue(GLuint texid)
{
	this->texid = texid;
}
GLuint Texture::getTexture()
{
	return texid;
}
GLuint64 Texture::getBindLessTexture()
{
	return texidbindless;
}
void Texture::setTextureType(aiTextureType type)
{
	textype = type;
}
void Texture::destroy()
{
	glDeleteTextures(1, &texid);
}
aiTextureType Texture::getTextureType()
{
	return textype;
}
void Texture::setBindLess()
{
	texidbindless = glGetTextureHandleARB(texid);
	glMakeTextureHandleResidentARB(texidbindless);
}
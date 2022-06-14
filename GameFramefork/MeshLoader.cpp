#include "MeshLoader.h"

#include "FBXMeshComponent.h"

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

using namespace std;


MeshLoader::MeshLoader(std::string filepath)
{
	OpenFile(filepath);
}

void MeshLoader::GetMesh(size_t meshIndex, FBXMeshComponent* resMesh)
{
	const aiScene* scene = importer.GetScene();

	HRESULT res = 0;

	aiMesh* mesh = scene->mMeshes[meshIndex];

	for (size_t i = 0; i < mesh->mNumVertices; ++i) {
		TexturedVertex v;

		v.Position.x = mesh->mVertices[i].x;
		v.Position.y = mesh->mVertices[i].y;
		v.Position.z = mesh->mVertices[i].z;

		v.Normal.x = mesh->mNormals[i].x;
		v.Normal.y = mesh->mNormals[i].y;
		v.Normal.z = mesh->mNormals[i].z;

		resMesh->addVertex(v);
		resMesh->addVertex({ v.Position.x, v.Position.y, v.Position.z, 1.0f });
		resMesh->addVertex({1.0f, 1.0f, 1.0f, 1.0f});
	}
	if (mesh->mTextureCoords != nullptr) {
		for (size_t i = 0; i < mesh->mNumVertices; ++i) {
			resMesh->getVertex(i).TexCoord.x = mesh->mTextureCoords[0][i].x;
			resMesh->getVertex(i).TexCoord.y = 1.0f - mesh->mTextureCoords[0][i].y;
		}
	}

	for (size_t i = 0; i < mesh->mNumFaces; ++i) {
		resMesh->addIndex(mesh->mFaces[i].mIndices[0]);
		resMesh->addIndex(mesh->mFaces[i].mIndices[1]);
		resMesh->addIndex(mesh->mFaces[i].mIndices[2]);
	}

	return;
}

void MeshLoader::OpenFile(std::string filepath)
{
	const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_GenNormals);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
	}
}

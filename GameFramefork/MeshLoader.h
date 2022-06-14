#pragma once

#include <string>

#include <assimp/Importer.hpp>

class FBXMeshComponent;

class MeshLoader
{
public:
	MeshLoader(std::string filepath);
	MeshLoader() = default;
	~MeshLoader() = default;

	void GetMesh(size_t meshIndex, FBXMeshComponent* resMesh);

	void OpenFile(std::string filepath);

private:


	Assimp::Importer importer;
};


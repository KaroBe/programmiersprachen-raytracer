#ifndef SDF_LOADER_HPP
#define SDF_LOADER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "scene.hpp"
#include "material.hpp"

struct SDFloader
{
/*
public:

	SDFloader();
*/
	//void addToMaterial(Material const& material);

	Scene load(std::string const& inputFile);
/*
private:
	//std::vector<Material> m_vecMaterials;
*/
	
};

#endif
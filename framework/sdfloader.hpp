#ifndef SDF_LOADER_HPP
#define SDF_LOADER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "scene.hpp"
#include "material.hpp"

struct SDFloader
{
/*
public:

	SDFloader();
*/
	//void addToMaterial(Material const& material);

	void test()
	{
		std::cout << "i got here";
	};

	Scene load(std::string const& inputFile);
/*
private:
	//std::vector<Material> m_vecMaterials;
*/

};

#endif
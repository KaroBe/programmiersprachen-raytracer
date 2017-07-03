#include "sdfloader.hpp"

	//SDFloader::SDFloader() :
	//m_vecMaterials{std::vector<Material> vec_material}
	//	{};
	
	/*
	void SDFloader::addToMaterial(Material const& material)
	{
		vec_material.push_back(material);
	}
	*/

	Scene SDFloader::load(std::string const& inputFile)
	{
		Scene scene{};
		std::fstream input;
		input.open(inputFile);

		if(input.is_open())
		{
			std::string line;
			std::string word;
			
			while(std::getline(input, line))
			{	
				std::stringstream stream;
				stream << line; 
				stream >> word;	
				if(word == "define")
				{
					stream >> word;

					if(word == "material")
					{
						Material in_material;
						
						stream >> in_material.m_name;
						stream >> in_material.m_ka.r;
						stream >> in_material.m_ka.g;
						stream >> in_material.m_ka.b;
						stream >> in_material.m_kd.r;
						stream >> in_material.m_kd.g;
						stream >> in_material.m_kd.b;
						stream >> in_material.m_ks.r;
						stream >> in_material.m_ks.g;
						stream >> in_material.m_ks.b;

						//addToMaterial(material);
						scene.m_materials.push_back(in_material);

					}
				}
			}
			return scene;
		}
		else
		{
			std::cout << "Couldn't find file. Empty Scene returned!" << std::endl;
			return scene;
		}
	}
	


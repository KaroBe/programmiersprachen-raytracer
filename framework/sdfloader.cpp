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
						//scene.m_materials.push_back(in_material.m_name, in_material);
						scene.m_materials[in_material.m_name] = in_material;
					}
					else if(word == "shape")
					{
						stream >> word;
						if(word == "box")
						{	//find name min max etc. in sdf file
							std::string name;
							stream >> name;

							glm::vec3 min;
							stream >> min.x;
							stream >> min.y;
							stream >> min.z;

							glm::vec3 max;
							stream >> max.x;
							stream >> max.y;
							stream >> max.z;

							std::string materialName;
							stream >> materialName;
							Material mat = scene.m_materials[materialName];

							//construct box with min max etc. found earlier
							Box in_box(name, mat, min, max);
							std::cout << "Added box:\n" << in_box <<std::endl;
							//std::shared_ptr<Shape> p1(in_box);
							//scene.m_shapes.push_back(std::make_shared<Shape>(in_box));
						}
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
	


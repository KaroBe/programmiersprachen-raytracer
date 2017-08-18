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
						std::cout <<"Added material:\n" << in_material << std::endl;
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
							auto boxptr = std::make_shared<Box>(name, mat, min, max);
							scene.m_shapes.push_back(boxptr);
							std::cout << "Added box:\n" << *boxptr << std::endl;

							//Box in_box(name, mat, min, max);
							//std::cout << "Added box:\n" << in_box <<std::endl;
							//std::shared_ptr<Shape> p1(in_box);
							//scene.m_shapes.push_back(std::make_shared<Shape>(in_box));
						}
						else if(word == "sphere")
						{
							std::string name;
							stream >> name;

							glm::vec3 center;
							stream >> center.x;
							stream >> center.y;
							stream >> center.z;

							float rad;
							stream >> rad;

							std::string materialName;
							stream >> materialName;
							Material mat = scene.m_materials[materialName];

							//Sphere in_sphere(name, mat, center, rad);
							//std::cout << "Added sphere:\n" << in_sphere <<std::endl;

							auto sphereptr = std::make_shared<Sphere>(name, mat, center, rad);
							scene.m_shapes.push_back(sphereptr);
							std::cout << "Added sphere:\n" << *sphereptr << std::endl;
						}
					}
					else if(word == "light")
					{
						std::string name;
						stream >> name;

						glm::vec3 position;
						stream >> position.x;
						stream >> position.y;
						stream >> position.z;

						Color color;
						stream >> color.r;
						stream >> color.g;
						stream >> color.b;

						float bright;
						stream >> bright;

						auto lightptr = std::make_shared<Light>(name, position, color, bright);
						scene.m_lights.push_back(lightptr);
						std::cout << "light added:\n" << *lightptr << std::endl;
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
	


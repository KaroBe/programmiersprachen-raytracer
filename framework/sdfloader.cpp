#include "sdfloader.hpp"

SDFloader() :
	m_vecMaterials{std::vector<Material> vec_material}{}

	void SDFloader::addToMaterial(Material const& material)
	{
		vec_material.push_back(material);
	}

	void SDFloader::sdfLoad(std::string const& inputFile)
	{
		std::fstream input;
		input.open(inputFile);

		if(input.is_open())
		{
			std::stringstream stream;
			std::string line;
			std::string word;
			
			while(std::getline(input, line))
			{	
				stream << line; 
				stream >> word;	
				if(word == "define")
				{
					stream >> word;

					if(word == "material")
					{
						Material material;
						
						stream >> material.m_name;
						stream >> material.m_ka.r;
						stream >> material.m_ka.g;
						stream >> material.m_ka.b;
						stream >> material.m_kd.r;
						stream >> material.m_kd.g;
						stream >> material.m_kd.b;
						stream >> material.m_ks.r;
						stream >> material.m_ks.g;
						stream >> material.m_ks.b;

						addToMaterial(material);

					}
				}
			}

			/*for (std::vector<Material>::iterator it = vec_material.begin(); it != vec_material.end(); ++it)
	    	{
	    		std::cout << ' ' << *it;
	    	}
	 		std::cout << '\n';*/
		}
		else
		{
			std::cout << "Couldn't find file." << std::endl;
		}


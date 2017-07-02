#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "material.hpp"

int main()
{
	std::fstream input;
	input.open("material_input.txt");

	if(input.is_open())
	{
		std::string line;
		std::vector<Material> vec_material;
		while(std::getline(input, line))
		{		//gets name
			int i = 16;
			std::string name;
			while(line.at(i) != ' ')
			{
				name.push_back(line[i]);
				++i;
			}
			++i;
			
			std::vector<float> numbers(10);
			for(int j = 0; j < numbers.size(); ++j)
			{		//gets numbers for colours etc
				float a = line[i] - '0';
				numbers[j] = a;
				i = i+2;
			}

			Color color1(numbers[0], numbers[1], numbers[2]);
			Color color2(numbers[3], numbers[4], numbers[5]);
			Color color3(numbers[6], numbers[7], numbers[8]);

			Material material(name, color1, color2, color3, numbers[9]);
			vec_material.push_back(material);
		}

		for (std::vector<Material>::iterator it = vec_material.begin(); it != vec_material.end(); ++it)
    	{
    		std::cout << ' ' << *it;
    	}
 		std::cout << '\n';
	}
	else
	{
		std::cout << "Couldn't find file." << std::endl;
	}

	return 0;
}
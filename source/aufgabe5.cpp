#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "material.hpp"
#include "scene.hpp"

int main()
{
    //hallo
        Scene scene{};
        std::ifstream input;
        input.open("/Users/lissyscholz/Documents/programmiersprachen/raytracer/programmiersprachen-raytracer/source/material_input.txt");

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
            std::cout << scene.m_materials[0] << std::endl;
            std::cout << scene.m_materials[1] << std::endl;
            std::cout << scene.m_materials[2] << std::endl;
        }
        else
        {
            std::cout << "Couldn't find file. Empty Scene returned!" << std::endl;
            //return scene;
        }
    
/*
    std::fstream input;
    input.open("material_input.txt");

    if(input.is_open())
    {
        std::string line;
        std::vector<Material> vec_material;
        while(std::getline(input, line))
        {       //gets name
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
            {       //gets numbers for colours etc
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
*/
    return 0;
}
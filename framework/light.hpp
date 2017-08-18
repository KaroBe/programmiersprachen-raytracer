
//light struct

#ifndef BUW_LIGHT_HPP
#define BUW_LIGHT_HPP

#include "color.hpp"
#include <glm/vec3.hpp>

struct Light
{
	Light(): m_name{""}, m_pos{0.0, 0.0, 0.0}, m_color{Color{0.0f, 0.0f, 0.0f}}, m_brightness{0.0f}{};

    Light(std::string name, glm::vec3 position, Color color, float brightness): 
        m_name{name}, m_pos{position}, m_color{color}, m_brightness{brightness}{};

    //Name
    std::string m_name;

    //Position
    glm::vec3 m_pos;
    
    //Color
    Color m_color;

    //Brightness
    float m_brightness;

    //Intensität = m_brightness * m_color

    // << Output Operator
    friend std::ostream& operator<<(std::ostream& os, Light const& light)
    {
        os  << "light name: " << light.m_name << "\n"
            << "position: " << light.m_pos.x << " " << light.m_pos.y << " " << light.m_pos.z << "\n"
            << "color: " << light.m_color << "\n"
            << "brightness: " << light.m_brightness << "\n";
        return os;
    }

};

#endif //BUW_LIGHT_HPP
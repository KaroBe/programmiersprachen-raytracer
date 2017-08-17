
//light struct

#ifndef BUW_LIGHT_HPP
#define BUW_LIGHT_HPP

#include "color.hpp"
#include <glm/vec3.hpp>

struct Light
{
    //Name
    std::string name;

    //Position
    glm::vec3 m_pos;
    
    //Color
    Color m_color;

    //Brightness
    float m_brightness;

    //Intensität = m_brightness * m_color

};

#endif //BUW_LIGHT_HPP
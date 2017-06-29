
#ifndef BUW_MATERIAL_HPP
#define BUW_MATERIAL_HPP

#include <iostream>
#include "color.hpp"

struct Material
{   
    //Default Constructor
    Material() :
        m_name{""},
        m_ka{Color{0.0f,0.0f,0.0f}},
        m_kd{Color{0.0f,0.0f,0.0f}},
        m_ks{Color{0.0f,0.0f,0.0f}},
        m_m{0.0f}
    {};

    //Custom Constructor
    Material(std::string name, Color ka, Color kd, Color ks, float m) :
        m_name{name},
        m_ka{ka},
        m_kd{kd},
        m_ks{ks},
        m_m{m}
        {};

    //Member Varibles:
    std::string m_name; //Name
    Color m_ka;         //ambiente Reflexion
    Color m_kd;         //diffuse Reflexion
    Color m_ks;         //spiegelnde Reflexion
    float m_m;          //Exponent für spiegelnde Reflexion

    // << Output Operator
    friend std::ostream& operator<<(std::ostream& os, Material const& material)
    {
        os  << "material name: " << material.m_name << "\n"
            << "ka: " << material.m_ka
            << "kd: " << material.m_kd
            << "ks: " << material.m_ks
            << "m: " << material.m_m << "\n";
        return os;
    }

    bool operator==(Material const& other)
    {
        if(m_ka==other.m_ka and m_kd==other.m_kd and m_ks==other.m_ks
            and m_m==other.m_m)
        {
            return true;
        }
        else
          return false;
    }

};

#endif //#define BUW_COLOR_HPP
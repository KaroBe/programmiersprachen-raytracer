
//camera struct

#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP

#include "color.hpp"
#include <glm/vec3.hpp>

struct Camera
{
    /*Standartmäßig gilt:
    fov_x = ??? 
    eye = (0|0|0) = in Koordinatenursprung
    up = (0|1|0) = auf positiver y-Achse
    */

    //c'tor standart-camera

    //Name
    std::string m_name;

    //horizontaler Öffnungswinkel
    float m_fov_x;
    
    //Position
    glm::vec3 m_eye;
    
    //Blickrichtung
    glm::vec3 m_dir;
    
    //Up-Vektor
    glm::vec3 m_up;

};

#endif //BUW_CAMERA_HPP
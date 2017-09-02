
//camera struct

#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP

#include "color.hpp"
#include <glm/vec3.hpp>

struct Camera
{
    Camera():
        m_name{""}, 
        m_fov_x{0.0f}, 
        m_eye{0.0f, 0.0f, 0.0f}, 
        m_dir{0.0f, 0.0f, 0.0f}, 
        m_up{0.0f, 0.0f, 0.0f}
        {};

    Camera(std::string name, float fov_x, glm::vec3 eye, glm::vec3 dir, glm::vec3 up): 
        m_name{name}, 
        m_fov_x{fov_x}, 
        m_eye{eye}, 
        m_dir{dir}, 
        m_up{up}{};

    //if only name and fov x are given:
    Camera(std::string name, float fov_x):
        m_name{name},
        m_fov_x{fov_x},
        m_eye{0.0f, 0.0f, 0.0f},
        m_dir{0.0f, 0.0f, -1.0f},    //negative z achse
        m_up{0.0f, 1.0f, 0.0f}
        {};   //positive y achse

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

    //Brauchen wir für Kameratransformation auch Transformationsmatrix?
    //Diese sollte dann bei der Berechnung der Rays in

    // << Output Operator
    friend std::ostream& operator<<(std::ostream& os, Camera const& camera)
    {
        os  << "camera name: " << camera.m_name << "\n"
            << "horizontal opening angle: " << camera.m_fov_x << "\n"
            << "position: " << camera.m_eye.x << " " << camera.m_eye.y << " " << camera.m_eye.z << " " << "\n"
            << "direction: " << camera.m_dir.x << " " << camera.m_dir.y << " " << camera.m_dir.z << " " << "\n"
            << "up-vector: " << camera.m_up.x << " " << camera.m_up.y << " " << camera.m_up.z << " " << "\n";
        return os;
    }
};

#endif //BUW_CAMERA_HPP
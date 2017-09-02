
//camera struct

#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP

#include "color.hpp"
#include <glm/vec3.hpp>

class Camera
{

public:


    Camera();
    Camera(std::string name, float fov_x, glm::vec3 eye, glm::vec3 dir, glm::vec3 up);
    Camera(std::string name, float fov_x);

    std::ostream& Camera::print (std::ostream& os) const;

    void translate (glm::vec3 vector);
    void rotate (float angle, glm::vec3 vector);


protected:

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

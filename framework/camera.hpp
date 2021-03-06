
//camera struct

#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP

#include "color.hpp"
#include "ray.hpp"
#include "pixel.hpp"
#include <glm/vec3.hpp>

class Camera
{

public:

    Camera();
    Camera(std::string name, float fov_x, glm::vec3 eye, glm::vec3 dir, glm::vec3 up);
    Camera(std::string name, float fov_x);

    std::string get_name() const;
    float get_fov_x() const;
    glm::vec3 get_eye() const;
    glm::vec3 get_dir() const;
    glm::vec3 get_up() const;

    std::ostream& print (std::ostream& os) const;

    void translate (glm::vec3 vector);
    void rotate (float angle, glm::vec3 vector);

    Ray calc_cam_rays (Pixel const& pixel, float w, float h) const;
    glm::mat4 calc_cam_tranformation () const;

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
    
    glm::mat4 m_world_transformation;
    glm::mat4 m_world_transformation_inv;
};

#endif //BUW_CAMERA_HPP

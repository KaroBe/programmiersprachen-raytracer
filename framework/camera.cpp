
#include "camera.hpp"

Camera::Camera():
    m_name{""}, 
    m_fov_x{0.0f},
    m_eye{0.0f, 0.0f, 0.0f}, 
    m_dir{0.0f, 0.0f, 0.0f}, 
    m_up{0.0f, 0.0f, 0.0f}
    {};

Camera::Camera(std::string name, float fov_x, glm::vec3 eye, glm::vec3 dir, glm::vec3 up): 
    m_name{name}, 
    m_fov_x{fov_x}, 
    m_eye{eye}, 
    m_dir{dir}, 
    m_up{up}
    {};

    //if only name and fov x are given:
Camera::Camera(std::string name, float fov_x):
    m_name{name},
    m_fov_x{fov_x},
    m_eye{0.0f, 0.0f, 0.0f},
    m_dir{0.0f, 0.0f, -1.0f},    //negative z achse
    m_up{0.0f, 1.0f, 0.0f}
    {};   //positive y achse


std::string Camera::get_name()
{
	return m_name;
}

float Camera::get_fov_x()
{
	return m_fov_x;
}

glm::vec3 get_eye()
{
	return m_eye;
}

glm::vec3 get_dir()
{
	return m_dir;
}

glm::vec3 get_up()
{
	return m_up;
}

// << Output Operator
std::ostream& Camera::print (std::ostream& os) const
{
    os  << "camera name: " << camera.m_name << "\n"
        << "horizontal opening angle: " << camera.m_fov_x << "\n"
        << "position: " << camera.m_eye.x << " " << camera.m_eye.y << " " << camera.m_eye.z << " " << "\n"
        << "direction: " << camera.m_dir.x << " " << camera.m_dir.y << " " << camera.m_dir.z << " " << "\n"
        << "up-vector: " << camera.m_up.x << " " << camera.m_up.y << " " << camera.m_up.z << " " << "\n";
    return os;
}


void translate (glm::vec3 vector)
{

}

void rotate (float angle, glm::vec3 vector)
{

}


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


std::string Camera::get_name() const
{
	return m_name;
}

float Camera::get_fov_x() const
{
	return m_fov_x;
}

glm::vec3 Camera::get_eye() const
{
	return m_eye;
}

glm::vec3 Camera::get_dir() const
{
	return m_dir;
}

glm::vec3 Camera::get_up() const
{
	return m_up;
}

// << Output Operator
std::ostream& Camera::print (std::ostream& os) const
{
    os  << "camera name: " << m_name << "\n"
        << "horizontal opening angle: " << m_fov_x << "\n"
        << "position: " << m_eye.x << " " << m_eye.y << " " << m_eye.z << " " << "\n"
        << "direction: " << m_dir.x << " " << m_dir.y << " " << m_dir.z << " " << "\n"
        << "up-vector: " << m_up.x << " " << m_up.y << " " << m_up.z << " " << "\n";
    return os;
}
/*
Ray Camera::calc_cam_rays (Pixel const& pixel, Scene& scene) const
{

  float p_x = float(pixel.x);
  float p_y = float(pixel.y);
  float w = float(scene.m_x_res);
  float h = float(scene.m_y_res);
  float fov_x = scene.m_camera.m_fov_x;

  float img_ratio = w/h;
  float dis_film = (0.5 / tan(fov_x/2));

  float x = (p_x * (img_ratio / w) - (img_ratio/2));
  float y = p_y * (1.0 / h) - 0.5;
  float z = -1.0 * dis_film;

  glm::vec3 direction{x,y,z};
  
  direction=glm::normalize(direction);
  
  Ray ray{{0,0,0}, direction};

  apply_cam_tranformation(ray);

  return ray;
}

void Camera::apply_cam_tranformation (Ray& in_ray) const
{
    //transform ray with cam_transf_matrix

}
*/
void Camera::translate (glm::vec3 vector)
{

}

void Camera::rotate (float angle, glm::vec3 vector)
{

}

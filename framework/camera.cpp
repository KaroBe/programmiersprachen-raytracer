
#include "camera.hpp"

Camera::Camera():
    m_name{""}, 
    m_fov_x{0.0f},
    m_eye{0.0f, 0.0f, 0.0f}, 
    m_dir{0.0f, 0.0f, 0.0f}, 
    m_up{0.0f, 0.0f, 0.0f},
    m_world_transformation{ 1.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 1.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 1.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 1.0},
    m_world_transformation_inv{glm::inverse(m_world_transformation)}
    {};

Camera::Camera(std::string name, float fov_x, glm::vec3 eye, glm::vec3 dir, glm::vec3 up): 
    m_name{name}, 
    m_fov_x{fov_x}, 
    m_eye{eye}, 
    m_dir{dir}, 
    m_up{up},
    m_world_transformation{ 1.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 1.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 1.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 1.0},
    m_world_transformation_inv{glm::inverse(m_world_transformation)}
    {
      //aus eye, dir und up die transformationsmatrix der Kamera berechnen
      m_world_transformation = calc_cam_tranformation();
      std::cout << "Added eye dir up stuff when construction";
      m_world_transformation_inv = glm::inverse(m_world_transformation);
    };

    //if only name and fov x are given:
Camera::Camera(std::string name, float fov_x):
    m_name{name},
    m_fov_x{fov_x},
    m_eye{0.0f, 0.0f, 0.0f},
    m_dir{0.0f, 0.0f, -1.0f},    //negative z achse
    m_up{0.0f, 1.0f, 0.0f},
    m_world_transformation{ 1.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 1.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 1.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 1.0},
    m_world_transformation_inv{glm::inverse(m_world_transformation)}
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

Ray Camera::calc_cam_rays (Pixel const& pixel, float w, float h) const
{

  float p_x = float(pixel.x);
  float p_y = float(pixel.y);
  float fov_x = m_fov_x;

  float img_ratio = w/h;
  float dis_film = (0.5 / tan(fov_x/2));

  float x = (p_x * (img_ratio / w) - (img_ratio/2));
  float y = p_y * (1.0 / h) - 0.5;
  float z = -1.0 * dis_film;

  glm::vec3 direction{x,y,z};
  
  direction=glm::normalize(direction);
  
  Ray ray{{0,0,0}, direction};

  //std::cout << "\n ray before: " << ray; 

  glm::mat4 mat = m_world_transformation;
  /*
  std::cout << "\n" 
     << mat[0].x << " " 
     << mat[1].x << " "
     << mat[2].x << " "
     << mat[3].x << "\n"

     << mat[0].y << " "
     << mat[1].y << " "
     << mat[2].y << " "
     << mat[3].y << "\n"

     << mat[0].z << " "
     << mat[1].z << " "
     << mat[2].z << " "
     << mat[3].z << "\n"

     << mat[0].w << " "
     << mat[1].w << " "
     << mat[2].w << " "
     << mat[3].w << "\n";
*/
  ray = transform_ray(m_world_transformation, ray);
  
  //std::cout << "ray after: " << ray << "\n";

  return ray;
}

glm::mat4 Camera::calc_cam_tranformation () const
{
  //transform ray with cam_transf_matrix
  //exe, dir, up sind attribute von *this!

  glm::vec3 e = m_eye;
  glm::vec3 n = glm::normalize(m_dir);
  glm::vec3 up = m_up;

  glm::vec3 u = glm::normalize(glm::cross(n,up));
  glm::vec3 v = glm::normalize(glm::cross(u,n));

  glm::mat4 cam_transformation;
  cam_transformation[0] = glm::vec4{u, 0.0f};
  cam_transformation[1] = glm::vec4{v, 0.0f};
  cam_transformation[2] = glm::vec4{-1.0f * n, 0.0f};
  cam_transformation[3] = glm::vec4{e, 1.0f};

  return cam_transformation;
}

void Camera::translate (glm::vec3 vector)
{
  glm::mat4 T;
  T[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
  T[1] = glm::vec4{0.0f, 1.0f, 0.0f, 0.0f};
  T[2] = glm::vec4{0.0f, 0.0f, 1.0f, 0.0f};
  T[3] = glm::vec4{vector.x, vector.y, vector.z, 1.0f};
  m_world_transformation = T * m_world_transformation;
  m_world_transformation_inv = glm::inverse(m_world_transformation);
}

void Camera::rotate (float angle, glm::vec3 vector)
{
  angle = ((2 * M_PI) / 360) * angle;
  glm::mat4 T = glm::rotate(glm::mat4(), angle, vector);
  m_world_transformation = T * m_world_transformation;
  m_world_transformation_inv = glm::inverse(m_world_transformation);
}

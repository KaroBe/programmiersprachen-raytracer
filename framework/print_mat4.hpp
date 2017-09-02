#ifndef PRINT_MAT4_HEADER_
#define PRINT_MAT4_HEADER_

#include <glm/glm.hpp>

std::ostream& print_mat4 (std::ostream& os, glm::mat4 mat)
{
  os << mat[0].x << " " 
     << mat[0].y << " "
     << mat[0].z << " "
     << mat[0].w << "\n"
     << mat[1].x << " "
     << mat[1].y << " "
     << mat[1].z << " "
     << mat[1].w << "\n"
     << mat[2].x << " "
     << mat[2].y << " "
     << mat[2].z << " "
     << mat[2].w << "\n"
     << mat[3].x << " "
     << mat[3].y << " "
     << mat[3].z << " "
     << mat[3].w << "\n";
  return os;
};

#endif
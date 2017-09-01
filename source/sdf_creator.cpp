#include <renderer.hpp>
#include <iostream>
#include <fstream>
#include <window.hpp>
#include "sdfloader.hpp"

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include <algorithm>
#include <tuple>

int main(int argc, char* argv[])
{
  //load scene with sdf - loader
  SDFloader loader{};
  //Scene scene = loader.load("/home/lissy/Dokumente/raytracer/programmiersprachen-raytracer/source/lissysscene");
  Scene scene = loader.load("/home/karoline/Documents/studium/17_sose/programmiersprachen/raytracer/programmiersprachen-raytracer/source/lissysscene");


  // WARNING: Transformationen in der Scene werden nicht beachtet, nur
  // die, die hier festgelegt sind als Ausgangslage:
  // variablen benennen mit 

  //skalierung
  std::vector<std::pair<std::string, glm::vec3>> scales;
  scales.push_back(std::make_pair("left_sphere",glm::vec3{0.0f,0.0f,0.0f}));
  
  //translation
  std::vector<std::pair<std::string, glm::vec3>> translations;
  translations.push_back(std::make_pair("left_sphere", glm::vec3{0.0f,0.0f,0.0f}));
  translations.push_back(std::make_pair("right_sphere", glm::vec3{0.0f,0.0f,0.0f}));
  translations.push_back(std::make_pair("eye", glm::vec3{-1.0f,0.0f,0.0f}));

  //winkel
  std::vector<std::tuple<std::string, float, glm::vec3>> rotations;
  rotations.push_back(std::make_tuple("left_sphere", 0.0f, glm::vec3{0.0f,0.0f,0.0f}));

  for (int x = 0; x<2; x++)
  {
    std::cout << "\nenter loop for the " << x << "th time";
    
    // Transformationen aufrechnen
    for(std::pair<std::string, glm::vec3>& t : translations)
    {
      if (t.first == "left_sphere")
      {
        t.second = t.second + glm::vec3{0.1f,0.0f,0.0f};
      }
      std::cout << "\n" << t.second.x  << " " 
                << t.second.y << " " 
                << t.second.z << "\n";
    }

    std::string file_name = "image_" + std::to_string(x);

    std::fstream sdf_output;
    sdf_output.open(file_name,std::fstream::in | std::fstream::app);
    sdf_output.clear();

    if(sdf_output.is_open())
    {
      //Materials
      sdf_output << "# Materials \n";
      for (std::pair<std::string, Material> m : scene.m_materials)
      {
        Material material = m.second;
        sdf_output << "define material "
            << material.m_name << " "
            << material.m_ka.r << " "
            << material.m_ka.g << " "
            << material.m_ka.b << " "
            << material.m_kd.r << " "
            << material.m_kd.g << " "
            << material.m_kd.b << " "
            << material.m_ks.r << " "
            << material.m_ks.g << " "
            << material.m_ks.b << " "
            << material.m_m << " "
            << material.m_refrac << " "
            << material.m_opac << "\n";
      }

      //Shapes
      sdf_output << "# Shapes\n";

      scene.m_composite->print_all_definitions(sdf_output);

      //Transformationen

      sdf_output << "# Transformations\n";

      std::stringstream cam_transformations;

      //translations
      for (std::pair<std::string,glm::vec3> t : translations)
      {
        std::cout << "\ntranslation of " << t.first;
        std::stringstream buffer;
        buffer << "transform " << t.first << " translate "
                  << t.second.x << " "
                  << t.second.y << " "
                  << t.second.z << "\n";
        if(t.first == "eye")
        { 
          cam_transformations << buffer.rdbuf();
        }
        else
        {
            sdf_output << buffer.rdbuf();
        }
      }

      //scales
      for (std::pair<std::string,glm::vec3> s : scales)
      {
        std::stringstream buffer;
        buffer << "transform " << s.first << " scale "
                            << s.second.x << " "
                            << s.second.y << " "
                            << s.second.z << "\n";
        if(s.first == "eye")
        { 
          cam_transformations << buffer.rdbuf();
        }
        else sdf_output << buffer.rdbuf();
      }

      //rotations
      for (std::tuple<std::string,float,glm::vec3> r : rotations)
      {
        std::stringstream buffer;
        glm::vec3 axis = std::get<2>(r);
        buffer << "transform " << std::get<0>(r) << " rotate "
                  << std::get<1>(r) << " "
                  << axis.x << " "
                  << axis.y << " "
                  << axis.z << "\n";
        if(std::get<0>(r) == "eye")
        { 
          cam_transformations << buffer.rdbuf();
        }
        else sdf_output << buffer.rdbuf();        
      }

      //lights

      sdf_output << "# Lights\n";

      for(std::shared_ptr<Light> l_ptr : scene.m_lights)
      {
        Light l = *l_ptr;
        sdf_output << "define light "
          << l.m_name << " "
          << l.m_pos.x << " " << l.m_pos.y << " " << l.m_pos.z << ""
          << l.m_color.r << " " << l.m_color.g << " " << l.m_color.b << " "
          << l.m_brightness << "\n";
      }
      
      //ambient light

      sdf_output << "# Ambient Light\n";

      sdf_output << "ambient" << scene.m_ambient_light;

      //camera
      sdf_output << "define camera eye " << scene.m_camera.m_fov_x << " "
                << scene.m_camera.m_eye.x << " "
                << scene.m_camera.m_eye.y << " "
                << scene.m_camera.m_eye.z << " "
                << scene.m_camera.m_dir.x << " "
                << scene.m_camera.m_dir.y << " "
                << scene.m_camera.m_dir.z << " "
                << scene.m_camera.m_up.x << " "
                << scene.m_camera.m_up.y << " "
                << scene.m_camera.m_up.z << "\n";

      //camera transformations
      sdf_output << cam_transformations.rdbuf();

      //render

      sdf_output << "# ...and go!\n";

      sdf_output << "render eye " << file_name << " " << scene.m_x_res << " " << scene.m_y_res;

      sdf_output.close();
    }
    else
    {
      std::cout << "ERROR OPENING FILE "<< file_name;
    }
  }

  return 0;
  //die generierten sdf_files kann man dann mit raytracer.cpp rendern
}
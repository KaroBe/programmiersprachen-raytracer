#include <renderer.hpp>
#include <window.hpp>
#include "sdfloader.hpp"

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

int main(int argc, char* argv[])
{
  //std::string karo_path = "/home/karoline/Documents/studium/17_sose/programmiersprachen/raytracer/programmiersprachen-raytracer/source/";
  std::string karo_path = "/home/karoline/Documents/studium/17_sose/programmiersprachen/raytracer/programmiersprachen-raytracer/build/source/";
  std::string lissy_path = "/home/lissy/Dokumente/raytracer/programmiersprachen-raytracer/source/";

  std::string user;
  std::cout << "\n~~~~~~~~~~~~ LE RAYTRACER ~~~~~~~~\nare you lissy [l] or karo [k] ? \n";
  std::cin >> user;

  std::string path;
  if(user == "l" or user == "lissy")
  {
    path = lissy_path;
  }
  else if(user == "k" or user == "karo")
  {
    path = karo_path;
  }
  else
  {
    std::cout << "\nwho dat? try again...\n";
    return 0;
  }

  for (int i = 0; i<2; i++)
  {
    //path += "lissysscene";
    std::string current_path = path + "image_" + std::to_string(i);
    std::cout << current_path;

    //load scene with sdf - loader
    SDFloader loader{};
    Scene scene = loader.load(current_path);

    //make Renderer with that scene, and w/h of file we want
    Renderer app{scene.m_x_res, scene.m_y_res, scene.m_fileOut, scene};
    std::cout << "Renderer generiert";

    app.render();
  }

  return 0;
}

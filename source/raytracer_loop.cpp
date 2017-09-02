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
  std::string lissy_path = "/home/lissy/Dokumente/raytracer/programmiersprachen-raytracer/build/source";

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

  for (int i = 0; i<3; i++)
  {
    //path += "lissysscene";
    std::string current_path = path + "sdf_" + std::to_string(i);
    std::cout << "\n "<< current_path << "\n";

    //load scene with sdf - loader
    SDFloader loader{};
    //Scene scene = loader.load();
    Scene scene = loader.load(current_path);

    //make Renderer with that scene, and w/h of file we want
    Renderer app{scene.m_x_res, scene.m_y_res, scene.m_fileOut, scene};
    std::cout << "\nRenderer generiert";

    //Open thread that can use the app variable and renders the
    //app
    std::thread thr([&app]() { app.render(); });
    thr.join();
  }

  return 0;
}

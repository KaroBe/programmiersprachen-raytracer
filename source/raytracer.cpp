#include <renderer.hpp>
#include <window.hpp>
#include "sdfloader.hpp"

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

int main(int argc, char* argv[])
{
  /*
  unsigned const width = 800;
  unsigned const height = 600;
  std::string const filename = "./checkerboard.ppm";
  */
  //load scene with sdf - loader
  SDFloader loader{};
  //Scene scene = loader.load("/home/lissy/Dokumente/raytracer/programmiersprachen-raytracer/source/simplescene");
  Scene scene = loader.load("/home/karoline/Documents/studium/17_sose/programmiersprachen/raytracer/programmiersprachen-raytracer/source/simplescene");

  //make Renderer with that scene, and w/h of file we want
  Renderer app{scene.m_x_res, scene.m_y_res, scene.m_fileOut, scene};
  std::cout << "renderer generiert";

  //Open thread that can use the app variable and renders the
  //app
  std::thread thr([&app]() { app.render(); });
  std::cout << "gerendert!";

/*
  Window win{glm::ivec2{scene.m_x_res,scene.m_y_res}};

  while (!win.should_close()) {
    if (win.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      win.close();
    }
    //print colorbuffer of renderer app to the window
    win.show(app.colorbuffer());
  }
*/
  thr.join();

  return 0;
}

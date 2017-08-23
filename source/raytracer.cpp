#include <renderer.hpp>
#include <window.hpp>
#include "sdfloader.hpp"

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

int main(int argc, char* argv[])
{
  unsigned const width = 800;
  unsigned const height = 600;
  std::string const filename = "./checkerboard.ppm";

  //load scene with sdf - loader
  SDFloader loader{};
  Scene scene = loader.load("/home/lissy/Dokumente/raytracer/programmiersprachen-raytracer/source/simplescene");
  
  //std::cout << "?";
  //Scene scene;

  //make Renderer with that scene, and w/h of file we want
  Renderer app{width, height, filename, scene};
  std::cout << "renderer generiert";

  //Open thread that can use the app variable and renders the
  //app
  std::thread thr([&app]() { app.render(); });
  std::cout << "gerendert!";

  Window win{glm::ivec2{width,height}};

  while (!win.should_close()) {
    if (win.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      win.close();
    }
    //print colorbuffer of renderer app to the window
    win.show(app.colorbuffer());
  }

  thr.join();

  return 0;
}

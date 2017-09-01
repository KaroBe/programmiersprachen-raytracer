#include <renderer.hpp>
#include <window.hpp>
#include "sdfloader.hpp"

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

int main(int argc, char* argv[])
{
  // TODO: Schleife oder so hinzufügen, die alle sdf-dateien aus einem
  //Ordner nacheinander einliest

  //load scene with sdf - loader
  SDFloader loader{};
  //Scene scene = loader.load("/home/lissy/Dokumente/raytracer/programmiersprachen-raytracer/source/lissysscene");
  Scene scene = loader.load("/home/karoline/Documents/studium/17_sose/programmiersprachen/raytracer/programmiersprachen-raytracer/source/lissysscene");

  //make Renderer with that scene, and w/h of file we want
  Renderer app{scene.m_x_res, scene.m_y_res, scene.m_fileOut, scene};
  std::cout << "renderer generiert";

  //Open thread that can use the app variable and renders the
  //app
  std::thread thr([&app]() { app.render(); });
  //std::cout << "gerendert!";

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

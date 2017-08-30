
#include <renderer.hpp>
#include <iostream>
#include <fstream>
#include <window.hpp>
#include "sdfloader.hpp"

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

int main(int argc, char* argv[])
{
  //load scene with sdf - loader
  SDFloader loader{};
  //Scene scene = loader.load("/home/lissy/Dokumente/raytracer/programmiersprachen-raytracer/source/lissysscene");
  Scene scene = loader.load("/home/karoline/Documents/studium/17_sose/programmiersprachen/raytracer/programmiersprachen-raytracer/source/lissysscene");

  /*
  wir haben ausgangs-scene eingelesen
  nun muss x mal die Parameter der Scene geändert und der sdf_creator
  für diese Scene angeschmissen werden.
  Dabei muss das sdf_file jeweils in einem neuen File gespeichert
  werden... dh string m_fileOut von scene jeweils anpassen und
  in name_x mit float x bei jeden Schleifenduchlauf erhöht werden
  */
 /* float frames = 124;
  for(int x = 0; i<frames; ++i)
  {*/

    //change scene parameters:
      //transformationsmatrix auf jeweilige Objekte anwenden
      //oder was auch immer eben farbe kein plan (disko disko party party :grin:)
      //scene.m_name ändern

    //z.B. sphere1.center immer zehntel unit nach rechts verschieben
    // sphere1.translate(glm::vec3{0.1f, 0.0f, 0.0f}) kp ob das ein
    //korrekter translationsvektor ist übrigens aber würde iwie sinn machen
    // ich denke man ändert hier wahrscheinlich nicht direkt die
    // koordinaten, sondern die world_transformation-matrix, wobei man
    // dann auch die inverse ändern muss
    //-> müssen wir erstmal die transformationssachen implementieren

    unsigned int x = 1;
    std::string file_name = "image_" + std::to_string(x);

    std::ofstream sdf_output;
    sdf_output.open(file_name);

    std::cout << "\ngettin here lol\n";

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
      sdf_output << "# Shapes"

      // PROBLEM ! ggf typ-variable in shape einbauen?
      // weiß sonst nicht wirklich wie man das im nachhinein
      // auslesen soll
      // und man kann auch nicht einfacg in shape print_definition
      // einbauen, weil man dann bei composite an seine Grenzen stößt:
      // m_composite würde zuerst ausgedruckt, und die Reihenfolge wird
      // falsch rum :sob:
      for (std::shared_ptr<Shape> shape : scene.m_content)
      {
        if(composite)
        else if (box)
        else if (sphere)        

      }      

/*
      shapes - erst boxen/spheres dann composites. composites wie
      tree der von unten ausgelesen wird, an letzter stelle steht
      das scene.m_composite
      vector mit shapes gibt es noch(?) aber eigentlich:
      m_composite rekursiv nach weiteren composites durchsuchen
*/

/*
      transformationen
      ??? sind in den shapes gespeichert -> einen stream für transformationen
      parallel zum auslesen der Shapes füllen, nachdem man mit
      shapes fertig ist, dessen inhalt in sdf_output schreiben

      lights
      vector
      
      ambient light
      scene.m_ambient_light

      camera
      m_camera
      
      camera transformationen
      ??? es sind ja iwie keine drei transformationsmatrixes haha mehr
      sondern nur noch eine transformation? oder was?
*/

    sdf_output.close();

  }

  return 0;
  //die generierten sdf_files kann man dann mit raytracer.cpp rendern
}

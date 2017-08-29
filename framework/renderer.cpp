// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const& file, Scene const& scene)
  : width_(w)
  , height_(h)
  , colorbuffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
  , m_scene(scene)
{}

void Renderer::render()
{
  const std::size_t checkersize = 20;

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {

      //new Pixel
      Pixel p(x,y);
      Color pcolor{0.0, 0.0, 0.0};
      /*
      //calculate some nice colors to test writing to colorbuffer n ppm
      if ( ((x/checkersize)%2) != ((y/checkersize)%2)) {
        p.color = Color(0.0, 1.0, float(x)/height_);
      } else {
        p.color = Color(1.0, 0.0, float(y)/width_);
      }
      */

      //cast ray trough that pixel -> Ray raycast(Pixel p)
      Ray r = raycast(p);
      pcolor = raytrace(r, 2);
      pcolor.r = pcolor.r / (pcolor.r + 1); //tonemapping
      pcolor.g = pcolor.g / (pcolor.g + 1);
      pcolor.b = pcolor.b / (pcolor.b + 1);
      p.color = pcolor;
      //std::cout << "x: " << x << " y: " << y << " Color: " << p.color << std::endl;

      //write Pixel to colorbuffer_ and ppm_
      write(p);
    }
  }
  //save altered file
  ppm_.save(filename_);
}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= colorbuffer_.size() || (int)buf_pos < 0) {
    std::cout << "HIER WURDE EIN PIXEL NICHT AUSGEGEBEN";
    std::cerr << "Fatal Error Renderer::write(ixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    //save new pixel to colorbuffer
    colorbuffer_[buf_pos] = p.color;
  }

  //write new pixel to ppm_writer
  ppm_.write(p);
}

Ray Renderer::raycast(Pixel const& pixel) //const
{
/*
  //Prototyp nach Jana Vorbild

  float dis_film = (width_/2) / (tan(m_scene.m_camera.m_fov_x/2));

  float x = float(pixel.x)/float(width_)-0.5;
  float y = float(pixel.y)/float(height_)-0.5;
  float z = -1.0f * dis_film;

  glm::vec3 direction = {x,y,z};

  direction = glm::normalize(direction);

  Ray ray{{0,0,0}, direction};
*/

  float p_x = float(pixel.x);
  float p_y = float(pixel.y);
  float w = float(width_);
  float h = float(height_);
  float fov_x = m_scene.m_camera.m_fov_x;

  float img_ratio = w/h;
 // std::cout << "\n " << img_ratio;
  float dis_film = (0.5 / tan(fov_x/2));

  float x = (pixel.x * (img_ratio / w) - (img_ratio/2));
  float y = pixel.y * (1.0 / h) - 0.5;
  float z = -1.0 * dis_film;

  glm::vec3 direction{x,y,z};
  
  direction=glm::normalize(direction);
  
  Ray ray{{0,0,0}, direction};

/*
  //Cast ray an shit - Karos nicht funktionierende Variante
  float NDCx = (pixel.x + 0.5f) / width_;
  float NDCy = (pixel.y + 0.5f) / height_;

  float x = (2*NDCx -1) * tan((m_scene.m_camera.m_fov_x / 2) * (M_PI/180)) * (width_/height_);
  float y = (1-2*NDCy)  * tan((m_scene.m_camera.m_fov_x / 2) * (M_PI/180));

  glm::vec3 direction(x,y,-1);

  //std::cout << "\nunnormalisiert: " << direction.x << ", " << direction.y << ", " << direction.z;
*/

  return ray;
}

Color Renderer::raytrace(Ray const& ray, unsigned int depth)
{
  Hit closestHit = m_scene.m_composite -> intersect(ray);
  Color color;
  if(closestHit.m_hit)
  {
    
    //ambientlight funktion -> berechtnet über object.material.ka und dem ambient light den farbwert
    Color ambient = closestHit.m_shape -> get_material().m_ka;
    color += m_scene.m_ambient_light * ambient;

    //lichtquellen -> für alle lichter -> berechnet mithilfe des objects die farbe im licht
    for(auto& light : m_scene.m_lights) 
    {
        if(color.r < 1.0f || color.g < 1.0f ||color.b < 1.0f)
        {
        bool noObject = false;

        //Vector von Intersection zu Lichtquelle berechnen
        glm::vec3 dirToLight = glm::normalize(light -> m_pos - closestHit.m_intersection); //normalize that light!!!

        //bisschen verschieben, damit intersect richtig funktioniert
        glm::vec3 newOrigin = closestHit.m_intersection + dirToLight * 0.001f; //so intersect works properly
        Ray rayToLight{newOrigin, dirToLight}; //vec from hit to lightsource
        
        //Liegt Objekt zwischen Shape und Lichtquelle?
        //Trifft der Ray eine andere Shape?
        Hit shadowHit = m_scene.m_composite -> intersect(rayToLight); //does the vec meet another object?
        //wenn OShape getroffen wird:
        //std::cout << "shadow hit: " << shadowHit << std::endl;


        if(shadowHit.m_hit)  
        {
          //liegt diese Shape zwischen Lichtquelle und Intersection?
          float disToLight = glm::length(light -> m_pos - closestHit.m_intersection); //is the objects infront of light?
          if(disToLight < shadowHit.m_distance)
          {
            noObject = true;
          }
        }
        else //wenn kein Objekt dazwischen liegt:
        {
          noObject = true;
        }

        if(noObject)  //difusses und dings anderes Licht von punktlichtquellen
        {
          float ln = std::max(glm::dot(dirToLight, closestHit.m_normale), 0.0f);
          //glm::vec3 ln(dirToLight.x * closestHit.m_normale.x,
          //            dirToLight.y * closestHit.m_normale.y,
          //            dirToLight.y * closestHit.m_normale.z);

          glm::vec3 r = glm::normalize(glm::reflect(dirToLight, closestHit.m_normale));
          glm::vec3 v = glm::normalize(glm::vec3{-ray.m_direction.x, -ray.m_direction.y, -ray.m_direction.z});
          float rv = std::max(glm::dot(r, v), 0.0f);
          float rvm = std::pow(rv, (closestHit.m_shape ->get_material().m_m));

          Color diffuse = closestHit.m_shape -> get_material().m_kd;
          Color specular = closestHit.m_shape -> get_material().m_ks;

          Color intensity = light -> m_color * light -> m_brightness;
          color += intensity * (diffuse * ln + specular * rvm);
        }

      } //else: shadow
    }

    //if depth > 0 -> reflektion berechnen
    if(depth > 0)
    {
      //zur erinnerung: https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing/adding-reflection-and-refraction
      glm::vec3 mirrorDirection = glm::normalize(glm::reflect(ray.m_direction, closestHit.m_normale));
      Ray mirrorRay{(closestHit.m_intersection + (0.0001f * mirrorDirection)), mirrorDirection};
      Color mirrorColor = raytrace(mirrorRay, depth-1);

      float kr = closestHit.m_shape -> get_material().m_refrac;
      Color ks = closestHit.m_shape -> get_material().m_ks;

      color = color * 0.5f + color * 0.5f * mirrorColor * ks * kr; //reflected color

      if(color.r < 1.0f || color.g < 1.0f ||color.b < 1.0f)
      {
        float opac = closestHit.m_shape -> get_material().m_opac;
        glm::vec3 refractDirection = glm::normalize(glm::refract(ray.m_direction, closestHit.m_normale, opac));
        Ray refractRay{(closestHit.m_intersection + (0.00001f * refractDirection)), refractDirection};
        Color refractColor = raytrace(refractRay, depth-1);

        //color = color * (mirrorColor * kr + refractColor * (1-kr));
        //color = color + refractColor;
        color += refractColor * ks * (1.0f - kr); //refracted color
      }
    }  
  }
  else    //wenn kein hit: nur ambient zurückgeben 
  {
   color = m_scene.m_ambient_light;
  }

  //rückgabe des berechneten
  return color;
}

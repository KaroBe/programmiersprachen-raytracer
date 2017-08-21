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
      
      //calculate some nice colors
      if ( ((x/checkersize)%2) != ((y/checkersize)%2)) {
        p.color = Color(0.0, 1.0, float(x)/height_);
      } else {
        p.color = Color(1.0, 0.0, float(y)/width_);
      }

      //write Pixel to colorbuffer
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

Color Renderer::raytrace(Ray const& ray)
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
      bool noObject = false;
      glm::vec3 newOrigin = closestHit.m_intersection + closestHit.m_intersection * 0.001f; //so intersect works properly
      glm::vec3 dirToLight = glm::normalize(light -> m_pos - closestHit.m_intersection);  //normalized to ligght = l!!
      Ray rayToLight{newOrigin, dirToLight}; //vec from hit to lightsource
      Hit shadowHit = m_scene.m_composite -> intersect(rayToLight); //does the vec meet another object?
      if(shadowHit.m_hit)  
      {
        float disToLight = glm::length(light -> m_pos - closestHit.m_intersection); //is the objects infront of light?
        if(disToLight < shadowHit.m_distance)
        {
          noObject = true;
        }
      }
      else  //if the ray meets no objects
      {
        noObject = true;
      }

      if(noObject)  //difusses und dings anderes Licht von punktlichtquellen
      {
        float ln = glm::dot(dirToLight, closestHit.m_normale);
        //glm::vec3 ln(dirToLight.x * closestHit.m_normale.x,
        //            dirToLight.y * closestHit.m_normale.y,
        //            dirToLight.y * closestHit.m_normale.z);

        glm::vec3 r = glm::normalize(glm::reflect(dirToLight, closestHit.m_normale));
        glm::vec3 v = glm::normalize(glm::vec3{-ray.m_direction.x, -ray.m_direction.y, -ray.m_direction.z});
        float rv = glm::dot(r, v);
        float rvm = std::pow(rv, (closestHit.m_shape ->get_material().m_m));

        Color diffuse = closestHit.m_shape -> getMaterial().m_kd;
        Color specular = closestHit.m_shape -> getMaterial().m_ks;
        color += (light -> m_color) * (diffuse * ln + specular * rvm);
      } //else: shadow
    }
    //if depth > 0 -> refelktion berechnen
    //rückgabe des berechneten
    //wenn kein hit: nur ambient zurückgeben
  }
  return color;
}
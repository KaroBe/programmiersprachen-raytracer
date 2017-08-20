//needed for testing
#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

//other stuff needed
#include <glm/vec3.hpp>
#include <cmath>
#include <iostream>

//include classes for testing

//Shapes
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "composite.hpp"

//DTOs
#include "material.hpp"
#include "color.hpp"
#include "ray.hpp"

//raytracing-related DTOs
#include "scene.hpp"
#include "hit.hpp"
#include "camera.hpp"
#include "light.hpp"

//the hard working classes
#include "sdfloader.hpp"
#include "renderer.hpp"


// ----------------------------------
// SHAPE TESTS
// ----------------------------------

//karos änderung

TEST_CASE("getter shape","[shape]")
{
    Sphere s {"name", Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f},glm::vec3{0.0f},1.0f};
    REQUIRE(s.get_name() == "name");

    Material c{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f};
    REQUIRE(s.get_material() == c); //added operator == in color.hpp
}

TEST_CASE("operator<< and print shape","[shape]")
{
    Sphere es {"empty_sphere"};
    std::cout << es;
    
    
    Sphere s {"name", Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f},glm::vec3{0.0f},1.0f};
    std::cout << s;
//trolololo
}

// ----------------------------------
// SPHERE TESTS
// ----------------------------------

TEST_CASE("constructors of sphere","[sphere]")
{
    Sphere s1 {"name"};
    Sphere s2 {"name",Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f},glm::vec3{0.0f}, 1.0f};

    REQUIRE(s1.get_center() == s2.get_center());
    REQUIRE(s1.get_radius() == s2.get_radius());
}

TEST_CASE("get_center and get_radius","[sphere]")
{
    Sphere s {"name",Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f},glm::vec3{0.0f}, 1.0f};

    REQUIRE(s.get_radius() == 1.0f);
    REQUIRE(s.get_center() == glm::vec3{0.0f});
}

TEST_CASE("area","[sphere]")
{
    Sphere s {"name",Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f},glm::vec3{0.0f}, 1.0f};
    REQUIRE(12.566f == Approx(s.area()).epsilon(0.001));
}

TEST_CASE("volume","[sphere]")
{
    Sphere s {"name",Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f},glm::vec3{0.0f}, 1.0f};
    REQUIRE(4.189 == Approx(s.volume()).epsilon(0.001));
}

TEST_CASE("print sphere","[sphere]")
{
    Sphere es {"empty_sphere"};
    std::cout << es;
    
    
    Sphere s {"name", Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f},glm::vec3{0.0f},1.0f};
    std::cout << s;
}

// ----------------------------------
// BOX TESTS
// ----------------------------------

TEST_CASE("constructors of box","[box]")
{
    Box b1 {"name"};
    Box b2 {"name",Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f},glm::vec3{0.0f}, glm::vec3{1.0f}};

    REQUIRE(b1.get_min() == b2.get_min());
    REQUIRE(b1.get_max() == b2.get_max());
}

TEST_CASE("get_min and get_max","[box]")
{
    Box b2 {"name",Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f},glm::vec3{0.0f}, glm::vec3{1.0f}};

    REQUIRE(b2.get_min() == glm::vec3{0.0f});
    REQUIRE(b2.get_max() == glm::vec3{1.0f});
}

TEST_CASE("area of box","[box]")
{
    Box b2 {"name",Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f},glm::vec3{0.0f}, glm::vec3{1.0f}};
    REQUIRE(6.0f == Approx(b2.area()).epsilon(0.001));
}

TEST_CASE("volume of box","[box]")
{
    Box b2 {"name", Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f}, glm::vec3{0.0f}, glm::vec3{1.0f}};

    REQUIRE(1.0f == Approx(b2.volume()).epsilon(0.001));
}

TEST_CASE("print box","[box]")
{
    Box eb {"empty_box"};
    std::cout << eb;
    
    
    Box b {"name", Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f}, glm::vec3{0.0f}, glm::vec3{1.0f}};
    std::cout << b;
}


// ----------------------------------
// AUFGABE 5.8 TEST
// ----------------------------------

TEST_CASE("virtual", "[Destructors]")
{

    std::cout << "\ntesting virtual and non-virtual construction and destruction\n";

    Color c_red {255.0f, 0.0f, 0.0f};
    Material red {"", c_red, c_red, c_red, 0.0f};

    glm::vec3 position {0.0f,0.0f,0.0f};

    std::cout << "Create s1\n";
    Sphere* s1 = new Sphere("sphere0",red,position,1.2f);
    std::cout << "Create s2\n";
    Shape* s2 = new Sphere("sphere1",red,position,1.2f);

    std::cout << "Printing objects: \n";
    std::cout << *s1;
    std::cout << *s2 << "\n";

    std::cout << "Delete s1\n";
    delete s1;
    std::cout << "Delete s2\n";
    delete s2;
}


// ----------------------------------
// MATERIAL Tests
// ----------------------------------

TEST_CASE("material in place of color struct", "Material")
{
    Color c{0.0f,0.0f,0.0f};
    Material mate1 {};
    std::cout << mate1;

    Material mate2 {"some material",c,c,c,0.0f};
    std::cout << mate2;
}


TEST_CASE("vektor normalization", "glm::vec3")
{
    glm::vec3 v {0.0f,0.0f,2.0f};
    glm::vec3 norm {0.0f};

    std::cout << "\n" << v.x << ", " << v.y
        << ", "  << v.z;
    
    norm = glm::normalize(v);

    std::cout << "\n" << norm.x << ", " << norm.y
        << ", "  << norm.z;
}

TEST_CASE("SDFloader test", "[SDFloader]")
{
    SDFloader loader{};
    /*
    load.sdfLoad("/Users/lissyscholz/Documents/
        programmiersprachen/raytracer/programmiers./prachen-
        raytracer/source/material_input.txt")""
    */
    //Scene s1 {};

    //std::string karo_file_path = "/home/karoline/Documents/studium/17_sose/programmiersprachen-aufgabenblatt-6/programmiersprachen-raytracer/source/material_input.txt";
    //s1 = loader.load(karo_file_path);
    /*
    Scene s2 {};
    std::string bla = "/bla";
    s2 = loader.load(bla);
    */
    loader.load("/home/lissy/Dokumente/raytracer/programmiersprachen-raytracer/source/simplescene");

}
//lissylissylissy <33333


//
// SDF LOADER TESTS
//

/*
TEST_CASE("SDFloader test", "[SDFloader]")
{
    std::cout << "\n\nSDF-LOADER TESTS\n**********************";

    SDFloader loader{};

    /*
    Lissy

    load.load("/Users/lissyscholz/Documents/
        programmiersprachen/raytracer/programmiers./prachen-
        raytracer/source/material_input.txt")
    */
    
    /*
    Karo
    */
    /*
    Scene s2 {};
    s2 = loader.load("/home/karoline/Documents/studium/17_sose/programmiersprachen/raytracer/programmiersprachen-raytracer/source/material_input.txt");
    
    for (std::shared_ptr<Shape> s : s2.m_shapes)
    {
        std::cout << *s;        
    }
    for (Material m : s2.m_materials)
    {
        std::cout << m;     
    }
    
}
*/
TEST_CASE("new intersect tests", "intersect")
{
    SECTION("sphere")
    {
        Color c {0.0f,0.0f,0.0f};

        Ray ray1 {glm::vec3{0.0f}, //from koordinatenursprung
                glm::vec3{1.0f,1.0f,-1.0f}}; //schräg in -z richtung

        Ray ray2 {glm::vec3{0.0f}, //aus koordinatenursprung
                glm::vec3{1.0f,1.0f,-2.0f}}; //schräg in anderem winkel in -z richtung

        Ray ray3 {glm::vec3{0.0f,0.0f,0.0f}, //von innerhalb der Box aus
                glm::vec3{0.0f,0.0f,-1.0f}}; // gerade in -z Richtung schauend

        Ray ray3b {glm::vec3{1.0f,1.0f,-2.0f}, //von innerhalb der Box aus
                glm::vec3{1.0f,1.0f,-1.0f}}; // schräg in -z Richtung schauend

        Ray ray4 {glm::vec3{0.0f}, //aus koordinatenursprung
                glm::vec3{0.0f,0.0f,-2.0f}}; //entlang -z Achse

        Ray ray4b {glm::vec3{1.0f,1.0f,0.0f}, //from (1|1|0)
                glm::vec3{0.0f,0.0f,-2.0f}}; //parallel -z Achse, gerade
       
        Sphere sphere{"testsphere", Material{"",c,c,c, 0.0f}, glm::vec3{0.0f, 0.0f, -2.0f}, 1.0f};

        std::cout << "ray 1: " << sphere.intersect(ray1) << std::endl;
        std::cout << "ray 2: " << sphere.intersect(ray2) << std::endl;
        std::cout << "ray 3: " << sphere.intersect(ray3) << std::endl;
        std::cout << "ray 3b: " << sphere.intersect(ray3b) << std::endl;
        std::cout << "ray 4: " << sphere.intersect(ray4) << std::endl;
        std::cout << "ray 4b: " << sphere.intersect(ray4b) << std::endl;
    }
    
    SECTION("box")
    {
        Color c {0.0f,0.0f,0.0f};

        Ray ray1 {glm::vec3{0.0f}, //from koordinatenursprung
                glm::vec3{1.0f,1.0f,-1.0f}}; //schräg in -z richtung

        Ray ray2 {glm::vec3{0.0f}, //aus koordinatenursprung
                glm::vec3{1.0f,1.0f,-2.0f}}; //schräg in anderem winkel in -z richtung

        Ray ray3 {glm::vec3{0.0f,0.0f,0.0f}, //von innerhalb der Box aus
                glm::vec3{2.0f,2.0f,-1.0f}}; // gerade in -z Richtung schauend

       Ray ray3b {glm::vec3{1.0f,1.0f,-2.0f}, //von innerhalb der Box aus
            glm::vec3{1.0f,1.0f,-1.0f}}; // schräg in -z Richtung schauend
            
        Ray ray4 {glm::vec3{0.0f}, //aus koordinatenursprung
                glm::vec3{0.0f,0.0f,-2.0f}}; //entlang -z Achse

        Ray ray4b {glm::vec3{1.0f,1.0f,0.0f}, //from (1|1|0)
                glm::vec3{0.0f,0.0f,-2.0f}}; //parallel -z Achse, gerade

        Box box {"test_box",
            Material{"",c,c,c, 0.0f},
            glm::vec3{0.0f,0.0f,-1.0f}, //min
            glm::vec3{2.0f,2.0f,-3.0f}};  //max

        std::cout << "ray 1: " << box.intersect(ray1) << std::endl;
        std::cout << "ray 2: " << box.intersect(ray2) << std::endl;
        std::cout << "ray 3: " << box.intersect(ray3) << std::endl;
        std::cout << "ray 3b: " << box.intersect(ray3b) << std::endl;
        std::cout << "ray 4: " << box.intersect(ray4) << std::endl;
        std::cout << "ray 4b: " << box.intersect(ray4b) << std::endl;
    }

    SECTION("composite")
    {
        Color c {0.0f,0.0f,0.0f};
        
        Ray ray1{glm::vec3(0.0f), glm::vec3(1.0f)}; //should meet sphere first
        Ray ray2{glm::vec3(9.0f), glm::vec3(-1.0f)};   //should meet box first
        Ray ray3{glm::vec3(0.0f), glm::vec3(-1.0f)};   //should meet nothing
        
        auto sphereptr = std::make_shared<Sphere>("testsphere", Material{"",c,c,c, 0.0f}, glm::vec3{2.0f}, 1.0f);
        auto boxptr = std::make_shared<Box>("testbox", Material{"",c,c,c, 0.0f}, glm::vec3{5.0f}, glm::vec3{8.0f});

        Composite composite{"testcomposite"};
        composite.add_shape(sphereptr);
        composite.add_shape(boxptr);

        std::cout << " \n~~ Composite Test ~~\n";
        
        std::cout << "ray 1: " << composite.intersect(ray1) << std::endl;
        std::cout << "ray 2: " << composite.intersect(ray2) << std::endl;
        std::cout << "ray 3: " << composite.intersect(ray3) << std::endl;

        std::cout << " \n~~ Composite Test Ende ~~\n";
    }
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}



// ----------------------------------
// TESTS FÜR DEN GANZEN NEUEN SHIT
// ----------------------------------


TEST_CASE("hit methods", "hit_struct")
{
    Hit default_hit;
    REQUIRE(default_hit.m_hit == false);
    REQUIRE(default_hit.m_distance == INFINITY);
    REQUIRE(default_hit.m_intersection == glm::vec3(INFINITY));
    REQUIRE(default_hit.m_shape == nullptr);
    
    auto s = std::make_shared<Box>("some_box");

    Hit no_hit(s);
    REQUIRE(no_hit.m_hit == false);
    REQUIRE(no_hit.m_distance == INFINITY);
    REQUIRE(no_hit.m_intersection == glm::vec3(INFINITY));
    REQUIRE(no_hit.m_shape == s);


    Hit hit(true,0.123f,glm::vec3{1.789f},s);
    REQUIRE(hit.m_hit == true);
    REQUIRE(hit.m_distance == 0.123f);
    REQUIRE(hit.m_intersection == glm::vec3(1.789f));
    REQUIRE(hit.m_shape == s);

    default_hit.m_shape = s;
    REQUIRE(default_hit == no_hit);

    Hit copy_hit = hit;
    REQUIRE(copy_hit == hit);
}

TEST_CASE("new color stuff", "color")
{
    Color c1(0.5f, 0.5f, 0.5f);
    Color c2(1.0f, 0.8f, 0.4f);
    Color c3(0.0f, 0.1f, 0.4f);
    Color result1(0.5f, 0.4f, 0.2f);
    Color result2(0.0f, 0.08f, 0.16f);

    REQUIRE((c1 * c2) == result1);
    c1 *= c2;
    REQUIRE(c1 == result1);
    /*
    REQUIRE((c2 * c3) == result2);
    c2 *= c3;
    REQUIRE(c2 == result2);*/
}


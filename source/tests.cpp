//needed for testing
#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

//other stuff needed
#include <glm/vec3.hpp>
#include <cmath>
#include <iostream>

//include classes for testing
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "material.hpp"
#include "color.hpp"

// ----------------------------------
// SHAPE TESTS
// ----------------------------------
//hallo ich heiße lissy tschüß
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
// AUFGABE 5.6 TEST
// ----------------------------------

TEST_CASE("intersectRaySphere", "[intersect]")
{
	//Ray
	glm::vec3 ray_origin{0.0f, 0.0f, 0.0f};
	//ray direction has to be normalized !
	//you can use:
		//v = glm::normalize(some_vector);
	glm::vec3 ray_direction{0.0f, 0.0f, 1.0f};

	//Sphere
	glm::vec3 sphere_center{0.0f, 0.0f, 5.0f};
	float sphere_radius{1.0f};

	float distance{0.0f};
	auto result = glm::intersectRaySphere(
		ray_origin, ray_direction,
		sphere_center,
		sphere_radius * sphere_radius,
		distance);

	REQUIRE(distance == Approx(4.0f));

	Sphere s {"some_sphere", Material{"",Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},Color{0.0f,0.0f,0.0f},0.0f},
		sphere_center, sphere_radius};

	Ray r {ray_origin,ray_direction};

	s.intersect(r,distance);

	REQUIRE(distance == Approx(4.0f));
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

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}

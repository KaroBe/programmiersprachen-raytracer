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
#include "color.hpp"

// ----------------------------------
// SHAPE TESTS
// ----------------------------------

TEST_CASE("getter shape","[shape]")
{
	Sphere s {"name", Color(0.0f,0.0f,0.0f),glm::vec3{0.0f},1.0f};
	REQUIRE(s.get_name() == "name");

	Color c{0.0f,0.0f,0.0f};
	REQUIRE(s.get_color() == c); //added operator == in color.hpp
}

TEST_CASE("operator<< and print shape","[shape]")
{
	Sphere es {"empty_sphere"};
	std::cout << es;
	
	
	Sphere s {"name", Color(0.0f,0.0f,0.0f),glm::vec3{0.0f},1.0f};
	std::cout << s;
}

// ----------------------------------
// SPHERE TESTS
// ----------------------------------

TEST_CASE("constructors of sphere","[sphere]")
{
	Sphere s1 {"name"};
	Sphere s2 {"name",Color{0.0f,0.0f,0.0f},glm::vec3{0.0f}, 1.0f};

	REQUIRE(s1.get_center() == s2.get_center());
	REQUIRE(s1.get_radius() == s2.get_radius());
}

TEST_CASE("get_center and get_radius","[sphere]")
{
	Sphere s {"name",Color{0.0f,0.0f,0.0f},glm::vec3{0.0f}, 1.0f};

	REQUIRE(s.get_radius() == 1.0f);
	REQUIRE(s.get_center() == glm::vec3{0.0f});
}

TEST_CASE("area","[sphere]")
{
	Sphere s {"name",Color{0.0f,0.0f,0.0f},glm::vec3{0.0f}, 1.0f};
	REQUIRE(12.566f == Approx(s.area()).epsilon(0.001));
}

TEST_CASE("volume","[sphere]")
{
	Sphere s {"name",Color{0.0f,0.0f,0.0f},glm::vec3{0.0f}, 1.0f};
	REQUIRE(4.189 == Approx(s.volume()).epsilon(0.001));
}

TEST_CASE("print sphere","[sphere]")
{
	Sphere es {"empty_sphere"};
	std::cout << es;
	
	
	Sphere s {"name", Color(0.0f,0.0f,0.0f),glm::vec3{0.0f},1.0f};
	std::cout << s;
}

// ----------------------------------
// BOX TESTS
// ----------------------------------

TEST_CASE("constructors of box","[box]")
{
	Box b1 {"name"};
	Box b2 {"name",Color{0.0f,0.0f,0.0f},glm::vec3{0.0f}, glm::vec3{1.0f}};

	REQUIRE(b1.get_min() == b2.get_min());
	REQUIRE(b1.get_max() == b2.get_max());
}

TEST_CASE("get_min and get_max","[box]")
{
	Box b2 {"name",Color{0.0f,0.0f,0.0f},glm::vec3{0.0f}, glm::vec3{1.0f}};

	REQUIRE(b2.get_min() == glm::vec3{0.0f});
	REQUIRE(b2.get_max() == glm::vec3{1.0f});
}

TEST_CASE("area of box","[box]")
{
	Box b2 {"name",Color{0.0f,0.0f,0.0f},glm::vec3{0.0f}, glm::vec3{1.0f}};
	REQUIRE(6.0f == Approx(b2.area()).epsilon(0.001));
}

TEST_CASE("volume of box","[box]")
{
	Box b2 {"name", Color{0.0f,0.0f,0.0f}, glm::vec3{0.0f}, glm::vec3{1.0f}};

	REQUIRE(1.0f == Approx(b2.volume()).epsilon(0.001));
}

TEST_CASE("print box","[box]")
{
	Box eb {"empty_box"};
	std::cout << eb;
	
	
	Box b {"name", Color{0.0f,0.0f,0.0f}, glm::vec3{0.0f}, glm::vec3{1.0f}};
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

	Sphere s {"some_sphere", Color{0.0f,0.0f,0.0f},
		sphere_center, sphere_radius};

	Ray r {ray_origin,ray_direction};

	s.intersect(r,distance);

	REQUIRE(distance == Approx(4.0f));
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}

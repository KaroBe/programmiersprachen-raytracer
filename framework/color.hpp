// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Color
// -----------------------------------------------------------------------------

#ifndef BUW_COLOR_HPP
#define BUW_COLOR_HPP

#include <iostream>

struct Color
{
  Color(): r(0.0f), g(0.0f), b(0.0f) {}

  Color(float red, float green, float blue) : r(red), g(green), b(blue) {}
  float r;
  float g;
  float b;

  friend std::ostream& operator<<(std::ostream& os, Color const& c)
  {
    os << "(" << c.r << ", " << c.g << ", " << c.b << ")\n";
    return os;
  }

  Color& operator+=(Color const& other)
  {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
  }

  Color& operator-=(Color const& other)
  {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
  }

  Color& operator*=(Color const& other)
  {
    r *= other.r;
    g *= other.g;
    b *= other.b;
    return *this;
  }

  Color operator*(Color const& other) const
  {
    Color newColor(r, g, b);
    newColor *= other;
    return newColor;
  }
  
  Color& operator*=(float other) //Fürs Skalarprodukt in givacolor!
  {
    r *= other;
    g *= other;
    b *= other;
    return *this;
  }

  bool operator==(Color const& other)
  {
    if(r==other.r and b==other.b and g==other.g)
      {
        return true;
      }
    else
      return false;
  }
/*
  bool operator<=(Color const& other)
  {
    if(r<=other.r and b<=other.b and g<=other.g)
      {
        return true;
      }
    else
      return false;
  }

  bool operator>=(Color const& other)
  {
    if(r>=other.r and b>=other.b and g>=other.g)
      {
        return true;
      }
    else
      return false;
  }
*/

  friend Color operator+(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp += b;
    return tmp;
  }

  friend Color operator-(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp -= b;
    return tmp;
  }

  friend Color operator*(Color const& a, float b)  //Fürs Skalarprodukt in givacolor!
  {
    auto tmp(a);
    tmp *= b;
    return tmp;
  }
};

#endif //#define BUW_COLOR_HPP

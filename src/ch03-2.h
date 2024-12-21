// 第3章：フライトウェイト

#include <iostream>

struct Mesh
{
};

struct Texture
{
};

static const Texture HILL_TEXTURE;
static const Texture RIVER_TEXTURE;
static const Texture GRASS_TEXTURE;

typedef std::pair<double, double> Vector;

struct Color
{
  Color(double r, double g, double b) : r(r), g(g), b(b) {}
  double r, g, b;
};
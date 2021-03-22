#include <iostream>
#include <vector>

#include "geometry.h"

void DemonstrateDynamicPolymorphismForLines() {
  const Point a(1, 3);
  const Point b(2, 4);
  const Point c(1, 5);

  BrokenLine first_line(std::vector<Point>({a, b, c}));
  CycledBrokenLine second_line(std::vector<Point>({a, b, c}));

  std::vector<BrokenLine*> lines = {
      &first_line, reinterpret_cast<BrokenLine*>(&second_line)};

  for (const auto& line : lines) {
    std::cout << line->CalculatePerimeter() << std::endl;
  }
}

void TestTriangleWithFourPoints() {
  const Point a(1, 3);
  const Point b(2, 4);
  const Point c(1, 5);
  std::vector<Point> points = {a, b, c, Point(3, 5)};
  Triangle triangle(points);
  std::cout << triangle.CalculatePerimeter() << std::endl;
}

void TestNotConvex() {
  const Point a(0, 0);
  const Point b(3, 0);
  const Point c(2, 1);
  const Point d(2, 2);

  std::vector<Point> points = {a, b, c, d};
  RegularPolygon polygon(points);
  std::cout << polygon.CalculateSquare() << std::endl;
}

void TestRegularPolygon() {
  const Point a(0, 0);
  const Point b(0, 1);
  const Point c(1, 1);
  const Point d(1, 0);

  std::vector<Point> points = {a, b, c, d};
  RegularPolygon polygon(points);
  std::cout << polygon.CalculateSquare() << std::endl;
}

void TestPolygon() {
  const Point a(1, 0);
  const Point b(0, 1);
  const Point c(-1, 0);
  const Point d(0, -1);

  std::vector<Point> points = {a, b, c, d};

  Polygon polygon(points);
  std::cout << polygon.CalculatePerimeter() << std::endl;
  std::cout << polygon.CalculateSquare() << std::endl;
}

void TestLine() {
  const Point a(1, 0);
  const Point b(0, 1);
  const Point c(-1, 0);
  const Point d(0, -1);

  std::vector<Point> points = {a, b, c, d};

  CycledBrokenLine broken_line(points);
  std::cout << broken_line.CalculatePerimeter() << std::endl;
  //  std::cout << broken_line.BrokenLine::CalculatePerimeter() << std::endl;
}

void TestTrapezoid() {
  const Point a(0, 0);
  const Point b(3, 0);
  const Point c(2, 2);
  const Point d(1, 2);

  std::vector<Point> points = {a, b, c, d};

  Trapezoid trapezoid(points);
  std::cout << trapezoid.CalculatePerimeter() << std::endl;
  std::cout << trapezoid.CalculateSquare() << std::endl;
}

void DemonstrateDynamicPolymorphismForShapes() {
  Trapezoid trapezoid(
      std::vector<Point>({Point(0, 0), Point(3, 0), Point(2, 2), Point(1, 2)}));
  Triangle triangle(
      std::vector<Point>({Point(1, 3), Point(2, 4), Point(1, 5)}));

  RegularPolygon regular_polygon(std::vector<Point>(
      {Point(1, 0), Point(0, 1), Point(-1, 0), Point(0, -1)}));

  std::vector<Polygon*> shapes = {reinterpret_cast<Polygon*>(&trapezoid),
                                  reinterpret_cast<Polygon*>(&triangle),
                                  reinterpret_cast<Polygon*>(&regular_polygon)};

  for (const auto& shape : shapes) {
    std::cout << "Square = " << shape->CalculateSquare() << " "
              << "Perimeter = " << shape->CalculatePerimeter() << std::endl;
  }
}

void TestCopyAssign() {
  BrokenLine line1(std::vector<Point>({Point(1, 3), Point(2, 4), Point(1, 5)}));

  BrokenLine line2(std::vector<Point>({Point(0, 0), Point(1, 0), Point(0, 1)}));
  std::cout << line1.CalculatePerimeter() << std::endl;
  line1 = line2;
  std::cout << line1.CalculatePerimeter() << std::endl;
  BrokenLine another_one(line1);
  std::cout << another_one.CalculatePerimeter() << std::endl;
}

int main() {
  try {
    TestCopyAssign();
  } catch (std::runtime_error& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}

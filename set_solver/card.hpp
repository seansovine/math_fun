#include <iostream>
#include <vector>

/* Putting definitions here for now, since small program. */

enum class Color { red, green, blue };
enum class Number { one, two, three };
enum class Shading { filled, outlined, striped };
enum class Shape { diamond, oval, squiggle };

// For iterating over all options in various places. (Consider alternatives.)
std::vector<Color> colors = {Color::red, Color::green, Color::blue};
std::vector<Number> numbers = {Number::one, Number::two, Number::three};
std::vector<Shading> shadings = {Shading::filled, Shading::outlined, Shading::striped};
std::vector<Shape> shapes = {Shape::diamond, Shape::oval, Shape::squiggle};

struct Card {
  Color color;
  Number number;
  Shading shading;
  Shape shape;

  Card(Color c, Number n, Shading shad, Shape shap)
      : color{c}, number{n}, shading{shad}, shape{shap} {}
};

std::ostream &operator<<(std::ostream &os, const Card &card) {
  os << "[ ";
  switch (card.color) {
  case Color::red:
    os << "R";
    break;
  case Color::green:
    os << "G";
    break;
  case Color::blue:
    os << "B";
    break;
  }
  switch (card.number) {
  case Number::one:
    os << "1";
    break;
  case Number::two:
    os << "2";
    break;
  case Number::three:
    os << "3";
    break;
  }
  switch (card.shading) {
  case Shading::filled:
    os << "F";
    break;
  case Shading::outlined:
    os << "O";
    break;
  case Shading::striped:
    os << "S";
    break;
  }
  switch (card.shape) {
  case Shape::diamond:
    os << "D";
    break;
  case Shape::oval:
    os << "O";
    break;
  case Shape::squiggle:
    os << "S";
    break;
  }
  os << " ]";
  return os;
}

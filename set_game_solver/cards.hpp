#include <iostream>
#include <vector>

/* Definitions and data structures. */

enum class Color { red, green, blue };
enum class Number { one, two, three };
enum class Shading { filled, outlined, striped };
enum class Shape { diamond, oval, squiggle };

struct Attributes {
  const static std::array<Color, 3> colors;
  const static std::array<Number, 3> numbers;
  const static std::array<Shading, 3> shadings;
  const static std::array<Shape, 3> shapes;
};

const std::array<Color, 3> Attributes::colors{Color::red, Color::green, Color::blue};
const std::array<Number, 3> Attributes::numbers{Number::one, Number::two, Number::three};
const std::array<Shading, 3> Attributes::shadings{Shading::filled, Shading::outlined, Shading::striped};
const std::array<Shape, 3> Attributes::shapes{Shape::diamond, Shape::oval, Shape::squiggle};

struct Card {
  Color color;
  Number number;
  Shading shading;
  Shape shape;

  Card(Color c, Number n, Shading shad, Shape shap) : color{c}, number{n}, shading{shad}, shape{shap} {}
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

struct Candidate {
  std::array<Card, 3> cards;

  Candidate(const Card &first, const Card &second, const Card &third) : cards{first, second, third} {}

  const Card &operator[](const int i) const { return cards[i]; }
};

using Cards = std::vector<Card>;
using Candidates = std::vector<Candidate>;

struct Results {
  int redCandidates;
  int greenCandidates;
  int blueCandidates;
  int distinctCandidates;
  Candidates sets;

  void setColorCandidates(Color color, int number) {
    switch (color) {
    case Color::red:
      redCandidates = number;
    case Color::green:
      greenCandidates = number;
    case Color::blue:
      blueCandidates = number;
    }
  }
};

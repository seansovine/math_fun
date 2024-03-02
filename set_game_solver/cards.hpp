#ifndef CARDS_H
#define CARDS_H

#include <array>
#include <iostream>
#include <vector>

/* Definitions and data structures. */

enum class Color { red, green, blue };
enum class Number { one, two, three };
enum class Shading { filled, outlined, striped };
enum class Shape { diamond, oval, squiggle };

struct Attributes {
  constexpr static std::array<Color, 3> colors = {Color::red, Color::green, Color::blue};
  constexpr static std::array<Number, 3> numbers = {Number::one, Number::two, Number::three};
  constexpr static std::array<Shading, 3> shadings = {Shading::filled, Shading::outlined, Shading::striped};
  constexpr static std::array<Shape, 3> shapes = {Shape::diamond, Shape::oval, Shape::squiggle};
};

struct Card {
  Color color;
  Number number;
  Shading shading;
  Shape shape;

  Card(Color c, Number n, Shading shad, Shape shap) : color{c}, number{n}, shading{shad}, shape{shap} {}
};

std::ostream &operator<<(std::ostream &os, const Card &card);

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

#endif // Header include guards

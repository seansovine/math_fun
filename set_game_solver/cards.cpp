#include "cards.hpp"

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

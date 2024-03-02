#include "cards.hpp"

#if __linux__
  #define R_SYM "\e[1;31mR\e[0m"
  #define G_SYM "\e[1;32mG\e[0m"
  #define B_SYM "\e[1;34mB\e[0m"
#else
  #define R_SYM "R"
  #define G_SYM "G"
  #define B_SYM "B"
#endif

std::ostream &operator<<(std::ostream &os, const Card &card) {
  os << "[ ";
  switch (card.color) {
  case Color::red:
    os << R_SYM;
    break;
  case Color::green:
    os << G_SYM;
    break;
  case Color::blue:
    os << B_SYM;
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

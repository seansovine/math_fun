#ifndef GAME_H
#define GAME_H

#include "cards.hpp"
#include "output.hpp"

/* Game setup. */

class ShuffledDeckBuilder {

public:
  ShuffledDeckBuilder() {
    generate();
    shuffle();
  }

  const Cards getDeck() const && { return deck; }

  Cards dealCards(unsigned num);

private:
  void generate();

  void shuffle();

private:
  Cards deck;
};

/* Game logic. */

class SetFinder {

public:
  SetFinder(Cards &&inTable);

  const Results find() &&;

private:
  void setup();

private:
  Cards table;
  Results results;
  std::array<Candidates, 3> candsByColor;
  Candidates colorDistinctCands;
};

#endif

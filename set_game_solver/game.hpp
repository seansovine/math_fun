#ifndef GAME_H
#define GAME_H

#include "cards.hpp"

/* Game setup. */

class ShuffledDeckBuilder {

public:
  ShuffledDeckBuilder() {
    generate();
    shuffle();
  }

  const Cards getDeck() const { return deck; }

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

  Results find();

private:
  void setup();

private:
  Cards table;
  Results results;
  std::array<Candidates, 3> candsByColor;
  Candidates colorDistinctCands;
};

#endif

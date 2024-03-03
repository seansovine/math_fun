#ifndef GAME_H
#define GAME_H

#include "cards.hpp"
#include "output.hpp"

/* Game setup. */

class ShuffledDeckBuilder {

public:
  ShuffledDeckBuilder();

  Cards getDeck() const { return deck; }

  size_t cardsInDeck() const { return size(deck); }

  Cards dealCards(unsigned num);

private:
  void generate();

  void shuffle();

private:
  Cards deck;
};

/* Game logic. */

/**
 *  Usage: Results results = SetFinder(std::move(table)).find();
 *
 *  Consumes table, finds sets, and moves results back out to caller.
 */

class SetFinder {

public:
  SetFinder(Cards &&inTable);

  Results &&find() &&;

private:
  void setup();

private:
  Cards table;
  Results results;
  std::array<Candidates, 3> candsByColor;
  Candidates colorDistinctCands;
};

#endif // Header include guard

#include "game.hpp"

/* Run set game solver. */

int main() {
  static const size_t CARDS_ON_TABLE = 15;
  static_assert(CARDS_ON_TABLE <= 3 * 3 * 3 * 3);

  std::cout << std::endl << "Generating and shuffling deck." << std::endl;
  auto deckBuilder = ShuffledDeckBuilder();

  Cards table = deckBuilder.dealCards(CARDS_ON_TABLE);
  std::cout << outputForSetup(table);

  std::cout << std::endl << "Finding sets:" << std::endl << std::endl;
  Results results = SetFinder(std::move(table)).find();
  std::cout << outputForResults(results);
}

// Linux build and run: clear && ./set -r

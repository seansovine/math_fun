#include "game.hpp"

/* Run set game solver. */

static constexpr size_t CARDS_ON_TABLE = 15;

int main() {
  std::cout << std::endl << "Generating and shuffling deck." << std::endl << std::endl;
  Cards table = ShuffledDeckBuilder{}.dealCards(CARDS_ON_TABLE);

  std::cout << outputTable(table);

  std::cout << std::endl << "Finding sets:" << std::endl << std::endl;
  Results results = SetFinder(std::move(table)).find();

  std::cout << outputForResults(results);
}

static_assert(CARDS_ON_TABLE <= 3 * 3 * 3 * 3);

// Linux build and run: clear && ./set -r

#include "game.hpp"

/* Output. */

void printTable(const Cards &table) {
  std::cout << "Cards on table:" << std::endl << std::endl;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      std::cout << table[j + 3 * i] << " ";
    }
    std::cout << std::endl;
  }
}

void printResults(const Results &results) {
  std::cout << " -- Generated " << results.redCandidates << " red candidates." << std::endl
            << "              " << results.greenCandidates << " green candidates." << std::endl
            << "              " << results.blueCandidates << " blue candidates." << std::endl
            << "              " << results.distinctCandidates << " color-distinct candidates." << std::endl;

  if (results.sets.size() == 0) {
    std::cout << std::endl << "No sets found!" << std::endl;
  } else {
    std::cout << std::endl << "" << results.sets.size() << " sets found! They are:" << std::endl << std::endl;
  }
  for (Candidate cand : results.sets) {
    for (Card card : cand.cards) {
      std::cout << card << " ";
    }
    std::cout << std::endl;
  }
}

/* Main. */

int main() {
  std::cout << std::endl << "Generating and shuffling deck." << std::endl;
  Cards deck = generateDeck();
  shuffle(deck);

  Cards table{deck.begin(), deck.begin() + 12};
  printTable(table);

  std::cout << std::endl << "Finding sets:" << std::endl << std::endl;
  Results sets = findSets(table);
  printResults(sets);
}

// c && g++ find_sets.cpp -o build/find_sets && echo "---" && ./build/find_sets && echo

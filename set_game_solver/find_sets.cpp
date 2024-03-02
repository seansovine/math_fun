#include <sstream>

#include "game.hpp"

/* Output. */

std::string outputForSetup(const Cards &table) {
  std::ostringstream buffer{};
  buffer << "Cards on table:" << std::endl << std::endl;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      buffer << table[j + 3 * i] << " ";
    }
    buffer << std::endl;
  }

  return buffer.str();
}

std::string outputForResults(const Results &results) {
  std::ostringstream buffer{};
  buffer << " -- Generated " << results.redCandidates << " red candidates." << std::endl
         << "              " << results.greenCandidates << " green candidates." << std::endl
         << "              " << results.blueCandidates << " blue candidates." << std::endl
         << "              " << results.distinctCandidates << " color-distinct candidates." << std::endl;

  if (results.sets.size() == 0) {
    buffer << std::endl << "No sets found!" << std::endl;
  } else {
    buffer << std::endl << "" << results.sets.size() << " sets found! They are:" << std::endl << std::endl;
  }
  for (Candidate cand : results.sets) {
    for (Card card : cand.cards) {
      buffer << card << " ";
    }
    buffer << std::endl;
  }

  return buffer.str();
}

/* Main. */

int main() {
  std::cout << std::endl << "Generating and shuffling deck." << std::endl;
  auto deckBuilder = ShuffledDeckBuilder();

  Cards table = deckBuilder.dealCards(12);
  std::cout << outputForSetup(table);

  std::cout << std::endl << "Finding sets:" << std::endl << std::endl;
  Results results = SetFinder(std::move(table)).find();
  std::cout << outputForResults(results);
}

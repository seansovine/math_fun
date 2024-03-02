#include <sstream>

#include "output.hpp"

/* Output function definitions. */

std::string outputForSetup(const Cards &table) {
  std::ostringstream buffer{};
  static const int TABLE_WIDTH = 4;

  int tableSize = size(table);
  int numRows = tableSize / TABLE_WIDTH + (tableSize % TABLE_WIDTH != 0);

  buffer << "Cards on table:" << std::endl << std::endl;
  for (int i = 0; i < numRows; i++) {
    for (int j = i * TABLE_WIDTH; j < (i + 1) * TABLE_WIDTH && j < tableSize; j++) {
      buffer << table[j] << " ";
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
	buffer << "-> ";
    for (Card card : cand.cards) {
      buffer << card << " ";
    }
    buffer << std::endl;
  }

  return buffer.str();
}

#include <sstream>

#include "output.hpp"

/* Output function definitions. */

static constexpr int TABLE_WIDTH = 4;

std::string printTableCards_(const Cards &table) {
  std::ostringstream buffer{};

  int tableSize = size(table);
  int numRows = tableSize / TABLE_WIDTH + (tableSize % TABLE_WIDTH != 0);

  for (int i = 0; i < numRows; i++) {
    for (int j = i * TABLE_WIDTH; j < (i + 1) * TABLE_WIDTH && j < tableSize; j++) {
      buffer << table[j] << " ";
    }
    buffer << std::endl;
  }

  return buffer.str();
}

std::string outputTable(const Cards &table) {
  std::ostringstream buffer{};

  buffer << "Cards on table:" << std::endl << std::endl;
  buffer << printTableCards_(table);

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

  buffer << std::endl << "Cards not part of any set:" << std::endl << std::endl;
  buffer << printTableCards_(results.remaining);

  return buffer.str();
}

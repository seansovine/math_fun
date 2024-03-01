#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <set>
#include <vector>

// Defines Card struct and Color, Number, Shading, Shape enums,
// and Attributes class w/ vectors for iteration.
#include "card.hpp"

/* functions */

using Cards = std::vector<Card>;
using Candidates = std::vector<Candidate>;

Cards generateDeck() {
  Cards deck;
  for (Color color : Attributes::colors) {
    for (Number number : Attributes::numbers) {
      for (Shading shading : Attributes::shadings) {
        for (Shape shape : Attributes::shapes) {
          deck.emplace_back(color, number, shading, shape);
        }
      }
    }
  }

  return deck;
}

void shuffle(Cards &deck) {
  std::random_device rd;
  std::mt19937 rng(rd());

  for (int i = deck.size() - 1; i >= 0; i--) {
    std::uniform_int_distribution<> distrib(0, i);
    int j = distrib(rng);
    Card temp = deck[i];
    deck[i] = deck[j];
    deck[j] = temp;
  }
}

Candidates getColorHomogCands(const Cards &colorCards) {
  Candidates colorCand{};
  if (colorCards.size() < 3) {
    return colorCand;
  }

  for (int i = 0; i < colorCards.size() - 2; i++) {
    for (int j = i + 1; j < colorCards.size() - 1; j++) {
      for (int k = j + 1; k < colorCards.size(); k++) {
        colorCand.emplace_back(colorCards[i], colorCards[j], colorCards[k]);
      }
    }
  }

  return colorCand;
}

Candidates getColorDistinctCands(const std::array<Cards, 3> &cardsByColor) {
  Candidates cands;
  for (Card card1 : cardsByColor[0]) {
    for (Card card2 : cardsByColor[1]) {
      for (Card card3 : cardsByColor[2]) {
        cands.emplace_back(card1, card2, card3);
      }
    }
  }

  return cands;
}

struct SameOrDiffChecker {
  bool operator()(const Candidate &cand) {
    if (!(cand[0].number == cand[1].number && cand[0].number == cand[2].number) &&
        !(cand[0].number != cand[1].number && cand[1].number != cand[2].number &&
          cand[0].number != cand[2].number)) {
      return false;
    }
    if (!(cand[0].shading == cand[1].shading && cand[0].shading == cand[2].shading) &&
        !(cand[0].shading != cand[1].shading && cand[1].shading != cand[2].shading &&
          cand[0].shading != cand[2].shading)) {
      return false;
    }
    if (!(cand[0].shape == cand[1].shape && cand[0].shape == cand[2].shape) &&
        !(cand[0].shape != cand[1].shape && cand[1].shape != cand[2].shape &&
          cand[0].shape != cand[2].shape)) {
      return false;
    }

    return true;
  }
};

Candidates findSets(const Cards &table) {
  SameOrDiffChecker sameOrDiff;

  Candidates sets{};
  std::array<Cards, 3> cardsByColor;

  // Generate color-homogeneous candidates.
  int i = 0;
  for (Color color : Attributes::colors) {
    // Collect cards with this color.
    Cards colorCards{};
    std::copy_if(table.begin(), table.end(), std::back_inserter(colorCards),
                 [color](const Card &card) { return card.color == color; });
    cardsByColor[i++] = colorCards;

    // Build and check candidate sets for this color.
    Candidates colorCands = getColorHomogCands(colorCards);
    std::cout << " -- Generated " << colorCands.size() << " homogeneous candidates." << std::endl;
    std::copy_if(colorCands.begin(), colorCands.end(), std::back_inserter(sets), sameOrDiff);
  }

  // Build and check color-distinct candidates.
  Candidates colorDistinctCands = getColorDistinctCands(cardsByColor);
  std::cout << " -- Generated " << colorDistinctCands.size() << " distinct candidates."
            << std::endl;
  std::copy_if(colorDistinctCands.begin(), colorDistinctCands.end(), std::back_inserter(sets),
               sameOrDiff);

  return sets;
}

/* main */

int main() {
  Cards deck = generateDeck();

  shuffle(deck);
  Cards table{deck.begin(), deck.begin() + 12};

  // Print cards on table.
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      std::cout << table[j + 3 * i] << " ";
    }
    std::cout << std::endl;
  }

  std::cout << std::endl << "Generating sets:" << std::endl;
  auto sets = findSets(table);

  // Print sets found, if any.
  if (sets.size() == 0) {
    std::cout << std::endl << "No sets found!" << std::endl;
  } else {
    std::cout << std::endl << "" << sets.size() << " sets found! They are:" << std::endl;
  }
  for (Candidate cand : sets) {
    for (Card card : cand.cards) {
      std::cout << card << " ";
    }
    std::cout << std::endl;
  }
}

// g++ find_sets.cpp -o build/find_sets && echo "---" && ./build/find_sets

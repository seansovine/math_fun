#include <array>
#include <chrono>
#include <iostream>
#include <random>
#include <set>
#include <vector>

// Defines Card struct and Color, Number, Shading, Shape enums,
// and colors, numbers, shadings, and shapes vectors.
#include "card.hpp"

std::vector<Card> generateDeck() {
  std::vector<Card> deck;
  for (Color color : colors) {
    for (Number number : numbers) {
      for (Shading shading : shadings) {
        for (Shape shape : shapes) {
          deck.emplace_back(color, number, shading, shape);
        }
      }
    }
  }

  return deck;
}

void shuffle(std::vector<Card> &deck) {
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

struct Candidate {
  std::array<Card, 3> cards;

  Candidate(const Card &first, const Card &second, const Card &third)
      : cards{first, second, third} {}
};

std::vector<Candidate> getColorHomogCand(const std::vector<Card> &colorCards) {
  std::vector<Candidate> colorCand{};
  for (int i = 0; i < colorCards.size() - 2; i++) {
    for (int j = i + 1; j < colorCards.size() - 1; j++) {
      for (int k = j + 1; k < colorCards.size(); k++) {
        colorCand.emplace_back(colorCards[i], colorCards[j], colorCards[k]);
      }
    }
  }
  return colorCand;
}

std::vector<Candidate> findSets(const std::vector<Card> &table) {
  auto sameOrDiffNumber = [](const std::array<Card, 3> &cand) -> bool {
    return (cand[0].number == cand[1].number && cand[0].number == cand[2].number) ||
           cand[0].number != cand[1].number && cand[1].number != cand[2].number &&
               cand[0].number != cand[2].number;
  };
  auto sameOrDiffShading = [](const std::array<Card, 3> &cand) -> bool {
    return (cand[0].shading == cand[1].shading && cand[0].shading == cand[2].shading) ||
           cand[0].shading != cand[1].shading && cand[1].shading != cand[2].shading &&
               cand[0].shading != cand[2].shading;
  };
  auto sameOrDiffShape = [](const std::array<Card, 3> &cand) -> bool {
    return (cand[0].shape == cand[1].shape && cand[0].shape == cand[2].shape) ||
           cand[0].shape != cand[1].shape && cand[1].shape != cand[2].shape &&
               cand[0].shape != cand[2].shape;
  };

  std::vector<Candidate> sets{};

  // Generate color-homogeneous candidates.
  for (Color color : colors) {
    std::vector<Card> colorCards{};
    // Collect cards with this color.
    for (Card card : table) {
      if (card.color == color) {
        colorCards.push_back(card);
      }
    }
    // Build and check candidate sets for this color.
    std::vector<Candidate> colorCands = getColorHomogCand(colorCards);
    for (Candidate cand : colorCands) {
      if (sameOrDiffNumber(cand.cards) && sameOrDiffShading(cand.cards) &&
          sameOrDiffShape(cand.cards)) {
        sets.push_back(cand);
      }
    }
  }

  // Now generate and check color-distinct candidates.
  // ...

  // First generate candidates based on color, then
  // check each for validity based on remaining traits.
  return sets;
}

int main() {
  std::vector<Card> deck = generateDeck();

  shuffle(deck);
  std::vector<Card> table{deck.begin(), deck.begin() + 12};

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      std::cout << table[j + 3 * i] << " ";
    }
    std::cout << std::endl;
  }

  std::cout << std::endl << "Generating sets:" << std::endl;
}

// g++ find_sets.cpp -o build/find_sets && echo "---" && ./build/find_sets

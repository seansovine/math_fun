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
  std::array<Card, 3> cards{};
};

std::vector<Candidate> findSets(const std::vector<Card> &table) {
  auto sameOrDiffNumber = [](const std::array<Card, 3> &cand) -> bool {
    return (cand[0].number == cand[1].number && cand[0].number == cand[2].number) ||
           cand[0].number != cand[1].number && cand[1].number != cand[2].number &&
               cand[0].number != cand[2].number;
  };

  std::vector<Candidate> sets{};
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

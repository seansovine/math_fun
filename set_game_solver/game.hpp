#ifndef GAME_H
#define GAME_H

#include <array>
#include <random>
#include <ranges>

#include "cards.hpp"

/* Game logic. */

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

Results findSets(const Cards &table) {
  using namespace std::views;

  Results results;
  SameOrDiffChecker sameOrDiff;
  std::array<Cards, 3> cardsByColor;

  int i = 0;
  for (Color color : Attributes::colors) {
    auto colorView = filter(table, [color](const Card &card) { return card.color == color; });
    Cards colorCards{begin(colorView), end(colorView)};

    // Generate and check color-homogeneous candidates.
    Candidates colorCands = getColorHomogCands(colorCards);
    results.setColorCandidates(color, colorCands.size());

    auto setsView = filter(colorCands, sameOrDiff);
    results.sets.insert(end(results.sets), begin(setsView), end(setsView));

    cardsByColor[i++] = std::move(colorCards);
  }

  // Generate and check color-distinct candidates.
  Candidates colorDistinctCands = getColorDistinctCands(cardsByColor);
  results.distinctCandidates = colorDistinctCands.size();

  auto setsView = filter(colorDistinctCands, sameOrDiff);
  results.sets.insert(end(results.sets), begin(setsView), end(setsView));

  return results;
}

#endif // Header include guard

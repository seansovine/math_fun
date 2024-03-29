#include <memory>
#include <random>
#include <ranges>
#include <stdexcept>

#include "game.hpp"

/* ShuffledDeckBuilder members functions. */

ShuffledDeckBuilder::ShuffledDeckBuilder() {
  generate();
  shuffle();
}

void ShuffledDeckBuilder::generate() {
  deck.reserve(3 * 3 * 3 * 3);
  for (Color color : Attributes::colors) {
    for (Number number : Attributes::numbers) {
      for (Shading shading : Attributes::shadings) {
        for (Shape shape : Attributes::shapes) {
          deck.emplace_back(color, number, shading, shape);
        }
      }
    }
  }
}

void ShuffledDeckBuilder::shuffle() {
  std::random_device rd;
  std::mt19937 rng(rd());

  for (int i = deck.size() - 1; i >= 0; i--) {
    std::uniform_int_distribution<> distrib(0, i);
    int j = distrib(rng);
    std::swap(deck[i], deck[j]);
  }
}

Cards ShuffledDeckBuilder::dealCards(unsigned num) {
  if (num > size(deck)) {
    throw new std::out_of_range("Number of cards requested is greater than number currently in deck.");
  }

  Cards dealt{begin(deck), begin(deck) + num};
  deck.erase(begin(deck), begin(deck) + num);

  for (size_t i = 0; i < size(dealt); i++) {
    dealt[i].tablePosition = i;
  }

  return dealt;
}

/* SetFinder member and helper functions. */

Candidates getColorHomogCands(const Cards &colorCards) {
  Candidates colorCand{};
  if (colorCards.size() < 3) {
    return colorCand;
  }

  for (size_t i = 0; i < colorCards.size() - 2; i++) {
    for (size_t j = i + 1; j < colorCards.size() - 1; j++) {
      for (size_t k = j + 1; k < colorCards.size(); k++) {
        colorCand.emplace_back(colorCards[i], colorCards[j], colorCards[k]);
      }
    }
  }

  return colorCand;
}

Candidates getColorDistinctCands(const CardsByColor &cardsByColor) {
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

SetFinder::SetFinder(Cards &&inTable) : table{inTable}, results{} { setup(); }

Results &&SetFinder::find() && {
  using namespace std::views;
  SameOrDiffChecker sameOrDiff;

  for (const auto &colorCands : candsByColor) {
    auto setsView = filter(colorCands, sameOrDiff);
    results.sets.insert(end(results.sets), begin(setsView), end(setsView));
  }

  auto setsView = filter(colorDistinctCands, sameOrDiff);
  results.sets.insert(end(results.sets), begin(setsView), end(setsView));

  for (Candidate set : results.sets) {
    for (Card card : set.cards) {
      table[card.tablePosition.value()].tablePosition = std::nullopt;
    }
  }

  auto remainingView = filter(table, [](const Card &card) -> bool { return card.tablePosition.has_value(); });
  results.setRemaining(remainingView);

  return std::move(results);
}

void SetFinder::setup() {
  using namespace std::views;

  int i = 0;
  CardsByColor cardsByColor;

  for (Color color : Attributes::colors) {
    auto colorView = filter(table, [color](const Card &card) { return card.color == color; });
    Cards colorCards{begin(colorView), end(colorView)};

    candsByColor[i] = getColorHomogCands(colorCards);
    results.setColorCandidates(color, size(candsByColor[i]));

    cardsByColor[i++] = std::move(colorCards);
  }

  colorDistinctCands = getColorDistinctCands(cardsByColor);
  results.distinctCandidates = size(colorDistinctCands);
}

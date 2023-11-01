# Set Game Solver

This program is a solver for the game Set.
If you aren't familiar with it, in Set there is a deck
of cards, and each card varies along four dimensions:
color, number, shape, and texture. For example, a card
could have 3 red solid diamonds on it.

Color of objects:

- red
- green
- blue

Number of objects:

- one
- two
- three

Shading of objects:

- filled
- outlined
- striped

Shape of objects:

- diamond
- oval
- squiggle

At the start of gameplay 12 cards are laid face-up on the table.
Players score points by forming _sets_ from the visible cards.
In Set, a _set_, is a collection of the cards that are either
all the same or all different in each dimensions.
So, for example, the cards in a set might all have the same shape,
all have different colors, all have different textures, and
all have the same number of objects.

## This program:

Randomly draws 12 cards from the Set deck, and then finds all
_sets_ (by the game's definition) contained in those 12 cards.

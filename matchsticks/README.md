# Matchstick Triangles

This little project is inspired by problem #60 "Matchstick Squares"
from the book _Ingenious Mathematical Problems & Methods_, which is
a collection of puzzles submitted by applied mathematicians to the
column _The Graham Dial_.

The idea is that you have a box of identical matchsticks, and
you first use them to construct a square. Then the challenge is to
find the fewest number of matches required to construct a
triangle on each face of the square, such that no two triangles
are congruent.

I didn't have anything at hand that would serve as identical
matchsticks, so I thought it could be fun to try to animate the
problem setup with Python and Matplotlib. Here's the animation
I came up with:

<p align="center" style="margin: 3em;">
	<img src="matchsticks.gif" width="500" height="459">
</p>

The independent variable here is the angle $\theta$ between the left
side of the square and the matchstick that is attached to the upper
left corner. All the other matchstick positions are determined
by that angle and the requirements that they touch end to end
and each touch one corner of the square.

**Angle of symmetry:**

I was curious about the angle $\theta$ that makes the diagram
symmetrical. We can work out that $\theta$ should satisfy

$$\frac{1}{2} = (1 - 2\sin(\theta / 2))\cdot \cos(\theta / 2) = \cos(\theta / 2) - \sin(\theta).$$

I didn't see an immediate way to solve the equation using trig identities,
so I made a small program `find_angle.py` to solve it
numerically using SciPy's `fsolve`. This produced the number

$$0.155816897844861 \cdot \pi,$$

which can verified with the graphing program.

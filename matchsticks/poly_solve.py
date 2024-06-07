import numpy as np

from sympy import nroots, trigsimp, cos, sin
from sympy.abc import x

## Find roots of polynomial numerically.

poly = 4 * (1 - 2 * x) ** 2 * (1 - x**2) - 1

# solns = solve(poly, quartics=False)
roots = nroots(poly)
print(f"Roots of {poly} are:\n")
for root in roots:
    print(f"\t{root}\n")

## Try using simpy's arcsine function.
# print()
# theta = 2 * asin(solns[1])
# print(theta)

## Attempt to simplify trigonometric expression.
# trig_expr = cos(x / 2) - sin(x)
# print(trigsimp(trig_expr))

## Compute with Numpy's arcsine function.

root_1 = float(roots[1])
theta = 2 * np.arcsin(root_1)
pi_mult = theta / np.pi

print(f"Approximate theta is: {pi_mult} x pi.")

"""Find the angle when the matchsticks are symmetrical.

The equation to be solved is:

  1/2 = cos(theta / 2) - sin(theta).

And we verified with matchsticks.py that the answer we
get by solving this with a root finder seems to be correct.
"""

import numpy as np
import scipy.optimize as opt


def f(theta):
    """Need a zero of this."""
    return -1 / 2 + np.cos(theta / 2.0) - np.sin(theta)


root = opt.fsolve(f, 1)
pi_mult = root / np.pi
# Returns 0.1558169 x Pi.

print(f"Found root at: {pi_mult[0]:.16f} x pi.")

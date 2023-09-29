"""Modeling the matchstick problem with Python.

All lines (matchsticks) have length 1.
"""

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as ptch
import matplotlib.animation as anim

# Symmetric at ~ 0.155816897844861 * pi.
THETA_INIT = np.pi / 3.0
THETA_FINAL = 0.001

CANVAS_WIDTH = 2.0

## Setup the plot.

fig = plt.figure()
ax = plt.axes(
    xlim=(-CANVAS_WIDTH, CANVAS_WIDTH),
    ylim=(-CANVAS_WIDTH, CANVAS_WIDTH),
)

square = ptch.Rectangle(
    (-1 / 2, -1 / 2), 1, 1, linewidth=1, edgecolor="red", facecolor="none"
)
ax.add_patch(square)

outer_lines = []
for i in range(4):
    (line,) = ax.plot([], [], "black", lw=1)
    outer_lines.append(line)


## For plotting matchstick lines.


def dist(r):
    """Distance from r to origin."""
    return np.sqrt(r[0] ** 2 + r[1] ** 2)


def unit_segment(p, q):
    """
    Return endpoint of unit segment starting
    at p and passing through q.
    """
    p = np.asarray(p)
    q = np.asarray(q)
    return p + (q - p) / dist(q - p)


def draw_lines(theta):
    """Draw lines for outer matchsticks."""
    x_vals_1 = [-1 / 2, -1 / 2 - np.sin(theta)]
    y_vals_1 = [1 / 2, 1 / 2 - np.cos(theta)]
    outer_lines[0].set_data(x_vals_1, y_vals_1)

    endpt_2 = unit_segment([x_vals_1[1], y_vals_1[1]], [-1 / 2, -1 / 2])
    x_vals_2 = [x_vals_1[1], endpt_2[0]]
    y_vals_2 = [y_vals_1[1], endpt_2[1]]
    outer_lines[1].set_data(x_vals_2, y_vals_2)

    endpt_3 = unit_segment([x_vals_2[1], y_vals_2[1]], [1 / 2, -1 / 2])
    x_vals_3 = [x_vals_2[1], endpt_3[0]]
    y_vals_3 = [y_vals_2[1], endpt_3[1]]
    outer_lines[2].set_data(x_vals_3, y_vals_3)

    endpt_4 = unit_segment([x_vals_3[1], y_vals_3[1]], [1 / 2, 1 / 2])
    # x_vals_4 = [x_vals_3[1], endpt_4[0]]
    # y_vals_4 = [y_vals_3[1], endpt_4[1]]
    x_vals_4 = [x_vals_3[1], 1 / 2]  # Cheating a bit to overcome rounding error.
    y_vals_4 = [y_vals_3[1], 1 / 2]
    outer_lines[3].set_data(x_vals_4, y_vals_4)


## For animating plot.


def init():
    line.set_data([], [])


def update_plt(s):
    draw_lines((1 - s) * THETA_INIT + s * THETA_FINAL)


## Show the animation.

t = np.linspace(0, 1, 100)
t = np.concatenate((t, t[::-1]))

ani = anim.FuncAnimation(
    fig=fig,
    func=update_plt,
    init_func=init,
    frames=t,
    interval=100,
    blit=False,
    repeat=True,
)

plt.show()

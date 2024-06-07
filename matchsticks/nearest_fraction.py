"""Find low-denominator approximation to a float.
"""

FLOAT = 0.1558168978448610
EPSILON = 0.0000001  # --> 371 / 2381

num = None
denom = None
found = False

for i in range(0, int(1e20)):
    for j in range(1, i):
        candidate = j / i
        if abs(FLOAT - candidate) < EPSILON:
            num = j
            denom = i
            found = True
            break
        elif candidate - FLOAT >= EPSILON:
            break

    if found:
        break

frac_float = num / denom
print(
    f"The fraction {num} / {denom} = {frac_float:.16f} is a good approximation to {FLOAT}."
)

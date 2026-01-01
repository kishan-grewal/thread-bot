# plot.py
import sys
import matplotlib.pyplot as plt

plt.ion()
fig, ax = plt.subplots()

# fixed limits
ax.set_xlim(0, 100)
ax.set_ylim(0, 100)

x, y, colours = [], [], []

scatter = ax.scatter([], [])

for line_in in sys.stdin:
    a, b, c = map(float, line_in.split())

    x.append(a)
    y.append(b)

    colours.append("red" if c == -1 else "blue")

    scatter.set_offsets(list(zip(x, y)))
    scatter.set_color(colours)

plt.ioff()
plt.show()

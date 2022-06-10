import matplotlib.pyplot as plt

n = 50000

x = [0 for i in range(n)]
y = [0 for i in range(n)]

x[0] = 1

for i in range (n):
    if i != 0:
        x[i] = y[i-1] + 1 - 1.4 * x[i-1] * x[i-1]
        y[i] = 0.3 * x[i-1]

plt.scatter(x, y)
plt.show()
import matplotlib.pyplot as plt

# Data
threads = list(range(1, 8))
locks = ["TAS", "TTAS", "ALock", "CLH", "MCS"]

data = {
    "TAS": [44922, 45284, 46194, 46255, 47114, 47629, 48969],
    "TTAS": [44873, 45131, 46036, 46051, 47017, 47609, 48695],
    "ALock": [44480, 45056, 46002, 46046, 47059, 47273, 48456],
    "CLH": [44655, 45023, 45727, 46005, 46586, 47190, 48120],
    "MCS": [43887, 45002, 45714, 46170, 46105, 46430, 47825]
}

plt.figure(figsize=(10, 6))

markers = ['o', 's', 'D', '^', 'v']

for lock, marker in zip(locks, markers):
    plt.plot(threads, data[lock], label=lock, marker=marker, linewidth=3)

plt.title('Time Taken for Different Locks with Varying Threads')
plt.xlabel('Number of Threads', fontsize=10)
plt.ylabel('Time Taken (in microseconds)', fontsize=10)
plt.xticks(threads)
plt.grid(True)
plt.legend(prop={'size': 12})
plt.savefig("svPlot.pdf", format="pdf", bbox_inches="tight")
plt.show()



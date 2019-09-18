import pandas
from matplotlib import pyplot as plt

filepath = "D:\\Documents\\NTU\\Year2\\Sem1\\CZ2001 Algorithms\\CZ2001-Lab\\Lab 2\\"
rangemax = 25

d = pandas.DataFrame(pandas.read_csv(filepath+"linearprobecountbad.csv", header=None))
d = d.transpose()
d.columns = d.iloc[0]
d = d.drop(0)
arr = []
yErr = []
x = range(1, 100)
for i in d:
    if i % 10 == 0 or i == 99:
        arr.append(d[i].values.mean())
        yErr.append(d[i].values.std())
# plt.errorbar(x[:rangemax], arr[:rangemax], yerr=yErr[:rangemax], fmt="r.")
for val in zip(arr, yErr):
    print("{0:.2f} +/- {1:.2f}".format(val[0], val[1]))
e = pandas.DataFrame(pandas.read_csv(filepath+"doublehashcountbad.csv", header=None))
e = e.transpose()
e.columns = e.iloc[0]
e = e.drop(0)
arre = []
yErre = []
for i in e:
    if i % 10 == 0 or i == 99:
        arre.append(e[i].values.mean())
        yErre.append(e[i].values.std())
for val in zip(arre, yErre):
    print("{0:.2f} +/- {1:.2f}".format(val[0], val[1]))
# plt.errorbar(x[:rangemax], arre[:rangemax], yerr=yErre[:rangemax], fmt="b.")
# plt.xlabel("Load factor")
# plt.ylabel("Time in microseconds")
# plt.title("[Failure] Linear Probe vs Double Hashing (Table Size: 1009, Query Size: 1000)")
# plt.legend(labels=["linear", "double"], loc='upper center', bbox_to_anchor=(0.5, -0.2))
# plt.savefig("failure{}.png".format(rangemax), bbox_inches="tight")

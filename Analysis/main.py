import pandas
import numpy
from matplotlib import pyplot as plt

filepath = "D:\\Documents\\NTU\\Year2\\Sem1\\CZ2001 Algorithms\\CZ2001-Lab\\Lab 2\\"

d = pandas.DataFrame(pandas.read_csv(filepath+"linearprobebad.csv", header=None))
d = d.transpose()
d.columns = d.iloc[0]
d = d.drop(0)
arr = []
yErr = []
x = range(1, 100)
for i in d:
    arr.append(d[i].values.mean())
    yErr.append(d[i].values.std())
plt.errorbar(x, arr, yerr=yErr, fmt="r.")

e = pandas.DataFrame(pandas.read_csv(filepath+"doublehashbad.csv", header=None))
e = e.transpose()
e.columns = e.iloc[0]
e = e.drop(0)
arre = []
yErre = []
for i in e:
    arre.append(e[i].values.mean())
    yErre.append(e[i].values.std())
plt.errorbar(x, arre, yerr=yErre, fmt="b.")
plt.xlabel("Load factor")
plt.ylabel("Time in microseconds")
plt.title("[Success] Linear Probe vs Double Hashing (Table Size: 1009, Query Size: 1000)")
plt.legend(labels=["linear", "double"], loc='upper center', bbox_to_anchor=(0.5, -0.2))
plt.show()

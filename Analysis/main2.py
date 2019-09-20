import pandas
from matplotlib import pyplot as plt

filepath = "D:\\Documents\\NTU\\Year2\\Sem1\\CZ2001 Algorithms\\CZ2001-Lab\\Lab 2\\"
rangemax = 100

d = pandas.DataFrame(pandas.read_csv(filepath+"linearprobecount.csv", header=None))
d = d.transpose()
d.columns = d.iloc[0]
d = d.drop(0)
arr = []
yErr = []
x = range(1, 100)
for i in d:
    arr.append(d[i].values.mean())
    yErr.append(d[i].values.std())
plt.errorbar(x[:rangemax], arr[:rangemax], yerr=yErr[:rangemax], fmt="r.")

e = pandas.DataFrame(pandas.read_csv(filepath+"doublehashcount.csv", header=None))
e = e.transpose()
e.columns = e.iloc[0]
e = e.drop(0)
arre = []
yErre = []
for i in e:
    arre.append(e[i].values.mean())
    yErre.append(e[i].values.std())
plt.errorbar(x[:rangemax], arre[:rangemax], yerr=yErre[:rangemax], fmt="b.")
plt.xlabel("Load factor")
plt.ylabel("Number of Steps")
plt.title("[Success] Linear Probe vs Double Hashing (Table Size: 1009, Query Size: 1000)")
plt.legend(labels=["linear", "double"], loc='upper center', bbox_to_anchor=(0.5, -0.2))
plt.show()
#plt.savefig("successcount{}.png".format(rangemax), bbox_inches="tight")

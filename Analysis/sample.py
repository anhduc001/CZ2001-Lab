import pandas
from matplotlib import pyplot as plt
import seaborn as sb
sb.set()

filepath = "D:\\Documents\\NTU\\Year2\\Sem1\\CZ2001 Algorithms\\CZ2001-Lab\\Lab 2\\"
rangemax = 25

d = pandas.DataFrame(pandas.read_csv(filepath+"linearprobe.csv", header=None))
d = d.transpose()
d.columns = d.iloc[0]
d = d.drop(0)
#sb.boxplot(d[d.iloc[50]].values)
plt.hist(d[d.iloc[90]].values, bins=50)
plt.show()
# plt.xlabel("Load factor")
# plt.ylabel("Time in microseconds")
# plt.title("[Failure] Linear Probe vs Double Hashing (Table Size: 1009, Query Size: 1000)")
# plt.legend(labels=["linear", "double"], loc='upper center', bbox_to_anchor=(0.5, -0.2))
# plt.savefig("failure{}.png".format(rangemax), bbox_inches="tight")

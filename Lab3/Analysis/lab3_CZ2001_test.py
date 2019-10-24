import pandas as pd
import matplotlib.pyplot as plt

def SizeInputPlot(df):
    df = df.set_index("Size")
    df.plot()
    plt.ylabel("Time")
    plt.xlabel("Size")
    plt.title("Time execution between TimSort and MergeSort")
    plt.savefig("SizeInput.png")

def SValuePlot(df):
    df = df.set_index("S")
    df.plot()
    plt.ylabel("Time")
    plt.xlabel("Size")
    plt.title("Time execution with different S values")
    plt.savefig("TestValue.png")

def KeyComparisons(df):
    df = df.set_index("Size")
    df.plot()
    plt.ylabel("KeyComparisons")
    plt.xlabel("Size")
    plt.title("Key comparisons between Timsort and MergeSort")
    plt.savefig("KeyComparisons.png")

if __name__ == "__main__":
    data_file = "C:\\Users\\v\\source\\repos\\CZ2001-Lab\\Lab3\\"
    # Read CSV
    df1 = pd.read_csv(data_file + "testSizeInput.csv")
    df2 = pd.read_csv(data_file + "testValueS.csv")
    df3 = pd.read_csv(data_file + "keyComparison.csv")
    SizeInputPlot(df1)
    SValuePlot(df2)
    KeyComparisons(df3)
    plt.show()

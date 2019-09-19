#pragma once
#include "vector"
using namespace std;
class TimSort
{
public:
	TimSort(void);
	~TimSort(void);
	void insertionSort(std::vector<int>v, int first, int last);
	void MergeSort(std::vector<int>v, int first, int last);
	void Timsort(std::vector<int>v, int first, int last, int S);
private:
	void Merge(std::vector<int>v, int first, int mid,int last);
};


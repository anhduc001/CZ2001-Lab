#include "TimSort.h"


TimSort::TimSort(void)
{

}


TimSort::~TimSort(void)
{

}
void TimSort::MergeSort(std::vector<int>v, int first, int last){
	if (first >= last){
		return ;
	}
	else{
		int mid = (first + last) / 2;
		MergeSort(v, first, mid);
		MergeSort(v, mid + 1, last);
		Merge(v, first, mid, last);
	}
}
void Merge(std::vector<int>v, int first, int mid,int last){
	std::vector<int>temp(v.size());
	int x = first;
	int y = mid + 1;
	int cur_index = 0;
	// Merge part
	while (x <= mid && y <= last){
		if ( v[x] < v[y]){
			temp[cur_index ++] = v[x];
			x ++;
		}
		else{
			temp[cur_index ++] = v[y];
			y ++;
		}
	}
	if (x <= mid){
		for (int i = x; i <= mid; i++){
			temp[cur_index ++] = v[i];
		}
	}
	else{
		for (int i = y; i <= last; i++){
			temp[cur_index ++] = v[i];
		}
	}
	// copy vector
	for (int i = 0; i < v.size(); i++){
		v[i] = temp[i];
	}
}
void TimSort::Timsort(std::vector<int>v, int first, int last, int S) {
	if (last - first > S) {
		int mid = (first + last) / 2;
		TimSort::Timsort(v, first, mid, S);
		TimSort::Timsort(v, mid + 1, last, S);
		TimSort::Merge(v, first, mid ,last);
	}
	else {
		insertionSort(v, first, last);
	}
}


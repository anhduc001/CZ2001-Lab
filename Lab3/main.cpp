#include <iostream>
#include <vector>

using namespace std;

void merge(std::vector<int>&v, int first, int mid, int last)
{
    std::vector<int> temp(v.size());
    int x = first;
    int y = mid + 1;
    int cur_index = first;
    // Merge part
    while (x <= mid && y <= last){
        if ( v[x] < v[y]){
            temp[cur_index++] = v[x++];
        }
        else{
            temp[cur_index++] = v[y++];
        }
    }
    if (x <= mid){
        for (int i = x; i <= mid; i++){
            temp[cur_index++] = v[i];
        }
    }
    else{
        for (int i = y; i <= last; i++){
            temp[cur_index++] = v[i];
        }
    }
    // copy vector
    for (int i = first; i <= last; i++){
        v[i] = temp[i];
    }
}

void mergeSort(std::vector<int>&v, int first, int last){
    if (first < last){
        int mid = first + (last - first) / 2;
        mergeSort(v, first, mid);
        mergeSort(v, mid + 1, last);
        merge(v, first, mid, last);
    }
}

void insertionSort(vector<int>&v, int first, int last) {
    int i, j, cur;
    for (i = first; i <= last; i++)
    {
        cur = v[i];
        j = i - 1;

        while (j >= 0 && v[j] > cur)
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = cur;
    }
}

void timSort(std::vector<int>&v, int first, int last, int S) {
    if (last - first > S) {
        int mid = (first + last) / 2;
        timSort(v, first, mid, S);
        timSort(v, mid + 1, last, S);
        merge(v, first, mid ,last);
    }
    else {
        insertionSort(v, first, last);
    }
}
void reverseVector(std::vector<int>&v) {
    std::vector<int> temp(v.size());
    for(int i = 0; i < v.size(); i++)
    {
        temp[i] = v[v.size() - i - 1];
    }
    for(int i = 0; i < v.size(); i++)
    {
        v[i] = temp[i];
    }
}

int main() {
    std::vector<int>v = {0,1,5,6,2,9,7,3};
    timSort(v, 0, v.size()-1, 2);
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << ' ';
    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
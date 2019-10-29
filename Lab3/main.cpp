#include <iostream>
#include <vector>
#include <random>
#include <set>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;

//Maximum size of the vector
const int maxSize = 10000;
//Number of tests per size or per S value
const int testFreq = 10;
//Max of S value
const int maxS = 400;

//Merge function
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

//Implementation of initial mergeSort
void mergeSort(std::vector<int>&v, int first, int last){
    if (last - first > 0){
        int mid = first + (last - first) / 2;
        mergeSort(v, first, mid);
        mergeSort(v, mid + 1, last);
        merge(v, first, mid, last);
    }
}
<<<<<<< HEAD

//Implementation of insertionSort
void insertionSort1(vector<int>&v, int first, int last) {
    int i, j, cur;
    for (i = first; i <= last; i++)
    {
        cur = v[i];
        j = i - 1;

        while (j >= 0 && v[j] > cur)
        {
            v[j + 1] = v[j];
            j--;
=======
// insert a number into a sorted vector
int binarySearch(vector<int> &v, int first, int last ,int i){
    int lower = first;
    int upper = last;
    while (lower < upper){
        int mid = (lower + upper) / 2;
        if (v[mid] < v[i]){
            return binarySearch(v, mid + 1, last, i);
        }
        else if (v[mid] > v[i]){
            return binarySearch(v, lower , mid - 1, i);
        }
        else{
            return mid;
        }
    }
    return (v[i] > v[lower])? lower + 1 : lower;
}
//implement insertion sort function
void insertionSort(vector<int>&v, int first, int last) {
    for (int i = first + 1; i <= last; i++){
        int index = binarySearch(v, first, i - 1, i);
        int copied = v[i];
        for (int j = i; j > index; j -- ){
            v[j] = v[j - 1];
>>>>>>> f263b85c8edf4d4fa38b50f0339011d713786d67
        }
        v[index] = copied;
    }
}
<<<<<<< HEAD
int binarySearch(vector<int> &v, int first, int last ,int i){
    int lower = first;
    int upper = last;
    while (lower < upper){
        int mid = (lower + upper) / 2;
        if (v[mid] < v[i]){
            return binarySearch(v, mid + 1, last, i);
        }
        else if (v[mid] > v[i]){
            return binarySearch(v, lower , mid - 1, i);
        }
        else{
            return mid;
        }
    }
    return (v[i] > v[lower])? lower + 1 : lower;
}

void insertionSort(vector<int>&v, int first, int last) {
    for (int i = first + 1; i <= last; i++){
        int index = binarySearch(v, first, i - 1, i);
        int copied = v[i];
        for (int j = i; j > index; j -- ){
            v[j] = v[j - 1];
        }
        v[index] = copied;
    }
}
//Implementation of timSort
void timSort(std::vector<int>&v, int first, int last, int S) {

    if (last - first > S) {
        int mid = first + (last - first) / 2;
        timSort(v, first, mid, S);
        timSort(v, mid + 1, last, S);
        merge(v, first, mid ,last);
    }
    else {
        insertionSort(v, first, last);
    }
}
void timSort1(std::vector<int>&v, int first, int last, int S) {
=======
//Implementation of Merge Insertion Sort
void MergeInsertionSort(std::vector<int>&v, int first, int last, int S) {

    if (last - first > S) {
        int mid = first + (last - first) / 2;
        MergeInsertionSort(v, first, mid, S);
        MergeInsertionSort(v, mid + 1, last, S);
        merge(v, first, mid ,last);
    }
    else {
        insertionSort(v, first, last);
    }
}
void timSort(std::vector<int>&v, int first, int last, int S) {
>>>>>>> f263b85c8edf4d4fa38b50f0339011d713786d67
    std::cout << first << ", "  << last << ", " << first - last << ", " << S<<endl;
    if (last - first > S) {
        int mid = first + (last - first) / 2;
        timSort(v, first, mid, S);
        timSort(v, mid + 1, last, S);
        merge(v, first, mid ,last);
    }
    else {
        insertionSort(v, first, last);
    }
}
//Randomly generates a vector of n unordered integers
vector<int> generateRandomInput(int n) {
    set<int> ret;
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0, n-1);
    while(ret.size() != n)
    {
        ret.insert(uni(rng));
    }
    vector<int> v;
    v.assign(ret.begin(), ret.end());
    shuffle (v.begin(), v.end(), rng);
    return v;
}

//Test the execution time with different-size vectors
long testSizeInput(vector<int> v, int choice){
    if (choice == 0)
    {
        auto start = chrono::steady_clock::now();
<<<<<<< HEAD
        timSort(v, 0, v.size() - 1, 1);
=======
        MergeInsertionSort(v, 0, v.size() - 1, 10);
>>>>>>> f263b85c8edf4d4fa38b50f0339011d713786d67
        auto end = chrono::steady_clock::now();
        return chrono::duration_cast<chrono::microseconds>(end - start).count();
    }
    else if (choice == 1)
    {
        auto start = chrono::steady_clock::now();
        mergeSort(v, 0, v.size() - 1);
        auto end = chrono::steady_clock::now();
        return chrono::duration_cast<chrono::microseconds>(end - start).count();
    }
    else
        return 0;

}
// test with different S value
long testValueS(vector<int> v, int S){
    auto start = chrono::steady_clock::now();
    MergeInsertionSort(v, 0, v.size() - 1, S);
    auto end = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::microseconds>(end - start).count();

}
<<<<<<< HEAD
=======
// return a vector cloning of a vector
>>>>>>> f263b85c8edf4d4fa38b50f0339011d713786d67
std::vector<int> clone(std::vector<int> v){
    vector<int> res ;
    for (int i = 0; i < v.size(); i++){
        res.push_back(v[i]);
    }
    return res;
}
// Binary Search key comparison
long long binarySearchKeyComparisons(vector<int> v, int first, int last, int i){
    int lower = first;
    int upper = last;
    while (lower < upper){
        int mid = (lower + upper) / 2;
        if (v[mid] < v[i]){
            return binarySearchKeyComparisons(v, mid + 1, last, i) + 1;
        }
        else if (v[mid] > v[i]){
            return binarySearchKeyComparisons(v, lower , mid - 1, i) + 1;
        }
        else{
            return 1;
        }
    }
    return 0;
}
// Insertion sort key comparison
long long InsertionSortKeyComparisons(vector<int> v, int first, int last){
    long long res = 0;
    for (int i = first + 1; i <= last; i++){
        int index = binarySearch(v, first, i - 1, i);
        res += binarySearchKeyComparisons(v, first, last, i);
        int copied = v[i];
        for (int j = i; j > index; j -- ){
            v[j] = v[j - 1];
        }
        v[index] = copied;
    }
    return res;
}
// MergeSort Key Comparison
long long MergeKeyComparisons(vector<int> v, int first, int mid, int last){
    std::vector<int> temp(v.size());
    int x = first;
    int y = mid + 1;
    int cur_index = first;
    long long res = 0;
    while (x <= mid && y <= last){
        if ( v[x] < v[y]){
            temp[cur_index++] = v[x++];
        }
        else{
            temp[cur_index++] = v[y++];
        }
        res++;
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
    return res;
}
//compute key comparison for TimSort
<<<<<<< HEAD
long long TimSortKeyComparisons(vector<int> v, int first, int last, int S){
=======
long long MergeInsertionSortKeyComparisons(vector<int> v, int first, int last, int S){
>>>>>>> f263b85c8edf4d4fa38b50f0339011d713786d67
    long long res = 0;
    if (last <= first){
        return 0;
    }
    if (last - first > S) {
        int mid = first + (last - first) / 2;
<<<<<<< HEAD
        res += TimSortKeyComparisons(v, first, mid, S);
        res += TimSortKeyComparisons(v, mid + 1, last, S);
=======
        res += MergeInsertionSortKeyComparisons(v, first, mid, S);
        res += MergeInsertionSortKeyComparisons(v, mid + 1, last, S);
>>>>>>> f263b85c8edf4d4fa38b50f0339011d713786d67
        res += MergeKeyComparisons(v, first,mid,last);
    }
    else {
        res += InsertionSortKeyComparisons(v, first, last);
    }
    return res;
}
long long MergeSortKeyComparisons(vector<int>v, int first, int last){
    long long res = 0;
    if (last - first > 0){
        int mid = first + (last - first) / 2;
        res += MergeSortKeyComparisons(v, first, mid);
        res += MergeSortKeyComparisons(v, mid + 1, last);
        res += MergeKeyComparisons(v, first, mid, last);
    }
    return res;
}
// testing key Comparison for each Sorting algorithm
long long keyCompare(vector<int>v, int choice){
    switch(choice){
        case 0:
<<<<<<< HEAD
            return TimSortKeyComparisons(v, 0, v.size() - 1, 200); // timsort key comparison analyse
=======
            return MergeInsertionSortKeyComparisons(v, 0, v.size() - 1, 10); // Merge insertion sort key comparison analyse
>>>>>>> f263b85c8edf4d4fa38b50f0339011d713786d67
        case 1:
            return MergeSortKeyComparisons(v,0, v.size() - 1);// mergesort key comparison analyse
        default:
            return 0;
    }
}
// main function
int main() {

<<<<<<< HEAD
    //Open file
    // testing for different size
=======
    //Open file testing for different size
>>>>>>> f263b85c8edf4d4fa38b50f0339011d713786d67
    ofstream size;
    size.open("testSizeInput.csv");
    //testing for different value S
    ofstream valueS;
    valueS.open("testValueS.csv");
    //testing for key comparison
    ofstream key_comparisons;
    key_comparisons.open("keyComparison.csv");
    // header of each CSV file
<<<<<<< HEAD
    size << "Size,timSort Time,mergeSort Time\n";
    valueS << "S,Time\n";
    key_comparisons << "Size, timSort keyComparisons, mergeSort keyComparisons\n";
=======
    size << "Size,MergeInsertionSort Time,MergeSort Time\n";
    valueS << "S,Time\n";
    key_comparisons << "Size, MergeInsertionSort keyComparisons, MergeSort keyComparisons\n";
>>>>>>> f263b85c8edf4d4fa38b50f0339011d713786d67
    // size loop
    for(int i = 1000; i <= maxSize; i += 1000)
    {
        size << i;
        long long time0 = 0;
        long long time1 = 0;
        long long keyComparison0 = 0; // Timsort
        long long keyComparison1 = 0; // MergeSort
        //Testing Loop, with 0 for timSort and 1 for mergeSort
        for (int j = 0; j < testFreq; j++) {
            std::vector<int> v = generateRandomInput(i);
            std::vector<int> v1 = clone(v);
            std::vector<int> v2 = clone(v);
            std::vector<int> v3 = clone(v);
            //time execution
            time0 += testSizeInput(v, 0);
            time1 += testSizeInput(v1, 1);
            // count key comparison
            keyComparison0 += keyCompare(v2, 0);
            keyComparison1 += keyCompare(v3, 1);
        }
        // write into Time testing file
        size << "," << time0 / testFreq;
        size << "," << time1 / testFreq;
        size << "\n";
        // write into Key comparison File
        key_comparisons << i;
        key_comparisons << "," << keyComparison0 / testFreq;
        key_comparisons << "," << keyComparison1 / testFreq;
        key_comparisons << "\n";
    }


    //Experiment with different S value
    std::vector<int> times(maxS);
	for (int j = 0; j < testFreq; j++) {
<<<<<<< HEAD
		std::vector<int> v = generateRandomInput(1000); // generate different vector each time
=======
		std::vector<int> v = generateRandomInput(10000); // generate different vector each time
>>>>>>> f263b85c8edf4d4fa38b50f0339011d713786d67
		for (int i = 0; i < maxS; i++)
		{
		    std::vector<int> v1 = clone(v);
            //Test Loop
			times[i] += testValueS(v1, i + 1);
		}
	}
    for (int i = 0; i < maxS; i++){
        valueS << i+1 << ", " << times[i] / testFreq << endl;
    }
    size.close();
    valueS.close();
    key_comparisons.close();
    cout << "Finish!!" << endl;
    return 0;
}

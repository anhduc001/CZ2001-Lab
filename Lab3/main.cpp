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

//Implementation of mergeSort
void mergeSort(std::vector<int>&v, int first, int last){
    if (last - first > 0){
        int mid = first + (last - first) / 2;
        mergeSort(v, first, mid);
        mergeSort(v, mid + 1, last);
        merge(v, first, mid, last);
    }
}

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
        }
        v[j + 1] = cur;
    }
}
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
        timSort(v, 0, v.size() - 1, 1);
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

long testValueS(vector<int> v, int S){
    auto start = chrono::steady_clock::now();
    timSort(v, 0, v.size() - 1, S);
    auto end = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::microseconds>(end - start).count();

}
std::vector<int> clone(std::vector<int> v){
    vector<int> res ;
    for (int i = 0; i < v.size(); i++){
        res.push_back(v[i]);
    }
    return res;
}
int main() {

    //Open file
    ofstream size;
    size.open("testSizeInput.csv");
    ofstream valueS;
    valueS.open("testValueS.csv");

    //Size Loop
    size << "Size,timSort Time,mergeSort Time\n";
    for(int i = 1000; i <= maxSize; i += 1000)
    {
        size << i;
        long long time0 = 0;
        long long time1 = 0;
        //Testing Loop, with 0 for timSort and 1 for mergeSort
        for (int j = 0; j < testFreq; j++) {
            std::vector<int> v = generateRandomInput(i);
            std::vector<int> v1 = clone(v);
            time0 += testSizeInput(v, 0);
            time1 += testSizeInput(v1, 1);
        }
        size << "," << time0 / testFreq;
        size << "," << time1 / testFreq;
        size << "\n";
    }


    //Experiment with different S value
    std::vector<int> times(maxS);
    valueS << "S,Time\n";
	for (int j = 0; j < testFreq; j++) {
		std::vector<int> v = generateRandomInput(1000); // generate different vector each time
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
    cout << "Finish!!" << endl;
    return 0;
}


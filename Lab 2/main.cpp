#include "fstream"
#include "iostream"
#include "chrono"
#include "random"
#include "vector"

using namespace std;
// Number of tests per data point
const int testFreq = 1000;
// Number of queries per test
const int testSize = 1000;

// Abstract Base Class
class HashTable{
    public:
        virtual bool insert(int item){return false;};
        virtual bool contains(int item){return false;};
        void print(){
            for(int i = 0; i < hashtableSize; i++){
                if(table[i] != 0){
                    cout << table[i] << "\n";
                }
            }
        }
        static const int hashtableSize = 1009;
protected:
        int table[hashtableSize] = {0};
};

// Libear Probing Implementation
class LinearProbe: public HashTable{
	private:
		int hashFunction(int item){
			return (61*item) % hashtableSize;
		};
	public:
		bool insert(int item) override{
			int base_index = hashFunction(item);
			int index = base_index;
			while(table[index] != 0){
				index++;
				if(index >= hashtableSize) index = index % hashtableSize;
				if(index == base_index) return false;
			}
			table[index] = item;
			return true;
		};
		bool contains(int item) override{
			int base_index = hashFunction(item);
			int index = base_index;
			while(table[index] != 0){
				if(table[index] == item) return true;
				index++;
				if(index >= hashtableSize) index = index % hashtableSize;
				if(index == base_index) return false;
			}
			return false;
		};
};
// Doubke Hashing Implementation
class DoubleHash: public HashTable{
	private:
		int hashFunction1(int item){
			return (61*item) % hashtableSize;
		};
		int hashFunction2(int item){
			return (item % 37) + 1;
		};
	public:
		bool insert(int item) override{
			int base_index = hashFunction1(item);
			int offset = hashFunction2(item);
			int index = base_index;
			while(table[index] != 0){
				index += offset;
				if(index >= hashtableSize) index = index % hashtableSize;
				if(index == base_index) return false;
			}
			table[index] = item;
			return true;
		}
		bool contains(int item) override{
			int base_index = hashFunction1(item);
			int offset = hashFunction2(item);
			int index = base_index;
			while(table[index] != 0){
				if(table[index] == item) return true;
				index += offset;
				if(index >= hashtableSize) index = index % hashtableSize;
				if(index == base_index) return false;
			}
			return false;
		}
};

// Randomly Generates 'num' unique integers that are not in the 'exist' vector.
vector<int> GenerateRandomNumbers(int num, vector<int>* exist){
    DoubleHash existing;
    if(exist != nullptr){
        for(int i:*exist){
            existing.insert(i);
        }
    }
    DoubleHash table;
    if(num > table.hashtableSize){
        num = table.hashtableSize;
    }
    vector<int> ret;
    random_device rd;     // only used once to initialise (seed) engine
    mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    uniform_int_distribution<int> uni(1000000,9999999); // guaranteed unbiased
    for(int i = 0; i < num; i++){
        ret.emplace_back(uni(rng));
        if(!table.contains(ret[i]) && !existing.contains(ret[i])){
            table.insert(ret[i]);
        }else{
            ret.erase(ret.end()-1);
            i--;
        }
    }
    return ret;
}

// Randomly samples 'num' times from the 'exist' vector.
vector<int> GenerateRandomSubset(int num, vector<int>* exist){
    vector<int> ret;
    random_device rd;     // only used once to initialise (seed) engine
    mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    uniform_int_distribution<int> uni(0,exist->size()); // guaranteed unbiased
    for(int i = 0; i < num; i++){
        ret.emplace_back((*exist)[uni(rd)]);
    }
    return ret;
}

// Performs a measurement of computational time in microseconds for the test to complete.
long test(const vector<int>& testArgs, const vector<int>& search, HashTable* table){
    for(int testArg : testArgs){
        table->insert(testArg);
    }
    auto start = chrono::steady_clock::now();
    for(int searchArg : search){
            table->contains(searchArg);
    }
    auto end = chrono::steady_clock::now();
//    cout << "Elapsed time in microseconds : "
//         << chrono::duration_cast<chrono::microseconds>(end - start).count()
//         << " µs" << endl;
    return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

int main()
{
    // Success test
    // Open files
    ofstream lin;
    lin.open("linearprobe.csv");
    ofstream dbl;
    dbl.open("doublehash.csv");

    cout << std::boolalpha;
    //Load Factor Loop
    for(int i = 1; i < 100; i++){
        lin << i;
        dbl << i;
        // Testing loop
        for(int j = 0; j < testFreq; j++){
            DoubleHash* dblhash = new DoubleHash;
            LinearProbe* linearp = new LinearProbe;
            vector<int> sample = GenerateRandomNumbers(HashTable::hashtableSize / 100 * i, NULL);
            vector<int> success = GenerateRandomSubset(testSize, &sample);
            lin << "," << test(sample, success, linearp);
            dbl << "," << test(sample, success, dblhash);
        }
        if(i < 99){
            lin << endl;
            dbl << endl;
        }
    }
    // Close Files
    lin.close();
    dbl.close();

    // Failure test
    // Open Files
    ofstream linb;
    linb.open("linearprobebad.csv");
    ofstream dblb;
    dblb.open("doublehashbad.csv");
    // Load Factor Loop
    for(int i = 1; i < 100; i++){
        linb << i;
        dblb << i;
        // Testing loop
        for(int j = 0; j < testFreq; j++){
            DoubleHash* dblhash = new DoubleHash;
            LinearProbe* linearp = new LinearProbe;
            vector<int> sample = GenerateRandomNumbers(HashTable::hashtableSize / 100 * i, NULL);
            vector<int> failed = GenerateRandomNumbers(HashTable::hashtableSize / 100 * i, NULL);
            linb << "," << test(sample, failed, linearp);
            dblb << "," << test(sample, failed, dblhash);
        }
        if(i < 99){
            linb << endl;
            dblb << endl;
        }
    }
    // Close file
    linb.close();
    dblb.close();
    return 0;
}

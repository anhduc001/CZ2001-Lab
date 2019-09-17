#include "iostream"
#include "chrono"
#include "random"
#include "vector"

using namespace std;

class HashTable{
    public:
        virtual bool insert(int item){};
        virtual bool contains(int item){};
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
    uniform_int_distribution<int> uni(1,10000); // guaranteed unbiased
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

void testSuccessful(const vector<int>& testArgs, HashTable* table){
    for(int testArg : testArgs){
        table->insert(testArg);
    }
    auto start = chrono::steady_clock::now();
    for(int testArg : testArgs){
        cout << table->contains(testArg) << " ";
    }
    auto end = chrono::steady_clock::now();
    cout << "Elapsed time in microseconds : "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " µs" << endl;
}

void testUnSuccessful(const vector<int>& testArgs, const vector<int>& failedSearch, HashTable* table){
    for(int testArg : testArgs){
        table->insert(testArg);
    }
    auto start = chrono::steady_clock::now();
    for(int searchArg : failedSearch){
            cout << table->contains(searchArg) << " ";
    }
    auto end = chrono::steady_clock::now();
    cout << "Elapsed time in microseconds : "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " µs" << endl;
}

int main()
{
    int i;
//    LinearProbe p;
//    HashTable& table = p;
//	table.insert(1);
//	table.insert(5);
//	table.insert(10);
//	cout << (table.contains(1) == 1);
//	cout << table.contains(2);
//	cout << table.contains(3);
//	cout << table.contains(4);
//	cout << table.contains(5);
//	cout << table.contains(10);
    cout << std::boolalpha;
    DoubleHash* dblhash = new DoubleHash;
    cout << "Double Hash created!\n";
    LinearProbe* linearp = new LinearProbe;
    cout << "Linear Probe created!\n";
    vector<int> sample = GenerateRandomNumbers(400, NULL);
    cout << "Setup complete!\n";
    testSuccessful(sample, dblhash);
    testSuccessful(sample, linearp);
    dblhash = new DoubleHash;
    cout << "Double Hash created!\n";
    linearp = new LinearProbe;
    cout << "Linear Probe created!\n";
    vector<int> wrong = GenerateRandomNumbers(400, &sample);
    cout << "setup2 complete!\n";
    testUnSuccessful(sample, wrong, dblhash);
    testUnSuccessful(sample, wrong, linearp);
	cin >> i;
    return 0;
}

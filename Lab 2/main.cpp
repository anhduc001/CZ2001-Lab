#include "iostream"
#define TABLE_SIZE  101
#define SECOND_HASH_PRIME 107
using namespace std;

class HashTable{
    protected:
        int table[TABLE_SIZE] = {0};
};

class LinearProbe : protected HashTable{
	private:
		int hashFunction(int item){
			return item % TABLE_SIZE;
		};
	public:
		bool insert(int item){
			int base_index = hashFunction(item);
			int index = base_index;
			while(table[index] != 0){
				index++;
				if(index >= TABLE_SIZE) index = index % TABLE_SIZE;
				if(index == base_index) return false;
			}
			table[index] = item;
			return true;
		};

		bool retrieve(int item){
			int base_index = hashFunction(item);
			int index = base_index;
			while(table[index] != 0){
				if(table[index] == item) return true;
				index++;
				if(index >= TABLE_SIZE) index = index % TABLE_SIZE;
				if(index == base_index) return false;
			}
			return false;
		};
};
class DoubleHash: protected HashTable{
	private:
		int hashFunction1(int item){
			return item % TABLE_SIZE;
		};
		int hashFunction2(int item){
			return item % SECOND_HASH_PRIME;
		};
	public:
		bool insert(int item){
			int base_index = hashFunction1(item);
			int offset = hashFunction2(item);
			int index = base_index;
			while(table[index] != 0){
				index += offset;
				if(index >= TABLE_SIZE) index = index % TABLE_SIZE;
				if(index == base_index) return false;
			}
			table[index] = item;
			return true;
		}
		bool retrieve(int item){
			int base_index = hashFunction1(item);
			int offset = hashFunction2(item);
			int index = base_index;
			while(table[index] != 0){
				if(table[index] == item) return true;
				index += offset;
				if(index >= TABLE_SIZE) index = index % TABLE_SIZE;
				if(index == base_index) return false;
			}
			return false;
		}
};

int main()
{
    int i;
	LinearProbe table;
	table.insert(1);
	table.insert(5);
	table.insert(10);
	cout << (table.retrieve(1) == 1);
	cout << table.retrieve(2) << endl;
	cout << table.retrieve(3) << endl;
	cout << table.retrieve(4) << endl;
	cout << table.retrieve(5) << endl;
	cout << table.retrieve(10)<< endl;
	cin >> i;
    return 0;
}

#include "iostream"

using namespace std;

class HashTable{
    protected:
        int table[101] = {0};
};

class LinearProbe: protected HashTable{
	private:
		int hashFunction(int item){
			return item % 101;
		};
	public:
		bool insert(int item){
			int base_index = hashFunction(item);
			int index = base_index;
			while(table[index] != 0){
				index++;
				if(index >= 101) index = index % 101;
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
				if(index >= 101) index = index % 101;
				if(index == base_index) return false;
			}
			return false;
		};
};
class DoubleHash: protected HashTable{
	private:
		int hashFunction1(int item){
			return item % 101;
		};
		int hashFunction2(int item){
			return item % 107;
		};
	public:
		bool insert(int item){
			int base_index = hashFunction1(item);
			int offset = hashFunction2(item);
			int index = base_index;
			while(table[index] != 0){
				index += offset;
				if(index >= 101) index = index % 101;
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
				if(index >= 101) index = index % 101;
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
	cout << table.retrieve(2);
	cout << table.retrieve(3);
	cout << table.retrieve(4);
	cout << table.retrieve(5);
	cout << table.retrieve(10);
	cin >> i;
    return 0;
}

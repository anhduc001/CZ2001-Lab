// CZ2001 Lab 2.cpp : main project file.

#include "stdafx.h"
#include "iostream"

using namespace System;
using namespace std;

public class HashTable{
	public:
		virtual bool insert(int item) = 0;
		virtual bool retrieve(int item) = 0;
};

public class LinearProbe: public HashTable{
	private:
		int table[101];
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

public class DoubleHash: public HashTable{
	private:
		int table[101];
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

int main(array<System::String ^> ^args)
{
	HashTable& table = LinearProbe();
	table.insert(1);
	table.insert(5);
	table.insert(10);
	Console::WriteLine(table.retrieve(1));
	Console::WriteLine(table.retrieve(2));
	Console::WriteLine(table.retrieve(3));
	Console::WriteLine(table.retrieve(4));
	Console::WriteLine(table.retrieve(5));
	Console::WriteLine(table.retrieve(10));
	std::cin.get();
    return 0;
}

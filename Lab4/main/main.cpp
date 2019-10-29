#include<iostream>
#include<math.h>
#include<stdio.h>
#include<fstream>
#include<vector>
#define NODE 4039
using namespace std;
vector<int>NodeRetrieve(std::string str){
    std::string delimeter = " ";
    vector<int>edge(2);
    int pos = str.find(delimeter);
    edge[0] = stoi(str.substr(0, pos));
    edge[1] = stoi(str.substr(pos + 1, str.length()));
    return edge;
}
int main(){
    std::string edge;
    fstream inFile;
    int degree[NODE];
    int c = 0;
    int x;
    for (int i = 0; i < NODE; i++){
        degree[i] = 0;
    }
    // readfile and debugging
    inFile.open("C:\\Users\\v\\source\\repos\\CZ2001-Lab\\Lab4\\dataset.txt");
    if (!inFile){
        std::cout << "Could not load the data set!" << std::endl;
    }
    else{
        std::cout << "Loaded successfully!" << std::endl;
    }
    // node degree calculation
    while (std::getline(inFile, edge)){
        vector<int> e = NodeRetrieve(edge);
        std::cout << e[0] <<" " << e[1] << endl;
        ++ degree[e[0]];
        ++ degree[e[1]];
    }

    std::cout << "finish!";
}

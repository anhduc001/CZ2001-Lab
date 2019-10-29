#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string multiply(string s, int x) {
    string r;
    int carry = 0;
    for(int i = s.size() - 1; i >= 0; --i) {
        int d = (s[i] - '0') * x + carry;
        r += to_string(d % 10);
        carry = d / 10;
    }
    if(carry != 0) r += to_string(carry);
    reverse(r.begin(), r.end());
    return r;
}

string divide(string s, int x) {
	// x < 10
    int len = s.size();
    string r;
    int mem = 0;
    for(int i = 0; i < len; i++) {
        int d = (s[i] - '0') + 10 * mem;
        r += to_string(d / x);
        mem = d % x;
    }
    return r;
}


void print(int n, int d) {
    string s1(n - 1, '1');
    string s2(n - 1, '8');
    // 3333*3333
    string s3 = s1 + "0" + s2 + "9";
    
    // 1111*1111
    string s4 = divide(s3, 9);
    
    // 1111*1111*d
    string s5 = multiply(s4, d);
    // 1111*1111*d*d
    string s6 = multiply(s5, d);	
    
    cout << s6;
}
int main() {
    int n = 12345;
    int d = 5;

    print(n, d);
}

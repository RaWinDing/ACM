// HDOJ 2604
// Queuing
// by A Code Rabbit

#include <iostream>
#include <string>

using namespace std;

int ans;
int n;

void Search(string str);

int main() {
    while (cin >> n) {
        ans = 0;
        Search("");
        cout << ans << endl; 
    }
}

void Search(string str) {
    if (str.length() >= n) {
        if (str.find("fmf") == string::npos &&
            str.find("fff") == string::npos)
        {
            ++ans;
        }
        return;
    }
    Search(str + "f");
    Search(str + "m");
} 

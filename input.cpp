// Simple demonstration of I/O
// file sample.txt:
//4     //number of test cases
//2 7   //testcase 1, two integers
//2 4
//6 3
//8 2

// compile with g++ -o input input.cpp
// then run: ./input < sample.txt > output.txt
// this will read sample and save results in output

#include <iostream>
using namespace std;

int main()
{
    int t, n, m;
    cin >> t;
    for(int i = 1; i <= t; ++i)
    {
        cin >> n >> m;
        cout << "Case #" << i << ": " << (n+m) << " " << (n*m) << endl;
    }

    return 0;
}

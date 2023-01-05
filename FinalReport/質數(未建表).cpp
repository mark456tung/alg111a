#include <iostream>
#include <math.h>
using namespace std;
int num = 20000000;

int main() {
    for (int i=0; i<num; i++)
    {
        if (i==0 || i==1)
            continue;
        bool prime = true;
        int sq = sqrt(i);
        for (int j=2; j<=sq; j++)
        {
            if (i % j == 0)
            {
                prime = false;
                break;
            }
        }
        if(prime)
            cout<<i<<endl;
    }
}
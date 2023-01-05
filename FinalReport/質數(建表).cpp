#include <iostream>
#include <math.h>
using namespace std;
int num = 20000000;
bool prime[20000000];
 
void eratosthenes()
{
    for (int i=0; i<num; i++)
        prime[i] = true;
    prime[0] = false;
    prime[1] = false;
    
    int sq = sqrt(num);
    for (int i=2; i<sq; i++)
    {
        if (prime[i])
        {
            for (int j=i*i; j<num; j+=i)
                prime[j] = false;
        }
    }
}

int main() {
    eratosthenes();
    for (int i=0; i<num; i++)
    {
        if (prime[i])
            cout<<i<<endl;
    }
}
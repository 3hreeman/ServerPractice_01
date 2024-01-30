
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
using namespace std;
const int MaxCount = 300000;
const int ThreadCount = 4;
bool IsPrimeNumber(int number)
{
    if(number == 1) return false;

    if(number == 2 || number == 3) return true;

    for(int i=2; i<number; i++)
    {
        if(number % i == 0) return false;
    }
    return true;
}

void PrintNumber(const vector<int> &numbers)
{
    for(int i : numbers)
    {
        cout << i << endl;
    }
}

int main()
{
    auto num = 1;

    vector<int> primes;

    auto t0 = chrono::system_clock::now();

    vector<shared_ptr<thread>> threads;

    for(int i=0; i<ThreadCount; i++)
    {
        shared_ptr<thread> thr (new thread([&]()
        {
            while(true)
            {
                int n;
                n = num;
                num++;
                if(n>=MaxCount) break;
                if(IsPrimeNumber(n))
                {
                    primes.push_back(n);
                }
            }           
        }));
        threads.push_back(thr);
    }

    for(auto thr : threads)
    {
        thr->join();
    }

    auto t1 = chrono::system_clock::now();
    cout << "took time : " << chrono::duration_cast<chrono::milliseconds>(t1-t0).count() << endl;

    return 0;
}

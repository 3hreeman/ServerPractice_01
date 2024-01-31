
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
using namespace std;
const int MaxCount = 1500000;
const int ThreadCount = 8;
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

void TestPrime()
{
    auto num = 1;

    recursive_mutex num_mutex;
    vector<int> primes;
    recursive_mutex primes_mutex;
    
    auto t0 = chrono::system_clock::now();
    
    vector<shared_ptr<thread>> threads;
    for(int i=0; i<ThreadCount; i++)
    {
        shared_ptr<thread> thr (new thread([&]()
        {
            while(true)
            {
                int n;
                {
                    lock_guard<recursive_mutex> num_lock(num_mutex);
                    n = num;
                    num++;
                }
                if(n>=MaxCount) break;
                if(IsPrimeNumber(n))
                {
                    lock_guard<recursive_mutex> prime_lock(primes_mutex);
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
}

int main()
{
    
}

#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <vector>
#include <chrono>
using namespace std;


vector<int> res1;
vector<int> res2;
vector<vector<int>> mulThRes;
mutex mMutex;

bool isPrimeNumber(int num)
{
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0) return false;
    }
    return true;
}

void findPrimeNumberInSingleThread(int num)
{
    for (int i = 1; i <= num; i++)
    {
        if (isPrimeNumber(i)) res1.emplace_back(i);
    }
}

void findPrimeNumberInMultiThread(int i, int j, int index)
{
    cout << "find prime numbers from " << i << " to " << j << endl;
    
    for (int k = i; k <= j; k++)
    {
        if (isPrimeNumber(k)) 
        {
            mulThRes[index].emplace_back(k);
        }
    }
}

void findPrimeNumber(int num, bool usingMultiThread)
{
    if (!usingMultiThread)
    {
        cout << "find prime number using single thread" << endl;
        thread t1(&findPrimeNumberInSingleThread, num);
        t1.join();
    }
    else
    {
        cout << "find prime number using multi thread" << endl;

        // const unsigned int numOfThreads = thread::hardware_concurrency();
        int numOfThreads = 8;
        int range = num / numOfThreads;

        vector<thread> ths(numOfThreads);

        mulThRes.resize(numOfThreads);

        int st = 1;
        for (int i = 0; i < numOfThreads - 1; i++)
        {
            ths[i] = thread(&findPrimeNumberInMultiThread, st, st + range, i);
            st = st + range + 1;
        }
        ths[numOfThreads - 1] = thread(&findPrimeNumberInMultiThread, st, num, numOfThreads - 1);
        
        //for_each(ths.begin(), ths.end(), mem_fn(&thread::join));
        for (auto& th : ths)
        {
            th.join();
        }

        for (const auto& res: mulThRes)
        {
            for (int i = 0; i < res.size(); i++)
            {
                res2.emplace_back(res[i]);
            }
        }

    }

}

int main()
{
    int n = 12345678;

    auto t_start = std::chrono::high_resolution_clock::now();
    findPrimeNumber(n, false);
    auto t_end = std::chrono::high_resolution_clock::now();

    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    cout << "Time! Duration: " << elapsed_time_ms << "ms" << endl;
    cout << "Total prime number: " << res1.size() << " , The last prime is: " << res1[res1.size() - 1]<< endl;


    t_start = std::chrono::high_resolution_clock::now();
    findPrimeNumber(n, true);
    t_end = std::chrono::high_resolution_clock::now();

    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    cout << "Time! Duration: " << elapsed_time_ms << "ms" << endl;
    cout << "Total prime number: " << res2.size() << " , The last prime is: " << res2[res2.size() - 1]<< endl;

    return 0;
}
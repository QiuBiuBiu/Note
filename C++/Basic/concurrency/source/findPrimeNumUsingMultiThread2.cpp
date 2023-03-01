#include <iostream>
#include <vector>
#include <thread>
#include <fstream>
#include <math.h>

using namespace std;

class Prime
{
private:
    int **primes;
    int N;

public:
    Prime(int N)
    {
        this->N = N;

        primes = new int *[N];

        for(int i=0; i < N; i++)
            primes[i] = new int[2],
            primes[i][0] = i,
            primes[i][1] = 1; // mark all as prime numbers
    }
    void eliminate(int p)
    {
        int i = p + p;
        while (i < N)
            primes[i][1] = 0, // mark the multiplicies of p as not primes 
            i += p;
    }
    void display()
    {
        for (int i = 1; i < N; i++)
        {
            if (primes[i][1] == 1)
                cout << primes[i][0] << " " ;

            if (i % 10 == 0) cout << endl;
        }
        cout << endl;
    }
    // void save(string file)
    // {
    //     ofstream fout(file);

    //     if(fout.is_open())
    //         {
    //             for(int i=1;i<N;i++)
    //                 {
    //                     if (primes[i][1] == 1)
    //                         fout<<primes[i][0]<<" " ;

    //                     if(i%10 == 0) fout<<endl;
    //                 }
    //             fout<<endl;

    //         fout.close();    
    //         }

    //     else
    //         cout<<"cannot open file "<<file;
    // }
};

int main()
{
    vector<thread> v;

    int N;
    cout<<"genereate primes numbers less than N = ";
    cin >> N;

    Prime p(N);

    for(int i= 2; i < sqrt(N) ; i++)
        //p.eliminate(i);
        v.push_back( thread (&Prime::eliminate, ref(p), i ) );

    for (auto& th : v) th.join();    

    //p.display();
    //p.save("primes.txt");

    return 0;
}
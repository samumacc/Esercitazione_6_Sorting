#include <iostream>
#include <chrono>
#include <unistd.h>
#include<vector>
#include <algorithm>
#include <sstream>
#include "SortingAlgorithm.hpp"

using namespace std;

template<typename T>
double durataBubble(vector<T>& data)
{
    chrono::steady_clock::time_point t_inizio=chrono::steady_clock::now();
    SortLibrary::BubbleSort(data);
    chrono::steady_clock::time_point t_fine=chrono::steady_clock::now();
    double time=chrono::duration_cast<chrono::nanoseconds>(t_fine-t_inizio).count();
    return time;

}

template<typename T>
double durataMerge(vector<T>& data)
{
    chrono::steady_clock::time_point t_inizio=chrono::steady_clock::now();
    SortLibrary::MergeSort(data);
    chrono::steady_clock::time_point t_fine=chrono::steady_clock::now();
    double time=chrono::duration_cast<chrono::nanoseconds>(t_fine-t_inizio).count();
    return time;
}


int main(int k, char **a)
{
    stringstream s;
    s<<a[1];
    int b;
    s>>b;
    cout<<b;


    //Test 1: vettore ordinato

    int rep = 10;
    vector<int> v(b);
    vector<int> v1(b);
    int n=0;
    generate(v.begin(), v.end(), [&n] () {return n++;}); //creo vettore partendo dall'inizio con numeri tutti diversi
    double sumB=0;
    double sumM=0;
    for (unsigned int i=0; i<rep; i++)
    {
        sumB=sumB+durataBubble(v);
        sumM=sumM+durataMerge(v);
    }
    double timeB=sumB/rep;
    double timeM=sumM/rep;
    cout << "vettori ordinati:"<<endl;
    cout << "con Bubble -->" << timeB << endl << "con Merge -->" << timeM <<endl;


    //Test 2: vettore decrescente

    sumB=0;
    sumM=0;
    for (unsigned int i=0; i<rep; i++)
    {
        n=b;
        generate(v.begin(), v.end(), [&n] () {return n--;});
        v1=v;
        sumB=sumB+durataBubble(v);
        sumM=sumM+durataMerge(v1);
    }
    timeB=sumB/rep;
    timeM=sumM/rep;
    cout<<"vettori decrescenti:"<<endl;
    cout<<"Bubble -->"<<timeB<<endl<<"Merge -->"<<timeM<<endl;


    // Test 3: vettore con primo terzo randomico

    sumB=0;
    sumM=0;
    for (unsigned int i=0; i<rep; i++)
    {
        n=0;
        generate(v.begin(), v.end(), [&n] () {return n++;});

        for (unsigned j=0; j<(b/3); j++)
        {
            v[j] =rand() % (3*b/2);
        }
        v1=v;
        sumB=sumB+durataBubble(v);
        sumM=sumM+durataMerge(v1);
    }
    timeB=sumB/rep;
    timeM=sumM/rep;

    cout<<"vettore con primo terzo random:"<<endl;
    cout<<"Bubble -->"<<timeB<<endl<<"Merge -->"<<timeM<<endl;


    //Test 4: metà randomici

    sumB=0;
    sumM=0;
    for (unsigned int i=0; i<rep; i++)
    {
        n=0;
        generate(v.begin(), v.end(), [&n] () {return n++;});

        for (unsigned j=0; j<b/2; j++)
        {
            v[j] =rand() % (3*b/2);
        }
        v1=v;
        sumB=sumB+durataBubble(v);
        sumM=sumM+durataMerge(v1);
    }
    timeB=sumB/rep;
    timeM=sumM/rep;
    cout<<"vettore metà casuale:"<<endl;
    cout<<"Bubble -->"<<timeB<<endl<<"Merge -->"<<timeM<<endl;


    //Test 5: vettore tutto randomico

    sumB=0;
    sumM=0;
    for (unsigned int i=0; i<rep; i++)
    {
        for (unsigned j=b; j>(b/3); --j)
        {
            v[j] =rand() % (3*b/2);
        }
        v1=v;
        sumB=sumB+durataBubble(v);
        sumM=sumM+durataMerge(v1);
    }
    timeB=sumB/rep;
    timeM=sumM/rep;
    cout<<"vettore tutto randomico:"<<endl;
    cout<<"Bubble -->"<<timeB<<endl<<"Merge -->"<<timeM<<endl;

    cout<<" Nel complesso, Merge è più veloce di Bubble a parte quando si utilizzano vettori che sono ordinati" << endl;

    return 0;
}

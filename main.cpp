//Liudmila Zyrianova
//CSCI 335
//10/28/2018
//Programming Assignment 2

#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "my_trees.h"


void Experiment (int N){

    std::vector<int> v;
    for (int i=0; i<N; ++i) v.push_back(i);

    int C = 3;
    for (int i=0; i<C; i++){
        std::random_shuffle ( v.begin(), v.end() );
    }


    std::chrono::steady_clock::time_point t1;
    std::chrono::steady_clock::time_point t2;

    //BST

    BSTcontainer<int> b;

    t1 = std::chrono::steady_clock::now();
    for (auto x : v) {
        b.Insert(x);
    }
    for (int i=0; i < v.size(); i=i+2) {
        b.Remove(v[i]);
    }
    t2 = std::chrono::steady_clock::now();
    std::cout<<"Time passed for BST with N = " << N <<" in ms is "<< std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()<<'\n';

    //AVL

    AVLcontainer<int> a;

    t1 = std::chrono::steady_clock::now();
    for (auto x : v) {
        a.Insert(x);
    }
    for (int i=0; i < v.size(); i=i+2) {
        a.Remove(v[i]);
    }
    t2 = std::chrono::steady_clock::now();
    std::cout<<"Time passed for AVL with N = " << N <<" in ms is "<<  std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()<<'\n';

}
int main(){

    Experiment(1000);
    Experiment(100000);
    Experiment(1000000);

    return 0;
}


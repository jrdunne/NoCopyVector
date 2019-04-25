#include "vector.h"
#include <cassert>
#include <string>
#include <iostream>

void test_push_back(){
    jrd::vector<size_t> veci;
    for (size_t i = 0; i < 100000; ++i){
        veci.push_back(i);
    }
    assert(veci.size() == 100000);

    jrd::vector<std::string> vecs;
    for (size_t i = 0; i < 10000; ++i){
        vecs.emplace_back("word thing" + std::to_string(i));
    }

    assert(vecs.size() == 10000);
}

void test_indexing(){
    jrd::vector<size_t> veci;
    for (size_t i = 0; i < 100000; ++i){
        veci.push_back(i);
    }

    for (size_t i = 0; i < 100000; ++i){
        assert(veci[i] == i);
    }
    assert(veci.size() == 100000);
    
    jrd::vector<std::string> vecs;
    for (size_t i = 0; i < 10000; ++i){
        vecs.emplace_back("word thing" + std::to_string(i));
    }

    for (size_t i = 0; i < 10000; ++i){
        assert(vecs[i] == "word thing" + std::to_string(i));
    }

    assert(vecs.size() == 10000);
}

int main(){

    test_push_back();
    test_indexing();


    return 0;
}


#include "vector.h"
#include <string>
#include <vector>
#include <iostream>
#include <deque>
#include <random>
#include <cassert>
#include <sys/time.h>

typedef unsigned long long timestamp_t;

static timestamp_t get_timestamp (){
    struct timeval now;
    gettimeofday (&now, NULL);
    return  static_cast<long long unsigned int>(now.tv_usec) + static_cast<timestamp_t>(now.tv_sec) * 1000000;
}

void test_runner(size_t num_iterations, size_t num_append);
void random_access(size_t num_iterations, size_t num_append);
void seq_access(size_t num_iterations, size_t num_append);
void iter_access(size_t num_iterations, size_t num_append);


void jrd_vec_size_t(size_t num_iterations, jrd::vector<size_t> & vec);
void jrd_vec_str(size_t num_iterations, jrd::vector<std::string> & vec);
void jrd_vec_random(size_t num_iterations, jrd::vector<size_t> & vec);
void jrd_vec_seq(size_t num_iterations, jrd::vector<size_t> & vec);
void jrd_vec_iter(size_t num_iterations, jrd::vector<size_t> & vec);

void std_vec_size_t(size_t num_iterations, std::vector<size_t> & vec);
void std_vec_str(size_t num_iterations, std::vector<std::string> & vec);
void std_vec_random(size_t num_iterations, std::vector<size_t> & vec);
void std_vec_seq(size_t num_iterations, std::vector<size_t> & vec);
void std_vec_iter(size_t num_iterations, std::vector<size_t> & vec);


void push_back_tests();
void random_access_tests();
void seq_access_tests();
void iter_access_tests();

int main(){
    srand(42);
    iter_access_tests();
    seq_access_tests();
    random_access_tests();
    push_back_tests();
}

void iter_access_tests(){
    std::cout << "iter 1000 times" << std::endl;
    iter_access(20, 1000);

    std::cout << "iter 10000 times" << std::endl;
    iter_access(20, 10000);

    std::cout << "iter 100000 times" << std::endl;
    iter_access(20, 100000);

    std::cout << "iter 200000 times" << std::endl;
    iter_access(20, 200000);

    std::cout << "iter 500000 times" << std::endl;
    iter_access(20, 500000);
}


void seq_access_tests(){
    std::cout << "seq 1000 times" << std::endl;
    seq_access(20, 1000);

    std::cout << "seq 10000 times" << std::endl;
    seq_access(20, 10000);

    std::cout << "seq 100000 times" << std::endl;
    seq_access(20, 100000);

    std::cout << "seq 200000 times" << std::endl;
    seq_access(20, 200000);

    std::cout << "seq 500000 times" << std::endl;
    seq_access(20, 500000);
}

void random_access_tests(){
    std::cout << "random 1000 times" << std::endl;
    random_access(20, 1000);

    std::cout << "random 10000 times" << std::endl;
    random_access(20, 10000);

    std::cout << "random 100000 times" << std::endl;
    random_access(20, 100000);

    std::cout << "random 200000 times" << std::endl;
    random_access(20, 200000);

    std::cout << "random 500000 times" << std::endl;
    random_access(20, 500000);
}

void push_back_tests(){
    std::cout << "push_back 1000 times" << std::endl;
    test_runner(20, 1000);

    std::cout << "push_back 10000 times" << std::endl;
    test_runner(20, 10000);

    std::cout << "push_back 100000 times" << std::endl;
    test_runner(20, 100000);

    std::cout << "push_back 200000 times" << std::endl;
    test_runner(20, 200000);

    std::cout << "push_back 500000 times" << std::endl;
    test_runner(20, 500000);
}


void random_access(size_t num_iterations, size_t num_append){
    timestamp_t t0;
    timestamp_t t1;
    
    long double total = 0.0;
    for (size_t i = 0; i < num_iterations; ++i){
        jrd::vector<size_t> vec;
        jrd_vec_size_t(num_append, vec);

        t0 = get_timestamp();
        jrd_vec_random(num_append, vec);
        t1 = get_timestamp();

        total += (t1 - t0);
    }

    long double secs = (total / num_iterations) / 1000000.0L;
    std::cout << "jrd::vector<size_t> [] took: " << secs << " seconds over " << num_iterations << " iterations" << std::endl;

    total = 0.0;
    for (size_t i = 0; i < num_iterations; ++i){
        std::vector<size_t> vec;
        std_vec_size_t(num_append, vec);

        t0 = get_timestamp();
        std_vec_random(num_append, vec);
        t1 = get_timestamp();

        total += (t1 - t0);
    }

    secs = (total / num_iterations) / 1000000.0L;
    std::cout << "std::vector<size_t> [] took: " << secs << " seconds over " << num_iterations << " iterations" << std::endl;
}


void iter_access(size_t num_iterations, size_t num_append){
    timestamp_t t0;
    timestamp_t t1;
    
    long double total = 0.0;
    for (size_t i = 0; i < num_iterations; ++i){
        jrd::vector<size_t> vec;
        jrd_vec_size_t(num_append, vec);

        t0 = get_timestamp();
        jrd_vec_iter(num_append, vec);
        t1 = get_timestamp();

        total += (t1 - t0);
    }

    long double secs = (total / num_iterations) / 1000000.0L;
    std::cout << "jrd::vector<size_t> iter took: " << secs << " seconds over " << num_iterations << " iterations" << std::endl;

    total = 0.0;
    for (size_t i = 0; i < num_iterations; ++i){
        std::vector<size_t> vec;
        std_vec_size_t(num_append, vec);

        t0 = get_timestamp();
        std_vec_iter(num_append, vec);
        t1 = get_timestamp();

        total += (t1 - t0);
    }

    secs = (total / num_iterations) / 1000000.0L;
    std::cout << "std::vector<size_t> iter took: " << secs << " seconds over " << num_iterations << " iterations" << std::endl;
}


void seq_access(size_t num_iterations, size_t num_append){
    timestamp_t t0;
    timestamp_t t1;
    
    long double total = 0.0;
    for (size_t i = 0; i < num_iterations; ++i){
        jrd::vector<size_t> vec;
        jrd_vec_size_t(num_append, vec);

        t0 = get_timestamp();
        jrd_vec_seq(num_append, vec);
        t1 = get_timestamp();

        total += (t1 - t0);
    }

    long double secs = (total / num_iterations) / 1000000.0L;
    std::cout << "jrd::vector<size_t> seq [] took: " << secs << " seconds over " << num_iterations << " iterations" << std::endl;

    total = 0.0;
    for (size_t i = 0; i < num_iterations; ++i){
        std::vector<size_t> vec;
        std_vec_size_t(num_append, vec);

        t0 = get_timestamp();
        std_vec_seq(num_append, vec);
        t1 = get_timestamp();

        total += (t1 - t0);
    }

    secs = (total / num_iterations) / 1000000.0L;
    std::cout << "std::vector<size_t> seq [] took: " << secs << " seconds over " << num_iterations << " iterations" << std::endl;
}

void test_runner(size_t num_iterations, size_t num_append){
    timestamp_t t0;
    timestamp_t t1;
    
    long double total = 0.0;
    for (size_t i = 0; i < num_iterations; ++i){
        jrd::vector<size_t> vec;
        t0 = get_timestamp();
        jrd_vec_size_t(num_append, vec);
        t1 = get_timestamp();
        total += (t1 - t0);
    }

    long double secs = (total / num_iterations) / 1000000.0L;
    std::cout << "jrd::vector<size_t> took: " << secs << " seconds over " << num_iterations << " iterations" << std::endl;

    total = 0.0;
    for (size_t i = 0; i < num_iterations; ++i){
        std::vector<size_t> vec;
        t0 = get_timestamp();
        std_vec_size_t(num_append, vec);
        t1 = get_timestamp();
        total += (t1 - t0);
    }

    secs = (total / num_iterations) / 1000000.0L;
    std::cout << "std::vector<size_t> took: " << secs << " seconds over " << num_iterations << " iterations" << std::endl;

    total = 0.0;
    for (size_t i = 0; i < num_iterations; ++i){
        jrd::vector<std::string> vec;
        t0 = get_timestamp();
        jrd_vec_str(num_append, vec);
        t1 = get_timestamp();
        total += (t1 - t0);
    }

    secs = (total / num_iterations) / 1000000.0L;
    std::cout << "jrd::vector<string> took: " << secs << " seconds over " << num_iterations << " iterations" << std::endl;

    total = 0.0;
    for (size_t i = 0; i < num_iterations; ++i){
        std::vector<std::string> vec;
        t0 = get_timestamp();
        std_vec_str(num_append, vec);
        t1 = get_timestamp();
        total += (t1 - t0);
    }

    secs = (total / num_iterations) / 1000000.0L;
    std::cout << "std::vector<string> took: " << secs << " seconds over " << num_iterations << " iterations" << std::endl;

}

void jrd_vec_size_t(size_t num_iterations, jrd::vector<size_t> & vec){
    for (size_t i = 0; i < num_iterations; ++i){
        vec.push_back(i);
    }
}
void jrd_vec_str(size_t num_iterations, jrd::vector<std::string> & vec){
    for (size_t i = 0; i < num_iterations; ++i){
        vec.push_back("some string " + std::to_string(i));
    }
}

void std_vec_size_t(size_t num_iterations, std::vector<size_t> & vec){
    for (size_t i = 0; i < num_iterations; ++i){
        vec.push_back(i);
    }
}
void std_vec_str(size_t num_iterations, std::vector<std::string> & vec){
    for (size_t i = 0; i < num_iterations; ++i){
        vec.push_back("some string " + std::to_string(i));
    }
}



void jrd_vec_random(size_t num_iterations, jrd::vector<size_t> & vec){
     for (size_t i = 0; i < num_iterations; ++i){
         auto j = vec[static_cast<size_t>(rand()) % num_iterations];
         vec[i] = j;
     }
}

void std_vec_random(size_t num_iterations, std::vector<size_t> & vec){
     for (size_t i = 0; i < num_iterations; ++i){
         auto j = vec[static_cast<size_t>(rand()) % num_iterations];
         vec[i] = j;
     }
}


void jrd_vec_seq(size_t num_iterations, jrd::vector<size_t> & vec){
     for (size_t i = 0; i < num_iterations; ++i){
         auto j = vec[i];
         vec[i] = j;
     }
}

void std_vec_seq(size_t num_iterations, std::vector<size_t> & vec){
     for (size_t i = 0; i < num_iterations; ++i){
         auto j = vec[i];
         vec[i] = j;
     }
}

void jrd_vec_iter(size_t num_iterations, jrd::vector<size_t> & vec){
    // TODO
     for (size_t i = 0; i < num_iterations; ++i){
         auto j = vec[i];
         vec[i] = j;
     }
}

void std_vec_iter(size_t num_iterations, std::vector<size_t> & vec){
    // TODO
     for (size_t i = 0; i < num_iterations; ++i){
         auto j = vec[i];
         vec[i] = j;
     }
}


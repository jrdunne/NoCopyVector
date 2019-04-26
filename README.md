# WIP Vector 

A vector class that does not copy data on resize at the cost of almost all performance metrics.

# Why
This vector does beat the STL allocations by a small amount for push_back(T)!

This means very little as it is practically unusable otherwise. 

# How
The initial size of the vector is 16 and when the space is full is allocates a new array of size 16*2. It does not copy when this happens it instead begins writing index 16 to 47 to the new array.

Accessing a random index is done using the following equations for block, ie. which array the index is in, and offset, the index into the array at block.

for vector[index]

vector[index] == blocks[block].data[offset]

block = log2(index) - (log2(initial_size) - 1)

offset = index - blocks[block].size // size of the array at the index



## Test file output
Output from test file on my laptop with gcc -O3

random 10000 times

jrd::vector<size_t> [] took: 0.00041135 seconds over 20 iterations 

std::vector<size_t> [] took: 0.00015795 seconds over 20 iterations 

random 100000 times 

jrd::vector<size_t> [] took: 0.0047554 seconds over 20 iterations 

std::vector<size_t> [] took: 0.0015667 seconds over 20 iterations 

random 200000 times

jrd::vector<size_t> [] took: 0.0098468 seconds over 20 iterations

std::vector<size_t> [] took: 0.0031346 seconds over 20 iterations

random 500000 times

jrd::vector<size_t> [] took: 0.0322224 seconds over 20 iterations

std::vector<size_t> [] took: 0.0104358 seconds over 20 iterations

push_back 1000 times

jrd::vector<size_t> took: 2.9e-06 seconds over 20 iterations

std::vector<size_t> took: 3.2e-06 seconds over 20 iterations

jrd::vector<string> took: 8.445e-05 seconds over 20 iterations

std::vector<string> took: 8.75e-05 seconds over 20 iterations

push_back 10000 times

jrd::vector<size_t> took: 2.195e-05 seconds over 20 iterations

std::vector<size_t> took: 4.275e-05 seconds over 20 iterations

jrd::vector<string> took: 0.00136665 seconds over 20 iterations

std::vector<string> took: 0.00114525 seconds over 20 iterations

push_back 100000 times

jrd::vector<size_t> took: 0.00019505 seconds over 20 iterations

std::vector<size_t> took: 0.00036845 seconds over 20 iterations

jrd::vector<string> took: 0.0291261 seconds over 20 iterations

std::vector<string> took: 0.0262681 seconds over 20 iterations

push_back 200000 times

jrd::vector<size_t> took: 0.00048395 seconds over 20 iterations

std::vector<size_t> took: 0.00078575 seconds over 20 iterations

jrd::vector<string> took: 0.0604088 seconds over 20 iterations

std::vector<string> took: 0.0527071 seconds over 20 iterations

push_back 500000 times

jrd::vector<size_t> took: 0.00126895 seconds over 20 iterations

std::vector<size_t> took: 0.0019747 seconds over 20 iterations

jrd::vector<string> took: 0.144453 seconds over 20 iterations

std::vector<string> took: 0.129929 seconds over 20 iterations


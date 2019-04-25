#ifndef _JRD_VECTOR_H
#define _JRD_VECTOR_H

#include <cstddef>
#include <cstring>
#include <utility>
#include <iterator>
#include <stdexcept>
#include <cmath>
#include <vector>


/*
 * 
 * The goal of this vector implementation is to provide
 * faster inserts and avoid copies on reallocations
 * I accomplish this by using a vector of pointers to array that grow
 * by powers of two when the existing storage fills up
 * 
 * random access O(1) block = floor(log(i)), block index = i % floor(log(i))
 * No reallocations happen ever at expense of code complexity
 * 
 */



/*
    ! insert/erase should not be used on a vector so I will not implement them
    ! also < <= > >= are too special use case for a container 
*/


namespace jrd{

template <typename T>
class vector {
    public:
        typedef T                                     value_type;
        typedef T &                                   reference;
        typedef const T &                             const_reference;
        typedef T *                                   pointer;
        typedef const T *                             const_pointer;
        typedef T *                                   iterator;
        typedef const T *                             const_iterator;
        typedef std::reverse_iterator<iterator>       reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef ptrdiff_t                             difference_type;
        typedef size_t                                size_type;

        vector() noexcept;
        explicit vector(size_type n);
        vector(size_type n, const T &val);
        vector(typename vector<T>::iterator first, typename vector<T>::iterator last);
        vector(std::initializer_list<T>);
        vector(const vector<T> &);
        vector(vector<T> &&) noexcept;
        ~vector();
        vector<T> & operator = (const vector<T> &);
        vector<T> & operator = (vector<T> &&);
        vector<T> & operator = (std::initializer_list<T>);


        iterator begin() noexcept;
        const_iterator cbegin() const noexcept;
        iterator end() noexcept;
        const_iterator cend() const noexcept;
        reverse_iterator rbegin() noexcept;
        const_reverse_iterator crbegin() const noexcept;
        reverse_iterator rend() noexcept;
        const_reverse_iterator crend() const noexcept;


        bool empty() const noexcept;
        size_type size() const noexcept;
        size_type capacity() const noexcept;
        void resize(size_type);
        void resize(size_type, const T &);
        void reserve(size_type);
        void shrink_to_fit();


        reference operator [](size_type);
        const_reference operator [](size_type) const;
        reference at(size_type);
        const_reference at(size_type) const;
        reference front();
        const_reference front() const;
        reference back();
        const_reference back() const;


        template <class ... Args> 
        inline void emplace_back(Args && ... args);
        inline void push_back(const T &);
        inline void push_back(T &&);
        void pop_back();


        void swap(vector<T> &);
        void clear() noexcept;

        bool operator == (const vector<T> &) const;
        bool operator != (const vector<T> &) const;
    private:
        struct block_type{
            block_type() noexcept;
            ~block_type();
            block_type(const size_type in_size);
            block_type(const T * in_data, const size_type in_size) noexcept;
            block_type(const block_type & other) = delete;
            block_type(block_type && other) noexcept;
            block_type & operator=(const block_type & other) = delete;
            block_type & operator=(block_type && other) noexcept;

            T * data;
            size_type size;
        };

        static constexpr size_type initial_size = 16;
        static constexpr size_type log_offset = static_cast<size_type>(log2(static_cast<float>(initial_size))) - 1;
        static constexpr size_type growth_factor = 2;


        size_type num_elements = 0;
        size_type next_free_index = 0;

        std::vector<block_type> blocks;

        inline void allocate_new_block();
};


template <typename T>
vector<T>::vector() noexcept : blocks(){
    blocks.emplace_back(initial_size);
}

template <typename T>
vector<T>::vector(typename vector<T>::size_type n) {
}

template <typename T>
vector<T>::vector(typename vector<T>::size_type n, const T &value) {
    // TODO
}

template <typename T>
vector<T>::vector(vector<T>::iterator first, vector<T>::iterator last) {
    while(first != last){
        push_back(*first);
        ++first;
    }
}

template <typename T>
vector<T>::vector(std::initializer_list<T> lst) {
    // TODO
}

template <typename T>
vector<T>::vector(const vector<T> &other) {
    *this = other;
}

template <typename T>
vector<T>::vector(vector<T> &&other) noexcept {
    *this = other;
}

template <typename T>
vector<T>::~vector() {
    // should run block_type dtor and clean up memory
    blocks.clear();
}

template <typename T>
vector<T> & vector<T>::operator = (const vector<T> &other) {
    // TODO
    return *this;
}

template <typename T>
vector<T> & vector<T>::operator = (vector<T> &&other) {
    // TODO
    return *this;
}

template <typename T>
vector<T> & vector<T>::operator = (std::initializer_list<T> lst) {
    // TODO
    return *this;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() noexcept {
    return 0x0;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cbegin() const noexcept {
    return 0x0;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() noexcept {
    return iterator(blocks.back().data[next_free_index]);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cend() const noexcept {
    return 0x0;
}

template <typename T>
typename vector<T>::reverse_iterator vector<T>::rbegin() noexcept {
    return reverse_iterator();
}

template <typename T>
typename vector<T>::const_reverse_iterator vector<T>::crbegin() const noexcept {
    return reverse_iterator();
}

template <typename T>
typename vector<T>::reverse_iterator vector<T>::rend() noexcept {
    return reverse_iterator();
}

template <typename T>
typename vector<T>::const_reverse_iterator vector<T>::crend() const noexcept {
    return reverse_iterator();
}

template <typename T>
bool vector<T>::empty() const noexcept {
    return num_elements == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const noexcept{
    return num_elements;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const noexcept {
    if (blocks.size() == 0) return 0;
    return (num_elements - next_free_index) + blocks.back().size;
}

template <typename T>
void vector<T>::resize(typename vector<T>::size_type sz) {
    // TODO
}

template <typename T>
void vector<T>::resize(typename vector<T>::size_type sz, const T &c) {
    // TODO
}

template <typename T>
void vector<T>::reserve(typename vector<T>::size_type _sz) {
    // TODO
}

template <typename T>
void vector<T>::shrink_to_fit() {
    // TODO
}

template <typename T>
typename vector<T>::reference vector<T>::operator [](typename vector<T>::size_type idx) {
    if (num_elements == 0 || idx >= num_elements) throw std::out_of_range("index out of range");
    size_type block = 0;
    size_type offset = idx;
    if (idx >= initial_size){
        block = static_cast<size_type>(log2(static_cast<double>(idx))) - log_offset;
        offset = idx - blocks[block].size;
    }
    return blocks[block].data[offset];  
}

template <typename T>
typename vector<T>::const_reference vector<T>::operator [](typename vector<T>::size_type idx) const {
    if (num_elements == 0 || idx >= num_elements) throw std::out_of_range("index out of range");
    size_type block = 0;
    size_type offset = idx;
    if (idx >= initial_size){
        block = static_cast<size_type>(log2(static_cast<double>(idx))) - log_offset;
        offset = idx - blocks[block].size;
    }
    return blocks[block].data[offset];  
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
    if (num_elements == 0 || pos >= num_elements) throw std::out_of_range("index out of range");
    size_type block = 0;
    size_type offset = pos;
    if (pos >= initial_size){
        block = static_cast<size_type>(log2(static_cast<double>(pos))) - log_offset;
        offset = pos - blocks[block].size;
    }
    return blocks[block].data[offset];  
}

template <typename T>
typename vector<T>::const_reference vector<T>::at(size_type pos) const {
    if (num_elements == 0 || pos >= num_elements) throw std::out_of_range("index out of range");
    size_type block = 0;
    size_type offset = pos;
    if (pos >= initial_size){
        block = static_cast<size_type>(log2(static_cast<double>(pos))) - log_offset;
        offset = pos - blocks[block].size;
    }
    return blocks[block].data[offset];  
}

template <typename T>
typename vector<T>::reference vector<T>::front() {
    if (blocks.size() == 0) throw std::out_of_range("no elements in jrd::vector");
    return blocks[0].data[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
    if (blocks.size() == 0) throw std::out_of_range("no elements in jrd::vector");
    return blocks[0].data[0];
}

template <typename T>
typename vector<T>::reference vector<T>::back() {
    // TODO 
    if (blocks.size() == 0) throw std::out_of_range("no elements in jrd::vector");
    throw std::runtime_error(" NOT IMPLEMENTED ");
    return blocks[0].data[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
    // TODO 
    if (blocks.size() == 0) throw std::out_of_range("no elements in jrd::vector");
    throw std::runtime_error(" NOT IMPLEMENTED ");
    return blocks[0].data[0];
}

template <typename T>
template <class ... Args>
inline void vector<T>::emplace_back(Args && ... args) {
    if (next_free_index == blocks.back().size) allocate_new_block();
    blocks.back().data[next_free_index++] = std::move( T( std::forward<Args>(args) ... ) );
    ++num_elements;
}

template <typename T>
inline void vector<T>::push_back(const T &val) {
    if (next_free_index == blocks.back().size) allocate_new_block();
    blocks.back().data[next_free_index++] = val;
    ++num_elements;
}

template <typename T>
inline void vector<T>::push_back(T &&val) {
    if (next_free_index == blocks.back().size) allocate_new_block();
    blocks.back().data[next_free_index++] = val;
    ++num_elements;
}

template <typename T>
void vector<T>::pop_back() {
    // TODO 
}

template <typename T>
void vector<T>::swap(vector<T> &rhs) {
    // TODO 
}

template <typename T>
void vector<T>::clear() noexcept {
    // TODO 
    blocks.clear();
    next_free_index = 0;
    num_elements = 0;
}

template <typename T>
void vector<T>::allocate_new_block(){
    if (blocks.size() == 1){
        blocks.emplace_back(initial_size);
    }else{
        blocks.emplace_back(blocks.back().size * growth_factor);
    }
    next_free_index = 0;
}

/* 
 *
 * vector boolean operators
 * 
 */

template <typename T>
bool vector<T>::operator == (const vector<T> &rhs) const {
    return true;
}

template <typename T>
bool vector<T>::operator != (const vector<T> &rhs) const {
    return false;
}


/* 
 * 
 * block_type member functions
 * 
 */

template <typename T>
vector<T>::block_type::~block_type(){
    if (data != nullptr) delete[] data;
}

template <typename T>
vector<T>::block_type::block_type() noexcept : data(nullptr), size(0) {}

template <typename T>
vector<T>::block_type::block_type(const size_type in_size) : data(new T[in_size]), size(in_size){}

template <typename T>
vector<T>::block_type::block_type(const T * in_data, const size_type in_size) noexcept : data(in_data), size(in_size) {}

template <typename T>
vector<T>::block_type::block_type(vector<T>::block_type && other) noexcept : data(other.data), size(other.size) {
    other.data = nullptr;
    other.size = 0;
}

template <typename T>
typename vector<T>::block_type & vector<T>::block_type::operator=(block_type && other) noexcept {
    if (this != &other) {
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
    } 
    return *this;
}


} // namespace jd

#endif

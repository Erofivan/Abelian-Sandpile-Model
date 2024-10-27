#include <iostream>

#include <initializer_list.h>

template <typename T>
class vector {
private:
    T* data; //pointer to an array
    size_t vector_size;
    size_t vector_capacity;

    void resize_private(size_t new_vector_capacity) {
        T* new_data = new T[new_vector_capacity]; //allocating a new array
        for (size_t i = 0; i < vector_size; ++i) {
            new_data[i] = data[i]; //copying an array
        }
        delete [] data; //erase old array
        data = new_data; //changing pointer to an array
        vector_capacity = new_vector_capacity; //changing vector capacity
    }
public:
    //default constructor
    vector(): vector_size(0), vector_capacity(1) {
        data = new T[vector_capacity];
    }


    //constructor with initializer
    vector(std::initializer_list<T> init): vector() {
        for (const auto& item : init) {
            push_back(item);
        }
    }


    //constructor with = initializer
    vector<T>& operator=(std::initializer_list<T> init) {
        delete [] data;
        vector_size = 0;
        vector_capacity = init.size();
        data = new T[vector_capacity];

        for (const auto& item : init) {
            push_back(item);
        }
        return *this;
    }
    

    //constuctor that initializer n element with value m
    vector(size_t n, const T& value = T()): vector() {
        resize_private(n);
        for (size_t i = 0; i < n; ++i) {
            data[i] = value;
        }
        vector_size = n;
    }


    //destructor
    ~vector() {
        delete [] data;
    }


    void push_back(const T& value) {
        if (vector_size == vector_capacity) {
            resize_private(vector_capacity * 2);
        } 
        data[vector_size++] = value;
    }


    void pop_back() {
        if (vector_size > 0) {
            --vector_size;
        } else {
            std::cerr << "vector::cannot_pop_back_empty_vector";
        }
    }


    T* begin() const {
        return data;
    }


    T* end() const {
        return data+vector_size;
    }


    size_t size() const {
        return vector_size;
    }


    size_t capacity() const {
        return vector_capacity;
    }


    bool empty() const {
        return vector_size == 0;
    }


    void clear() {
        vector_size = 0;
    }


    void shrink_to_fit() {
        if (vector_size < vector_capacity) {
            resize_private(vector_size);
        } 
    }


    void resize(size_t new_vector_size, const T& default_value = T()) {
        //if resizes to bigger to next
        if (new_vector_size > vector_capacity) {
            resize_private(new_vector_size);
        }
        for (size_t i = vector_size; i < new_vector_size; ++i) {
            data[i] = default_value;
        }
        //skip to this if resizes to smaller
        vector_size = new_vector_size;
    }


    T& operator[](size_t index) const {
        if (index < vector_size) {
            return data[index];
        } 
        std::cerr << "vector::index_out_of_range";
    }
};

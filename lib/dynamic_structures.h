#pragma once

#include <iostream>
#include <initializer_list>
#include <utility>
#include <cstddef>
#include <type_traits>
#include <functional>
#include <fstream>
#include <cstdint>
#include <memory> // Для std::unique_ptr

// Forward declaration of classes
template <typename T> class list;
template <typename T> class vector;
class string;
template <typename T, typename Enable = void> struct HashSelector;
template <typename K, typename V, typename H = typename HashSelector<K>::type> class unordered_map;
template <typename T> class queue;

// Hash function structure for custom types
struct CoolHash {
    size_t operator()(const std::pair<int, int>& p) const;
    size_t operator()(string s) const;
};

// HashSelector struct for selecting hash functions
template <typename T, typename Enable>
struct HashSelector;

template <>
struct HashSelector<string> {
    using type = CoolHash;
};

template <>
struct HashSelector<std::pair<int, int>> {
    using type = CoolHash;
};

template <typename T>
struct HashSelector<T, typename std::enable_if<!(
    std::is_same<T, string>::value ||
    std::is_same<T, std::pair<int, int>>::value)>::type> {
    using type = std::hash<T>; 
};

// Declaration of all the classes
template <typename T> class list {
    // class definition
public:
    list(); // Constructor
    ~list(); // Destructor
    void push_back(const T& value);
    void push_front(const T& value);
    void pop_back();
    void pop_front();
    T& back();
    T& front();
    size_t size() const;
    bool empty() const;
    void clear();

private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(const T& value): data(value), next(nullptr), prev(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    size_t list_size;
};

// Now you should declare vector similarly
template <typename T> class vector {
public:
    vector(); // Constructor
    vector(std::initializer_list<T> init); // Initializer list constructor
    ~vector(); // Destructor
    void push_back(const T& value);
    void pop_back();
    size_t size() const;
    size_t capacity() const;
    bool empty() const;
    void clear();
    void shrink_to_fit();
    void resize(size_t new_vector_size, const T& default_value = T());

    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    T* begin() const;
    T* end() const;

private:
    T* data; // Pointer to elements
    size_t vector_size; // Current size
    size_t vector_capacity; // Allocated capacity
    void resize_private(size_t new_vector_capacity); // Private method
};

// String class declaration
class string {
public:
    string();
    string(const char* str);
    string(const string& other);
    string(string&& other) noexcept;
    ~string();

    string& operator=(const string& other);
    string& operator=(string&& other) noexcept;

    bool operator==(const string& other) const;
    string operator+(const string& other) const;

    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    size_t size() const;
    const char* c_str() const;

    string substr(size_t start, size_t len) const;
    size_t find(char ch) const;

private:
    char* data;
    size_t length;
};

template <typename K, typename V, typename H = typename HashSelector<K>::type>
class unordered_map {
public:
    unordered_map(size_t initial_bucket_count = 8);
    unordered_map(const unordered_map& other);
    ~unordered_map();
    
    void clear();
    bool empty() const;
    size_t size() const;
    size_t count(const K& key) const;
    void insert(const K& key, const V& value);
    void remove(const K& key);
    V& operator[](const K& key);
    
    class iterator {
        // iterator definition
    };

private:
    using BucketType = list<std::pair<K, V>>;
    BucketType* buckets;
    size_t bucket_count;
    size_t num_elements;
    H hasher;

    float load_factor() const;
    void rehash();
};

// Queue class declaration
template <typename T>
class queue {
public:
    queue();
    ~queue();
    T& front();
    T& back();
    void push(const T& value);
    void pop();
    bool empty() const;
    void clear();
    size_t size() const;

    class iterator {
        // iterator definition
    };

    iterator begin() const;
    iterator end() const;

private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t length;
};
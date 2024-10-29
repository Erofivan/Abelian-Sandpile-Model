#include "dynamic_structures.h"

// Implementation of the list class
template <typename T>
list<T>::list() : head(nullptr), tail(nullptr), list_size(0) {}

template <typename T>
list<T>::~list() {
    clear();
}

template <typename T>
void list<T>::push_back(const T& value) {
    Node* new_node = new Node(value);
    if (!head) {
        head = new_node;
        tail = head;
    } else {
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
    }
    ++list_size;
}

template <typename T>
void list<T>::push_front(const T& value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;
        tail = head;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    list_size++;
}

template <typename T>
void list<T>::pop_back() {
    if (list_size > 0) {
        Node* temp = tail;
        if (list_size == 1) {
            tail = nullptr;
            head = tail;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        --list_size;
    } else {
        std::cerr << "list::cannot_pop_back_empty_list";
        std::abort();
    }
}

template <typename T>
void list<T>::pop_front() {
    if (list_size > 0) {
        Node* temp = head;
        if (list_size == 1) {
            tail = nullptr;
            head = tail;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
        list_size--;
    } else {
        std::cerr << "list::cannot_pop_front_empty_list";
        std::abort();
    }
}

template <typename T>
T& list<T>::back() {
    if (list_size > 0) {
        return tail->data;
    } else {
        std::cerr << "list::cannot_get_back_of_empty_list";
        std::abort();
    }
}

template <typename T>
T& list<T>::front() {
    if (list_size > 0) {
        return head->data;
    } else {
        std::cerr << "list::cannot_get_front_of_empty_list";
        std::abort();
    }
}

template <typename T>
size_t list<T>::size() const {
    return list_size;
}

template <typename T>
bool list<T>::empty() const {
    return list_size == 0;
}

template <typename T>
void list<T>::clear() {
    while (!empty()) {
        pop_back();
    }
}

// Implementation of the vector class
template <typename T>
vector<T>::vector() : vector_size(0), vector_capacity(1) {
    data = new T[vector_capacity];
}

template <typename T>
vector<T>::vector(std::initializer_list<T> init) : vector() {
    for (const auto& item : init) {
        push_back(item);
    }
}

template <typename T>
vector<T>& vector<T>::operator=(std::initializer_list<T> init) {
    delete[] data;
    vector_size = 0;
    vector_capacity = init.size();
    data = new T[vector_capacity];
    for (const auto& item : init) {
        push_back(item);
    }
    return *this;
}

template <typename T>
vector<T>::vector(size_t n, const T& value) : vector() {
    resize_private(n);
    for (size_t i = 0; i < n; ++i) {
        data[i] = value;
    }
    vector_size = n;
}

template <typename T>
vector<T>::~vector() {
    delete[] data;
}

template <typename T>
void vector<T>::push_back(const T& value) {
    if (vector_size == vector_capacity) {
        resize_private(vector_capacity * 2);
    }
    data[vector_size++] = value;
}

template <typename T>
void vector<T>::pop_back() {
    if (vector_size > 0) {
        --vector_size;
    } else {
        std::cerr << "vector::cannot_pop_back_empty_vector" << std::endl;
        std::abort();
    }
}

template <typename T>
size_t vector<T>::size() const {
    return vector_size;
}

template <typename T>
size_t vector<T>::capacity() const {
    return vector_capacity;
}

template <typename T>
bool vector<T>::empty() const {
    return vector_size == 0;
}

template <typename T>
void vector<T>::clear() {
    vector_size = 0;
}

template <typename T>
void vector<T>::shrink_to_fit() {
    if (vector_size < vector_capacity) {
        resize_private(vector_size);
    }
}

template <typename T>
void vector<T>::resize(size_t new_vector_size, const T& default_value) {
    if (new_vector_size > vector_capacity) {
        resize_private(new_vector_size);
    }
    for (size_t i = vector_size; i < new_vector_size; ++i) {
        data[i] = default_value;
    }
    vector_size = new_vector_size;
}

template <typename T>
T& vector<T>::operator[](size_t index) {
    if (index < vector_size) {
        return data[index];
    } else {
        std::cerr << "vector::index_out_of_range" << std::endl;
        std::abort();
    }
}

template <typename T>
const T& vector<T>::operator[](size_t index) const {
    if (index < vector_size) {
        return data[index];
    } else {
        std::cerr << "vector::index_out_of_range" << std::endl;
        std::abort();
    }
}

template <typename T>
T* vector<T>::begin() const {
    return data;
}

template <typename T>
T* vector<T>::end() const {
    return data + vector_size;
}

// Implementation of the string class
string::string() : data(nullptr), length(0) {}

string::string(const char* str) {
    if (str) {
        length = 0;
        while (str[length] != '\0') {
            ++length;
        }
        data = new char[length + 1];
        for (size_t i = 0; i < length; ++i) {
            data[i] = str[i];
        }
        data[length] = '\0';
    } else {
        length = 0;
        data = nullptr;
    }
}

string::string(const string& other) {
    length = other.length;
    data = new char[length + 1];
    for (size_t i = 0; i < length; ++i) {
        data[i] = other.data[i];
    }
    data[length] = '\0';
}

string::string(string&& other) noexcept : data(other.data), length(other.length) {
    other.data = nullptr;
    other.length = 0;
}

string::~string() {
    delete[] data;
}

string& string::operator=(const string& other) {
    if (this != &other) {
        delete[] data;
        length = other.length;
        data = new char[length + 1];
        for (size_t i = 0; i < length; ++i) {
            data[i] = other.data[i];
        }
        data[length] = '\0';
    }
    return *this;
}

string& string::operator=(string&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        length = other.length;
        other.data = nullptr;
        other.length = 0;
    }
    return *this;
}

bool string::operator==(const string& other) const {
    if (length != other.length) return false;
    for (size_t i = 0; i < length; ++i) {
        if (data[i] != other.data[i]) return false;
    }
    return true;
}

string string::operator+(const string& other) const {
    string result;
    result.length = length + other.length;
    result.data = new char[result.length + 1];
    
    for (size_t i = 0; i < length; ++i) {
        result.data[i] = data[i]; 
    }
    for (size_t i = 0; i < other.length; ++i) {
        result.data[length + i] = other.data[i]; 
    }
    result.data[result.length] = '\0'; 

    return result;
}

char& string::operator[](size_t index) {
    return data[index];
}

const char& string::operator[](size_t index) const {
    return data[index];
}

size_t string::size() const { 
    return length;
}

const char* string::c_str() const { 
    return data ? data : ""; 
}

string string::substr(size_t start, size_t len) const {
    if (start >= length) {
        return string(); 
    }

    if (len >= start) {
        len = len - start;    
    }
    string result;
    result.length = len;
    result.data = new char[len + 1];
    for (size_t i = 0; i < len; ++i) {
        result.data[i] = data[start + i];
    }
    result.data[len] = '\0'; 

    return result;
}

size_t string::find(char ch) const {
    for (size_t i = 0; i < length; ++i) {
        if (data[i] == ch) {
            return i;
        }
    }
    return length;
}
// Implementation of CoolHash struct methods
size_t CoolHash::operator()(const std::pair<int, int>& p) const {
    auto h1 = std::hash<int>{}(p.first);
    auto h2 = std::hash<int>{}(p.second);
    return h1 ^ h2;
}

size_t CoolHash::operator()(string s) const {
    const size_t prime1 = 4583;
    const size_t prime2 = 9949;

    size_t hash1 = 0;
    size_t hash2 = 0;
    size_t length = s.size();

    for (size_t i = 0; i < length; ++i) {
        hash1 = hash1 * prime1 + static_cast<size_t>(s[i]);
    }

    for (size_t i = 0; i < length; ++i) {
        hash2 = hash2 * prime1 + static_cast<size_t>(s[i]);
    }

    return hash1 ^ (hash2 << 1);
}
// Implementation of the unordered_map class methods
template <typename K, typename V, typename H>
unordered_map<K, V, H>::unordered_map(size_t initial_bucket_count)
    : bucket_count(initial_bucket_count), num_elements(0), buckets(new BucketType[bucket_count]) {}

template <typename K, typename V, typename H>
unordered_map<K, V, H>::unordered_map(const unordered_map& other)
    : bucket_count(other.bucket_count), num_elements(other.num_elements), hasher(other.hasher) {
    buckets = new BucketType[bucket_count];
    for (size_t i = 0; i < bucket_count; ++i) {
        for (const auto& pair : other.buckets[i]) {
            buckets[i].push_back(pair);
        }
    }
}

template <typename K, typename V, typename H>
unordered_map<K, V, H>::~unordered_map() {
    clear();
    delete[] buckets;
}

template <typename K, typename V, typename H>
void unordered_map<K, V, H>::clear() {
    for (size_t i = 0; i < bucket_count; ++i) {
        buckets[i].clear();
    }
    num_elements = 0;
}

template <typename K, typename V, typename H>
bool unordered_map<K, V, H>::empty() const {
    return num_elements == 0;
}

template <typename K, typename V, typename H>
size_t unordered_map<K, V, H>::size() const {
    return num_elements;
}

template <typename K, typename V, typename H>
size_t unordered_map<K, V, H>::count(const K& key) const {
    size_t index = hasher(key) % bucket_count;
    for (const auto& pair : buckets[index]) {
        if (pair.first == key) {
            return 1;
        }
    }
    return 0;
}

template <typename K, typename V, typename H>
void unordered_map<K, V, H>::insert(const K& key, const V& value) {
    size_t index = hasher(key) % bucket_count;
    for (auto& pair : buckets[index]) {
        if (pair.first == key) {
            pair.second = value;
            return;
        }
    }
    buckets[index].push_back(std::make_pair(key, value));
    ++num_elements;

    if (load_factor() > 0.75) {
        rehash();
    }
}

template <typename K, typename V, typename H>
void unordered_map<K, V, H>::remove(const K& key) {
    size_t index = hasher(key) % bucket_count;
    auto& bucket = buckets[index];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->first == key) {
            bucket.erase(it);
            --num_elements;
            return;
        }
    }
}

template <typename K, typename V, typename H>
V& unordered_map<K, V, H>::operator[](const K& key) {
    size_t index = hasher(key) % bucket_count;
    for (auto& pair : buckets[index]) {
        if (pair.first == key) {
            return pair.second;
        }
    }
    buckets[index].push_back(std::make_pair(key, V()));
    ++num_elements;
    if (load_factor() > 0.75) {
        rehash();
        index = hasher(key) % bucket_count;
    }
    return buckets[index].back().second;
}

template <typename K, typename V, typename H>
typename unordered_map<K, V, H>::iterator unordered_map<K, V, H>::begin() {
    for (size_t i = 0; i < bucket_count; ++i) {
        if (!buckets[i].empty()) {
            return iterator(buckets, i, buckets[i].begin(), bucket_count);
        }
    }
    return end();
}

template <typename K, typename V, typename H>
typename unordered_map<K, V, H>::iterator unordered_map<K, V, H>::end() {
    return iterator(buckets, bucket_count, typename BucketType::iterator(), bucket_count);
}

// Queue class implementation
template <typename T>
queue<T>::queue() : head(nullptr), tail(nullptr), length(0) {}

template <typename T>
queue<T>::~queue() {
    clear();
}

template <typename T>
T& queue<T>::front() {
    if (head == nullptr) {
        std::cerr << "error: queue is empty" << std::endl;
        std::abort(); // Alternatively, you could throw an exception.
    }
    return head->data;
}

template <typename T>
T& queue<T>::back() {
    if (tail == nullptr) {
        std::cerr << "error: queue is empty" << std::endl;
        std::abort(); // Alternatively, you could throw an exception.
    }
    return tail->data;
}

template <typename T>
void queue<T>::push(const T& value) {
    Node* newNode = new Node(value);
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    ++length;
}

template <typename T>
void queue<T>::pop() {
    if (head == nullptr) {
        std::cerr << "error: queue is empty" << std::endl;
        std::abort(); // Alternatively, you could throw an exception.
    }
    Node* temp = head;
    head = head->next;
    if (head) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete temp;
    --length;
}

template <typename T>
bool queue<T>::empty() const {
    return length == 0;
}

template <typename T>
void queue<T>::clear() {
    while (length > 0) {
        pop();
    }
}

template <typename T>
size_t queue<T>::size() const {
    return length;
}

template <typename T>
typename queue<T>::iterator queue<T>::begin() const {
    return iterator(head);
}

template <typename T>
typename queue<T>::iterator queue<T>::end() const {
    return iterator(nullptr);
}
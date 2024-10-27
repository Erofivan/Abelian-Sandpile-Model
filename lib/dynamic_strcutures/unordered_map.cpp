#include <iostream>

template <typename T>
class list{
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


public:
    list(): head(nullptr), tail(nullptr), list_size(0) {}


    ~list() {
        clear();
    }


    void push_back(const T& value) {
        Node* new_node = new Node(value);
        if (!head) {
            tail = new_node;
            head = tail;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        ++list_size;
    }


    void push_front(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            tail = newNode;
            head = tail;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        list_size++;
    }


    void pop_back() {
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
        }
    }

    void pop_front() {
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
        }
    }


    T& back() {
        if (list_size > 0) {
            return tail->data;
        } else {
            std::cerr << "list::cannot_get_back_of_empty_list";
        }
    }


    T& front() {
        if (list_size > 0) {
            return head->data;
        } else {
            std::cerr << "list::cannot_get_front_of_empty_list";
        }
    }


    size_t size() const {
        return list_size;
    }


    bool empty() const {
        return list_size == 0;
    }


    void clear() {
        while (!empty()) {
            pop_back();
        }
    }


    //iterators
    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* node): current(node) {}


        T& operator*() {
            return current->data;
        }


        Iterator& operator++() { 
            if (current) {
                current = current->next;
            }
            return *this;
        }


        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    Iterator erase(Iterator pos) {
        if (pos.current == nullptr) {
            return end();
        }

        Node* to_delete = pos.current;

        if (to_delete == head) {
            head = head->next;
            if (head) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
        } 
        else if (to_delete == tail) {
            tail = tail->prev;
            if (tail) {
                tail->next = nullptr;
            } else {
                head = nullptr;
            }
        } else {
            Node* prev_node = to_delete->prev;
            Node* next_node = to_delete->next;
            prev_node->next = next_node;
            if (next_node) {
                next_node->prev = prev_node;
            }
        }

        delete to_delete;
        --list_size;

        return Iterator(head ? head : nullptr);
    }


    Iterator begin() {
        return Iterator(head);
    }


    Iterator end() {
        return Iterator(nullptr);
    }
};

template <typename T>
class initializer_list {
private:
    const T* data;
    size_t list_size;


public:
    initializer_list(const T* arr, size_t size): data(arr), list_size(size) {}


    const T& operator[](size_t index) const {
        if (index < list_size) {
            return data[index];
        }
    }


    size_t size() const {
        return size;
    }


    const T* begin() const {
        return data;
    }


    const T* end() const {
        return data + list_size;
    }
};

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

template <typename K, typename V, typename H = std::hash<K>>
class unordered_map {
public:
    using PairType = std::pair<K, V>;
    using BucketType = list<PairType>;

private:
    BucketType* buckets;      //list of buckets
    size_t bucket_count;      //number of buckets
    size_t num_elements;      //current amount of elements
    H hasher; 


    float load_factor() const {
        return static_cast<float>(num_elements) / bucket_count;
    }


    void rehash() {
        size_t new_bucket_count = bucket_count * 2;
        BucketType* new_buckets = new BucketType[new_bucket_count];

        for (size_t i = 0; i < bucket_count; ++i) {
            for (auto& pair : buckets[i]) {
                size_t new_index = hasher(pair.first) % new_bucket_count;
                new_buckets[new_index].push_back(pair);
            }
        }

        delete [] buckets;

        //update buckets
        buckets = new_buckets;
        bucket_count = new_bucket_count;
    }
public:
    unordered_map(size_t initial_bucket_count = 8) 
        : bucket_count(initial_bucket_count), num_elements(0) {
        buckets = new BucketType[bucket_count];
    }

    //copying constructor
    unordered_map(const unordered_map& other) 
    : bucket_count(other.bucket_count), 
      num_elements(other.num_elements), 
      hasher(other.hasher) {
        buckets = new BucketType[bucket_count];
        for (size_t i = 0; i < bucket_count; ++i) {
            for (const auto& pair : other.buckets[i]) {
                buckets[i].push_back(pair);
            }
        }
    }

    ~unordered_map() {
        clear();
        delete[] buckets;
    }

    void clear() {
        for (size_t i = 0; i < bucket_count; ++i) {
            buckets[i].clear();
        }
        num_elements = 0;
    }

    bool empty() const {
        return num_elements == 0;
    }

    size_t size() const {
        return num_elements;
    }

    size_t count(const K& key) const {
        size_t index = hasher(key) % bucket_count;
        for (const auto& pair : buckets[index]) {
            if (pair.first == key) {
                return 1;
            }
        }
        return 0;
    }

    void insert(const K& key, const V& value) {
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

    void remove(const K& key) {
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

    V& operator[](const K& key) {
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
        }
        return buckets[index].back().second;
    }

    BucketType* begin() {
        return buckets;
    }

     BucketType* end() {
        return buckets + bucket_count;
    }
};


int main() {
    list<int> l;
    l.push_back(3);
    l.erase(3);
}
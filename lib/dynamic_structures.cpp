#include <iostream>
#include <functional>
#include <type_traits>

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
            head = new_node;
            tail = head;
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
            head = newNode;
            tail = head;
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
            std::abort();
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
            std::abort();
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
    class iterator {
    private:
        Node* current;

    public:
        //constructor for ::iterator()
        iterator() : current(nullptr) {}

        iterator(Node* node): current(node) {}


        T& operator*() {
            return current->data;
        }


        iterator& operator++() { 
            if (current) {
                current = current->next;
            }
            return *this;
        }


        bool operator!=(const iterator& other) const {
            return current != other.current;
        }

        bool operator==(const iterator& other) const {
            return current == other.current;
        }

        Node* current_node() const {
            return current;
        }

        T* operator->() {
            return &current->data; 
        }
    };

    iterator erase(iterator pos) {
        if (pos.current_node() == nullptr) {
            return end(); 
        }

        Node* to_delete = pos.current_node();
        
        Node* next_node = to_delete->next;

        if (to_delete == head) {
            head = head->next;
            if (head) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
        } else if (to_delete == tail) {
            tail = tail->prev;
            if (tail) {
                tail->next = nullptr;
            } else {
                head = nullptr;
            }
        } else {
            Node* prev_node = to_delete->prev;
            prev_node->next = to_delete->next;
            if (next_node) {
                next_node->prev = prev_node;
            }
        }

        delete to_delete;
        --list_size;

        return iterator(next_node); 
    }




    iterator begin() {
        return iterator(head);
    }


    iterator end() {
        return iterator(nullptr);
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
            std::abort();
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
        std::abort();
    }
};

class string {
private:
    char* data;
    size_t length;

public:
    string(): data(nullptr), length(0) {}

    string(const char* str) {
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

    string(const string& other) {
        length = other.length;
        data = new char[length + 1];
        for (size_t i = 0; i < length; ++i) {
            data[i] = other.data[i];
        }
        data[length] = '\0';
    }

    string(string&& other) noexcept : data(other.data), length(other.length) {
        other.data = nullptr;
        other.length = 0;
    }

    ~string() {
        delete[] data;
    }

    string& operator=(const string& other) {
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

    string& operator=(string&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            length = other.length;
            other.data = nullptr;
            other.length = 0;
        }
        return *this;
    }

    bool operator==(const string& other) const {
        if (length != other.length) return false;
        for (size_t i = 0; i < length; ++i) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

     string operator+(const string& other) const {
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

    char& operator[](size_t index) {
        return data[index];
    }

    const char& operator[](size_t index) const {
        return data[index];
    }

    size_t size() const { 
        return length;
    }

    const char* c_str() const { 
        return data ? data : ""; 
    }

    string substr(size_t start, size_t len) const {
        if (start >= length) {
            return string(); 
        }

        if (start + len > length) {
            len = length - start;
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

    int find(char ch) const {
        for (size_t i = 0; i < length; ++i) {
            if (data[i] == ch) {
                return i;
            }
        }
        return -1;
    }

    friend std::istream& operator>>(std::istream& is, string& str);
    friend std::ostream& operator<<(std::ostream& os, const string& str);
};

std::ostream& operator<<(std::ostream& os, const string& str) {
    os << str.c_str();
    return os;
}

std::istream& operator>>(std::istream& is, string& str) {
    char buffer[str.length+1];

    is >> buffer;

    delete [] str.data;

    str.length = 0;
    while (buffer[str.length] != '\0') {
        ++str.length;
    }
    str.data = new char[str.length + 1];
    for (size_t i = 0; i < str.length; ++i) {
        str.data[i] = buffer[i];
    }
    str.data[str.length] = '\0';

    return is;
}

struct CoolHash{

    size_t operator()(string s) const {
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
};

template <typename T, typename Enable = void>
struct HashSelector;

template <>
struct HashSelector<string> {
    using type = CoolHash;
};

template<typename T>
struct HashSelector<T, typename std::enable_if<!std::is_same<T, string>::value>::type> {
    using type = std::hash<T>; 
};

template <typename K, typename V, typename H = typename HashSelector<K>::type>
class unordered_map {
public:
    typedef std::pair<K, V> PairType;
    typedef list<PairType> BucketType;

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
    class iterator {
    private:
        BucketType* buckets;
        size_t bucket_index;
        typename BucketType::iterator list_iterator;
        size_t total_buckets;

    public:
        iterator(BucketType* bs, size_t idx, 
        typename BucketType::iterator it, size_t total)
            : buckets(bs), bucket_index(idx), 
            list_iterator(it), total_buckets(total) {}

        PairType& operator*() {
            return *list_iterator;
        }

        iterator& operator++() {
            ++list_iterator;

            while (bucket_index < total_buckets 
            && list_iterator == buckets[bucket_index].end()) {
                ++bucket_index;
                if (bucket_index < total_buckets) {
                    list_iterator = buckets[bucket_index].begin();
                }
            }
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return bucket_index != other.bucket_index 
            || list_iterator != other.list_iterator;
        }

        bool operator==(const iterator& other) const {
            return bucket_index == other.bucket_index 
            && list_iterator == other.list_iterator;
        }
    };
    
    class const_iterator {
    private:
        const BucketType* buckets;
        size_t bucket_index;
        typename BucketType::const_iterator list_iterator;
        size_t total_buckets;

    public:
        const_iterator(const BucketType* bs, size_t idx, 
                       typename BucketType::const_iterator it, size_t total)
            : buckets(bs), bucket_index(idx), 
              list_iterator(it), total_buckets(total) {}

        const PairType& operator*() const {
            return *list_iterator;
        }

        const_iterator& operator++() {
            ++list_iterator;
            while (bucket_index < total_buckets 
                   && list_iterator == buckets[bucket_index].end()) {
                ++bucket_index;
                if (bucket_index < total_buckets) {
                    list_iterator = buckets[bucket_index].begin();
                }
            }
            return *this;
        }

        bool operator!=(const const_iterator& other) const {
            return bucket_index != other.bucket_index 
                   || list_iterator != other.list_iterator;
        }

        bool operator==(const const_iterator& other) const {
            return bucket_index == other.bucket_index 
                   && list_iterator == other.list_iterator;
        }
    };
    
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
            index = hasher(key) % bucket_count;
        }
        return buckets[index].back().second;;
    }

    iterator begin() {
        for (size_t i = 0; i < bucket_count; ++i) {
            if (!buckets[i].empty()) {
                return iterator(buckets, i, buckets[i].begin(), bucket_count);
            }
        }
        return end();
    }

    iterator end() {
        return iterator(buckets, bucket_count, 
        typename BucketType::iterator(), bucket_count);
    }

    const_iterator begin() const {
        for (size_t i = 0; i < bucket_count; ++i) {
            if (!buckets[i].empty()) {
                return const_iterator(buckets, i, buckets[i].cbegin(), bucket_count);
            }
        }
        return end();
    }

    const_iterator end() const {
        return const_iterator(buckets, bucket_count, 
                              typename BucketType::const_iterator(), bucket_count);
    }
};
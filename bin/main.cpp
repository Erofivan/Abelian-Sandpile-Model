#include <iostream>
#include <fstream>

//////////////////// Dynamic structures begin /////////////////////////

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

    class const_iterator {
    private:
        const Node* current;

    public:
        const_iterator() : current(nullptr) {}
        const_iterator(const Node* node) : current(node) {}

        const T& operator*() const {
            return current->data;
        }

        const_iterator& operator++() { 
            if (current) {
                current = current->next;
            }
            return *this;
        }

        bool operator!=(const const_iterator& other) const {
            return current != other.current;
        }

        bool operator==(const const_iterator& other) const {
            return current == other.current;
        }

        const Node* current_node() const {
            return current;
        }

        const T* operator->() const {
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

    const_iterator cbegin() const {
        return const_iterator(head);
    }

    const_iterator cend() const {
        return const_iterator(nullptr);
    }
};

#include <initializer_list>
template <typename T>
class vector {
private:
    T* data;
    size_t vector_size;
    size_t vector_capacity;

    void resize_private(size_t new_vector_capacity) {
        T* new_data = new T[new_vector_capacity];
        for (size_t i = 0; i < vector_size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        vector_capacity = new_vector_capacity;
    }

public:
    vector() : vector_size(0), vector_capacity(1) {
        data = new T[vector_capacity];
    }

    vector(std::initializer_list<T> init) : vector() {
        for (const auto& item : init) {
            push_back(item);
        }
    }

    vector<T>& operator=(std::initializer_list<T> init) {
        delete[] data;
        vector_size = 0;
        vector_capacity = init.size();
        data = new T[vector_capacity];
        for (const auto& item : init) {
            push_back(item);
        }
        return *this;
    }

    vector(size_t n, const T& value = T()) : vector() {
        resize_private(n);
        for (size_t i = 0; i < n; ++i) {
            data[i] = value;
        }
        vector_size = n;
    }

    ~vector() {
        delete[] data;
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
            std::cerr << "vector::cannot_pop_back_empty_vector" << std::endl;
            std::abort();
        }
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
        if (new_vector_size > vector_capacity) {
            resize_private(new_vector_size);
        }
        for (size_t i = vector_size; i < new_vector_size; ++i) {
            data[i] = default_value;
        }
        vector_size = new_vector_size;
    }

    T& operator[](size_t index) {
        if (index < vector_size) {
            return data[index];
        } else {
            std::cerr << "vector::index_out_of_range" << std::endl;
            std::abort();
        }
    }

    const T& operator[](size_t index) const {
        if (index < vector_size) {
            return data[index];
        } else {
            std::cerr << "vector::index_out_of_range" << std::endl;
            std::abort();
        }
    }

    T* begin() const {
        return data;
    }

    T* end() const {
        return data + vector_size;
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

    size_t find(char ch) const {
        for (size_t i = 0; i < length; ++i) {
            if (data[i] == ch) {
                return i;
            }
        }
        return length;
    }

    friend std::istream& operator>>(std::istream& is, string& str);
    friend std::ostream& operator<<(std::ostream& os, const string& str);
    friend std::istream& getline(std::istream& is, string& str);
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

std::istream& getline(std::istream& is, string& str) {
    delete[] str.data;
    str.data = nullptr;
    str.length = 0;

    char buffer[1024]; 
    is.getline(buffer, sizeof(buffer)); 

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

    size_t operator()(const std::pair<int, int>& p) const {
        auto h1 = std::hash<int>{}(p.first);
        auto h2 = std::hash<int>{}(p.second);
        return h1 ^ h2;
    }

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

template <>
struct HashSelector<std::pair<int,int>> {
    using type = CoolHash;
};

template<typename T>
struct HashSelector<T, typename std::enable_if<!(std::is_same<T, string>::value &&
                std::is_same<T, std::pair<int,int>>::value)>::type> {
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
                   && list_iterator == buckets[bucket_index].cend()) {
                ++bucket_index;
                if (bucket_index < total_buckets) {
                    list_iterator = buckets[bucket_index].cbegin();
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
                return const_iterator(buckets, i, 
                                      buckets[i].cbegin(), bucket_count);
            }
        }
        return end();
    }

    const_iterator end() const {
        return const_iterator(buckets, bucket_count, 
                              typename BucketType::const_iterator(), 
                              bucket_count);
    }
};

template <typename T>
class queue {
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

public:
    queue() : head(nullptr), tail(nullptr), length(0) {}

    ~queue() {
        while (length > 0) {
            pop();
        }
    }

    T& front() {
        if (head == nullptr) {
            std::cerr << "error: queue is empty" << std::endl;
        }
        return head->data;
    }

    T& back() {
        if (tail == nullptr) {
            std::cerr << "error: queue is empty" << std::endl;
        }
        return tail->data;
    }

    // void push_front(const T& value) {
    //     Node* newNode = new Node(value);
    //     if (head == nullptr) {
    //         head = tail = newNode;
    //     } else {
    //         newNode->next = head;
    //         head->prev = newNode;
    //         head = newNode;
    //     }
    //     ++length;
    // }

    void push(const T& value) {
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

    void pop() {
        if (head == nullptr) {
            std::cerr << "error: queue is empty" << std::endl;
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

    // void pop_back() {
    //     if (tail == nullptr) {
    //         std::cerr << "error: queue is empty" << std::endl;
    //     }
    //     Node* temp = tail;
    //     tail = tail->prev;
    //     if (tail) {
    //         tail->next = nullptr;
    //     } else {
    //         head = nullptr;
    //     }
    //     delete temp;
    //     --length;
    // }

    bool empty() const {
        return length == 0;
    }

    void clear() {
        while (length > 0) {
            pop();
        }
    }

    size_t size() const {
        return length;
    }

    class iterator {
    private:
        Node* current;

    public:
        iterator(Node* node) : current(node) {}

        T& operator*() const {
            return current->data;
        }

        iterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return current != other.current;
        }
    };

    iterator begin() const {
        return iterator(head);
    }

    iterator end() const {
        return iterator(nullptr);
    }
};
///////////////// Dynamic structures end////////////////////////////

/////////////////// Parser begin //////////////////////////

struct ArgValues{
    string input_path = nullptr;
    string output_path = nullptr;
    int max_iter = 1;
    int freq = 0;
    size_t max_option_size = 0;
};
int StringToInt(string str) {
    long long num = 0;
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9') {
            return -1;
        } else {
            int t = (int)(str[i]) - 48;
            num += t;
            num *= 10;
        }
        ++i;
    }
    num /= 10;
    return num;
}

bool DetectNumber(string s) {
    for (size_t i = 0; i < s.size(); ++i) {
        if (!('0' <= s[i] && s[i] <= '9')) return true;
    }
    return false;
}
void FillArgValues(ArgValues& arg_value, string key, string value) {
    if (key == "-o") {
        arg_value.output_path = value;
    } else if (key == "-i") {
        arg_value.input_path = value;
    } else if (key == "-m") {
        if (DetectNumber(value)) {
            std::cerr << "error: " << key << " expects a number";
            return;
        }
        arg_value.max_iter = StringToInt(value);
    } else if (key == "-f") {
        if (DetectNumber(value)) {
            std::cerr << "error: " << key << " expects a number";
            return;
        }
        arg_value.freq = StringToInt(value);
    }
}

bool ProcessCommand(const string arg, ArgValues& arg_values,
                    unordered_map<string, string>& valid_commands_list) {
    string cmd = arg.substr(0, arg.find('='));

    // Handling error arguments
    if (cmd.substr(0, 2) == "--" and cmd.size() == 2) {
        std::cerr << "error: unknown option " << arg << std::endl;
        return false; // Return if we found wrong option
    }

    if (cmd.substr(0, 1) == "-" and cmd.size() == 1) {
        std::cerr << "error: unknown option " << arg << std::endl;
        return false; // Return if we found wrong option
    }

    if (cmd.size() > arg_values.max_option_size || 
        valid_commands_list.count(cmd) == 0) {
        std::cerr << "error: unknown option " << arg << std::endl;
        return false; // Return if we found wrong option
    } else if (!(arg.substr(0,2) == "--") &&
        arg.find('=') != arg.size()) {
        std::cerr << "error: unknown option " << arg << std::endl;
        return false; // Return if we found wrong option
    }

    // Handling dublicated agruments
    if (!(valid_commands_list[cmd] == nullptr) &&
        arg.substr(0, 2) == "--") {
        std::cerr << "error: repetition of an argument " 
                  << cmd << std::endl;
        return false; // Return if we found dublicated option
    }


    // Make flags for arguments that we already handled
    // Set flag that we already handled this type of argument
    string cmd_value = arg.substr(arg.find('=')+1, arg.size());
    if (arg.substr(0, 2) == "--") {
        // Handling no value providition
        if (cmd_value == "" && (cmd.find('=') != cmd.size())) {
            std::cerr << "error: " << cmd << " expects a value" << std::endl;
            return false;
        } else if (cmd_value == "" && (cmd.find('=') == cmd.size())) {
            return true;
        }
        string ShortArg = arg.substr(1, 3);
        valid_commands_list[cmd] = cmd_value;

        FillArgValues(arg_values, ShortArg, cmd_value);

        return false;
    } else {
        if (!(valid_commands_list[valid_commands_list[cmd]] == nullptr)) {
            std::cerr << "error: repetition of an argument " 
                    << cmd << std::endl;
            return false; // Return if we found dublicated option
        }
        string LongArg = valid_commands_list[cmd];
        string empty = "nl2#@. 0E2,n1_9y s*6#,lopjG ]K9j";
        valid_commands_list[LongArg] = empty; 
        return true;
    }
}

ArgValues Parser(const int argc, char* argv[], 
                 unordered_map<string, string>& valid_commands_list) {
    // Structure for containing argument values
    ArgValues arg_values;

    // We need to know max option size, so we can handle long wrong options
    for (auto& i : valid_commands_list) {
        string current_option = i.first.substr(0, i.first.find('=')); // We get the argument up to '=' sign. If '=' is not present we get whole argument. @example "--output=abc" will return "--output" and "--outputabc" will return "--outputabc"
        size_t current_option_size = current_option.size();
        if (current_option_size > arg_values.max_option_size) {
            arg_values.max_option_size = current_option_size;
        }
    }

    // Processing all arguments
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            bool is_next_arg_a_value = ProcessCommand(
                                            argv[i], 
                                            arg_values, 
                                            valid_commands_list);
            bool is_long = false;
            string argvi = argv[i];
            if (argvi.substr(0, 2) == "--") {
                is_long = true;
            }
            if (is_next_arg_a_value && is_long && i+1 != argc) {
                string argviiplus1 = argv[i+1];
                valid_commands_list[argvi] = argviiplus1;
                FillArgValues(arg_values, argvi.substr(1, 3), argv[i+1]);
                ++i;
                continue;
            } else if (is_next_arg_a_value && !(is_long) && i+1 != argc) {
                FillArgValues(arg_values, argv[i], argv[i+1]);
                ++i;
                continue;       
            } else if (is_next_arg_a_value && i+1 == argc) {
                std::cerr << "error: " << argv[i] << " expects a value" << std::endl;
            }
        } else {
            std::cerr << "error: unknown option " << argv[i] << std::endl;
        }
    }
    return arg_values;
}

void FillValidCommandList(unordered_map<string, string>& valid_commands_list) {
    /** @note 
     *  If you add command here you also need to add them into MakeArgumentLong function
     */

    // Base options
    valid_commands_list["-i"] = "--input";
    valid_commands_list["--input"] = nullptr;
    valid_commands_list["-o"] = "--output";
    valid_commands_list["--output"] = nullptr;
    valid_commands_list["-m"] = "--max-iter";
    valid_commands_list["--max-iter"] = nullptr;
    valid_commands_list["-f"] = "--freq";
    valid_commands_list["--freq"] = nullptr;

    // My options
}

//////////////////// Parser end /////////////////////////

//////////////// Helper stats begin /////////////////////////////

enum ErrorCode{
    InputPathWasNotProvided,
    OutputPathWasNotProvided,
};

void ErrorMessage(size_t ErrorCode = 0) {
    switch(ErrorCode) {
        case 0: {
            std::cerr << "error: input path was not provided" << std::endl;
            break;
        }
        case 1: {
            std::cerr << "error: output path was not provided" << std::endl;
            break;
        }
        default: {
            std::cerr << "error: unknown error has occured" << std::endl;
            break;
        }
    }
}

void PreviewValues(ArgValues& arg_values) {
    bool HasErrorOccured = false;
    if (arg_values.input_path == nullptr) {
        ErrorMessage(ErrorCode(InputPathWasNotProvided));
        HasErrorOccured = true;
    }
    if (arg_values.output_path == nullptr) {
        ErrorMessage(ErrorCode(OutputPathWasNotProvided));
        HasErrorOccured = true;
    }
    std::cout << "Input path: " << arg_values.input_path << std::endl;
    std::cout << "Outputh path: " << arg_values.output_path << std::endl;
    std::cout << "Max iter: " << arg_values.max_iter << std::endl;
    std::cout << "Freq: " << arg_values.freq << std::endl;
}

/////////////// Helper stats end //////////////////////////////

//////////////// Read from file begin /////////////////////////
#include <tuple>
#include <fstream>
#include <sstream>

vector<std::tuple<int, int, int>> ReadCoordinates(string& str) {
    const int kInputPathNameSize = str.size();
    char buffer[kInputPathNameSize + 1]; 
    memcpy(buffer, str.c_str(), kInputPathNameSize); 
    buffer[kInputPathNameSize] = '\0';
    const char* filename = buffer;

    std::ifstream fin(filename);

    if (!fin.is_open()) {
        std::ofstream fout(filename); 
        fout.close();
        fin.open(filename);
    }

    vector<std::tuple<int, int, int>> data;

    string line; 
    while (getline(fin, line)) { 
        std::istringstream ss(line.c_str());
        int x, y, grains;
        ss >> x >> y >> grains;

        if (ss) { 
            data.push_back(std::make_tuple(x, y, grains));
        }
    }

    fin.close();
    return data;
}

//////////////// Read from file end /////////////////////////

/////////////////////Sandpile begin //////////////////////////
void hilbert(int n, int x, int y, 
                    int xi, int xj, 
                    int yi, int yj, 
                    vector<std::pair<int, int>>& points) {
    if (n <= 0) return;
    hilbert(n-1, x, y, yi/2, yj/2, xi/2, xj/2, points);
    points.push_back({x + xi/2, y + yi/2});
    hilbert(n-1, x + xi/2, y + yi/2, xi/2, xj/2, yi/2, yj/2, points);
    points.push_back({x + xi/2 + xj/2, y + yi/2 + yj/2});
    hilbert(n-1, x+xi/2 + xj/2, y+yi/2+yj/2, xi/2, xj/2, yi/2, yj/2, points);
    points.push_back({x + xi + xj/2, y + yi + yj/2});
    hilbert(n-1, x+xi+xj/2, y+yi + yj/2, -yi/2, -yj/2, -xi/2, -xj/2, points);
}


vector<std::pair<int, int>> generate_hilbert_curve(int order) {
    vector<std::pair<int, int>> points;
    hilbert(order, 0, 0, 1 << (order-1), 0, 0, 1 << (order-1), points);
    return points;
}


void distribute_sand(unordered_map<std::pair<int, int>, int>& sediment, 
                     vector<std::pair<int, int>>& hilbert_order) {
    queue<std::pair<int, int>> changes;
    
    for (auto& entry : sediment) {
        if (entry.second >= 4) {
            changes.push(entry.first);
        }
    }

    unordered_map<std::pair<int, int>, int> changes_map;
    while (!changes.empty()) {
        std::pair<int, int> coord = changes.front();
        changes.pop();

        int sand_count = sediment[coord];
        if (sand_count >= 4) {
            int distribute_count = sand_count / 4;
            sediment[coord] -= distribute_count * 4;

            vector<int> vec = {1, 3, 4, 5};
            vector<std::pair<int, int>> neighbors = {
                std::make_pair(coord.first - 1, coord.second),
                std::make_pair(coord.first + 1, coord.second),
                std::make_pair(coord.first, coord.second - 1),
                std::make_pair(coord.first, coord.second + 1)
            };

            for (auto& neighbor : neighbors) {
                if (changes_map.count(neighbor) == 0) {
                    changes_map[neighbor] = 0; //initialize if not exists
                }
                changes_map[neighbor] += distribute_count;
            }
        }
    }

    for (auto& entry : changes_map) {
        auto& neighbor = entry.first;
        int added_sand = entry.second;

        if (sediment.count(neighbor) == 0) {
            sediment[neighbor] = 0;
        }

        sediment[neighbor] += added_sand;
    }
}

//////////////////// Sandpile end ////////////////////////////

int main(int argc, char* argv[]) {
    // Creating and filling of an unordered map, containing all valid options
    unordered_map <string, string> valid_commands_list;
    FillValidCommandList(valid_commands_list);

    // Parcing command options into sctructure for further handling
    ArgValues arg_values; // Structure for containing argument values
    arg_values = Parser(argc, argv, valid_commands_list);

    // Outout values if needed
    PreviewValues(arg_values);

    // Reading and getting coordinates
    vector<std::tuple<int, int, int>> starting_coordinates = 
                    ReadCoordinates(arg_values.input_path);

    // Preparing for proccseing all the coordinates
    int hilbert_curve_order = 5; //order of default hilbert curve
    int total_iterations = arg_values.max_iter;

    // Initializing sandpile storage
    unordered_map<std::pair<int, int>, int> sediment; //coords of all sand grands
    for (auto& i : starting_coordinates) {
        sediment[{std::get<0>(i), std::get<1>(i)}] = std::get<2>(i);
    }
    
    vector<std::pair<int, int>> hilbert_order = 
                                generate_hilbert_curve(hilbert_curve_order);

    if (arg_values.freq == 0) arg_values.freq = arg_values.max_iter;
    for (int i = 0; i < total_iterations; ++i) {
        distribute_sand(sediment, hilbert_order);

        if (arg_values.freq != 0 && (i) % arg_values.freq == 0) {
            for (auto& i : sediment) {
                std::cout << i.first.first << ' ' << i.first.second << ' ' <<
                             i.second << std::endl;
            }
        }
    }
}
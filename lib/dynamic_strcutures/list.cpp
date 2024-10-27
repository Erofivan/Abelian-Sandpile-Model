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


    Iterator begin() {
        return Iterator(head);
    }


    Iterator end() {
        return Iterator(nullptr);
    }
};
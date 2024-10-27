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
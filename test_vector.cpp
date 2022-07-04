#include <iostream>
#include <array>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <iterator>

template <typename Type, int N>
Type arr_length(const std::array<Type, N>& arr){
    Type temp = arr[0] * arr[0];
    for(const auto& elem : arr) { temp += elem * elem; }
    return temp;
}

template <typename Type>
Type vec_length(const std::vector<Type>& vec){
    Type temp = vec[0] * vec[0];
    for(const auto& elem : vec) { temp += elem * elem; }
    return temp;
}

template <typename Type, int N>
class Vector;

template <typename Type, int N>
std::ostream& operator<<(std::ostream& out, const Vector<Type, N>& vec);


template <typename Type, int N>
class Vector {
    static_assert(N >= 0);
    std::array<Type, N> data_;

public:
    constexpr Vector() {
        data_.fill(0); 
    }
    constexpr Vector(const Vector<Type, N>& other) {
        data_ = other.data_;
    }
    constexpr Vector(std::initializer_list<Type> list) {
        std::copy(list.begin(), list.end(), data_.begin());
    }
    
    const Type& operator[](unsigned int i) const { return data_[i]; }
    Type& operator[](unsigned int i) { return data_[i]; }

    Vector<Type, N> operator*=(Type num) {
        for(auto& elem : data_) {
            elem *= num;
        }
        return *this;
    }
    Vector<Type, N> operator/=(Type num) {
        for(auto& elem : data_) {
            elem /= num;
        }
        return *this;
    }
    Vector<Type, N> operator+=(const Vector<Type, N>& other) {
        for(auto i = 0; i<N; i++) { data_[i] += other[i]; }
        return *this;
    }
    Vector<Type, N> operator-=(const Vector<Type, N>& other) {
        for(auto i = 0; i<N; i++) { data_[i] -= other[i]; }
        return *this;
    }

    Vector<Type, N> operator*(Type num) const {
        Vector<Type, N> temp;
        for(auto i = 0; i<N; i++) { temp[i] = data_[i] * num; }
        return temp;
    }

    Vector<Type, N> operator/(Type num) const {
        Vector<Type, N> temp;
        for(auto i = 0; i<N; i++) { temp[i] = data_[i] / num; }
        return temp;
    }

    Vector<Type, N> operator+(const Vector<Type, N>& other) const {
        Vector<Type, N> temp;
        for(auto i = 0; i<N; i++) { temp[i] = data_[i] + other[i]; }
            return temp;
    }
    Vector<Type, N> operator-(const Vector<Type, N>& other) const {
        Vector<Type, N> temp;
        for(auto i = 0; i<N; i++) { temp[i] = data_[i] - other[i]; }
        return temp;
    }

    bool operator<(const Vector<Type, N>& other) const {
        return arr_length<Type, N>(data_) < arr_length<Type, N>(other.data_);
    }

    bool operator>(const Vector<Type,N>& other) const {
        return arr_length<Type, N>(data_) > arr_length<Type, N>(other.data_);
    }

    bool operator==(const Vector<Type, N>& other) const {
        return (operator<(other) == operator>(other));
    }

    friend Vector<Type, N> operator*(Type num, const Vector<Type, N>& vec);
    friend Vector<Type, N> operator/(Type num, const Vector<Type, N>& vec);
    friend std::ostream& operator<< <>(std::ostream& out,  const Vector& vec);
};

template <typename Type, int N>
Vector<Type, N> operator*(Type num, const Vector<Type, N>& vec) {
    return vec * num;
}

template <typename Type, int N>
Vector<Type, N> operator/(Type num, const Vector<Type, N>& vec) {
    return vec / num;
}

template <typename Type, int N>
std::ostream& operator<<(std::ostream& out, const Vector<Type, N>& vec) {
    std::copy(vec.data_.begin(), vec.data_.end(), std::ostream_iterator<Type>(out, " "));
    return out << "\n";
}

constexpr int Dynamic = -1;

template <typename Type, int Dynamic>
class Vector;

template <typename Type>
std::ostream& operator<<(std::ostream& out, const Vector<Type, Dynamic>& vec);


template <typename Type>
class Vector<Type, Dynamic> {
    std::vector<Type> data_;
    int size_;

public:
    constexpr Vector() : data_(), size_(0) {}
    constexpr Vector(const Vector<Type, Dynamic>& other) {
        data_.resize(other.data_.size());
        size_ = data_.size(); 
        data_ = other.data_;
    }
    constexpr Vector(std::initializer_list<Type> list) {
        Resize(list.size());
        std::copy(list.begin(), list.end(), data_.begin());
    }

    void Resize(Type new_size) {
        data_.resize(new_size);
        std::fill_n(std::next(data_.begin(), size_), (new_size - size_), 0);
        size_ = new_size;
    }

    int getSize() const {return size_;}

    const Type& operator[](unsigned int i) const { return data_[i]; }
    Type& operator[](unsigned int i) { return data_[i]; }


    Vector<Type, Dynamic> operator*=(Type num) {
        for(auto& elem : data_) { elem *= num; }
        return *this;
    }
    Vector<Type, Dynamic> operator/=(Type num) {
        for(auto& elem : data_) { elem /= num; }
        return *this;
    }
    Vector<Type, Dynamic>& operator+=(const Vector<Type, Dynamic>& other) {
        // Resize(other.size_);
        for(auto i = 0; i<size_; i++) { data_[i] += other[i]; }
        return *this;
    }

    Vector<Type, Dynamic>& operator-=(const Vector<Type, Dynamic>& other) {
        // Resize(other.size_);
        for(auto i = 0; i<size_; i++) { data_[i] -= other[i]; }
        return *this;
    }

    Vector<Type, Dynamic> operator*(Type num) const {
        Vector<Type, Dynamic> temp;
        temp.Resize(size_);
        for(auto i = 0; i<size_; i++) { temp[i] = data_[i] * num; }
        return temp;
    }

    Vector<Type, Dynamic> operator/(Type num) const {
        Vector<Type, Dynamic> temp;
        temp.Resize(size_);
        for(auto i = 0; i<size_; i++) { temp[i] = data_[i] / num; }
        return temp;
    }

    Vector<Type, Dynamic> operator+(const Vector<Type, Dynamic>& other) const {
        Vector<Type, Dynamic> temp;
        temp.Resize(size_);
        for(auto i = 0; i<size_; i++) { temp[i] = data_[i] + other[i]; }
        return temp;
    }

    Vector<Type, Dynamic> operator-(const Vector<Type, Dynamic>& other) const {
        Vector<Type, Dynamic> temp;
        temp.Resize(size_);
        for(auto i = 0; i<size_; i++) { temp[i] = data_[i] - other[i]; }
        return temp;
    }

    bool operator<(const Vector<Type, Dynamic>& other) const {
        return vec_length<Type>(data_) < vec_length<Type>(other.data_);
    }

    bool operator>(const Vector<Type, Dynamic>& other) const {
        return vec_length<Type>(data_) > vec_length<Type>(other.data_);
    }

    bool operator==(const Vector<Type, Dynamic>& other) const {
        return (operator<(other) == operator>(other));
    }

    friend Vector<Type, Dynamic> operator*(Type num, const Vector<Type, Dynamic>& vec);
    friend Vector<Type, Dynamic> operator/(Type num, const Vector<Type, Dynamic>& vec);
    friend std::ostream& operator<< <>(std::ostream& out,  const Vector<Type, Dynamic>& vec);
};

template <typename Type>
Vector<Type, Dynamic> operator*(Type num, const Vector<Type, Dynamic>& vec) {
    return vec * num;
}

template <typename Type>
Vector<Type, Dynamic> operator/(Type num, const Vector<Type, Dynamic>& vec) {
    return vec / num;
}

template <typename Type>
std::ostream& operator<<(std::ostream& out, const Vector<Type,Dynamic>& vec) {
    std::copy(vec.data_.begin(), vec.data_.end(), std::ostream_iterator<Type>(out, " "));
    return out << "\n";
}

int main() {
    std::initializer_list<int> list1 {6, 7, 8};
    std::initializer_list<int> list2 {1, 2, 3};

    Vector<int, -1> example(list1);
    Vector<int, -1> example2(list2);
    std::cout <<(example > example2) << (example < example2) << (example == example2);
}
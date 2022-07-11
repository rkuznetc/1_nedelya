#include <iostream>
#include <array>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <iterator>

template <typename Type, int N>
Type arr_length(const std::array<Type, N>& arr){
    Type temp = arr[0] * arr[0];
    for(auto i = 1; i<N; i++) { temp += arr[i] * arr[i]; }
    return temp;
}

template <typename Type>
Type vec_length(const std::vector<Type>& vec){
    Type temp = vec[0] * vec[0];
    for(auto i = 1; i<vec.size(); i++) { temp += vec[i] * vec[i]; }
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
    constexpr Vector() = default;
    constexpr Vector(const Vector<Type, N>& other) {
        data_ = other.data_;
    }
    constexpr Vector(const std::initializer_list<Type>& list) {
        std::copy(list.begin(), list.end(), data_.begin());
    }
    
    const Type& operator[](unsigned int i) const { return data_[i]; }
    Type& operator[](unsigned int i) { return data_[i]; }

    Vector<Type, N>& operator*=(Type num) {
        for(auto& elem : data_) {
            elem *= num;
        }
        return *this;
    }
    Vector<Type, N>& operator/=(Type num) {
        for(auto& elem : data_) {
            elem /= num;
        }
        return *this;
    }
    Vector<Type, N>& operator+=(const Vector<Type, N>& other) {
        for(int i = 0; i<N; i++) { data_[i] += other[i]; }
        return *this;
    }
    Vector<Type, N>& operator-=(const Vector<Type, N>& other) {
        for(int i = 0; i<N; i++) { data_[i] -= other[i]; }
        return *this;
    }

    Vector<Type, N> operator*(Type num) const {
        return Vector<Type, N>(*this) *= num;
    }

    Vector<Type, N> operator/(Type num) const {
        return Vector<Type, N>(*this) /= num;
    }

    Vector<Type, N> operator+(const Vector<Type, N>& other) const {
        return Vector<Type, N>(*this) += other;
    }
    Vector<Type, N> operator-(const Vector<Type, N>& other) const {
        return Vector<Type, N>(*this) -= other;
    }

    bool operator==(const Vector<Type, N>& other) const {
        return (arr_length<Type, N>(data_) == arr_length<Type, N>(other.data_));
    }

    friend std::ostream& operator<< <>(std::ostream& out,  const Vector& vec);
};

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
    constexpr Vector(const std::initializer_list<Type>& list) {
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


    Vector<Type, Dynamic>& operator*=(Type num) {
        for(auto& elem : data_) { elem *= num; }
        return *this;
    }
    Vector<Type, Dynamic>& operator/=(Type num) {
        for(auto& elem : data_) { elem /= num; }
        return *this;
    }
    Vector<Type, Dynamic>& operator+=(const Vector<Type, Dynamic>& other) {
        for(auto i = 0; i<size_; i++) { data_[i] += other[i]; }
        return *this;
    }

    Vector<Type, Dynamic>& operator-=(const Vector<Type, Dynamic>& other) {
        for(auto i = 0; i<size_; i++) { data_[i] -= other[i]; }
        return *this;
    }

    Vector<Type, Dynamic> operator*(Type num) const {
        return Vector<Type, Dynamic>(*this) *= num;
    }

    Vector<Type, Dynamic> operator/(Type num) const {
        return Vector<Type, Dynamic>(*this) /= num;
    }

    Vector<Type, Dynamic> operator+(const Vector<Type, Dynamic>& other) const {
        return Vector<Type, Dynamic>(*this) += other;
    }

    Vector<Type, Dynamic> operator-(const Vector<Type, Dynamic>& other) const {
        return Vector<Type, Dynamic>(*this) -= other;
    }

    bool operator==(const Vector<Type, Dynamic>& other) const {
        return (vec_length<Type>(data_) == vec_length<Type>(other.data_));
    }

    friend std::ostream& operator<< <>(std::ostream& out,  const Vector<Type, Dynamic>& vec);
};

template <typename Type>
std::ostream& operator<<(std::ostream& out, const Vector<Type,Dynamic>& vec) {
    std::copy(vec.data_.begin(), vec.data_.end(), std::ostream_iterator<Type>(out, " "));
    return out << "\n";
}


int main() {
    std::initializer_list<int> list1 {3, 4, 5};
    std::initializer_list<int> list2 {5, 4, 3};

    Vector<int, -1> example(list1);
    Vector<int, -1> example2(list2);
    Vector<int, -1> test(example2);
    example += example2;
    std::cout << example << example2 << test;
    std::cout << (example == example2) << "\n";

    Vector<int, -1> example3;
    example3 = example2 * 5;
    std::cout << example3;
    Vector<int, -1> example4;
    example4 = example3 + example2;
    std::cout << example4;
}

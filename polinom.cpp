#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

class Polynomial_v1 {
private:
    std::vector<int> coeffs;
    int N; // старший порядок(ненулевой)

    void clear_zeros() {
        while(coeffs[N] == 0) {
            coeffs.erase(
                std::prev(coeffs.end())
            );
            N--;
        }
    }
public:
    Polynomial_v1() : N(0), coeffs() {}

    Polynomial_v1(const std::vector<int>& coefficents) : coeffs(coefficents), N(coefficents.size() - 1) {}
    Polynomial_v1(const Polynomial_v1& other) {
        for(const int& coeff : other.coeffs) {coeffs.push_back(coeff);}
        N = other.N;
    }

    int getPower(){return N;}

    Polynomial_v1& operator=(const Polynomial_v1& other) {
        if(this != &other) {
            N = other.N;
            coeffs.clear();
            for(const int& coeff : other.coeffs) {coeffs.push_back(coeff);}
        }
        return *this;
    }

    Polynomial_v1& operator*=(int num) {
        for(int& coeff : coeffs) {coeff *= num;}
        return *this;
    }
    
    Polynomial_v1& operator/=(int num) {
        for(int& coeff : coeffs) {coeff /= num;}
        return *this;
    }
    
    Polynomial_v1& operator+=(const Polynomial_v1& other) {
        if(other.N > N) {
            for(int i = N; i<other.N; i++) {
                coeffs.push_back(0);
            }
            N = other.N;
        }

        for(int i = 0; i<=other.N; i++) {
            coeffs[i] += other.coeffs[i];
        }
        clear_zeros();
        return *this;
    }

    Polynomial_v1& operator-=(const Polynomial_v1& other) {
        if(other.N > N) {
            for(int i = N; i<other.N; i++) {
                coeffs.push_back(0);
            }
            N = other.N;
        }

        for(int i = 0; i<=other.N; i++) {
            coeffs[i] -= other.coeffs[i];
        }
        clear_zeros();
        return *this;
    }

    Polynomial_v1 operator*(int num) const { 
        return Polynomial_v1(*this) *= num; 
    }

    Polynomial_v1 operator/(int num) const {
        return Polynomial_v1(*this) /= num;
    }

    Polynomial_v1 operator+(const Polynomial_v1& other) const {
        return Polynomial_v1(*this) += other;
    }

    Polynomial_v1 operator-(const Polynomial_v1& other) const {
        return Polynomial_v1(*this) -= other;
    }

    Polynomial_v1 derivative() const {
        Polynomial_v1 deriv;
        for(int i = 1; i<=N; i++) { deriv.coeffs.push_back(i * coeffs[i]); }
        deriv.N = N-1;
        return deriv;
    }

    Polynomial_v1 antiderivative(int Const) const {
        Polynomial_v1 antideriv;
        antideriv.coeffs.push_back(Const);
        for(int i = 0; i<=N; i++) { antideriv.coeffs.push_back(coeffs[i] / (i+1)); }
        antideriv.N = N+1;
        antideriv.clear_zeros();
        return antideriv;
    }

    Polynomial_v1 operator*(const Polynomial_v1& other) const {
        std::vector<int> temp;
        for(int i = 0; i<=(N + other.N); i++) { temp.push_back(0);}

        for(int i = 0; i<=N; i++) {
            for(int j = 0; j<=other.N; j++) { temp[i+j] += coeffs[i] * other.coeffs[j]; }
        }
        return Polynomial_v1(temp);
    }
    Polynomial_v1 operator/(const Polynomial_v1& divider) const {
        std::vector<int> coeffs_backwards;
        Polynomial_v1 divisible = *this; 
        int temp;

        for(int i = N; i >= divider.N; i--) {
            temp = divisible.coeffs[i] / divider.coeffs[divider.N];
            coeffs_backwards.push_back(temp);
            for(int j = 0; j <= divider.N; j++) {divisible.coeffs[divisible.N - j] -= temp * divider.coeffs[divider.N - j];}
            divisible.N--;
        }

        std::reverse(coeffs_backwards.begin(), coeffs_backwards.end());
        return Polynomial_v1(coeffs_backwards);
    }

    bool operator==(const Polynomial_v1& other) {
        return coeffs == other.coeffs; 
    }

    friend std::ostream& operator<<(std::ostream&, const Polynomial_v1&);
};

std::ostream& operator<<(std::ostream& os, const Polynomial_v1& polin) {
    for(const int& coeff : polin.coeffs) {os << coeff << " ";}
    return os << "\n";
}

class Polynomial_v2 {
private:
    std::map<int, int> coeffs;

    void clear_zeros() {
        std::vector<int> to_erase;
        for(const auto& coeff : coeffs) {
            if(coeff.second == 0){ to_erase.push_back(coeff.first); }
        }
        for(const auto& elem : to_erase) {coeffs.erase(elem);}
    }
public:
    Polynomial_v2() {}
    Polynomial_v2(std::map<int, int> coeffs) : coeffs(coeffs) {}
    Polynomial_v2(const Polynomial_v2& other) {
        for(const auto& coeff : other.coeffs) {coeffs.emplace(coeff);}
    }

    Polynomial_v2& operator*=(int num) {
        for(auto& coeff : coeffs) {coeff.second *= num;}
        return *this;
    }

    Polynomial_v2& operator/=(int num) {
        for(auto& coeff : coeffs) {coeff.second /= num;}
        return *this;
    }

    Polynomial_v2& operator+=(const Polynomial_v2& other) {
        for(auto& coeff : other.coeffs) {
            if(coeffs.find(coeff.first) != coeffs.end()) {
                coeffs[coeff.first] += coeff.second;
            } else {
                coeffs.emplace(coeff.first, coeff.second);
            }
        }
        clear_zeros();
        return *this;
    }

    Polynomial_v2& operator-=(const Polynomial_v2& other) {
        for(auto& coeff : other.coeffs) {
            if(coeffs.find(coeff.first) != coeffs.end()) {
                coeffs[coeff.first] -= coeff.second;
            } else {
                coeffs.emplace(coeff.first, -coeff.second);
            }
        }
        clear_zeros();
        return *this;
    }

    Polynomial_v2 operator*(int num) const {return Polynomial_v2(*this) *= num;}

    Polynomial_v2 operator/(int num) const {return Polynomial_v2(*this) /= num;}

    Polynomial_v2 operator+(const Polynomial_v2& other) const {
        return Polynomial_v2(*this) += other;
    }
    Polynomial_v2 operator-(const Polynomial_v2& other) const {
        return Polynomial_v2(*this) -= other;
    }

    Polynomial_v2 derivative() const {
        std::map<int, int> temp_map; 

        for(const auto& coeff : coeffs) { 
            if(coeff.first != 0) temp_map.emplace(coeff.first - 1, coeff.first * coeff.second); 
        }
        return Polynomial_v2(temp_map);
    }
    
    Polynomial_v2 antiderivative(int Const) const {
        std::map<int, int> temp_map;
        temp_map.emplace(0, Const);
        for(const auto& coeff : coeffs) { temp_map.emplace(coeff.first + 1, coeff.second / (coeff.first + 1)); }
        return Polynomial_v2(temp_map);
    }

    Polynomial_v2 operator*(const Polynomial_v2& other) const {
        std::map<int, int> temp_map;
        for(const auto& coeff : coeffs) {
            for(const auto& other_coeff : other.coeffs) {
                if(temp_map.emplace(coeff.first + other_coeff.first, coeff.second * other_coeff.second).second) {}
                else {temp_map[coeff.first + other_coeff.first] += coeff.second * other_coeff.second;}
            }
        }
        Polynomial_v2 Res(temp_map);
        Res.clear_zeros();
        return Res;
    }

    Polynomial_v2 operator/(const Polynomial_v2& divider) const {
        std::map<int, int> temp_map;
        Polynomial_v2 divisible = *this;
        int divisible_power = divisible.coeffs.size();
        int temp;

        auto it1 = divisible.coeffs.begin();
        auto it2 = divider.coeffs.begin();
        for(int i = coeffs.size() - 1; i>=(divider.coeffs.size() - 1); i--) {
            temp = (*std::next(it1, i)).second / (*std::next(it2, divider.coeffs.size() - 1)).second;
            if(temp != 0) temp_map.emplace((*std::next(it1, i)).first - (*std::next(it2, divider.coeffs.size() - 1)).first,
                temp);
            for(int j = 1; j<=divider.coeffs.size(); j++) {
                (*std::next(it1, divisible_power - j)).second -= temp *
                    (*std::next(it2, divider.coeffs.size() - j)).second;
            }
            divisible_power--;
        }

        return Polynomial_v2(temp_map);
    }

    bool operator==(const Polynomial_v2& other) { return coeffs == other.coeffs; }

    friend std::ostream& operator<<(std::ostream& os, const Polynomial_v2& polyn) {
        for(auto it = polyn.coeffs.begin(); it != std::prev(polyn.coeffs.end()); it = std::next(it)) {
            std::cout << (*it).second << "x^" << (*it).first << " + ";
        }
        return os << (*std::prev(polyn.coeffs.end())).second << "x^" << (*std::prev(polyn.coeffs.end())).first << "\n";
    }
};

//          Проверка первого класса v2

// int main() {
//     std::map<int, int> map1 {{0, 152}, {1, 67}, {2, 6}, {5, 8}, {6, 1}};
//     std::map<int, int> map2 {{1, 1}, {0, 8}};
//     std::map<int, int> map3 {{1, 1}, {0, 3}};
//     std::map<int, int> map4 {{0, 2}, {2, 1}, {1, -1}};
//     Polynomial_v2 pol1(map3);
//     Polynomial_v2 pol2(map4);
//     Polynomial_v2 pol3;
//     Polynomial_v2 pol4;
//     pol3 = pol2.derivative();
//     pol4 = pol1.antiderivative(122);
//     std::cout << pol1 << pol2 << pol3 << pol4;
//     return EXIT_SUCCESS;
// }


//          Проверка первого класса v1

// int main() {
    // std::vector<int> vect1 {1, 2, 3};
    // std::vector<int> vect2 {3, 4, 5, 6, 7};
    // Polynomial_v1 pol1(vect1);
    // Polynomial_v1 pol2(vect2);
    // std::cout << pol1 << pol2;
    // std::cout << pol1.getN() << " " << pol2.getN() << "\n";
    // pol1 += pol2;
    // pol2 -= pol1;
    // std::cout << pol1 << pol2;
    // Polynomial_v1 pol1_deriv(pol1.derivative());
    // Polynomial_v1 pol2_antideriv(pol2.antiderivative(0));
    // std::cout << pol1_deriv << pol2_antideriv;
    // std::cout << pol1_deriv.getN() << " " << pol2_antideriv.getN();
    // std::vector<int> vect3 {-840, -431, -85, 11, 1};
    // std::vector<int> vect4 {7, 4, 1};
    // Polynomial_v1 pol3(vect3);
    // Polynomial_v1 pol4(vect4);
    // Polynomial_v1 quot;
    // quot = pol3 / pol4;
    // std::cout << quot;
// }

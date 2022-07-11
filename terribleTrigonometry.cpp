#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>

struct Point {
    double x;
    double y;
};

std::vector<Point> terribleTrigonometry(unsigned int n) {
    std::vector<Point> temp;
    
    if(n != 0) {
        double phi = 2 * M_PI / n;
        temp.push_back({cos(0.), sin(0.)});
        if(n != 1) {temp.push_back({cos(phi), sin(phi)});}
    }

    for(auto i = 2; i < n ; i++) {
        temp.push_back({ 
            (temp[i-1].x * temp[1].x - temp[i-1].y * temp[1].y) ,
            (temp[i-1].y * temp[1].x + temp[i-1].x * temp[1].y)
        });
    }

    return temp;
}

int main() {
    unsigned int n = 6;

    auto start = std::chrono::steady_clock::now();
    std::vector<Point> vect = terribleTrigonometry(n);
    auto end = std::chrono::steady_clock::now();

    
    auto delay = end.time_since_epoch().count() - start.time_since_epoch().count();
    std::cout << "Seconds past: " << 
                (delay / std::pow(10, 9)) << std::endl; 
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(
                   start.time_since_epoch()).count() << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(
                   end.time_since_epoch()).count() << std::endl;

    for (auto elem : vect) {
        std::cout << elem.x << " " << elem.y << std::endl;
    };

    return EXIT_SUCCESS;
}

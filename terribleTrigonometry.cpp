#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>

struct Point {
    double x;
    double y;
};

std::vector<Point> terribleTrigonometry(unsigned int n) {
    double phi = 2 * M_PI / n;
    std::vector<Point> temp(n);

    double temp_x, temp_y;
    
    for(auto i = 0; i < (n+1)/2 ; i++) {

        if(phi*i == M_PI/2 || phi*i == 3*M_PI/2) {
            temp_x = 0.;
        } else { temp_x = cos(phi * i); }

        if(phi*i == M_PI || phi*i == 2*M_PI) {
            temp_y = 0.;
        } else { temp_y = sin(phi * i); }

        temp[i] = {temp_x, temp_y};
        temp[n-i] = {temp_x, -temp_y};
    }
    
    if((n % 2) == 0 && n != 0) temp[n/2] = {-1, 0};

    return temp;
}

int main() {
    unsigned int n = 100;

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

    // for (auto elem : vect) {
    //     std::cout << elem.x << " " << elem.y << std::endl;
    // };

    return EXIT_SUCCESS;
}
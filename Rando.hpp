#ifndef RANDO
#define RANDO

#include <cmath>
#include <mutex> 
#include <random>

std::mt19937_64 my_rng;// Random Number Engine
std::uniform_real_distribution<double> my_unif_real_dist(0.0, 1.0);//Random Number Distribution
std::mutex my_rng_mutex; 

double RANDOM() {
    std::lock_guard<std::mutex> lock(my_rng_mutex);
    return my_unif_real_dist(my_rng);
}

void Seed(int seed) {
    std::lock_guard<std::mutex> lock(my_rng_mutex);
    my_rng.seed(seed);
    // mutex is released when lock goes out of scope
}

int intRand(const int& min, const int& max) {
    thread_local std::mt19937 generator;
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

#endif
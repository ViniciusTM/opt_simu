#include <vector>
#include "genetic.h"

//----------- Solution -----------//
Solution::Solution(int s, int d, int o, int l) {
    
}

//------------ Genetic ------------//
void Genetic::run() {

    while() {
        std::cout << "=======================================" << std::endl;
        std::cout << "-----> Generation: " << gen_number << std::endl;
        generation_step();
        std::cout << "Best solution:" << best_sol << std::endl;
        std::cout << "Num simulations (gen):" << simu_n << std::endl;
        std::cout << "Num simutaions (total):" << Solution.simu_n << std::endl;
        std::cout << "Population std:" << pop_std << std::endl;
    }
}
//
//  GearRatioOptimization.hpp
//  planetary_gearbox
//
//  Created on 22.06.2023.
//

#ifndef GearRatioOptimization_hpp
#define GearRatioOptimization_hpp

#include <iostream>
#include <numeric>
#include <map>
#include <vector>

/**
 @brief Class that implements the solution of the problem of gear ratio optimization
 */
class GearRatioOptimization{
public:
    double functionValue = 0;
    double K;
    int n; //num of satellite groups
    double z_max;
    double z_1, z_2, z_42, z_41;
    GearRatioOptimization(int _n, double _K, double _z) : n(_n), K(_K), z_max(_z) {};
    GearRatioOptimization(int _n, double _K) : n(_n), K(_K){z_max = 105;};
    GearRatioOptimization() = delete;
    
    /**
     @brief user method to get solution
     @return vector of name and values pairs
     */
    std::vector <std::pair<std::string, double>> getSolution(){
        std::vector <std::pair<std::string,double>> solution;
        EnumerationMethod();
        solution.push_back(std::make_pair("Число зубьев солнечной шестерни Z1",z_1));
        solution.push_back(std::make_pair("Число зубьев эпицикла Z2",z_2));
        solution.push_back(std::make_pair("Число зубьев сателита z41",z_41));
        solution.push_back(std::make_pair("Число зубьев сателита z42",z_42));
        solution.push_back(std::make_pair("Оптимальное решение параметра К ", ((double)z_2/(double)z_1)));
        solution.push_back(std::make_pair("Погрешность", functionValue * 100));
        return solution;
    }
    
private:
    
    /**
     @brief method calculating the value of goal function
     @param[in] _z1 is number of teeth on the sun gear
     @param[in] _z2 is number of teeth on the epicycle
     @return value of goal function with passed parameters
     */
    double goalFunction(double _z1, double _z2){
        return std::abs((K - (_z2/_z1)) / K);
    }
    
    /**
     @brief method execute enumaration of numer of teeth on gears
     */
    void EnumerationMethod(){
        int _z1, _z2, _z41 = 0, _z42 = 0;
        for (_z2 = 56; _z2 <= z_max; _z2++) {
            for (_z1 = _z2 - 2 ; _z1 >= 17; _z1 -= 2) {
                if ((_z1 + _z2) % n != 0)
                    continue;
                for (_z41 = _z2; _z41 >= 17; _z41--) {
                    if (2 * _z41 + 3 > _z2 - _z1 - 2)
                        continue;
                    for (_z42 = _z41 - 1 ; _z42 >= 17; _z42--){
                        if(std::gcd(_z41, _z42) != 1)
                            continue;
                        double newFunctionValue = goalFunction(_z1, _z2);
                        if (functionValue == 0 || newFunctionValue < functionValue){
                            functionValue = newFunctionValue;
                            z_1 = _z1;
                            z_2 = _z2;
                            z_41 = _z41;
                            z_42 = _z42;
                        }
                    }
                }
            }
        }
        return;
    }
};


#endif

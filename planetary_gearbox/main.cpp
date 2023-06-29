//
//  main.cpp
//  planetary_gearbox
//
//  Created on 20.06.2023.
//

#include <iostream>
#include "GearRatioOptimization.hpp"

int main(int argc, const char * argv[]) {
    double K;
    std::string str;
    std::vector <std::pair<std::string,double>> solution;
    
    /**
     entering the required values ​​and checking their correctness
     */
    std::cout << "Введите значение К (1.5 <= К <= 4)" << std::endl;
    while (1) {
        std::getline(std::cin, str, '\n');
        K = std::stod(str);
        if (K >= 1.5 && K <= 4)
            break;
        std::cout << "Введенное значение не удовлетворяет условию 1.5 <= К <= 4, введите другое значение"<< std::endl;
    }
    GearRatioOptimization* GRO;
    std:: cout << "При необходимости укажите новое значение максимального числа зубев. Иначе нажмите Enter." << std::endl;
    std::getline(std::cin, str, '\n');
    
    /**
     Derivation of the obtained solution of the optimization problem
     */
    for (int i = 3; i <= 5; i++) {
        std::cout << "\nКоличество групп n = " << i << std::endl;
        if (str == "") //Choice of class constructor depending on value of z_max
            GRO = new GearRatioOptimization(i, K);
        else
            GRO = new GearRatioOptimization(i, K, std::stod(str));
        solution = GRO->getSolution();
        if (solution[solution.size() - 1].second > 5.001) //Cheking value of error
            std::cout << "Погрешность оптимального решения составляет больше 5%" << std::endl;
        for(auto pair : solution){
            std::cout << std::endl;
            if (pair.first == "Погрешность")
                std::cout.precision(2);
            std::cout << pair.first << " = " << pair.second;
        }
        std::cout << "%\n" << std::endl;
        std::cout.precision(5);
    }
    
}

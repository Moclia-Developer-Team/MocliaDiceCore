/**
 * @name MocliaDice
 * @brief 方法测试
 * @file main.cpp
 * @copyright 星翛-STASWIT 2018-2022
 * */
#include "GeneralUnit.h"
#include "RollDiceUnit.h"

int main() {
    Moclia::calc mc;
    try
    {
        Moclia::exp_t epp;
        epp.original = "20da(a2+6)a";
        mc.expressionStandard(epp);
        mc.expressionCalculator(epp);
        std::cout << epp.original << std::endl;
        std::cout << epp.reason << std::endl;
        std::cout << epp.middleCalc << "=" << epp.finalResult << std::endl;

    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}

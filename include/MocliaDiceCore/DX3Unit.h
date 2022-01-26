/**
 * @name MocliaDice
 * @brief 双重十字（Double Cross）的相关定义
 * @file DX3Unit.h
 * @copyright 星翛-STASWIT 2018-2022
 * */
#pragma once

#ifndef MOCLIADICECORE_DX3UNIT_H
#define MOCLIADICECORE_DX3UNIT_H
#endif //MOCLIADICECORE_DX3UNIT_H

#include "GeneralUnit.h"
#include "RollDiceUnit.h"

namespace Moclia
{
    class DX3
    {
    public:
       static void addDice(exp_t dx3Calc);
    private:
        /**
        * @brief 双重十字加骰处理
        * @param general 初始掷骰个数
        * @param addup 加骰线
        * @param surface 骰子面数
        * @note DX3加骰计算方法： 先进行初始计算，若有加骰，增加总加骰数，当不达成加骰条件时，最终结果为总加骰数 * 10 + 最后一次掷骰里的最大值
        * */
        static void addDiceCalc(int64_t general, int64_t addup, int64_t surface, int64_t &totalResult, std::string &middleResult, int64_t lastAdd);
        static void expStandard(exp_t &dx3Exp, std::deque<int64_t> &result);
    };
}
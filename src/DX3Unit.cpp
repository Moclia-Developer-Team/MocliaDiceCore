/**
 * @name MocliaDice
 * @brief 双重十字（Double Cross）的相关实现
 * @file DX3Unit.cpp
 * @headerfile DX3Unit.h
 * @copyright 星翛-STASWIT 2018-2022
 * */

#include "MocliaDiceCore/DX3Unit.h"

namespace Moclia
{
    void DX3::addDiceCalc(int64_t general, int64_t addup, int64_t surface, int64_t &totalResult, std::string &iterationCalc, std::string &middleCalc, int64_t lastAdd, std::string &exception)
    {
        if (addup < 2)
        {
        #ifdef MOCLIA_LANG_ZH
            exception = "加骰下限为2";
        #else
            exception = "add dice lower limit is 2";
        #endif
            return;
        }
        int64_t rand = general;
        int64_t nextRand = 0;
        int64_t totalAdd = lastAdd;
        dice_t dx3d;
        dx3d = calc::diceCalc(rand,surface,'K',rand);
        if (!dx3d.exception.empty())
        {
            exception = dx3d.exception;
            return;
        }
        iterationCalc += "[";
        for (int64_t dxrand : dx3d.randResult)
        {
            if (iterationCalc.back() == '[')
            {
                iterationCalc += std::to_string(dxrand);
            }
            else
            {
                iterationCalc += ',';
                iterationCalc += std::to_string(dxrand);
            }

            if (dxrand >= addup)
            {
                nextRand++;
                totalAdd++;
            }
        }
        iterationCalc += "]";

        if (nextRand != 0)
        {
            iterationCalc += ",";
            addDiceCalc(nextRand, addup, surface, totalResult, iterationCalc, middleCalc, totalAdd, exception);
        }
        else
        {
            tool::quickSort(dx3d.randResult,0,dx3d.randResult.size() - 1);
            totalResult = totalAdd * 10 + dx3d.randResult.back();
        }
        return;
    }

    void DX3::expStandard(exp_t &dx3Exp, std::deque<int64_t> &result)
    {
        bool isReason = false;
        std::string expEp = "+-*xX/DKQdkq()";
        std::string stand = "";
        exp_t dx3Epr;
        dx3Exp.reason.clear();

        if (!result.empty())
        {
            result.clear();
        }

        for (char exp : dx3Exp.original)
        {
            if (!isReason)
            {
                if (expEp.find(exp) != std::string::npos || std::isdigit(exp) != 0)
                {
                    stand += exp;
                }
                else if (exp == 'C' || exp == 'c' || exp == 'M' || exp == 'm')
                {
                    dx3Epr.original = stand;
                    stand.clear();
                    calc::expressionCalculator(dx3Epr);
                    result.push_back(strtoll(dx3Epr.finalResult.c_str(), nullptr,10));
                }
                else
                {
                    isReason = true;
                    dx3Exp.reason += exp;
                }
            }
            else
            {
                dx3Exp.reason += exp;
            }
        }
    }

    void DX3::addDice(exp_t dx3Calc)
    {
        std::deque<int64_t> CM;
        int64_t calcResult;
        expStandard(dx3Calc,CM);
        if (CM.size() != 3)
        {
            switch (CM.size())
            {
                case 0:
                #ifdef MOCLIA_LANG_ZH
                    dx3Calc.exception = "DX3加骰无数据输入"
                #else
                    dx3Calc.exception = "DX3 add dice no data input";
                #endif
                    return;
                case 1:
                #ifdef MOCLIA_LANG_ZH
                    dx3Calc.exception = "未设定加骰线"
                #else
                    dx3Calc.exception = "No add dice line";
                #endif
                    return;
                case 2:
                    CM.push_back(10);
                    break;
                default:
                    break;
            }
        }
        addDiceCalc(CM[0],CM[1],CM[2], calcResult, dx3Calc.iterationCalc, dx3Calc.middleCalc, 0, dx3Calc.exception);

        return;
    }
}
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
    void DX3::addDiceCalc(int64_t general, int64_t addup, int64_t surface, int64_t &totalResult, std::string &middleResult, int64_t lastAdd)
    {
        if (addup < 2)
        {
            // exception
            return;
        }
        int64_t rand = general;
        int64_t nextRand = 0;
        int64_t totalAdd = lastAdd;
        dice_t dx3d;
        dx3d = calc::diceCalc(rand,surface,'K',rand);
        middleResult += "[";
        for (int64_t dxrand : dx3d.randResult)
        {
            if (middleResult.back() == '[')
            {
                middleResult += std::to_string(dxrand);
            }
            else
            {
                middleResult += ',';
                middleResult += std::to_string(dxrand);
            }

            if (dxrand >= addup)
            {
                nextRand++;
                totalAdd++;
            }
        }
        middleResult += "]";

        if (nextRand != 0)
        {
            middleResult += ",";
            addDiceCalc(nextRand,addup,surface,totalResult,middleResult,totalAdd);
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
                    calc::expressionStandard(dx3Epr);
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
        addDiceCalc(CM[0],CM[1],CM[2],calcResult,dx3Calc.iterationCalc,0);
        return;
    }
}
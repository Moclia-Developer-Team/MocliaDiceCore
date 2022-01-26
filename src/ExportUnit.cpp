/**
 * @name MocliaDice
 * @brief 导出函数定义
 * @file ExportUnit.cpp
 * @headerfile ExportUnit.h
 * @copyright 星翛-STASWIT 2018-2022
 * */
#include "MocliaDiceCore/ExportUnit.h"

uint64_t RDTSCTool()
{
    return Moclia::tool::getCycleCount();
}

int64_t randTool(int64_t min, int64_t max)
{
    return Moclia::tool::randNumber(min,max);
}

void classicDiceUnit(const char *inputExp, const char * middleExp, const char *reason, int64_t result, const char *exception)
{
    Moclia::exp_t classicExp;
    classicExp.original = inputExp;
    Moclia::calc::expressionStandard(classicExp);
    Moclia::calc::expressionCalculator(classicExp);
    inputExp = classicExp.original.c_str();
    middleExp = classicExp.middleCalc.c_str();
    reason = classicExp.reason.c_str();
    result = strtoll(classicExp.finalResult.c_str(), nullptr, 10);
    exception = classicExp.exception.c_str();
    return;
}

void fudgeDiceUnit(const char *inputExp, const char *middleExp, const char *reason, int64_t result, const char *exception)
{
    Moclia::exp_t fudgeExp;
    fudgeExp.original = inputExp;
    Moclia::fudge::calc(fudgeExp);
    middleExp = fudgeExp.middleCalc.c_str();
    reason = fudgeExp.reason.c_str();
    result = strtoll(fudgeExp.finalResult.c_str(), nullptr, 10);
    exception = fudgeExp.exception.c_str();
    return;
}

void dx3AddDiceUnit(const char *inputExp, const char *iterationExp, const char *middleExp, const char *reason, int64_t result, const char *exception)
{
    Moclia::exp_t dx3Exp;
    dx3Exp.original = inputExp;
    Moclia::DX3::addDice(dx3Exp);
    inputExp = dx3Exp.original.c_str();
    iterationExp = dx3Exp.iterationCalc.c_str();
    middleExp = dx3Exp.middleCalc.c_str();
    reason = dx3Exp.reason.c_str();
    result = strtoll(dx3Exp.finalResult.c_str(), nullptr, 10);
    exception = dx3Exp.exception.c_str();
    return;
}
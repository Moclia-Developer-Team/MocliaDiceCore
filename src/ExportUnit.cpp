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

void classicDiceUnit(char *&inputExp, char *&middleExp, char *&reason, int64_t &result, char *&exception)
{
    Moclia::exp_t classicExp;
    classicExp.original = inputExp;
    Moclia::calc::expressionCalculator(classicExp);

    inputExp = new char (classicExp.original.size() + 1);
    middleExp = new char (classicExp.middleCalc.size() + 1);
    reason = new char (classicExp.reason.size() + 1);
    exception = new char (classicExp.exception.size() + 1);

    strcpy_s(inputExp, strlen(classicExp.original.c_str()) + 1, classicExp.original.c_str());
    strcpy_s(middleExp, strlen(classicExp.middleCalc.c_str()) + 1,classicExp.middleCalc.c_str());
    strcpy_s(reason, strlen(classicExp.reason.c_str()) + 1, classicExp.reason.c_str());
    strcpy_s(exception, strlen(classicExp.exception.c_str()) + 1, classicExp.exception.c_str());

    result = strtoll(classicExp.finalResult.c_str(), nullptr, 10);
    return;
}

void fudgeDiceUnit(char *&inputExp, char *&middleExp, char *&reason, int64_t &result, char *&exception)
{
    Moclia::exp_t fudgeExp;
    fudgeExp.original = inputExp;
    Moclia::fudge::calc(fudgeExp);

    middleExp = new char (fudgeExp.middleCalc.size() + 1);
    reason = new char (fudgeExp.reason.size() + 1);
    exception = new char (fudgeExp.exception.size() + 1);

    strcpy_s(middleExp, strlen(fudgeExp.middleCalc.c_str()) + 1, fudgeExp.middleCalc.c_str());
    strcpy_s(reason, strlen(fudgeExp.reason.c_str()) + 1, fudgeExp.reason.c_str());
    strcpy_s(exception, strlen(fudgeExp.exception.c_str()) + 1,fudgeExp.exception.c_str());

    result = strtoll(fudgeExp.finalResult.c_str(), nullptr, 10);
    return;
}

void dx3AddDiceUnit(char *&inputExp, char *&iterationExp, char *&middleExp, char *&reason, int64_t &result, char *&exception)
{
    Moclia::exp_t dx3Exp;
    dx3Exp.original = inputExp;
    Moclia::DX3::addDice(dx3Exp);

    inputExp = new char (dx3Exp.original.size() + 1);
    iterationExp = new char (dx3Exp.iterationCalc.size() + 1);
    middleExp = new char (dx3Exp.middleCalc.size() + 1);
    reason = new char (dx3Exp.reason.size() + 1);
    exception = new char (dx3Exp.reason.size() + 1);

    strcpy_s(inputExp,strlen(dx3Exp.original.c_str()) + 1,dx3Exp.original.c_str());
    strcpy_s(iterationExp, strlen(dx3Exp.iterationCalc.c_str()) + 1,dx3Exp.iterationCalc.c_str());
    strcpy_s(middleExp, strlen(dx3Exp.middleCalc.c_str()) + 1, dx3Exp.middleCalc.c_str());
    strcpy_s(reason, strlen(dx3Exp.reason.c_str()) + 1, dx3Exp.reason.c_str());
    strcpy_s(exception, strlen(dx3Exp.exception.c_str()) + 1, dx3Exp.exception.c_str());

    result = strtoll(dx3Exp.finalResult.c_str(), nullptr, 10);
    return;
}
//
// Created by wubai on 2022/1/25 0025.
//
#pragma once

#ifndef MOCLIADICECORE_EXPORTUNIT_H
#define MOCLIADICECORE_EXPORTUNIT_H

#endif //MOCLIADICECORE_EXPORTUNIT_H

#define MOCLIA_BUILD_SHARED_LIB

#ifdef MOCLIA_BUILD_SHARED_LIB
#if defined(_WIN32) || defined(_WIN64)
#define MOCLIA_EXPORT  __declspec(dllexport)
#elif defined(__Linux__)
#define MOCLIA_EXPORT  attribute__ ((visibility("default")))
#else
    #define MOCLIA_EXPORT
#endif
#else
#define MOCLIA_EXPORT
#endif

#include "RollDiceUnit.h"

extern "C"
{
struct exp_t
{
    std::string original; // 输入和规范化后的原始表达式
    std::deque<std::string> postfix; // 转换后的后缀表达式
    std::string middleCalc; // 返回给用户的计算中间过程
    std::string finalResult; // 最终计算得到的结果
    std::string reason; // 分离出来的理由
    std::string exception; // 表达式错误信息

    void clear();
};

struct dice_t
{
    int64_t number = 0; // 骰子个数
    int64_t surface = 0; // 骰子面数
    char extFlag = 'K'; // K还是Q
    int64_t flagNum = 1; // 取多少个值
    int64_t result = 0; // 所有骰子结果的总和
    std::deque<int64_t> randResult; // 投掷原始结果的队列
};
// 可以提供的工具函数（GeneralUnit/tool）
MOCLIA_EXPORT uint64_t toolGetRDTSC();
MOCLIA_EXPORT int64_t toolRandNumber(int64_t min, int64_t max);
MOCLIA_EXPORT void toolStringToWString();
MOCLIA_EXPORT void toolWStringToString();
// 基础掷骰相关函数（RollDiceUnit/calc）
MOCLIA_EXPORT void classicDice(dice_t &dice);
MOCLIA_EXPORT void classicDiceExpCalc(exp_t &expression);
MOCLIA_EXPORT void classicDiceExpStandard(exp_t &expression);
}
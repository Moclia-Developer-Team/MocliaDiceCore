/**
 * @name MocliaDice
 * @brief 掷骰表达式的处理和计算相关方法定义
 * @file RollDiceUnit.h
 * @copyright 星翛-STASWIT 2018-2022
 * @note 如果要使用英文错误输出，请取消定义 MOCLIA_LANG_ZH
 * */
#pragma once

#ifndef MOCLIADICECORE_ROLLDICEUNIT_H
#define MOCLIADICECORE_ROLLDICEUNIT_H
#endif //MOCLIADICECORE_ROLLDICEUNIT_H

#include "GeneralUnit.h"

/**
 * @namespace moclia
 * @brief 墨可莉雅的所有定义和实现
 * */
namespace Moclia
{
    /**
     * @brief 骰子结构
     * @class int64_t number：骰子个数\n
     *         int64_t surface：骰子面数\n
     *         int64_t reason：所有骰子结果的总和\n
     *         std::deque\<int64_t\> randomResult：掷骰原始结果的队列\n
     * */
    struct dice_t
    {
        int64_t number = 0; // 骰子个数
        int64_t surface = 0; // 骰子面数
        char extFlag = 'K'; // K还是Q
        int64_t flagNum = 1; // 取多少个值
        int64_t result = 0; // 所有骰子结果的总和
        std::deque<int64_t> randResult; // 投掷原始结果的队列
        std::deque<std::string> randResultStr;
        std::string exception; // 错误
    };

    /**
     * @brief 表达式结构
     * @class std::string original：输入和规范化后的原始表达式\n
     *        std::deque\<std::string\> postfix：转换后的后缀表达式\n
     *        std::string iterationCalc：返回给用户的迭代计算中间过程\n
     *        std::string middleCalc：返回给用户的计算中间过程\n
     *        std::string finalResult：最终计算得到的结果\n
     *        std::string reason：分离出来的理由
     * */
    struct exp_t
    {
        std::string original; // 输入和规范化后的原始表达式
        std::deque<std::string> postfix; // 转换后的后缀表达式
        std::string iterationCalc; // 迭代计算中间过程
        std::string middleCalc; // 返回给用户的计算中间过程
        std::string finalResult; // 最终计算得到的结果
        std::string reason; // 分离出来的理由
        std::string exception; // 表达式错误信息

        void clear();
    };

    /**
     * @brief 掷骰计算类
     * */
    class calc
    {
    public:
        // 掷骰表达式计算和中间过程生成
        static void expressionCalculator(exp_t &expression);
        // XdYkqZ规则最小掷骰表达式计算
        static dice_t diceCalc(int64_t diceNumber, int64_t diceSurface, char extFlag, int64_t flagNum);
    private:
        // 掷骰表达式规范化
        static void expressionStandard(exp_t &expression);
        // 中缀表达式转后缀表达式
        static void toPostfixExp(std::string &infix, std::deque<std::string> &exper);
        // 后缀表达式转中缀表达式
        static void toInfixExp(exp_t &expression);
    };
}
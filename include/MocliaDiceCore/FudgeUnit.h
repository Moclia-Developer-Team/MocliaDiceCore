/**
 * @name MocliaDice
 * @brief 自由无界定制游戏引擎（FUDGE）和桌面环境里的奇妙冒险（FATE）规则的相关定义
 * @file FudgeUnit.h
 * @copyright 星翛-STASWIT 2018-2022
 * */
#pragma once

#ifndef MOCLIADICECORE_FUDGEUNIT_H
#define MOCLIADICECORE_FUDGEUNIT_H
#endif //MOCLIADICECORE_FUDGEUNIT_H

#include "GeneralUnit.h"
#include "RollDiceUnit.h"

namespace Moclia
{
    class fudge
    {
    public:
        /**
         * @brief Fudge表达式接收与处理
         * @param fudgeExp 确认为Fudge表达式的表达式变量
         * */
        static void calc(exp_t &fudgeExp);
    private:
        /**
         * @brief fudge处理函数内部表达式
         * */
        struct fdice_t
        {
            int64_t number; // 掷fudge骰的个数
            std::string randResult; // fudge每个骰的掷骰结果
            std::string finalResult; // 最终结果
            std::string exception; // 错误原因
        };

        /**
         * @brief Fudge掷骰表达式规范化
         * @param fudgeExp Fudge表达式
         * */
        static void fudgeExpStandard(exp_t &fudgeExp);
        /**
         * @brief Fudge计算核心
         * @param fudgeRoll fudge自定义类型
         * */
        static void fudgeRoll(fdice_t &fudgeRoll);
    };
}
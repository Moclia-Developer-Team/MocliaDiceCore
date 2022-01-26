/**
 * @name MocliaDice
 * @brief 导出函数定义
 * @file ExportUnit.h
 * @copyright 星翛-STASWIT 2018-2022
 * */
#pragma once

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

#include "GeneralUnit.h" // 全局工具
#include "RollDiceUnit.h" // 基础掷骰
#include "FudgeUnit.h" // Fudge引擎相关
#include "DX3Unit.h" // DX3规则相关

extern "C"
{
    /**
     * @brief 获取高精度CPU时钟刻
     * @return CPU高精度时钟刻
     * @note 可以用来计时或者作为随机数种子
     * */
    MOCLIA_EXPORT uint64_t RDTSCTool();
    /**
     * @brief 生成整数随机数
     * @param min 生成随机数的最小值
     * @param max 生成随机数的最大值
     * @return 在[min,max]范围内的随机值
     * @note 生成的随机数符合均等分布
     * */
    MOCLIA_EXPORT int64_t randTool(int64_t min, int64_t max);
    /**
     * @brief 基础掷骰表达式计算
     * @param inputExp 输入的未规范过的字符串表达式
     * @param middleExp 存放中间计算过程的字符串变量
     * @param reason 规范化后分离出的原因
     * @param result 存放最终计算得到的结果
     * @param exception 如有出错这里不为空
     * @return inputExp 规范后原始字符串表达式\n
     *         middleExp 中间计算过程\n
     *         reason 原因\n
     *         result 计算结果\n
     *         exception 有错误这里不为空
     * @note 该函数作为最基础的掷骰表达式处理函数，被所有规则表达式处理函数引用。\n
     * 该函数处理统一处理了表达式规范化到计算的全部过程，使用者可轻松获取计算结果和附属结果。
     * */
    MOCLIA_EXPORT void classicDiceUnit(const char *inputExp, const char * middleExp, const char *reason, int64_t result, const char *exception);
    /**
     * @brief Fudge引擎特殊骰子的表达式计算
     * @param inputExp 原始未规范Fudge表达式
     * @param middleExp 存放中间计算过程的变量
     * @param reason 存放理由的变量
     * @param result 存放最终计算结果的变量
     * @param exception 如有出错这里不为空
     * @return inputExp 规范化后的原始表达式\n
     *         middleExp 中间掷骰得到的结果\n
     *         reason 规范化后分离出来的理由\n
     *         result 根据Fudge规则计算得的最终结果\n
     *         exception 有错误这里不为空
     * @note Fudge引擎采用的骰子是一个特殊的六面骰，两个对面标记+，两个对面标记-，两个对面为空。\n
     * */
    MOCLIA_EXPORT void fudgeDiceUnit(const char *inputExp, const char *middleExp, const char *reason, int64_t result, const char *exception);
    /**
     * @brief 双重十字加骰表达式计算
     * @param inputExp 原始未规范Fudge表达式
     * @param iterationExp 存放加骰迭代过程中的掷骰结果的变量
     * @param middleExp 存放中间计算过程的变量
     * @param reason 存放理由的变量
     * @param result 存放最终计算结果的变量
     * @param exception 如有出错这里不为空
     * @return inputExp 规范化后的原始表达式\n
     *         iterationExp 加骰迭代掷骰的结果\n
     *         middleExp 最终结果计算的计算式\n
     *         reason 规范化后分离出来的理由\n
     *         result 根据DX3规则计算得的最终结果\n
     *         exception 有错误这里不为空
     * @note DX3的加骰最终计算结果是：加骰次数 × 10 + 最后一次掷骰结果中的最大值
     * */
    MOCLIA_EXPORT void dx3AddDiceUnit(const char *inputExp, const char *iterationExp, const char *middleExp, const char *reason, int64_t result, const char *exception);
}
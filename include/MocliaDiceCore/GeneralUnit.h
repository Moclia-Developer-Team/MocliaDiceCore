/**
 * @name MocliaDice
 * @brief 引用库定义包含和通用工具类定义及其他通用引用
 * @file GeneralUnit.h
 * @copyright 星翛-STASWIT 2018-2022
 * @note 如果要使用英文错误输出，请取消定义 MOCLIA_LANG_ZH
 * */
#pragma once

#ifndef MOCLIADICE_GENERALUNIT_H
#define MOCLIADICE_GENERALUNIT_H
#endif //MOCLIADICE_GENERALUNIT_H

#define MOCLIA_LANG_ZH

#include <iostream>
#include <deque>
#include <random>
#include <exception>
#include <string>
#include <algorithm>
#include <codecvt>
#include <locale>
#include <iterator>
#include <cmath>
#include <map>

/**
 * @namespace moclia
 * @brief 墨可莉雅的所有定义和实现
 * */
namespace Moclia
{
    /**
     * @brief 工具类
     * */
    class tool
    {
    public:
        // 获取cpu时钟刻
        static uint64_t getCycleCount();
        // 数组求和
        static int64_t dequeSum(std::deque<int64_t> needSum);
        // 随机数生成器
        static int64_t randNumber(int64_t min, int64_t max);
        // 带下标的快速排序算法
        static void quickSort(std::deque<int64_t> &sortArray, std::deque<int64_t> &subscriptArray, int64_t beginSort, int64_t endSort);
        // 正常快速排序算法
        static void quickSort(std::deque<int64_t> &sortArray, int64_t beginSort, int64_t endSort);
        // string 转 wstring
        static void sswConversion(std::string &str, std::wstring &wstr);
        // wstring 转 string
        static void sswConversion(std::wstring &wstr, std::string &str);
        // 查询窄字节字符串是否全是数字
        static bool isDigitAll(std::string str);
        // 查询宽字节字符串是否全是数字
        static bool isDightAll(std::wstring wstr);
        // 清除双精度浮点计算里多余的0
        static void clearZero(std::string &str);
        // 判断字符串是不是浮点数
        static bool isFloat(std::string str);
        // 拼接表达式
        static void expSum(std::string &str, std::string &expression);
        // 关键变量替换
        static void varImport();
    };
}
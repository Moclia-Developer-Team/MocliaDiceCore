/**
 * @name MocliaDiceCore
 * @brief 通用工具类的实现
 * @file GeneralUnit.cpp
 * @headerfile GeneralUnit.h
 * @copyright 星翛-STASWIT 2018-2022
 * */
#include "GeneralUnit.h"

namespace Moclia
{
#ifdef _WIN32
    /**
     * @brief 获取CPU高精度时间戳作为随机数种子
     * @return CPU时钟刻
     * @test 完成单元测试
     * @note 因为使用了内联汇编，所以部分编译器无法通过编译
     * */
    uint64_t tool::getCycleCount()
    {
        return __rdtsc();
    }
#elif __linux__
    /**
     * @brief 获取CPU高精度时间戳作为随机数种子
     * @return CPU时钟刻
     * @test 完成单元测试
     * @note 因为使用了内联汇编，所以部分编译器无法通过编译
     * */
    uint64_t tool::getCycleCount()
    {
        uint64_t low,high;
        __asm__ volatile ("rdtsc" : "=a" (low), "=d" (high));
        return (high << 32) | low;
    }
#endif

    /**
     * @brief 整型数组求和
     * @param needSum 需要求和的纯整型数组
     * @return 求和后的结果
     * */
    int64_t tool::dequeSum(std::deque<int64_t> needSum)
    {
        int64_t result = 0;

        for (int64_t num : needSum)
        {
            result += num;
        }

        return result;
    }

    /**
     * @brief 随机数生成器
     * @param min 生成随机数的最小边界
     * @param max 生成随机数的最大边界
     * @return 随机数
     * @note 范围 [min,max]
     * */
    int64_t tool::randNumber(int64_t min, int64_t max)
    {
        std::mt19937_64 drand(getCycleCount());
        std::uniform_int_distribution<int64_t> dist(min,max);
        return dist(drand);
    }

    /**
     * @brief 标准快速排序算法
     * @param sortArray 要排序的队列
     * @param beginSort 要排序队列的起始位置
     * @param endSort 要排序队列的结束位置
     * @note 排序后的结果直接存储在sortArray中
     * */
    void tool::quickSort(std::deque<int64_t> &sortArray, int64_t beginSort, int64_t endSort)
    {
        if (beginSort < endSort)
        {
            int64_t temp = sortArray.at(beginSort),
                left = beginSort,
                right = endSort;

            while (left < right)
            {
                while (left < right && sortArray.at(right) > temp)
                {
                    right--;
                }

                sortArray.at(left) = sortArray.at(right);

                while (left < right && sortArray.at(left) <= temp)
                {
                    left++;
                }

                sortArray.at(right) = sortArray.at(left);
            }

            sortArray.at(left) = temp;

            quickSort(sortArray, beginSort, left - 1);
            quickSort(sortArray, left + 1, endSort);
        }
        else
        {
            return;
        }
    }

    /**
     * @brief 带下标排序的快速排序算法
     * @param sortArray 要排序的队列
     * @param subscriptArray 要排序的队列的下标队列
     * @param beginSort 要排序队列的起始位置
     * @param endSort 要排序队列的结束位置
     * @note 排序后的结果直接存储在sortArray中，同时下标会根据原队列排序情况被打乱，但下标和数字对应关系不变
     * */
    void tool::quickSort(
            std::deque<int64_t> &sortArray, std::deque<int64_t> &subscriptArray, int64_t beginSort, int64_t endSort)
    {
        if (beginSort < endSort)
        {
            int64_t temp = sortArray.at(beginSort),
                tempPos = subscriptArray.at(beginSort),
                left = beginSort,
                right = endSort;

            while (left < right)
            {
                while (left < right && sortArray.at(right) > temp)
                {
                    right--;
                }

                sortArray.at(left) = sortArray.at(right);
                subscriptArray.at(left) = subscriptArray.at(right);

                while (left < right && sortArray.at(left) <= temp)
                {
                    left++;
                }

                sortArray.at(right) = sortArray.at(left);
                subscriptArray.at(right) = subscriptArray.at(left);
            }

            sortArray.at(left) = temp;
            subscriptArray.at(left) = tempPos;

            quickSort(sortArray, subscriptArray, beginSort, left - 1);
            quickSort(sortArray, subscriptArray, left + 1, endSort);
        }
        else
        {
            return;
        }
    }

    /**
     * @brief 宽字节字符串判断是否全是数字
     * @param wstr 宽字节字符串
     * @return true or false
     * */
    bool tool::isDightAll(std::wstring wstr)
    {
        bool flag = !wstr.empty() && std::all_of(wstr.begin(), wstr.end(), ::iswdigit);
        return flag;
    }

    /**
     * @brief 窄字节字符串判断是否全是数字
     * @param str 窄字节字符串
     * @return true or false
     * */
    bool tool::isDigitAll(std::string str)
    {
        bool flag = !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
        return flag;
    }

    /**
     * @brief 判断窄字节字符串是否是浮点数字符串
     * @param str 窄字节字符串
     * @return true or false
     * */
    bool tool::isFloat(std::string str)
    {
        if (str[0] = '-')
        {
            str = str.substr(1,str.size() - 1);
        }
        for (char num : str)
        {
            if (std::isdigit(num) == 0)
            {
                if (num != '.')
                {
                    return false;
                }
            }
        }

        return true;
    }

    /**
     * @brief 窄字节字符串转宽字节字符串
     * @param str 窄字节字符串
     * @param wstr 宽字节字符串
     * */
    void tool::sswConversion(std::string &str, std::wstring &wstr)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        wstr = converter.from_bytes(str);
        return;
    }

    /**
     * @brief 宽字节字符串转窄字节字符串
     * @param wstr 宽字节字符串
     * @param str 窄字节字符串
     * */
    void tool::sswConversion(std::wstring &wstr, std::string &str)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        str = converter.to_bytes(wstr);
        return;
    }

    /**
     * @brief 清除浮点数计算后返回的字符串多余的0
     * @param str 存储浮点数的字符串
     * @note 如果是非纯浮点数字符串是不会执行方法的
     * */
    void tool::clearZero(std::string &str)
    {
        if (isFloat(str) && str.find(".") != std::string::npos)
        {
            bool extZero = true;
            for (int64_t digit = str.size() - 1; digit >= 0; digit--)
            {
                if (str[digit] != '0')
                {
                    if (str[digit] == '.' && extZero)
                    {
                        extZero = false;
                        digit--;
                    }
                    else
                    {
                        extZero = false;
                    }
                }

                if (extZero == false)
                {
                    str = str.substr(0,digit + 1);
                    return;
                }
            }
        }
        else
        {
            return;
        }
    }

    /**
     * @brief 表达式字符串合并
     * @param str 要合并的字符串
     * @param expression 被合并的字符串
     * @note 废弃方法
     * */
    void tool::expSum(std::string &str, std::string &expression)
    {
        if (expression.empty())
        {
            expression = str;
        }
        else
        {
            expression += "+" + str;
        }
        return;
    }
}
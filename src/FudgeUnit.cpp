/**
 * @name MocliaDice
 * @brief 自由无界定制游戏引擎（FUDGE）和桌面环境里的奇妙冒险（FATE）规则的相关实现
 * @file FudgeUnit.cpp
 * @headerfile FudgeUnit.h
 * @copyright 星翛-STASWIT 2018-2022
 * */

#include "MocliaDiceCore/FudgeUnit.h"

/**
 * @brief Fudge特殊说明：正常骰子的对面值 ==> fudge骰子面值
 * @note 1 => 6 ==> + => 1\n
 *       2 => 5 ==> - => -1\n
 *       3 => 4 ==> 0 => 0\n
 * @details Fudge使用的骰子是一个两面为+，两面为-，两面为空的特殊六面骰，一般为四个，这里使用标准六面骰换算替代。
 * */

namespace Moclia
{
    // fudge数字和标识换算
    std::map<int64_t,std::string> fudgeContrast =
            {
                {0,"0"},
                {1,"+"},
                {-1,"-"}
            };

    // Fudge掷骰
    void fudge::fudgeRoll(fdice_t &fudgeRoll)
    {
        dice_t fDice;
        //exp_t fExp;
        fDice = calc::diceCalc(fudgeRoll.number,6,'K',fudgeRoll.number);
        for (int64_t fr : fDice.randResult)
        {
            switch (fr)
            {
                case 1:
                case 6:
                    fr = 1;
                    fDice.randResultStr.emplace_back(fudgeContrast[fr]);
                    break;
                case 2:
                case 5:
                    fr = -1;
                    fDice.randResultStr.emplace_back(fudgeContrast[fr]);
                    break;
                case 3:
                case 4:
                    fr = 0;
                    fDice.randResultStr.emplace_back(fudgeContrast[fr]);
                    break;
                default:
                    break;
            }
        }

        //fDice.result = tool::dequeSum(fDice.randResult);
        fudgeRoll.finalResult = std::to_string(tool::dequeSum(fDice.randResult));
        fudgeRoll.randResult = "[";

        for (int64_t fs : fDice.randResult)
        {
            if (fudgeRoll.randResult.back() == '[')
            {
                fudgeRoll.randResult += fudgeContrast[fs];
            }
            else if (fudgeRoll.randResult.back() == '+'
                || fudgeRoll.randResult.back() == '-'
                || fudgeRoll.randResult.back() == '0'
                || fudgeRoll.randResult.back() == ',')
            {
                fudgeRoll.randResult += ",";
                fudgeRoll.randResult += fudgeContrast[fs];
            }
            else
            {
                //exception
            }
        }

        fudgeRoll.randResult += "]";
        return;
    }

    // Fudge表达式规范化
    void fudge::fudgeExpStandard(exp_t &fudgeExp)
    {
        bool isReason = false;
        std::string stand;
        fudgeExp.reason.clear();
        for (char fo : fudgeExp.original)
        {
            if (stand.empty() && (fo == 'f' || fo == 'F'))
            {
                stand = "4F";
                isReason = true;
            }

            if (!isReason)
            {
                if (std::isdigit(fo) != 0)
                {
                    stand += fo;
                }
                else if (fo == 'f' || fo == 'F')
                {
                    stand += 'F';
                    isReason = true;
                }
                else
                {
#ifdef MOCLIA_LANG_ZH
                    fudgeExp.exception = "Fudge表达式错误";
#else
                    fudgeExp.exception = "Wrong fudge expression";
#endif
                }
            }
            else
            {
                fudgeExp.reason += fo;
            }
        }

        fudgeExp.original = stand;
        stand.clear();
    }

    // Fudge表达式接收与处理
    void fudge::calc(exp_t &fudgeExp)
    {
        fdice_t fd;
        std::string temp;
        fudgeExpStandard(fudgeExp);
        for (char fe : fudgeExp.original)
        {
            switch (fe)
            {
                case '0' ... '9':
                    temp += fe;
                    break;
                case 'F':
                default:
                    break;
            }
        }

        fd.number = strtoll(temp.c_str(), nullptr,10);
        temp.clear();
        fudgeRoll(fd);
        fudgeExp.middleCalc = fd.randResult;
        fudgeExp.finalResult = fd.finalResult;
        return;
    }
}
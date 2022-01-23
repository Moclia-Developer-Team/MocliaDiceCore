/**
 * @name MocliaDice
 * @brief 处理掷骰表达式所有方法的实现
 * @file RollDiceUnit.cpp
 * @headerfile RollDiceUnit.h
 * @copyright 星翛-STASWIT 2018-2022
 * */
#include "MocliaDiceCore/RollDiceUnit.h"

/**
 * @namespace moclia
 * @brief 墨可莉雅的所有定义和实现
 * */
namespace Moclia
{
    tool calcTool;
    /**
     * @brief XdYkqZ规则掷骰表达式计算
     * @param diceNumber：骰子的个数
     * @param diceSurface：这堆骰子的面数
     * @param extFlag：k或q，大小写均可
     * @param getSize：k或q后的参数
     * @note K{num}：指代取这堆骰子中最大的num个结果\n
     * Q{num}：指代取这对骰子中最小的num个结果
     * @return 取到的掷骰原始值的数组和该数组求和的结果组成的结构体
     * @struct std::deque\<int64_t\> randomResult\n
     *         int64_t rollResult
     * @test 完成单元测试
     * */
    dice_t calc::diceCalc(int64_t diceNumber, int64_t diceSurface, char extFlag, int64_t flagNum)
    {
        std::deque<int64_t> diceResult; // 保存所有掷骰结果
        dice_t reDice; // 返回的骰子结构
        reDice.randResult.clear();

        if (diceSurface == 0)
        {
            reDice.result = 0;
            reDice.randResult.push_back(0);
            return reDice;
        }

        // 掷几个骰子循环几次
        for (int diceRoll = 0; diceRoll < diceNumber; diceRoll++)
        {
            // 将掷骰结果入栈
            diceResult.push_back(calcTool.randNumber(1,diceSurface));
        }

        // 判断KQ值是否小于骰子个数
        if (flagNum < diceNumber)
        {
            // 复制掷骰结果用来排序
            std::deque<int64_t> dResultForSort(diceResult);

            // 创建结果的原下标队列
            std::deque<int64_t> resultSubscript;
            for (int sub = 0; sub < dResultForSort.size(); sub++)
            {
                resultSubscript.push_back(sub);
            }

            // 带下标排序的快速排序算法
            calcTool.quickSort(dResultForSort,resultSubscript,0,dResultForSort.size() - 1);

            std::deque<int64_t> kqResult;
            std::deque<int64_t> subSort;
            // 根据extFlag决定读取顺序
            if (toupper(extFlag) == 'K')
            {
                // 逆向查找下标并存入排序队列
                for (int64_t kGetSub = 0; kGetSub < flagNum; kGetSub++)
                {
                    subSort.push_back(resultSubscript.at(resultSubscript.size() - kGetSub - 1));
                }

                // 不带下标的快速排序算法
                calcTool.quickSort(subSort,0,subSort.size() - 1);

                // 循环通过排序后的下标取原值
                for (int64_t kGetResult = 0; kGetResult < flagNum; kGetResult++)
                {
                    kqResult.push_back(diceResult.at(subSort.at(kGetResult)));
                }
            }
            else if (toupper(extFlag) == 'Q')
            {
                // 正向查找下标并存入排序队列
                for (int64_t qGetSub = 0; qGetSub < flagNum; qGetSub++)
                {
                    subSort.push_back(resultSubscript.at(qGetSub));
                }

                // 不带下标的快速排序算法
                calcTool.quickSort(subSort,0,subSort.size() - 1);

                // 循环通过排序后的下标取原值
                for (int64_t qGetResult = 0; qGetResult < flagNum; qGetResult++)
                {
                    kqResult.push_back(diceResult.at(subSort.at(qGetResult)));
                }
            }
            else
            {
                // 抛出错误
#ifdef MOCLIA_LANG_ZH
                throw std::invalid_argument("extFlag仅接受 k 或 q 参数，不区分大小写");
#else
                throw std::invalid_argument("The extFlag argument can only input k or q");
#endif
            }

            reDice.randResult = kqResult;
            reDice.result = calcTool.dequeSum(kqResult);
        }
        else if (flagNum == diceNumber) // 如果二者相等免去排序步骤
        {
            reDice.randResult = diceResult;
            reDice.result = calcTool.dequeSum(diceResult);
        }
        else
        {
            // 抛出错误
#ifdef MOCLIA_LANG_ZH
            throw std::out_of_range("flagNum不能大于diceNumber");
#else
            throw std::out_of_range("The value of flagNum could not bigger than diceNumber");
#endif
        }

        return reDice;
    }

    /**
     * @brief 表达式计算
     * @param expression 表达式结构
     * @note 输入的是表达式结构里的 original , 输出的是表达式结构里的 middleCalc, finalResult, reason
     * */
    void calc::expressionCalculator(exp_t &expression)
    {
        toPostfixExp(expression.original,expression.postfix);

        std::deque<std::string> temp;
        std::string tmpStr,left,right;
        int64_t tmpSiz;
        int64_t kqRight = 0;
        dice_t toRoll;
        char kqFlag;
        double tmpNum;

        for (std::string post : expression.postfix)
        {
            if (std::isdigit(post[0])) // 如果是数字直接入栈
            {
                temp.push_back(post);
            }
            else
            {
                switch (post[0])
                {
                    case '+':
                        tmpSiz = temp.size();
                        left = temp.at(tmpSiz - 2);
                        right = temp.at(tmpSiz - 1);
                        tmpNum = strtod(left.c_str(), nullptr)
                                + strtod(right.c_str(), nullptr);
                        temp.pop_back();
                        temp.pop_back();
                        tmpStr = std::to_string(tmpNum);
                        temp.push_back(tmpStr);
                        break;
                    case '-':
                        tmpSiz = temp.size();
                        left = temp.at(tmpSiz - 2);
                        right = temp.at(tmpSiz - 1);
                        tmpNum = strtod(left.c_str(), nullptr)
                                 - strtod(right.c_str(), nullptr);
                        temp.pop_back();
                        temp.pop_back();
                        tmpStr = std::to_string(tmpNum);
                        temp.push_back(tmpStr);
                        break;
                    case '*':
                        tmpSiz = temp.size();
                        tmpNum = strtod(temp.at(tmpSiz - 1).c_str(), nullptr)
                                 * strtod(temp.at(tmpSiz - 2).c_str(), nullptr);
                        temp.pop_back();
                        temp.pop_back();
                        tmpStr = std::to_string(tmpNum);
                        temp.push_back(tmpStr);
                        break;
                    case '/':
                        tmpSiz = temp.size();
                        tmpNum = strtod(temp.at(tmpSiz - 1).c_str(), nullptr)
                                 / strtod(temp.at(tmpSiz - 2).c_str(), nullptr);
                        temp.pop_back();
                        temp.pop_back();
                        tmpStr = std::to_string(tmpNum);
                        temp.push_back(tmpStr);
                        break;
                    case '^':
                        tmpSiz = temp.size();
                        tmpNum = pow(strtod(temp.at(tmpSiz - 2).c_str(), nullptr),
                                     strtod(temp.at(tmpSiz - 1).c_str(), nullptr));
                        temp.pop_back();
                        temp.pop_back();
                        tmpStr = std::to_string(tmpNum);
                        temp.push_back(tmpStr);
                        break;
                    case 'D':
                        tmpSiz = temp.size();
                        toRoll.number = strtoll(temp.at(tmpSiz - 2).c_str(), nullptr, 10);
                        toRoll.surface = strtoll(temp.at(tmpSiz - 1).c_str(), nullptr, 10);
                        if (kqRight == 0)
                        {
                            toRoll = diceCalc(toRoll.number,toRoll.surface,
                                              'K', toRoll.number);
                        }
                        else
                        {
                            toRoll = diceCalc(toRoll.number,toRoll.surface,
                                              kqFlag, kqRight);
                        }
                        tmpNum = toRoll.result;
                        temp.pop_back();
                        temp.pop_back();
                        tmpStr = std::to_string(tmpNum);
                        temp.push_back(tmpStr);
                        break;
                    case 'K':
                        kqFlag = 'K';
                        tmpSiz = temp.size();
                        kqRight = strtoll(temp.at(tmpSiz - 1).c_str(), nullptr, 10);
                        temp.pop_back();
                        break;
                    case 'Q':
                        kqFlag = 'Q';
                        tmpSiz = temp.size();
                        kqRight = strtoll(temp.at(tmpSiz - 1).c_str(), nullptr, 10);
                        temp.pop_back();
                        break;
                    case '.':
                        tmpSiz = temp.size();
                        tmpNum = (strtod(temp.at(tmpSiz - 1).c_str(), nullptr) /
                                pow(10,temp.at(tmpSiz - 1).size()))
                                 + strtod(temp.at(tmpSiz - 2).c_str(), nullptr);
                        temp.pop_back();
                        temp.pop_back();
                        tmpStr = std::to_string(tmpNum);
                        temp.push_back(tmpStr);
                        break;
                }
            }
        }

        expression.finalResult = temp.back();
        calcTool.clearZero(expression.finalResult);
        temp.pop_back();
        expression.postfix.clear();
        return;
    }

    /**
     * @brief 中缀表达式转后缀表达式
     * @param infix  中缀表达式
     * @param exper  存放后缀表达式的队列
     * @note 运算符顺序：\n
     *      第一队列：+、-\n
     *      第二队列：*、/\n
     *      第三队列：^\n
     *      第四队列：D、K、Q\n
     *      第五队列：.\n
     *      改变优先级：(、)
     * */
    void calc::toPostfixExp(std::string &infix, std::deque<std::string> &exper)
    {
        //std::deque<std::string> exper; // 存数字和最终后缀表达式的队列
        exper.clear(); // 保证存后缀表达式的队列是空的，避免干扰
        std::deque<char> opera; // 存运算符的队列
        std::string tmpStr; // 缓存+类型转换
        std::string operaEp = "+-*/^()DKQ."; //运算符组
        int64_t tmpNum; // 类型转换
        for (char &ep : infix)
        {
            if (std::isdigit(ep) != 0) // 判断是否是数字
            {
                // 是数字直接入栈，多位数整合后入栈
                if (exper.empty())
                {
                    tmpStr = ep;
                    exper.push_back(tmpStr);
                }
                else if (!exper.empty() && calcTool.isDigitAll(tmpStr))
                {
                    tmpStr = ep;
                    tmpNum = strtoll(exper.back().c_str(),nullptr,10) * 10
                            + strtoll(tmpStr.c_str(),nullptr,10);
                    exper.pop_back();
                    exper.push_back(std::to_string(tmpNum));
                }
                else
                {
                    tmpStr = ep;
                    exper.push_back(tmpStr);
                }
            }
            else
            {
                // 不是数字即为运算符
                if (opera.empty() && operaEp.find(ep) != std::string::npos)
                {
                    // 如果运算符栈为空栈，直接入栈
                    tmpStr = ep;
                    opera.push_back(ep);
                }
                else if (!opera.empty() && operaEp.find(ep) != std::string::npos)
                {
                    // 如果不是空栈，判断上一个运算符
                    switch (ep)
                    {
                        // 加减是一级
                        case '+':
                        case '-':
                            switch (opera.back()) // 判断加减前的运算符
                            {
                                // 如果是连续加减
                                case '+':
                                case '-':
                                case '(':
                                    tmpStr = ep;
                                    opera.push_back(ep);
                                    break;
                                case '*':
                                case '/':
                                case '^':
                                case 'D':
                                case '.':
                                    tmpStr = opera.back();
                                    exper.push_back(tmpStr);
                                    opera.pop_back();
                                    opera.push_back(ep);
                                    break;
                                case 'K':
                                case 'Q':
                                    tmpStr = opera.back();
                                    exper.push_back(tmpStr);
                                    opera.pop_back();
                                    tmpStr = opera.back();
                                    exper.push_back(tmpStr);
                                    opera.pop_back();
                                    opera.push_back(ep);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        // 乘除是二级
                        case '*':
                        case '/':
                            switch (opera.back())  // 判断乘除前的运算符
                            {
                                case '+':
                                case '-':
                                case '*':
                                case '/':
                                case '(':
                                    tmpStr = ep;
                                    opera.push_back(ep);
                                    break;
                                case '^':
                                case 'D':
                                case '.':
                                    tmpStr = opera.back();
                                    exper.push_back(tmpStr);
                                    opera.pop_back();
                                    opera.push_back(ep);
                                    break;
                                case 'K':
                                case 'Q':
                                    tmpStr = opera.back();
                                    exper.push_back(tmpStr);
                                    opera.pop_back();
                                    tmpStr = opera.back();
                                    exper.push_back(tmpStr);
                                    opera.pop_back();
                                    opera.push_back(ep);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        // 乘方是三级
                        case '^':
                            switch (opera.back())
                            {
                                case '+':
                                case '-':
                                case '*':
                                case '/':
                                case '^':
                                case '(':
                                    tmpStr = ep;
                                    opera.push_back(ep);
                                    break;
                                case 'D':
                                case '.':
                                    tmpStr = opera.back();
                                    exper.push_back(tmpStr);
                                    opera.pop_back();
                                    opera.push_back(ep);
                                    break;
                                case 'K':
                                case 'Q':
                                    tmpStr = opera.back();
                                    exper.push_back(tmpStr);
                                    opera.pop_back();
                                    tmpStr = opera.back();
                                    exper.push_back(tmpStr);
                                    opera.pop_back();
                                    opera.push_back(ep);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        // 掷骰是四级
                        case 'D':
                        case 'K':
                        case 'Q':
                            switch (opera.back())
                            {
                                case '+':
                                case '-':
                                case '*':
                                case '/':
                                case '^':
                                case 'D':
                                case 'K':
                                case 'Q':
                                case '(':
                                    tmpStr = ep;
                                    opera.push_back(ep);
                                    break;
                                case '.':
                                    tmpStr = opera.back();
                                    exper.push_back(tmpStr);
                                    opera.pop_back();
                                    opera.push_back(ep);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        // 括号和小数点特殊处理
                        case '.':
                        case '(':
                            tmpStr = ep;
                            opera.push_back(ep);
                            break;
                        case ')':
                            while (opera.back() != '(')
                            {
                                tmpStr = opera.back();
                                exper.push_back(tmpStr);
                                opera.pop_back();
                            }
                            opera.pop_back();
                            break;
                        default:
                            break;
                    }
                }
                else
                {
#ifdef MOCLIA_LANG_ZH
                    throw std::invalid_argument("错误的运算符");
#else
                    throw std::invalid_argument("wrong opera");
#endif
                }
            }
        }

        for (auto operaPos = opera.rbegin(); operaPos < opera.rend(); operaPos++)
        {
            tmpStr = *operaPos;
            exper.push_back(tmpStr);
        }

        opera.clear();
    }

    /**
     * @brief 掷骰表达式规范化
     * @param expression 表达式结构
     * @note 仅处理表达式结构中的 original
     * */
    void calc::expressionStandard(exp_t &expression)
    {
        std::string stand;
        char temp = 0;
        std::string expEp = "+-*xX/^()DdKkQq.0123456789";
        std::string expCanWork = ")DdKkQq";
        bool isResult = false;
        int64_t bracketCount = 0; // 括号计数
        int decimalPointCount = 0; // 小数点计数
        int defaultDice = 100; // 默认骰

        expression.reason.clear();
        expression.exception.clear();

        if (expression.original.empty())
        {
            expression.original = "1D100";
        }

        for (char exp : expression.original)
        {
            if (!isResult)
            {
                if (expEp.find(exp) != std::string::npos)
                {
                    switch (exp)
                    {
                        case '+':
                        case '-':
                        case '*':
                        case '/':
                        case '^':
                            if (decimalPointCount != 0)
                            {
                                decimalPointCount--;
                            }

                            if (std::isdigit(temp) != 0)
                            {
                                // 是数字不做任何处理
                                stand += exp;
                                temp = exp;
                            }
                            else
                            {
                                // 非数字继续处理
                                if (expCanWork.find(temp) != std::string::npos)
                                {
                                    if (temp == 'D')
                                    {
                                        stand += std::to_string(defaultDice);
                                    }
                                    stand += exp;
                                    temp = exp;
                                }
                                else
                                {
                                    expression.reason += exp;
                                    isResult = true;
                                }
                            }
                            break;
                        case 'x':
                        case 'X':
                            if (decimalPointCount != 0)
                            {
                                decimalPointCount--;
                            }

                            if (std::isdigit(temp) != 0)
                            {
                                // 是数字不做任何处理
                                stand += '*';
                                temp = '*';
                            }
                            else
                            {
                                // 非数字继续处理
                                if (expCanWork.find(temp) != std::string::npos)
                                {
                                    if (temp == 'D')
                                    {
                                        stand += std::to_string(defaultDice);
                                    }
                                    stand += '*';
                                    temp = '*';
                                }
                                else
                                {
                                    expression.reason += exp;
                                    isResult = true;
                                }
                            }
                            break;
                        case '(':
                            bracketCount++;
                            // 判断是否是运算符
                            if (temp == 0 || expEp.find(temp) != std::string::npos)
                            {
                                if (temp == ')')
                                {
                                    expression.reason += exp;
                                    isResult = true;
                                }
                                else
                                {
                                    stand += exp;
                                    temp = exp;
                                }
                            }
                            else
                            {
                                expression.reason += exp;
                                isResult = true;
                            }
                            break;
                        case ')':
                            bracketCount--;
                            if (decimalPointCount != 0)
                            {
                                decimalPointCount--;
                            }

                            if (std::isdigit(temp) != 0)
                            {
                                // 是数字不做任何处理
                                stand += exp;
                                temp = exp;
                            }
                            else
                            {
                                // 非数字继续处理
                                if (expCanWork.find(temp) != std::string::npos)
                                {
                                    if (temp == 'D')
                                    {
                                        stand += std::to_string(defaultDice);
                                    }
                                    stand += exp;
                                    temp = exp;
                                }
                                else
                                {
                                    expression.reason += exp;
                                    isResult = true;
                                }
                            }
                            break;
                        case '.':
                            if (decimalPointCount != 0)
                            {
                                expression.reason += exp;
                                isResult = true;
                            }

                            if (std::isdigit(temp) != 0)
                            {
                                // 是数字不做任何处理
                                stand += exp;
                                temp = exp;
                                decimalPointCount++;
                            }
                            else
                            {
                                // 非数字继续处理
                                expression.reason += exp;
                                isResult = true;
                            }
                            break;
                        case 'D':
                            if (decimalPointCount != 0)
                            {
                                decimalPointCount--;
                            }

                            if (std::isdigit(temp) != 0)
                            {
                                // 是数字不做任何处理
                                stand += exp;
                                temp = exp;
                            }
                            else
                            {
                                // 非数字继续处理
                                if (temp == 0 || expCanWork.find(temp) != std::string::npos)
                                {
                                    if (temp != ')')
                                    {
                                        stand += std::to_string(1);
                                    }
                                    stand += exp;
                                    temp = exp;
                                }
                                else
                                {
                                    expression.reason += exp;
                                    isResult = true;
                                }
                            }
                            break;
                        case 'd':
                            if (decimalPointCount != 0)
                            {
                                decimalPointCount--;
                            }

                            if (std::isdigit(temp) != 0)
                            {
                                // 是数字不做任何处理
                                stand += 'D';
                                temp = 'D';
                            }
                            else
                            {
                                // 非数字继续处理
                                if (temp == 0 || expCanWork.find(temp) != std::string::npos)
                                {
                                    if (temp != ')')
                                    {
                                        stand += std::to_string(1);
                                    }
                                    stand += 'D';
                                    temp = 'D';
                                }
                                else
                                {
                                    expression.reason += exp;
                                    isResult = true;
                                }
                            }
                            break;
                        case 'K':
                        case 'Q':
                            if (decimalPointCount != 0)
                            {
                                decimalPointCount--;
                            }

                            if (std::isdigit(temp) != 0)
                            {
                                // K前存在D且D的位置是和K匹配的位置
                                if (stand.find_last_of('D') != std::string::npos && calcTool.isDigitAll(stand.substr(stand.find_last_of('D') + 1,stand.size() - 1)))
                                {
                                    stand += exp;
                                    temp = exp;
                                }
                                else
                                {
                                    expression.reason += exp;
                                    isResult = true;
                                }
                            }
                            else
                            {
                                // 非数字继续处理
                                if (temp == 'D')
                                {
                                    stand += std::to_string(defaultDice);
                                    stand += exp;
                                    temp = exp;
                                }
                                else if (temp == ')')
                                {
                                    if (stand.find_last_of('D') != std::string::npos && stand[stand.find_last_of('D') + 1] == '(')
                                    {
                                        stand += exp;
                                        temp = exp;
                                    }
                                }
                                else
                                {
                                    expression.reason += exp;
                                    isResult = true;
                                }
                            }
                            break;
                        case 'k':
                            if (decimalPointCount != 0)
                            {
                                decimalPointCount--;
                            }

                            if (std::isdigit(temp) != 0)
                            {
                                // K前存在D且D的位置是和K匹配的位置
                                if (stand.find_last_of('D') != std::string::npos && calcTool.isDigitAll(stand.substr(stand.find_last_of('D') + 1,stand.size() - 1)))
                                {
                                    stand += 'K';
                                    temp = 'K';
                                }
                                else
                                {
                                    expression.reason += exp;
                                    isResult = true;
                                }
                            }
                            else
                            {
                                // 非数字继续处理
                                if (temp == 'D')
                                {
                                    stand += std::to_string(defaultDice);
                                    stand += 'K';
                                    temp = 'K';
                                }
                                else if (temp == ')')
                                {
                                    if (stand.find_last_of('D') != std::string::npos && stand[stand.find_last_of('D') + 1] == '(')
                                    {
                                        stand += 'K';
                                        temp = 'K';
                                    }
                                }
                                else
                                {
                                    expression.reason += exp;
                                    isResult = true;
                                }
                            }
                            break;
                        case 'q':
                            if (decimalPointCount != 0)
                            {
                                decimalPointCount--;
                            }

                            if (std::isdigit(temp) != 0)
                            {
                                // Q前存在D且D的位置是和Q匹配的位置
                                if (stand.find_last_of('D') != std::string::npos && calcTool.isDigitAll(stand.substr(stand.find_last_of('D') + 1,stand.size() - 1)))
                                {
                                    stand += 'Q';
                                    temp = 'Q';
                                }
                                else
                                {
                                    expression.reason += exp;
                                    isResult = true;
                                }
                            }
                            else
                            {
                                // 非数字继续处理
                                if (temp == 'D')
                                {
                                    stand += std::to_string(defaultDice);
                                    stand += 'Q';
                                    temp = 'Q';
                                }
                                else if (temp == ')')
                                {
                                    if (stand.find_last_of('D') != std::string::npos && stand[stand.find_last_of('D') + 1] == '(')
                                    {
                                        stand += 'Q';
                                        temp = 'Q';
                                    }
                                }
                                else
                                {
                                    expression.reason += exp;
                                    isResult = true;
                                }
                            }
                            break;
                        case '0' ... '9':
                            if (temp == ')')
                            {
#ifdef MOCLIA_LANG_ZH
                                expression.exception = "错误的表达式";
                                //throw std::invalid_argument("错误的表达式");
#else
                                expression.exception = "invalid expression";
                                //throw std::invalid_argument("invalid expression");
#endif
                                return;
                            }
                            stand += exp;
                            temp = exp;
                            break;
                        default:
                            break;
                    }
                }
                else
                {
                    expression.reason += exp;
                    isResult = true;
                }
            }
            else
            {
                expression.reason += exp;
            }
        }

        if (stand.empty())
        {
            stand = "1D100";
        }

        if (std::isdigit(stand.back()) == 0 && stand.back() != ')')
        {
            if (stand.back() == 'D')
            {
                stand += std::to_string(defaultDice);
            }
            else
            {
                stand += std::to_string(1);
            }
        }

        if (bracketCount != 0)
        {
#ifdef MOCLIA_LANG_ZH
            expression.exception = "括号不匹配";
            //throw std::logic_error("括号不匹配");
#else
            expression.exception = "括号不匹配";
            //throw std::logic_error("bracket mismatch");
#endif
            return;
        }

        expression.original = stand;
        return;
    }

    /**
     * @brief 清除exp_t的所有数据
     * */
    void exp_t::clear()
    {
        exp_t::exception.clear();
        exp_t::reason.clear();
        exp_t::original.clear();
        exp_t::postfix.clear();
        exp_t::finalResult.clear();
        exp_t::middleCalc.clear();
    }
}
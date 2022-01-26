
#include "MocliaDiceCore/ExportUnit.h"

extern "C"
{
    MOCLIA_EXPORT uint64_t toolGetRDTSC()
    {
        return Moclia::tool::getCycleCount();
    }
    MOCLIA_EXPORT int64_t toolRandNumber(int64_t min, int64_t max)
    {
        return Moclia::tool::randNumber(min,max);
    }
    MOCLIA_EXPORT void toolStringToWString()
    {

    }
    MOCLIA_EXPORT void toolWStringToString()
    {

    }

    MOCLIA_EXPORT void classicDice(dice_t &dice)
    {

    }
    MOCLIA_EXPORT void classicDiceExpCalc(exp_t &expression)
    {

    }
    MOCLIA_EXPORT void classicDiceExpStandard(exp_t &expression)
    {

    }
}
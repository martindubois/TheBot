
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// File      TheBot-A/LabJack.cpp

#include "Component.h"

// ===== Import =============================================================
#include <KMS/Thread/Lock.h>

// ===== Labjack ============================================================
#include <LabJackUD.h>

// ===== TheBot-A ===========================================================
#include "../Common/LabJack.h"

// Constants
// //////////////////////////////////////////////////////////////////////////

#define AO_QTY (sizeof(mAO_States) / sizeof(mAO_States[0]))

#define IO_QTY (sizeof(mIO_Modes) / sizeof(mIO_Modes[0]))

// Public
// //////////////////////////////////////////////////////////////////////////

const KMS::DAQ::Id LabJack::FIO0 =  0;
const KMS::DAQ::Id LabJack::FIO1 =  1;
const KMS::DAQ::Id LabJack::FIO2 =  2;
const KMS::DAQ::Id LabJack::FIO3 =  3;
const KMS::DAQ::Id LabJack::FIO4 =  4;
const KMS::DAQ::Id LabJack::FIO5 =  5;
const KMS::DAQ::Id LabJack::FIO6 =  6;
const KMS::DAQ::Id LabJack::FIO7 =  7;

const KMS::DAQ::Id LabJack::EIO0 =  8;
const KMS::DAQ::Id LabJack::EIO1 =  9;
const KMS::DAQ::Id LabJack::EIO2 = 10;
const KMS::DAQ::Id LabJack::EIO3 = 11;
const KMS::DAQ::Id LabJack::EIO4 = 12;
const KMS::DAQ::Id LabJack::EIO5 = 13;
const KMS::DAQ::Id LabJack::EIO6 = 14;
const KMS::DAQ::Id LabJack::EIO7 = 15;

const KMS::DAQ::Id LabJack::CIO0 = 16;
const KMS::DAQ::Id LabJack::CIO1 = 17;
const KMS::DAQ::Id LabJack::CIO2 = 18;
const KMS::DAQ::Id LabJack::CIO3 = 19;

LabJack::LabJack()
{
    LJ_ERROR lRet = OpenLabJack(LJ_dtU3, LJ_ctUSB_RAW, NULL, true, &mHandle);
    if (LJE_NOERROR != lRet)
    {
        KMS_EXCEPTION_WITH_INFO(DEVICE, "OpenLabJack failed", lRet);
    }

    lRet = ePut(mHandle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);
    if (LJE_NOERROR != lRet)
    {
        KMS_EXCEPTION_WITH_INFO(DEVICE, "ePut failed", lRet);
    }

    for (unsigned int i = 0; i < AO_QTY; i++)
    {
        mAO_States[i].mValue_Raw = 0;
        mAO_States[i].mValue_V = 0.0;
    }

    for (unsigned int i = 0; i < IO_QTY; i++)
    {
        mIO_Modes [i] = IO_Mode::DIGITAL_INPUT;
        mIO_States[i] = false;
    }
}

void LabJack::IO_SetMode(KMS::DAQ::Id aId, IO_Mode aMode)
{
    assert(IO_QTY > aId);

    if (mIO_Modes[aId] != aMode)
    {
        LJ_ERROR lRet;

        KMS::Thread::Lock lLocl(&mZone0);

        switch (mIO_Modes[aId])
        {
        case IO_Mode::ANALOG_INPUT:
            assert(EIO7 >= aId);

            lRet = ePut(mHandle, LJ_ioPUT_ANALOG_ENABLE_BIT, aId, 0, 0);
            if (LJE_NOERROR != lRet)
            {
                KMS_EXCEPTION_WITH_INFO(DEVICE, "ePut failed", lRet);
            }
            break;

        case IO_Mode::DIGITAL_INPUT :
        case IO_Mode::DIGITAL_OUTPUT:
        case IO_Mode::DIGITAL_OUTPUT_LOW_HIGH_Z: break;

        default: assert(false);
        }

        switch (aMode)
        {
        case IO_Mode::ANALOG_INPUT:
            assert(EIO7 >= aId);

            lRet = ePut(mHandle, LJ_ioPUT_ANALOG_ENABLE_BIT, aId, 1, 0);
            if (LJE_NOERROR != lRet)
            {
                KMS_EXCEPTION_WITH_INFO(DEVICE, "ePut failed", lRet);
            }
            break;

        case IO_Mode::DIGITAL_INPUT:
        case IO_Mode::DIGITAL_OUTPUT: break;

        case IO_Mode::DIGITAL_OUTPUT_LOW_HIGH_Z: mIO_States[aId] = true; break;

        default: assert(false);
        }

        mIO_Modes[aId] = aMode;
    }
}

// ===== KMS::DAQ::IAnalogInputs ========================================

KMS::DAQ::AnalogValue LabJack::AI_Read(KMS::DAQ::Id aId)
{
    KMS::DAQ::AnalogValue lResult_V;

    KMS::Thread::Lock lLocl(&mZone0);

    LJ_ERROR lRet = eAIN(mHandle, aId, 0, &lResult_V, 0, 0, 0, 0, 0, 0);
    if (LJE_NOERROR != lRet)
    {
        KMS_EXCEPTION_WITH_INFO(DEVICE, "eAIN failed", lRet);
    }

    return lResult_V;
}

KMS::DAQ::AnalogValue_Raw LabJack::AI_Read_Raw(KMS::DAQ::Id aId)
{
    double lResult;

    KMS::Thread::Lock lLocl(&mZone0);

    LJ_ERROR lRet = eAIN(mHandle, aId, 0, &lResult, 0, 0, 0, 1, 0, 0);
    if (LJE_NOERROR != lRet)
    {
        KMS_EXCEPTION_WITH_INFO(DEVICE, "eAIN failed", lRet);
    }

    lResult -= 32768;

    return static_cast<KMS::DAQ::AnalogValue_Raw>(lResult);
}

// ===== KMS::DAQ::IAnalogOutputs =======================================

KMS::DAQ::AnalogValue LabJack::AO_Get(KMS::DAQ::Id aId) const
{
    assert(AO_QTY > aId);

    return mAO_States[aId].mValue_V;
}

KMS::DAQ::AnalogValue_Raw LabJack::AO_Get_Raw(KMS::DAQ::Id aId) const
{
    assert(AO_QTY > aId);

    return mAO_States[aId].mValue_Raw;
}

void LabJack::AO_Write(KMS::DAQ::Id aId, KMS::DAQ::AnalogValue aValue_V)
{
    assert(AO_QTY > aId);

    KMS::Thread::Lock lLocl(&mZone0);

    LJ_ERROR lRet = eDAC(mHandle, aId, aValue_V, 0, 0, 0);
    if (LJE_NOERROR != lRet)
    {
        KMS_EXCEPTION_WITH_INFO(DEVICE, "eDAQ failed", lRet);
    }

    mAO_States[aId].mValue_V = aValue_V;
}

void LabJack::AO_Write_Raw(KMS::DAQ::Id aId, KMS::DAQ::AnalogValue_Raw aValue)
{
    assert(AO_QTY > aId);

    KMS::Thread::Lock lLocl(&mZone0);

    LJ_ERROR lRet = eDAC(mHandle, aId, aValue, 1, 0, 0);
    if (LJE_NOERROR != lRet)
    {
        KMS_EXCEPTION_WITH_INFO(DEVICE, "eDAQ failed", lRet);
    }

    mAO_States[aId].mValue_Raw = aValue;
}

// ===== KMS::DAQ::IDigitalInputs =======================================

bool LabJack::DI_Read(KMS::DAQ::Id aId)
{
    long lResult = 0xffffffff;

    KMS::Thread::Lock lLocl(&mZone0);

    LJ_ERROR lRet = eDI(mHandle, aId, &lResult);
    if (LJE_NOERROR != lRet)
    {
        KMS_EXCEPTION_WITH_INFO(DEVICE, "eDI failed", lRet);
    }

    return lResult;
}

// ===== KMS::DAQ::IDigitalOutputs ======================================

void LabJack::DO_Clear(KMS::DAQ::Id aId)
{
    assert(IO_QTY > aId);

    KMS::Thread::Lock lLocl(&mZone0);

    LJ_ERROR lRet = eDO(mHandle, aId, 0);
    if (LJE_NOERROR != lRet)
    {
        KMS_EXCEPTION_WITH_INFO(DEVICE, "eDO failed", lRet);
    }

    mIO_States[aId] = false;
}

bool LabJack::DO_Get(KMS::DAQ::Id aId) const
{
    assert(IO_QTY > aId);

    return mIO_States[aId];
}

void LabJack::DO_Set(KMS::DAQ::Id aId, bool aValue)
{
    assert(IO_QTY > aId);

    LJ_ERROR lRet = LJE_FUNCTION_INVALID;

    KMS::Thread::Lock lLocl(&mZone0);

    switch (mIO_Modes[aId])
    {
    case IO_Mode::DIGITAL_OUTPUT:
        lRet = eDO(mHandle, aId, aValue ? 1 : 0);
        break;

    case IO_Mode::DIGITAL_OUTPUT_LOW_HIGH_Z:
        if (aValue)
        {
            long lState;
            lRet = eDI(mHandle, aId, &lState);
        }
        else
        {
            lRet = eDO(mHandle, aId, 0);
        }
        break;

    default: assert(false);
    }

    if (LJE_NOERROR != lRet)
    {
        KMS_EXCEPTION_WITH_INFO(DEVICE, "eDI or eDO failed", lRet);
    }

    mIO_States[aId] = aValue;
}

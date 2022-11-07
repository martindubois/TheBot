
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// File      Common/LabJack.h

#pragma once

// ===== Import/Includes ====================================================
#include <KMS/DAQ/IAnalogInputs.h>
#include <KMS/DAQ/IAnalogOutputs.h>
#include <KMS/DAQ/IDigitalInputs.h>
#include <KMS/DAQ/IDigitalOutputs.h>
#include <KMS/Thread/Gate.h>

class LabJack : public KMS::DAQ::IAnalogInputs, public KMS::DAQ::IAnalogOutputs, public KMS::DAQ::IDigitalInputs, public KMS::DAQ::IDigitalOutputs
{

public:

    enum class IO_Mode
    {
        ANALOG_INPUT,
        DIGITAL_INPUT,
        DIGITAL_OUTPUT,
        DIGITAL_OUTPUT_LOW_HIGH_Z,
    };

    static const KMS::DAQ::Id FIO0;
    static const KMS::DAQ::Id FIO1;
    static const KMS::DAQ::Id FIO2;
    static const KMS::DAQ::Id FIO3;
    static const KMS::DAQ::Id FIO4;
    static const KMS::DAQ::Id FIO5;
    static const KMS::DAQ::Id FIO6;
    static const KMS::DAQ::Id FIO7;

    static const KMS::DAQ::Id EIO0;
    static const KMS::DAQ::Id EIO1;
    static const KMS::DAQ::Id EIO2;
    static const KMS::DAQ::Id EIO3;
    static const KMS::DAQ::Id EIO4;
    static const KMS::DAQ::Id EIO5;
    static const KMS::DAQ::Id EIO6;
    static const KMS::DAQ::Id EIO7;

    static const KMS::DAQ::Id CIO0;
    static const KMS::DAQ::Id CIO1;
    static const KMS::DAQ::Id CIO2;
    static const KMS::DAQ::Id CIO3;

    static const KMS::DAQ::Id DAC0;
    static const KMS::DAQ::Id DAC1;

    LabJack();

    void IO_SetMode(KMS::DAQ::Id aId, IO_Mode aMode);

    // ===== KMS::DAQ::IAnalogInputs ========================================
    virtual KMS::DAQ::AnalogValue     AI_Read    (KMS::DAQ::Id aId);
    virtual KMS::DAQ::AnalogValue_Raw AI_Read_Raw(KMS::DAQ::Id aId);

    // ===== KMS::DAQ::IAnalogOutputs =======================================
    virtual KMS::DAQ::AnalogValue     AO_Get      (KMS::DAQ::Id aId) const;
    virtual KMS::DAQ::AnalogValue_Raw AO_Get_Raw  (KMS::DAQ::Id aId) const;
    virtual void                      AO_Write    (KMS::DAQ::Id aId, KMS::DAQ::AnalogValue aValue_V);
    virtual void                      AO_Write_Raw(KMS::DAQ::Id aId, KMS::DAQ::AnalogValue_Raw aValue);

    // ===== KMS::DAQ::IDigitalInputs =======================================
    virtual bool DI_Read(KMS::DAQ::Id aId);

    // ===== KMS::DAQ::IDigitalOutputs ======================================
    virtual void DO_Clear(KMS::DAQ::Id aId);
    virtual bool DO_Get  (KMS::DAQ::Id aId) const;
    virtual void DO_Set  (KMS::DAQ::Id aId, bool aValue = true);

private:

    class AO_State
    {

    public:

        KMS::DAQ::AnalogValue_Raw mValue_Raw;
        KMS::DAQ::AnalogValue     mValue_V;

    };

    AO_State mAO_States[2];

    IO_Mode mIO_Modes [20];
    bool    mIO_States[20];

    // ===== Zone0 ==========================================================
    KMS::Thread::Gate mZone0;

    long mHandle;

};

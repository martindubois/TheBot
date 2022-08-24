
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// File      TheBot-A-Test/Motors.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include "../Common/LabJack.h"
#include "../Common/Motors.h"

KMS_TEST(Motors_MotorsA, "Motors_MotorsA", "Motors-A", sTest_MotorsA)
{
    LabJack lLJ;
    Motors lM;

    lLJ.IO_SetMode(LabJack::CIO1, LabJack::IO_Mode::DIGITAL_INPUT);
    lLJ.IO_SetMode(LabJack::CIO3, LabJack::IO_Mode::DIGITAL_INPUT);
    lLJ.IO_SetMode(LabJack::EIO0, LabJack::IO_Mode::DIGITAL_OUTPUT_LOW_HIGH_Z);
    lLJ.IO_SetMode(LabJack::EIO2, LabJack::IO_Mode::DIGITAL_OUTPUT_LOW_HIGH_Z);

    KMS::DAQ::DigitalInput  lLeftAlarm    (&lLJ, LabJack::CIO1);
    KMS::DAQ::DigitalInput  lLeftPending  (&lLJ, LabJack::CIO3);
    KMS::DAQ::DigitalOutput lLeftEnable   (&lLJ, LabJack::EIO0);
    KMS::DAQ::DigitalOutput lLeftDirection(&lLJ, LabJack::EIO2);

    lLJ.IO_SetMode(LabJack::CIO0, LabJack::IO_Mode::DIGITAL_OUTPUT_LOW_HIGH_Z);

    KMS::DAQ::DigitalOutput lPulse(&lLJ, LabJack::CIO0);

    lLJ.IO_SetMode(LabJack::EIO1, LabJack::IO_Mode::DIGITAL_OUTPUT_LOW_HIGH_Z);
    lLJ.IO_SetMode(LabJack::EIO3, LabJack::IO_Mode::DIGITAL_OUTPUT_LOW_HIGH_Z);
    lLJ.IO_SetMode(LabJack::EIO5, LabJack::IO_Mode::DIGITAL_INPUT);
    lLJ.IO_SetMode(LabJack::EIO7, LabJack::IO_Mode::DIGITAL_INPUT);

    KMS::DAQ::DigitalOutput lRightDirection(&lLJ, LabJack::EIO1);
    KMS::DAQ::DigitalOutput lRightEnable   (&lLJ, LabJack::EIO3);
    KMS::DAQ::DigitalInput  lRightPending  (&lLJ, LabJack::EIO5);
    KMS::DAQ::DigitalInput  lRightAlarm    (&lLJ, LabJack::EIO7);

    lM.InitAlarm    (&lLeftAlarm    , &lRightAlarm);
    lM.InitDirection(&lLeftDirection, &lRightDirection);
    lM.InitEnable   (&lLeftEnable   , &lRightEnable);
    lM.InitPending  (&lLeftPending  , &lRightPending);

    lM.InitPulse(&lPulse);

    lM.On();

    lM.Move(MoveDirection::FORWARD, 800);

    Sleep(30000);

    lM.Off();
}

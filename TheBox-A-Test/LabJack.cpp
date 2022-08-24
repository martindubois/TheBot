
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// File      TheBot-A-Test/LabJack.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include "../Common/LabJack.h"

KMS_TEST(LabJack_LabJackA, "LabJack_LabJackA", "LabJack-A", sTest_LabjackA)
{
    LabJack lLJ;

    lLJ.AO_Write(0, 0.0);

    KMS_TEST_ASSERT(0.0 == lLJ.AO_Get(0));

    lLJ.AO_Write_Raw(0, 0);

    KMS_TEST_ASSERT(0 == lLJ.AO_Get_Raw(0));

    lLJ.IO_SetMode(0, LabJack::IO_Mode::ANALOG_INPUT);
    lLJ.IO_SetMode(1, LabJack::IO_Mode::DIGITAL_INPUT);
    lLJ.IO_SetMode(2, LabJack::IO_Mode::DIGITAL_OUTPUT);
    lLJ.IO_SetMode(3, LabJack::IO_Mode::DIGITAL_OUTPUT_LOW_HIGH_Z);

    KMS::DAQ::AnalogValue     lValue_V   = lLJ.AI_Read    (0);
    KMS::DAQ::AnalogValue_Raw lValue_Raw = lLJ.AI_Read_Raw(0);

    std::cout << "Analog Input 0 = " << lValue_V << " V (" << lValue_Raw << ")" << std::endl;

    KMS_TEST_ASSERT(lLJ.DO_Get(3));

    lLJ.IO_SetMode(0, LabJack::IO_Mode::DIGITAL_INPUT);

    lLJ.DO_Clear(2);
    lLJ.DO_Clear(3);

    KMS_TEST_ASSERT(!lLJ.DO_Get(2));
    KMS_TEST_ASSERT(!lLJ.DO_Get(3));

    lLJ.DO_Set(2);
    lLJ.DO_Set(3);

    KMS_TEST_ASSERT(lLJ.DO_Get(2));
    KMS_TEST_ASSERT(lLJ.DO_Get(3));

    lLJ.DO_Set(2, false);
    lLJ.DO_Set(3, false);

    KMS_TEST_ASSERT(!lLJ.DO_Get(2));
    KMS_TEST_ASSERT(!lLJ.DO_Get(3));

    for (KMS::DAQ::Id lId = 4; lId < 20; lId++)
    {
        bool lValue = lLJ.DI_Read(lId);

        std::cout << "Digital Input " << static_cast<unsigned int>(lId) << " = " << (lValue ? "true" : "false") << std::endl;
    }
}

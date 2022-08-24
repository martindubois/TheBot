
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// File      Common/Motors.h

#pragma once

// ===== Import/Includes ====================================================
#include <KMS/DAQ/DigitalInput.h>
#include <KMS/DAQ/DigitalOutput.h>
#include <KMS/Msg/IReceiver.h>
#include <KMS/Msg/Sender.h>
#include <KMS/Thread/Thread.h>

// ===== TheBot-A ===========================================================
#include "../Common/Types.h"

class Motors : public KMS::Msg::IReceiver
{

public:

    Motors();

    ~Motors();

    void InitAlarm  (KMS::DAQ::DigitalInput* aLeft, KMS::DAQ::DigitalInput* aRight);
    void InitPending(KMS::DAQ::DigitalInput* aLeft, KMS::DAQ::DigitalInput* aRight);

    void InitDirection(KMS::DAQ::DigitalOutput* aLeft, KMS::DAQ::DigitalOutput* aRight);
    void InitEnable   (KMS::DAQ::DigitalOutput* aLeft, KMS::DAQ::DigitalOutput* aRight);

    void InitPower(KMS::DAQ::DigitalOutput* aPower);
    void InitPulse(KMS::DAQ::DigitalOutput* aPulse);

    void Off();
    void On ();

    void Move(MoveDirection aDir, unsigned int aCount);

    void Turn(TurnDirection aDir, unsigned int aCount);

    KMS::Msg::Sender mOnAlarm;
    KMS::Msg::Sender mOnCompleted;

    // ===== KMS::Msg::IReceiver ============================================
    virtual bool Receive(void* aSender, unsigned int aCode, void* aData);

private:

    void DisableMotors();
    void EnableMotors();

    bool OnIterate();

    void ResetDirections();

    KMS::DAQ::DigitalInput* mAlarm[2];
    KMS::DAQ::DigitalInput* mPending[2];

    KMS::DAQ::DigitalOutput* mDirection[2];
    KMS::DAQ::DigitalOutput* mEnable[2];
    KMS::DAQ::DigitalOutput* mPulse;
    KMS::DAQ::DigitalOutput* mPower;

    unsigned int mCount;
    unsigned int mMotor;

    KMS::Thread::Thread mThread;

};

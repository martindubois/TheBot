
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// File      TheBot-A/Motors.cpp

#include "Component.h"

// ===== TheBot-A ===========================================================
#include "../Common/Motors.h"

// Constants
// //////////////////////////////////////////////////////////////////////////

#define MOTOR_LEFT  (0)
#define MOTOR_RIGHT (1)

#define MOTOR_QTY   (2)

#define MSG_ITERATE (1)

// Public
// //////////////////////////////////////////////////////////////////////////

Motors::Motors() : mMotor(MOTOR_LEFT), mOnAlarm(this), mOnCompleted(this), mPulse(NULL)
{
    for (unsigned int i = MOTOR_LEFT; i <= MOTOR_RIGHT; i++)
    {
        mAlarm    [i] = NULL;
        mPending  [i] = NULL;
        mDirection[i] = NULL;
        mEnable   [i] = NULL;
    }

    mThread.mOnIterate .Set(this, MSG_ITERATE );
}

Motors::~Motors()
{
    DisableMotors();

    ResetDirections();
}

void Motors::InitAlarm(KMS::DAQ::DigitalInput* aLeft, KMS::DAQ::DigitalInput* aRight)
{
    assert(NULL != aLeft);
    assert(NULL != aRight);

    mAlarm[MOTOR_LEFT ] = aLeft;
    mAlarm[MOTOR_RIGHT] = aRight;
}

void Motors::InitPending(KMS::DAQ::DigitalInput* aLeft, KMS::DAQ::DigitalInput* aRight)
{
    assert(NULL != aLeft);
    assert(NULL != aRight);

    mPending[MOTOR_LEFT ] = aLeft;
    mPending[MOTOR_RIGHT] = aRight;
}

void Motors::InitDirection(KMS::DAQ::DigitalOutput* aLeft, KMS::DAQ::DigitalOutput* aRight)
{
    assert(NULL != aLeft);
    assert(NULL != aRight);

    mDirection[MOTOR_LEFT ] = aLeft;
    mDirection[MOTOR_RIGHT] = aRight;

    ResetDirections();
}


void Motors::InitEnable(KMS::DAQ::DigitalOutput* aLeft, KMS::DAQ::DigitalOutput* aRight)
{
    assert(NULL != aLeft);
    assert(NULL != aRight);

    mEnable[MOTOR_LEFT ] = aLeft;
    mEnable[MOTOR_RIGHT] = aRight;

    DisableMotors();
}

void Motors::InitPower(KMS::DAQ::DigitalOutput* aPower)
{
    assert(NULL != aPower);

    mPower = aPower;

    mPower->Set(true);
}

void Motors::InitPulse(KMS::DAQ::DigitalOutput* aPulse)
{
    assert(NULL != aPulse);

    mPulse = aPulse;

    mPulse->Set(true);
}

void Motors::Off()
{
    assert(NULL != mPower);

    mPower->Set(true);

    DisableMotors();

    mThread.StopAndWait(1000);
}

void Motors::On()
{
    assert(NULL != mPower);

    mCount = 0;

    mPower->Set(false);

    EnableMotors();

    mThread.Start();
}

void Motors::Move(MoveDirection aDir, unsigned int aCount)
{
    assert(NULL != mDirection[MOTOR_LEFT]);
    assert(NULL != mDirection[MOTOR_RIGHT]);

    if (0 < mCount)
    {
        KMS_EXCEPTION(STATE, "Busy");
    }

    switch (aDir)
    {
    case MoveDirection::BACKWARD:
        mDirection[MOTOR_LEFT ]->Set(false);
        mDirection[MOTOR_RIGHT]->Set(false);
        break;

    case MoveDirection::FORWARD:
        ResetDirections();
        break;

    default: assert(false);
    }

    mCount = aCount;
}

void Motors::Turn(TurnDirection aDir, unsigned int aCount)
{
    assert(NULL != mDirection[MOTOR_LEFT]);
    assert(NULL != mDirection[MOTOR_RIGHT]);

    if (0 < mCount)
    {
        KMS_EXCEPTION(STATE, "Busy");
    }

    switch (aDir)
    {
    case TurnDirection::LEFT:
        mDirection[MOTOR_LEFT ]->Set(false);
        mDirection[MOTOR_RIGHT]->Set(true );
        break;

    case TurnDirection::RIGHT:
        mDirection[MOTOR_LEFT ]->Set(true);
        mDirection[MOTOR_RIGHT]->Set(false);
        break;

    default: assert(false);
    }

    mCount = aCount;
}

// ===== KMS::Msg::IReceiver ================================================

bool Motors::Receive(void* aSender, unsigned int aCode, void* aData)
{
    bool lResult = false;

    switch (aCode)
    {
    case MSG_ITERATE : lResult = OnIterate (); break;

    default: assert(false);
    }

    return lResult;
}

// Private
// //////////////////////////////////////////////////////////////////////////

void Motors::DisableMotors()
{
    assert(NULL != mEnable[MOTOR_LEFT ]);
    assert(NULL != mEnable[MOTOR_RIGHT]);

    mEnable[MOTOR_LEFT ]->Set(false);
    mEnable[MOTOR_RIGHT]->Set(false);
}

void Motors::EnableMotors()
{
    assert(NULL != mEnable[MOTOR_LEFT ]);
    assert(NULL != mEnable[MOTOR_RIGHT]);

    mEnable[MOTOR_LEFT ]->Set(true);
    mEnable[MOTOR_RIGHT]->Set(true);
}

bool Motors::OnIterate()
{
    assert(MOTOR_QTY > mMotor);

    assert(NULL != mAlarm[mMotor]);
    assert(NULL != mPulse);

    if (0 < mCount)
    {
        mPulse->Set(false);
        mPulse->Set(true);

        mCount--;

        Sleep(1);

        if ((0 == mCount) && mOnCompleted.IsSet())
        {
            mOnCompleted.Send();
        }
    }
    else
    {
        Sleep(100);
    }

    mMotor = (mMotor + 1) % MOTOR_QTY;

    bool lAlarm = mAlarm[mMotor]->Read();
    if (!lAlarm)
    {
        if (mOnAlarm.IsSet())
        {
            mOnAlarm.Send();
        }
        else
        {
            Off();
        }
    }

    return true;
}

void Motors::ResetDirections()
{
    assert(NULL != mDirection[MOTOR_LEFT ]);
    assert(NULL != mDirection[MOTOR_RIGHT]);

    mDirection[MOTOR_LEFT ]->Set(true);
    mDirection[MOTOR_RIGHT]->Set(true);
}

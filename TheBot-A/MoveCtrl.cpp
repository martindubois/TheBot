
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// File      TheBot-A/MoveCtrl.cpp

#include "Component.h"

// ===== Import =============================================================
#include <KMS/Convert.h>

// ===== TheBot-A ===========================================================
#include "../Common/MoveCtrl.h"

// Configuration
// //////////////////////////////////////////////////////////////////////////

#define DEFAULT_BASE_m                 (0.27)
#define DEFAULT_WHEEL_DIAMETER_m       (0.5)
#define DEFAULT_WHEEL_REVOLUTION_pulse (840)

#define MSG_ALARM     (1)
#define MSG_COMPLETED (2)

#define TWO_PI (2 * M_PI)

// Public
// //////////////////////////////////////////////////////////////////////////

MoveCtrl::MoveCtrl()
    : mBase_m(DEFAULT_BASE_m)
    , mHeading_rad(0.0)
    , mState(State::OFF)
    , mWheelDiameter_m(DEFAULT_WHEEL_DIAMETER_m)
    , mWheelRevolution_pulse(DEFAULT_WHEEL_REVOLUTION_pulse)
    , mX_m(0.0)
    , mY_m(0.0)
{
}

double MoveCtrl::GetHeading() const { return mHeading_rad; }

double MoveCtrl::GetX() const { return mX_m; }
double MoveCtrl::GetY() const { return mY_m; }

void MoveCtrl::SetBase(double aIn_m) { mBase_m = aIn_m; }

void MoveCtrl::SetWheelDiameter(double aIn_m) { mWheelDiameter_m = aIn_m; }

void MoveCtrl::SetWheelRevolution(double aIn_pulse) { mWheelRevolution_pulse = aIn_pulse; }

void MoveCtrl::Off()
{
    mMotors.Off();
    
    mState = State::OFF;
}

void MoveCtrl::On()
{
    mDistance_pulse = 0.0;

    mMove_Distance_m = 0.0;
    mMove_X_m = 0.0;
    mMove_Y_m = 0.0;

    mTarget_Heading_rad = 0.0;
    mTarget_X_m = 0.0;
    mTarget_Y_m = 0.0;

    mTurn_Angle_rad = 0.0;

    mState = State::ON;
    
    mMotors.On();
}

void MoveCtrl::GoTo(double aX_m, double aY_m)
{
    switch (mState)
    {
    case State::MOVING:
    case State::OFF:
    case State::TURNING:
    case State::TURNING_BEFORE_MOVE:
        KMS_EXCEPTION(STATE, "Invalid state");

    case State::ON:
        mMove_X_m = aX_m - mX_m;
        mMove_Y_m = aY_m - mY_m;

        mMove_Distance_m = sqrt(mMove_X_m * mMove_X_m + mMove_Y_m * mMove_Y_m);
        if (0.001 <= mMove_Distance_m)
        {
            mTarget_X_m = aX_m;
            mTarget_Y_m = aY_m;

            double lHeading_rad = atan2(mMove_Y_m, mMove_X_m);

            mState = State::TURNING_BEFORE_MOVE;

            Internal_GoTo(lHeading_rad);
        }
        else
        {
            mMove_X_m = 0.0;
            mMove_Y_m = 0.0;

            mMove_Distance_m = 0.0;

            mTarget_X_m = mX_m;
            mTarget_Y_m = mY_m;
        }
        break;

    default: assert(false);
    }
}

void MoveCtrl::GoTo(double aHeading_rad)
{
    switch (mState)
    {
    case State::MOVING:
    case State::OFF:
    case State::TURNING:
    case State::TURNING_BEFORE_MOVE:
        KMS_EXCEPTION(STATE, "Invalid state");

    case State::ON:
        mState = State::TURNING;

        Internal_GoTo(aHeading_rad);
        break;

    default: assert(false);
    }
}

void MoveCtrl::Move(MoveDirection aDirection, double aDistance_m)
{
    mMove_Distance_m  = 0.0;

    mTarget_Heading_rad = mHeading_rad;

    switch (aDirection)
    {
    case MoveDirection::BACKWARD:
        mTarget_X_m = mX_m - cos(mHeading_rad) * aDistance_m;
        mTarget_Y_m = mY_m - sin(mHeading_rad) * aDistance_m;
        break;

    case MoveDirection::FORWARD:
        mTarget_X_m = mX_m + cos(mHeading_rad) * aDistance_m;
        mTarget_Y_m = mY_m + sin(mHeading_rad) * aDistance_m;
        break;

    default: assert(false);
    }

    Internal_Move(aDirection, aDistance_m);
}

void MoveCtrl::Turn(TurnDirection aDirection, double aAngle_rad)
{
    switch (mState)
    {
    case State::MOVING:
    case State::OFF:
    case State::TURNING:
    case State::TURNING_BEFORE_MOVE:
        KMS_EXCEPTION(STATE, "Invalid state");

    case State::ON:
        switch (aDirection)
        {
        case TurnDirection::LEFT : mTarget_Heading_rad = mHeading_rad + aAngle_rad; break;
        case TurnDirection::RIGHT: mTarget_Heading_rad = mHeading_rad - aAngle_rad; break;

        default: assert(false);
        }

        if (0.0 > mTarget_Heading_rad)
        {
            mTarget_Heading_rad += TWO_PI;
        }
        else if (TWO_PI < mTarget_Heading_rad)
        {
            mTarget_Heading_rad -= TWO_PI;
        }

        mState = State::TURNING;

        Internal_Turn(aDirection, aAngle_rad);
        break;

    default: assert(false);
    }
}

// ===== KMS::Msg::IReceiver ================================================

bool MoveCtrl::Receive(void* aSender, unsigned int aCode, void* aData)
{
    bool lResult = false;

    switch (aCode)
    {
    case MSG_ALARM    : lResult = OnAlarm    (); break;
    case MSG_COMPLETED: lResult = OnCompleted(); break;

    default: assert(false);
    }

    return lResult;
}

// ===== KMS::Cfg::Configurable =============================================

void MoveCtrl::DisplayHelp(FILE* aOut) const
{
    assert(NULL != aOut);

    fprintf(aOut,
        "===== MoveCtrl =====\n"
        "Base\n"
        "    Set the base to the default value\n"
        "    Default: %f m\n"
        "Base = {Value}\n"
        "    Set the base\n"
        "WheelDiameter\n"
        "    Set the wheel diameter to the default value\n"
        "    Default: %f m\n"
        "WheelDiameter = {Value}\n"
        "    Set the wheel diameter\n"
        "WheelRevolution\n"
        "    Set the wheel revolution to the default value\n"
        "    Default: %u pulses\n"
        "WheelRevolution = {Value}\n"
        "    Set the wheel revolution\n",
        DEFAULT_BASE_m,
        DEFAULT_WHEEL_DIAMETER_m,
        DEFAULT_WHEEL_REVOLUTION_pulse);

    KMS::Cfg::Configurable::DisplayHelp(aOut);
}

bool MoveCtrl::SetAttribute(const char* aA, const char* aV)
{
    if (NULL == aV)
    {
        CFG_IF("Base"           ) { SetBase           (DEFAULT_BASE_m                ); return true; }
        CFG_IF("WheelDiameter"  ) { SetWheelDiameter  (DEFAULT_WHEEL_DIAMETER_m      ); return true; }
        CFG_IF("WheelRevolution") { SetWheelRevolution(DEFAULT_WHEEL_REVOLUTION_pulse); return true; }
    }
    else
    {
        CFG_CONVERT("Base"           , SetBase           , KMS::Convert::ToDouble);
        CFG_CONVERT("WheelDiameter"  , SetWheelDiameter  , KMS::Convert::ToDouble);
        CFG_CONVERT("WheelRevolution", SetWheelRevolution, KMS::Convert::ToDouble);
    }

    return KMS::Cfg::Configurable::SetAttribute(aA, aV);
}

// Private
// //////////////////////////////////////////////////////////////////////////

void Internal_GoTo(double aHeading_rad)
{
    assert(0.0    <= aHeading_rad);
    assert(TWO_PI >= aHeading_rad);

    mTartet_Heading_rad = aHeading_rad;

    double lLeft_rad;
    double lRight_rad;

    if (mHeading_rad < aHeading_rad)
    {
        lLeft_rad  = 2 * M_PI + mHeading_Rad - aHeading_rad;
        lRight_rad = aHeading_rad - mHeading_rad;
    }
    else
    {
        lLeft_rad = mHeading_rad - aHeading_rad;
        lRight_rad = 2 * M_PI + aHeading_rad - mHeading_rad;
    }

    if (lLeft_rad < lRight_rad)
    {
        Internal_Turn(TurnDirection::LEFT, lLeft_rad);
    }
    else
    {
        Internal_Turn(TurnDirection::RIGHT, lRight_rad);
    }
}

void Internal_Move(MoveDirection aDirection, double aDistance_m)
{
    assert(0.0 < mWheelDiameter_m);
    assert(0.0 < mWheelRevolution_pulse);

    double lRev = aDistance_m / mWheelDiameter_m;

    mDistance_pulse = lRev * mWheelRevolution_pulse;

    mMotors.Move(aDirection, static_cast<unsigned int>(mDistance_pulse));
}

void Internal_Turn(TurnDirection aDirection, double aAngle_rad)
{
    assert(0.0 < mBase_m);
    assert(0.0 < mWheelDiameter_m);
    assert(0.0 < mWheelRevolution_pulse);

    switch (aDirection)
    {
    case TurnDirection::LEFT : mTurn_Angle_rad =   aAngle_rad; break;
    case TurnDirection::RIGHT: mTurn_Angle_Rad = - aAngle_rad; break;

    default: assert(false);
    }

    double lDistance_m = (mBase_m / 2.0) * aAngle_rad;

    double lRev = lDistance_m / mWheelDiameter_m;

    mDistance_pulse = lRev * mWheelRevolution_pulse;

    mMotors.Turn(aDirection, static_cast<unsigned int>(mDistance_pulse));
}

bool MoveCtrl::OnAlaram()
{
    unsigned int lCount_pulse = mMotors.GetCount();

    double lMissing = lCount_pulse;
    
    lMissing =/ mDistance_pulse;

    switch (mState)
    {
    case State::MOVING:
        mX_m = mTarget_X_m - lMissing * mDelta_X_rad;
        mY_m = mTarget_Y_m - lMissing * mDelta_Y_rad;
        break;

    case State::OFF:
    case State::ON : break;

    case State::TURNING:
    case State::TURNING_BEFORE_MOVE:
        mHeading_rad = mTarget_Heading_rad - lMissing * mTurn_Angle_rad;
        break;

    default: assert(false);
    }

    mMotors.Off();
}

bool MoveCtrl::OnCompleted()
{
    switch (mState)
    {
    case State::MOVING:
        mMove_X_m = 0.0;
        mMove_Y_m = 0.0;

        mX_m = mTarget_X_m;
        mY_m = mTarget_Y_m;

        mState = State::ON;
        break;

    case State::TURNING:
        mTurn_Angle_rad = 0.0;

        mHeading_rad = mTarget_Heading_rad;

        mState = State::ON;
        break;

    case State::TURNING_BEFORE_MOVE:
        mTurn_Angle_rad = 0.0;

        mHeading_rad = mTarget_Heading_rad;

        double lDistance_m = mMove_Distance_m;
        mMove_Distance_m = 0.0;

        mState = State::MOVING;

        Internal_Move(MoveDirection::FORWARD, lDistance_m);
        break;

    default: assert(false);
    }
}

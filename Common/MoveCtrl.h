
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// File      Common/MoveCtrl.h

#pragma once

// ===== Import/Includes ====================================================
#include <KMS/Cfg/Configurable.h>
#include <KMS/Cfg/IReceiver.h>

// ===== TheBot-A ===========================================================
#include "../Common/Motors.h"

class MoveCtrl : public KMS::Cfg::Configurable, public KMS::Msg::IReceiver
{

public:

    MoveCtrl();

    double GetHeading() const;

    double GetX() const;

    double GetY() const;

    void SetBase(double aIn_m);

    void SetWheelDiameter(double aIn_m);

    void SetWheelRevolution(double aIn_pulse);

    void Off();

    void On();

    void GoTo(double aX_m, double aY_m);

    void GoTo(double aHeading_rad);

    void Move(MoveDirection aDirection, double aDistance_m);

    void Turn(TurnDirection aDirection, double aAngle_rad);

    Motors mMotors;

    // ===== KMS::Msg::IReceiver ============================================
    virtual bool Receive(void* aSender, unsigned int aCode, void* aData);

    // ===== KMS::Cfg::Configurable =========================================
    virtual void DisplayHelp(FILE* aOut) const;
    virtual bool SetAttribute(const char* aA, const char* aV);

private:

    // --> OFF <==+========+=======+----+
    //      |     |        |       |    |
    //      +--> ON <===+--|-----+ |    |
    //            |     |  |     | |    |
    //            +--> MOVING <--|-|--+ |
    //            |              | |  | |
    //            +---------> TURNING | |
    //            |                   | |
    //            +--> TURNING_BEFORE_MOVE
    enum class State
    {
        MOVING,
        OFF,
        ON,
        TURNING,
        TURNING_BEFORE_MOVE,
    }

    void Internal_GoTo(double aHeading_rad);
    void Internal_Move(MoveDirection aDirection, double aDistance_m);
    void Internal_Turn(TurnDirection aDirection, double aAngle_rad);

    bool OnAlarm();
    bool OnCompleted();

    double mDistance_pulse;

    double mMove_Distance_m;
    double mMove_X_m;
    double mMove_Y_m;

    double mTurn_Angle_rad;

    State mState;

    double mTarget_Heading_rad;

    double mTarget_X_m;
    double mTarget_Y_m;

    // ===== Current position and heading ===================================

    double mHeading_rad;

    double mX_m;
    double mY_m;

    // ===== Configurable attributes ========================================
    double mBase_m;
    double mWheelDiameter_m;
    double mWheelRevolution_pulse;

};

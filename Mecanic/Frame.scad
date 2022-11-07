
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// Fichier   Mecanic/Frame.scad

include <C:\_VC\Base3D\Metric\M4.scad>

CFG_SMALL = 1;

// Front_Right();

// translate( [ SIZE_X + 2,          0, 0 ] ) Front_Left();
translate( [          0, SIZE_Y + 2, 0 ] ) Back_Right();
// translate( [ SIZE_X + 2, SIZE_Y + 2, 0 ] ) Back_Left();

module Back_Left()
{
    difference()
    {
        Base_Left();

        Hole_M4( SIZE_X - 20 - 30 - 20              - 7, 10 );
        Hole_M4( SIZE_X - 20 - 30 - 20 - M4_DELTA_X - 7, 10 );

        Hole_M4( SIZE_X - 20 - 30 - 20 - 19, SIZE_Y - 25 );

        if ( 0 == CFG_SMALL )
        {
            Hole_Center( 0, 0 );
            Hole_Corner( SIZE_X - 20, SIZE_Y - 20 );

            Hole_Wheel( SIZE_X - 20 - 30, - 80 );

            Slot_BF( SIZE_X - 10 - 2, - EPS );
            Slot_BF_Mini( 20 - 1, SIZE_Y - 10 - 2 - 15 );

            Round( 20 + 3, SIZE_Y - 10 - 2 - 15, 9 );

            Slot_LR_Mini( SIZE_X - 10 - 2 - 15, 20 - 1 );
        }

        translate( [ SIZE_X - 20, SIZE_Y - 20, TICK ] )
            Slot_Diag( 180 + 39 );

        Slot_LR( - EPS, SIZE_Y - 10 - 2 );

        translate( [ SIZE_X - 25, 10, TICK ] )
            Slot_RDiag( 180 - 39 );
    }
}

module Back_Right()
{
    difference()
    {
        Base_Right();

        Hole_M4( 20 + 30 + 20              + 7, 10 );
        Hole_M4( 20 + 30 + 20 + M4_DELTA_X + 7, 10 );

        Hole_M4( 20 + 30 + 20 + 19, SIZE_Y - 25 );

        if ( 0 == CFG_SMALL )
        {
            Hole_Center( SIZE_X, 0 );
            Hole_Corner( 20, SIZE_Y - 20 );

            Hole_Wheel( 20, - 80 );

            Slot_BF( 10, - EPS );
            Slot_BF_Mini( SIZE_X - 20 - 3, SIZE_Y - 10 - 2 - 15 );

            Round( SIZE_X - 20 - 3, SIZE_Y - 10 - 2 - 15, 9 );

            Slot_LR_Mini( 10 + 2, 20 - 1 );
        }

        translate( [ 20, SIZE_Y - 20, TICK ] )
            Slot_Diag( 360 - 39 );

        Slot_LR( 20, SIZE_Y - 10 - 2 );

        translate( [ 25, 10, TICK ] )
            Slot_RDiag( 39 );
    }
}

module Front_Left()
{
    difference()
    {
        Base_Left();

        Hole_M4( SIZE_X - 20 - 30 - 20              - 7, SIZE_Y - 30 );
        Hole_M4( SIZE_X - 20 - 30 - 20 - M4_DELTA_X - 7, SIZE_Y - 30 );

        Hole_M4( SIZE_X - 20 - 30 - 20 - 19, 25 );

        if ( 0 == CFG_SMALL )
        {
            Hole_Center( 0, SIZE_Y );
            Hole_Corner( SIZE_X - 20, 20 );

            Hole_Wheel( SIZE_X - 20 - 30, SIZE_Y - 90 );

            Slot_BF( SIZE_X - 10 - 2, 20 );
            Slot_BF_Mini( 20 - 1, 10 + 2 );

            Round( 20 + 3, 10 + 2 + 15, 9 );

            Slot_LR_Mini( SIZE_X - 10 - 2 - 15, SIZE_Y - 20 - 3 );
        }

        translate( [ SIZE_X - 20, 20, TICK ] )
            Slot_Diag( 180 - 39 );

        Slot_LR( - EPS, 10 );

        translate( [ SIZE_X - 25, SIZE_Y - 10, TICK ] )
            Slot_RDiag( 180 + 39 );
    }
}

module Front_Right()
{
    difference()
    {
        Base_Right();

        Hole_M4( 20 + 30 + 20              + 7, SIZE_Y - 30 );
        Hole_M4( 20 + 30 + 20 + M4_DELTA_X + 7, SIZE_Y - 30 );

        Hole_M4( 20 + 30 + 20 + 19, 25 );

        if ( 0 == CFG_SMALL )
        {
            Hole_Center( SIZE_X, SIZE_Y );
            Hole_Corner( 20, 20 );

            Hole_Wheel( 20, SIZE_Y - 90 );

            Slot_BF( 10, 20 );
            Slot_BF_Mini( SIZE_X - 20 - 3, 10 + 2 );

            Round( SIZE_X - 20 - 3, 10 + 2 + 15, 9 );

            Slot_LR_Mini( 10 + 2, SIZE_Y - 20 - 3 );
        }

        translate( [ 20, 20, TICK ] )
            Slot_Diag( 39 );

        Slot_LR( 20, 10 );

        translate( [ 25, SIZE_Y - 10, TICK ] )
            Slot_RDiag( 360 - 39 );
    }
}

// Private
// //////////////////////////////////////////////////////////////////////////

module Base_Right()
{
    if ( 0 == CFG_SMALL )
    {
        cube( [ SIZE_X, SIZE_Y, SIZE_Z ] );
    }
    else
    {
        translate( [ 20 + 30 + 5, 0, 0 ] )
            cube( [ SMALL_X, SIZE_Y, SIZE_Z ] );
    }
}

module Base_Left()
{
    if ( 0 == CFG_SMALL )
    {
        cube( [ SIZE_X, SIZE_Y, SIZE_Z ] );
    }
    else
    {
        translate( [ SIZE_X - 20 - 30 - 5 - SMALL_X, 0, 0 ] )
            cube( [ SMALL_X, SIZE_Y, SIZE_Z ] );
    }
}

module Hole_Center( aX, aY )
{
    translate( [ aX, aY, - EPS ] )
        cylinder( 2 * EPS + SIZE_Z, 31, 31, $fn = 20 );
}

module Hole_Corner( aX, aY )
{
    translate( [ aX, aY, - EPS ] )
        cylinder( 2 * EPS + SIZE_Z, 10, 10, $fn = 32 );
}

module Hole_M4( aX, aY )
{
    translate( [ aX, aY, - EPS ] )
    {
        M4_Head_Z( 4 );
        M4_Shank_Z( 2 * EPS + SIZE_Z );
    }
}

module Hole_Wheel( aX, aY )
{
    translate( [ aX, aY, - EPS ] )
        cube( [ 30, 140, 2 * EPS + SIZE_Z ] );
}

module Round( aX, aY, aR )
{
    translate( [ aX, aY, 2 ] )
        cylinder( EPS + SIZE_Z - 2, aR, aR, $fn = 32 );
}

// BF = Back to Front
module Slot_BF( aX, aY )
{
    translate( [ aX, aY, TICK ] )
        cube( [ 2, EPS + SIZE_Y - 20, EPS + SIZE_Z - TICK ] );
}

module Slot_BF_Mini( aX, aY )
{
    translate( [ aX, aY, TICK ] )
        cube( [ 4, 15, EPS + SIZE_Z - TICK ] );
}

module Slot_Diag( aAngle_deg )
{
    rotate( [ 0, 0, aAngle_deg ] )
    {
        translate( [ 0, - 2, 0 ] )
            cube( [ 215, 4, EPS + SIZE_Z - TICK ] );
    }
}

// LR = Left to Right
module Slot_LR( aX, aY )
{
    translate( [ aX, aY, TICK ] )
        cube( [ EPS + SIZE_X - 20, 2, EPS + SIZE_Z - TICK ] );
}

module Slot_LR_Mini( aX, aY )
{
    translate( [ aX, aY, TICK ] )
        cube( [ 15, 4, EPS + SIZE_Z - TICK ] );
}

// RDiag = Reverse Diagonal
module Slot_RDiag( aAngle_deg )
{
    rotate( [ 0, 0, aAngle_deg ] )
    {
        translate( [ 0, - 3, 0 ] )
            cube( [ 215, 6, EPS + SIZE_Z - TICK ] );
    }
}

EPS = 0.1;

SIZE_X = 212;
SIZE_Y = 172.5;
SIZE_Z = 13;

TICK = 3;

SMALL_X = 70;

M4_DELTA_X = 38;

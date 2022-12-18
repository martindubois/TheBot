
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// Fichier   Mecanic/RearWheel.scad

include <C:\_VC\Base3D\Metric\M4.scad>

use <SlottedPanel.scad>

Block();
SlottedPanel();

module Block()
{
    SlottedBlock();

    color( "Blue" )
    {
        difference()
        {
            translate( [ - WHEEL_SIZE_X / 2, - GAP_Y - WHEEL_SIZE_Y, WHEEL_OFFSET_Z ] )
                cube( [ WHEEL_SIZE_X, WHEEL_SIZE_Y, TICK_S ] );

            translate( [ 0, - GAP_Y - WHEEL_SIZE_Y / 2, 0 ] )
            {
                for ( x = [ - HOLE_DIST_X / 2, HOLE_DIST_X / 2 ] )
                {
                    for ( y = [ - HOLE_DIST_Y / 2, HOLE_DIST_Y / 2 ] )
                    {
                        translate( [ x, y, WHEEL_OFFSET_Z - EPS ] )
                            M4_Shank_Z( 2 * EPS + TICK_S );
                    }
                }
            }
        }

        intersection()
        {
            translate( [ - TICK_L / 2, - GAP_Y - WHEEL_SIZE_Y, WHEEL_OFFSET_Z + TICK_S ] )
                cube( [ TICK_L, GAP_Y + WHEEL_SIZE_Y, 67 ] );

            translate( [ 0, 0, WHEEL_OFFSET_Z + TICK_S ] )
            {
                scale( [ 1, 1, 0.95 ] )
                    sphere( GAP_Y + WHEEL_SIZE_Y, $fn = 128 );
            }
        }
    }
}

// Private
// //////////////////////////////////////////////////////////////////////////

PANEL_BORDER_SIZE_Z = 3;

EPS = 0.1;

// Distance between the panel face and the wheel.
GAP_Y = 20;

HOLE_DIST_X = 26;
HOLE_DIST_Y = 34;

PANEL_SIZE_Y = 7;

// Distance betweer the bottom of the panel and the top of the wheel. A
// negative value indicate the top of the week is lower than the bottom of
// the panel
WHEEL_OFFSET_Z = - 5;

WHEEL_SIZE_X = 40;
WHEEL_SIZE_Y = 50;

SLOT_SIZE_Z = 39;

SLOT_Z = 25;

SPACE = 0.2;

TICK_L = 10;

TICK_S = 5;

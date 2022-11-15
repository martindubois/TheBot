
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// Fichier   Mecanic/KCD4.scad

// Used to mount the ON-OFF-ON switch

use <Panel.scad>

Panel();

module Panel()
{
    difference()
    {
        Panel_Small();

        translate( [ - SWITCH_X / 2, - EPS, SWITCH_OFFSET_Z ] )
            cube( [ SWITCH_X, EPS + 1, SWITCH_Z ] );

        translate( [ 0, 10, SWITCH_OFFSET_Z + BORDER ] )
            cylinder( HOLE_Z, 17, 17, $fn = 64 );
    }

    translate( [ SWITCH_X / 2, - GARD_Y, SWITCH_OFFSET_Z - TICK ] )
        cube( [ 2, GARD_Y, 2 * TICK + SWITCH_Z ] );

    for ( z = [ SWITCH_OFFSET_Z - TICK, SWITCH_OFFSET_Z + SWITCH_Z ] )
    {
        translate( [ 0, 0, z ] )
        {
            rotate( [ 0, 0, - 17.4 ] )
                cube( [ SWITCH_X / 2 + 0.8, GARD_Y + 1, TICK ] );
        }
    }
}

BORDER = 2;

EPS = 0.1;

GARD_Y = 5;

HOLE_X = 28;
HOLE_Z = 21;

SWITCH_OFFSET_Z = 15;

SWITCH_X = 32;
SWITCH_Z = 25;

TICK = 2;

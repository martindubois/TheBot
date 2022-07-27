
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// Fichier   Mecanic/LabJackU3-LV.scad

// Use to mound the LabJack U3-LV inside the box.

use <C:\_VC\Base3D\Metric\M3.scad>

use <Panel.scad>

difference()
{
    union()
    {
        Panel_Medium();

        // Stop
        for ( x = [ - 37.5 - 5, 37.5 ] )
        {
            translate( [ x, SIZE_Y + 2, 3 ] )
                cube( [ 5, 5, 5 ] );
        }
    }

    // Mounting hole
    translate( [ 0, - EPS, SIZE_Z - 6 ] )
    {
        M3_Head_Y( EPS + 4 );
        M3_Shank_Y( 2 * EPS + SIZE_Y + 2 );
    }

    // Use less plastic

    for ( x = [ BORDER_W, SIZE_X - 40 ] )
    {
        translate( [ - SIZE_X / 2 + x, TICK, BORDER_W ] )
            cube( [ HOLE_X, EPS + SIZE_Y + 2, SIZE_Z - 2 * BORDER_W ] );
    }

    translate( [ - HOLE_X / 2, TICK, BORDER_W ] )
        cube( [ HOLE_X, EPS + SIZE_Y + 2, SIZE_Z - 3 * BORDER_W ] );
}

// Private
// //////////////////////////////////////////////////////////////////////////

BORDER_W = 9;

EPS = 0.1;

HOLE_X = 30;

SIZE_X = 142;
SIZE_Y =   5;
SIZE_Z = Panel_SizeZ();

TICK = 2;

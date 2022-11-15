
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// Fichier   Mecanic/KCD4.scad

// Used to mount the ON-OFF-ON switch

use <C:\_VC\Base3D\Metric\M3.scad>

use <Panel.scad>

Panel();

module Panel()
{
    difference()
    {
        union()
        {
            Panel_Small();

            translate( [ 0, 0, HOLE_OFFSET_Z ] )
            {
                rotate( [ - 90, 0, 0 ] )
                {
                    cylinder( HOLE_Y + TICK   , HOLE_R  + TICK, HOLE_R  + TICK - 5, $fn = 64);
                    cylinder( HOLE_Y + BLOCK_Y, LASER_R + TICK, LASER_R + TICK    , $fn = 32);
                }
            }

            translate( [ - 1 - TICK, 7, HOLE_OFFSET_Z - 15 ] )
                cube( [ 3 * TICK, HOLE_Y - 7 + BLOCK_Y, BLOCK_Z ] );
        }

        translate( [ 0, - EPS, HOLE_OFFSET_Z ] )
        {
            rotate( [ - 90, 0, 0 ] )
            {
                cylinder( EPS + HOLE_Y , HOLE_R , HOLE_R - 5, $fn = 64);
                cylinder( EPS + LASER_Y, LASER_R, LASER_R, $fn = 32);
            }
        }

        translate( [ - 1, HOLE_Y + TICK, HOLE_OFFSET_Z - BLOCK_Z / 2 - EPS ] )
            cube( [ TICK, BLOCK_Y, 2 * EPS + BLOCK_Z ] );

        for ( z = [ HOLE_OFFSET_Z - 11, HOLE_OFFSET_Z + 11 ] )
        {
            translate( [ - TICK - 1 - EPS, HOLE_Y + BLOCK_Y - 7, z ] )
            {
                M3_Shank_X( 2 * EPS + TICK );
                M3_Thread_X( 2 * EPS + 3 * TICK );
            }
        }
    }
}

BLOCK_Y = 20;
BLOCK_Z = 30;

EPS = 0.1;

HOLE_OFFSET_Z = Panel_SizeZ() / 2;

HOLE_R = 15;
HOLE_Y = 10;

LASER_R =  6.1;
LASER_Y = 35;

TICK = 2;

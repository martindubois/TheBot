
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// Fichier   Mecanic/HBVCAM.scad

// Use to mound the camera

use <C:\_VC\Base3D\Cylinder.scad>
use <C:\_VC\Base3D\Metric\M3.scad>

use <Panel.scad>

Panel();
Retainer();

module Panel()
{
    difference()
    {
        union()
        {
            Panel_Small();

            for ( x = [ - 17, 13 ] )
            {
                translate( [ x, SIZE_Y + BORDER_Y, SIZE_Z / 2 - 17 ] )
                    cube( [ 4, 13, 34 ] );
            }

            for ( y = [ - 17, 14 ] )
            {
                translate( [ - 13, SIZE_Y + BORDER_Y, SIZE_Z / 2 + y ] )
                    cube( [ 26, 8, 3 ] );
            }
        }

        translate( [ - 15, 18, SIZE_Z / 2 - 13 ] )
            cube( [ 30, 3, 26 ] );

        translate( [ 0, - EPS, SIZE_Z / 2 ] )
            Cylinder_Y( 2 * EPS + SIZE_Y + BORDER_Y, HOLE_R, 32 );
    }
}

module Retainer()
{
    color( "red" )
    {
        difference()
        {
            union()
            {
                translate( [ - 13, 20, 32 ] )
                    cube( [ 26, 2, 3 ] );

                translate( [ - R_X / 2, 22, 14 ] )
                    cube( [ R_X, 2, 39 ] );

                for ( z = [ 14, 51 ] )
                {
                    translate( [ - R_X / 2, 12, z ] )
                        cube( [ R_X, 10, 2 ] );
                }

                for ( z = [ 3, 53 ] )
                {
                    translate( [ - R_X / 2, 12, z ] )
                        cube( [ R_X, 2, 11 ] );
                }
            }

            for ( x = [ - SIZE_X / 2 + 2 * BORDER_W, SIZE_X / 2 - 2 * BORDER_W ] )
            {
                for ( z = [ 2 * BORDER_W, SIZE_Z - 2 * BORDER_W ] )
                {
                    translate( [ x, 12 - EPS, z ] )
                    {
                        M3_Shank_Y( 2 * EPS + SIZE_Y + BORDER_Y );
                    }
                }
            }
        }
    }
}

// Private
// //////////////////////////////////////////////////////////////////////////

BORDER_W = 3;
BORDER_Y = 2;

EPS = 0.1;

HOLE_R = 11;

R_X = 36;

SIZE_X = 46;
SIZE_Y =  5;
SIZE_Z = Panel_SizeZ();

TICK = 2;

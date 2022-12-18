
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// Fichier   Mecanic/Screen.scad

use <SlottedPanel.scad>

Block();
// SlottedPanel();

module Block()
{
    SlottedBlock();

    color( "Blue" )
    {
        difference()
        {
            translate( [ - SIZE_X / 2, - DIST_Y, 0 ] )
                cube( [ SIZE_X, DIST_Y, SIZE_Z ] );

            for ( x = [ - 10.5, 10.5 ] )
            {
                translate( [ x, - DIST_Y, BASE_Z ] )
                {
                    scale( [ 1, 0.5, 1 ] )
                        cylinder( SIZE_Z, 2, 2, $fn = 16 );
                }
            }

            for ( z = [ 11, 26, 41, 56 ] )
            {
                translate( [ - SIZE_X / 2 - EPS, - DIST_Y / 2, z ] )
                {
                    rotate( [ 0, 90, 0 ] )
                    {
                        scale( [ 1.5, 1, 1 ] )
                            cylinder( 2 * EPS + SIZE_X, 4, 4, $fn = 32 );
                    }
                }
            }
        }

        translate( [ - SIZE_X / 2, - DIST_Y - BASE_Y, 0 ] )
            cube( [ SIZE_X, BASE_Y, BASE_Z ] );

        translate( [ - CENTER_X / 2, - DIST_Y - CENTER_Y, BASE_Z ] )
            cube( [ CENTER_X, CENTER_Y, CENTER_Z ] );

        translate( [ - TOP_X / 2, - DIST_Y - CENTER_Y - TOP_Y, BASE_Z ] )
            cube( [ TOP_X, TOP_Y, TOP_Z ] );
    }
}

// Private
// //////////////////////////////////////////////////////////////////////////

BASE_Y =  5;
BASE_Z = 10;

CENTER_X =  6;
CENTER_Y =  1.5;
CENTER_Z = 51;

EPS = 0.1;

DIST_Y = 15;

SIZE_X = 28;
SIZE_Z = 66;

TOP_X = 13;
TOP_Y =  2;
TOP_Z = 53;

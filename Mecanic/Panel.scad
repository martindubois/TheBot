
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// Fichier   Mecanic/Panel.scad

use <C:\_VC\Base3D\Metric\M3.scad>

Panel_Medium();

function Panel_SizeZ() = SIZE_Z;

module Panel_Large() { Panel( SIZE_LARGE_X ); }

module Panel_Medium() { Panel( SIZE_MEDIUM_X ); }

module Panel_Small() { Panel( SIZE_SMALL_X ); }

module Panel_XSmall() { Panel( SIZE_X_SMALL_X ); }

// Private
// //////////////////////////////////////////////////////////////////////////

module Panel( aSizeX )
{
    difference()
    {
        union()
        {
            translate( [ - aSizeX / 2, 0, 0 ] )
                cube( [ aSizeX, SIZE_Y, SIZE_Z ] );

            translate( [ - aSizeX / 2 + BORDER_W, SIZE_Y, BORDER_W ] )
                cube( [ aSizeX - 2 * BORDER_W, BORDER_Y, SIZE_Z - 2 * BORDER_W ] );
        }

        for ( x = [ - aSizeX / 2 + 2 * BORDER_W, aSizeX / 2 - 2 * BORDER_W ] )
        {
            for ( z = [ 2 * BORDER_W, SIZE_Z - 2 * BORDER_W ] )
            {
                translate( [ x, - EPS, z ] )
                {
                    M3_Head_Y( 3 );
                    M3_Shank_Y( 2 * EPS + SIZE_Y + BORDER_Y );
                }
            }
        }

        for ( x = [ - aSizeX / 2 + BORDER_W - EPS, aSizeX / 2 - BORDER_W - CORNER ] )
        {
            for ( z = [ BORDER_W - EPS, SIZE_Z - BORDER_W - CORNER ] )
            {
                translate( [ x, SIZE_Y, z ] )
                    cube( [ CORNER + EPS, BORDER_Y + EPS, CORNER + EPS ] );
            }
        }
    }
}

BORDER_W = 3;
BORDER_Y = 2;

CORNER = 3;

EPS = 0.1;

SIZE_LARGE_X   = 170;
SIZE_MEDIUM_X  = 142;
SIZE_SMALL_X   =  46;
SIZE_X_SMALL_X =  41;
SIZE_Y         =   5;
SIZE_Z         =  66;

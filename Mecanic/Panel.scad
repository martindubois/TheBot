
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// Fichier   Mecanic/Panel.scad

use <C:\_VC\Base3D\Cylinder.scad>
use <C:\_VC\Base3D\Metric\M3.scad>

Panel_Small_Left( true );

function Panel_SizeZ() = SIZE_Z;

module Panel_Large() { Panel( SIZE_LARGE_X ); }

module Panel_Medium() { Panel( SIZE_MEDIUM_X ); }

module Panel_Small() { Panel( SIZE_SMALL_X ); }

module Panel_Small_Left( aTWrapHoles )
{
    difference()
    {
        Panel_Small();

        translate( [ - SIZE_SMALL_X / 2, 0, 0 ] )
            UpCorner();

        if ( aTWrapHoles )
        {
            TWrapHoles();
        }
    }
}

module Panel_Small_Right( aTWrapHoles )
{
    difference()
    {
        Panel_Small();

        translate( [ SIZE_SMALL_X / 2, 0, 0 ] )
            UpCorner();

        if ( aTWrapHoles )
        {
            TWrapHoles();
        }
    }
}

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

module TWrapHoles()
{
    for ( x = [ - 7, 3 ] )
    {
        for ( z = [ SIZE_Z / 2 - 7, SIZE_Z / 2 + 3 ] )
        {
            translate( [ x, 3 - EPS, z ] )
                cube( [ 4, 2 * EPS + 4, 4 ] );
        }
    }

    translate( [ - 7, - EPS, SIZE_Z / 2 - 7 ] )
        cube( [ 14, EPS + 3, 14 ] );
}

module UpCorner()
{
    translate( [ 0, 0, SIZE_Z - 13 ] )
    {
        translate( [ - UP_R + EPS, 0, 0 ] )
        {
            translate( [ 0, - EPS, 0 ] )
                cube( [ 2 * UP_R, 2 * EPS + 7, 13 + EPS ] );

            translate( [ - 3, 5, 0 ] )
                cube( [ 2 * ( UP_R + 3 ), EPS + 2, 13 + EPS ] );
        }

        translate( [ 0, - EPS, 0 ] )
            Cylinder_Y( 2 * EPS + 7, UP_R, 32 );

        translate( [ 0, 5, 0 ] )
            Cylinder_Y( 2 + EPS, UP_R + 3, 32 );
    }
}

BORDER_W = 3;
BORDER_Y = 2;

CORNER = 3;

EPS = 0.1;

UP_R = 10;

SIZE_LARGE_X   = 170;
SIZE_MEDIUM_X  = 142;
SIZE_SMALL_X   =  46;
SIZE_X_SMALL_X =  41;
SIZE_Y         =   5;
SIZE_Z         =  66;


// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2024 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// Fichier   Mecanic/Ethernet_USB.scad

// Use to mound the Ethernet to USB adapter

use <C:\_VC\Base3D\Metric\M3.scad>

use <Panel.scad>

Panel();
Retainer();

module Panel()
{
    Panel_Small_Right( false );

    translate( [ 0, SIZE_Y + BORDER_Y, SUPPORT_H ] )
    {
        difference()
        {
            translate( [ - SUPPORT_X / 2, 0, 0 ] )
                cube( [ SUPPORT_X, SUPPORT_Y, SUPPORT_Z ] );

            translate( [ - ADAPTER_X / 2, TICK, - EPS ] )
                cube( [ ADAPTER_X, SUPPORT_Y - TICK + EPS, 2 * EPS + SUPPORT_Z ] );
        }
    }
}

module Retainer()
{
    color( "red" )
    {
        difference()
        {
            translate( [ - RETAINER_X / 2, RETAINER_D, RETAINER_H ] )
                cube( [ RETAINER_X, TICK, SIZE_Z - RETAINER_H - TICK ] );

            translate( [ - ( ADAPTER_X - 4 ) / 2, RETAINER_D - EPS, RETAINER_H - EPS ] )
                cube( [ ADAPTER_X - 4, 2 * EPS + 2, 10 ] );

            for ( x = [ - SIZE_X / 2 + 2 * BORDER_W, SIZE_X / 2 - 2 * BORDER_W ] )
            {
                for ( z = [ 2 * BORDER_W, SIZE_Z - 2 * BORDER_W ] )
                {
                    translate( [ x, RETAINER_D - EPS, z ] )
                    {
                        M3_Shank_Y( 2 * EPS + SIZE_Y + BORDER_Y );
                    }
                }
            }
        }

        lWidth = ( SUPPORT_X - ADAPTER_X ) / 2;

        for ( x = [ - SUPPORT_X / 2, SUPPORT_X / 2 - lWidth ] )
        {
            translate( [ x, RETAINER_D - 5, SUPPORT_H ] )
                cube( [ lWidth, 5, SUPPORT_Z + TICK ] );
        }
    }
}

// Private
// //////////////////////////////////////////////////////////////////////////

ADAPTER_X = 30;

BORDER_Y = 2;
BORDER_W = 3;

EPS = 0.1;

RETAINER_D = 28;
RETAINER_H =  2;
RETAINER_X = 42;

SIZE_X = 46;
SIZE_Y =  5;
SIZE_Z = Panel_SizeZ();

SUPPORT_H = 12;
SUPPORT_X = SIZE_X - 8;
SUPPORT_Y = 10;
SUPPORT_Z = 20;

TICK = 2;

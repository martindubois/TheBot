
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// Fichier   Mecanic/Corner.scad

use <C:\_VC\Base3D\Metric\M3.scad>

// Corner_4();

translate( [ 30, 0, 0 ] ) Corner_2();

// translate( [ 60, 0, 0 ] ) Corder_1();

module Corner_4()
{
    difference()
    {
        union()
        {
            translate( [ - SIZE_X / 2, 0, 0 ] )
                cube( [ SIZE_X, SIZE_Y, SIZE_X ] );

            for ( z = [ 0, SIZE_X - CORNER_X ] )
            {
                for ( x = [ - SIZE_X / 2, SIZE_X / 2 - CORNER_X ] )
                {
                    translate( [ x, SIZE_Y, z ] )
                        cube( [ CORNER_X, CORNER_Y, CORNER_X ] );
                }
            }
        }
            
        for ( z = [ 5, 19 ] )
        {
            for ( x = [ - 7.5, 7.5 ] )
                Hole( x, z );
        }
    }
}

module Corner_2()
{
    difference()
    {
        union()
        {
            translate( [ - SIZE_X / 2, 0, 0 ] )
                cube( [ SIZE_X, SIZE_Y, SIZE_X / 2 ] );

            for ( x = [ - SIZE_X / 2, SIZE_X / 2 - CORNER_X ] )
            {
                translate( [ x, SIZE_Y, 0 ] )
                    cube( [ CORNER_X, CORNER_Y, CORNER_X ] );
            }
        }

        for ( x = [ - 7.5, 7.5 ] )
            Hole( x, 5 );
    }
}

module Corder_1()
{
    difference()
    {
        union()
        {
            translate( [ - SIZE_X / 2, 0, 0 ] )
                cube( [ SIZE_X / 2, SIZE_Y, SIZE_X / 2 ] );

            translate( [ - SIZE_X / 2, SIZE_Y, 0 ] )
                cube( [ CORNER_X, CORNER_Y, CORNER_X ] );
        }

        Hole( - 7.5, 5 );
    }
}

// Private
// //////////////////////////////////////////////////////////////////////////

module Hole( aX, aZ )
{
    translate( [ aX, - EPS, aZ ] )
        M3_Thread_Y( 2 * EPS + SIZE_Y + CORNER_Y );
}

CORNER_X = 5;
CORNER_Y = 1;

EPS = 0.1;

SIZE_X = 24;
SIZE_Y = 2;

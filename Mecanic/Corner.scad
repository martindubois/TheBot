
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// Fichier   Mecanic/Corner.scad

use <C:\_VC\Base3D\Metric\M3.scad>

Corner_4();

translate( [ 30, 0, 0 ] ) Corner_2();

translate( [ 60, 0, 0 ] ) Corder_1();

module Corner_4()
{
    difference()
    {
        translate( [ - SIZE_X / 2, 0, 0 ] )
            cube( [ SIZE_X, SIZE_Y, SIZE_X ] );
            
        for ( z = [ 5, 19 ] )
        {
            for ( x = [ - 7, 7 ] )
            {
                translate( [ x, - EPS, z ] )
                    M3_Thread_Y( 2 * EPS + SIZE_Y ); 
            }
        }
    }
}

module Corner_2()
{
    difference()
    {
        translate( [ - SIZE_X / 2, 0, 0 ] )
            cube( [ SIZE_X, SIZE_Y, SIZE_X / 2 ] );

        for ( x = [ - 7, 7 ] )
        {
            translate( [ x, - EPS, 5 ] )
                M3_Thread_Y( 2 * EPS + SIZE_Y ); 
        }
    }
}

module Corder_1()
{
    difference()
    {
        translate( [ - SIZE_X / 2, 0, 0 ] )
            cube( [ SIZE_X / 2, SIZE_Y, SIZE_X / 2 ] );

        translate( [ - 7, - EPS, 5 ] )
            M3_Thread_Y( 2 * EPS + SIZE_Y ); 
    }
}

// Private
// //////////////////////////////////////////////////////////////////////////

DIST = 14;

EPS = 0.1;

SIZE_X = 24;
SIZE_Y = 2;

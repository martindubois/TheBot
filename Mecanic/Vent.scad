
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// Fichier   Mecanic/Vent.scad

use <Panel.scad>

Panel();

module Panel()
{
    difference()
    {
        Panel_Small();

        for ( x = [ - 7, 7 ] )
        {
            for ( z = [ 9, 21, 33, 45, 57 ] )
            {
                Hole( x, z );
            }
        }

        for ( x = [ - 14, 0, 14 ] )
        {
            for ( z = [ 15, 27, 39, 51 ] )
            {
                Hole( x, z );
            }
        }
    }
}

// Private
// //////////////////////////////////////////////////////////////////////////

module Hole( aX, aZ )
{
    translate( [ aX, - 1, aZ ] )
    {
        rotate( [ - 70, 0, 0 ] )
        {
            scale( [ 1, 0.5, 1 ] )
                cylinder( 10, 5, 5, $fn = 32 );
        }
    }
}
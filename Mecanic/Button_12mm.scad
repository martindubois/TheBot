
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// Fichier   Mecanic/Button_12mm.scad

use <Panel.scad>

Panel();

module Panel()
{
    difference()
    {
        Panel_Small();

        for ( z = [ 15, 45 ] )
        {
            translate( [ 0, - EPS, z ] )
            {
                rotate( [ - 90, 0, 0 ] )
                    cylinder( 2 * EPS + 7, 6.1, 6.1, $fn = 32 );
            }
        }
    }
}

// Private
// //////////////////////////////////////////////////////////////////////////

EPS = 0.1;

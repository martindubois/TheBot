
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TheBot
// Fichier   Mecanic/SlottedPanel.scad

use <Panel.scad>

SlottedBlock();
SlottedPanel();

module SlottedBlock()
{
    color("Blue")
    {
        translate( [ - TICK_S / 2, 0, SLOT_Z + SPACE ] )
            cube( [ TICK_S, 2 * SPACE + PANEL_SIZE_Y, SLOT_SIZE_Z - SPACE ] );

        translate( [ - TICK_S / 2, 0, SLOT_Z + SPACE + SLOT_SIZE_Z - SPACE ] )
            cube( [ TICK_S, 5, PANEL_BORDER_SIZE_Z ] );

        translate( [ - TICK_L / 2, 2 * SPACE + PANEL_SIZE_Y, SLOT_Z + SPACE ] )
            cube( [ TICK_L, TICK_S, SLOT_SIZE_Z - SPACE + PANEL_BORDER_SIZE_Z ] );
    }
}

module SlottedPanel()
{
    difference()
    {
        Panel_Small();

        translate( [ - SPACE - TICK_S / 2, - EPS, SLOT_Z ] )
            cube( [ 2 * SPACE + TICK_S, 2 * EPS + PANEL_SIZE_Y, SLOT_SIZE_Z + PANEL_BORDER_SIZE_Z + EPS ] );
    }
}

// Private
// //////////////////////////////////////////////////////////////////////////

EPS = 0.1;

PANEL_BORDER_SIZE_Z = 3;

PANEL_SIZE_Y = 7;

SLOT_SIZE_Z = 38;

SLOT_Z = 25;

SPACE = 0.2;

TICK_L = 10;

TICK_S = 5;

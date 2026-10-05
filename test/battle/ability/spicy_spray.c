#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Spicy Spray burns any attacker that damages its user")
{
    enum Move move;
    PARAMETRIZE { move = MOVE_SCRATCH; }
    PARAMETRIZE { move = MOVE_SWIFT; }

    GIVEN {
        ASSUME(MoveMakesContact(MOVE_SCRATCH));
        ASSUME(!MoveMakesContact(MOVE_SWIFT));
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_SCOVILLAIN) { Ability(ABILITY_SPICY_SPRAY); }
    } WHEN {
        TURN { MOVE(player, move); }
        TURN {}
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_SPICY_SPRAY);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_BRN, player);
        STATUS_ICON(player, burn: TRUE);
    }
}
#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Eelevate blocks Ground-type moves")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_MUD_SLAP) == TYPE_GROUND);
        PLAYER(SPECIES_EELEKTROSS) { Ability(ABILITY_EELEVATE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_MUD_SLAP); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_EELEVATE);
    } THEN {
        EXPECT_EQ(player->hp, player->maxHP);
    }
}

SINGLE_BATTLE_TEST("Eelevate raises its user's highest stat after a knockout")
{
    GIVEN {
        PLAYER(SPECIES_EELEKTROSS) { Ability(ABILITY_EELEVATE); Speed(100); }
        OPPONENT(SPECIES_MAGIKARP) { HP(1); Speed(1); }
        OPPONENT(SPECIES_MAGIKARP) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); SEND_OUT(opponent, 1); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_EELEVATE);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
    } THEN {
        EXPECT_EQ(player->statStages[STAT_ATK], DEFAULT_STAT_STAGE + 1);
    }
}
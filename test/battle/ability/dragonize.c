#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Dragonize converts Normal-type moves and boosts their power", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_NONE; }
    PARAMETRIZE { ability = ABILITY_DRAGONIZE; }

    GIVEN {
        WITH_CONFIG(B_ATE_MULTIPLIER, GEN_7);
        ASSUME(GetMoveType(MOVE_TACKLE) == TYPE_NORMAL);
        PLAYER(SPECIES_DRUDDIGON) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.8), results[1].damage);
    }
}
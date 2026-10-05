#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Fire Mane boosts Fire-type moves by 50%", s16 damage)
{
    enum Move move;
    enum Ability ability;
    PARAMETRIZE { move = MOVE_SCRATCH; ability = ABILITY_KLUTZ; }
    PARAMETRIZE { move = MOVE_SCRATCH; ability = ABILITY_FIRE_MANE; }
    PARAMETRIZE { move = MOVE_FLAME_CHARGE; ability = ABILITY_KLUTZ; }
    PARAMETRIZE { move = MOVE_FLAME_CHARGE; ability = ABILITY_FIRE_MANE; }
    PARAMETRIZE { move = MOVE_FLAMETHROWER; ability = ABILITY_KLUTZ; }
    PARAMETRIZE { move = MOVE_FLAMETHROWER; ability = ABILITY_FIRE_MANE; }

    GIVEN {
        ASSUME(GetMoveType(MOVE_SCRATCH) != TYPE_FIRE);
        ASSUME(GetMoveType(MOVE_FLAME_CHARGE) == TYPE_FIRE);
        ASSUME(GetMoveType(MOVE_FLAMETHROWER) == TYPE_FIRE);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
        EXPECT_MUL_EQ(results[2].damage, Q_4_12(1.5), results[3].damage);
        EXPECT_MUL_EQ(results[4].damage, Q_4_12(1.5), results[5].damage);
    }
}
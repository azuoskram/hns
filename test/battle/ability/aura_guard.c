#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(MoveMakesContact(MOVE_SCRATCH));
    ASSUME(MoveMakesContact(MOVE_FIRE_PUNCH));
    ASSUME(GetMoveType(MOVE_FIRE_PUNCH) == TYPE_FIRE);
    ASSUME(GetMoveType(MOVE_EMBER) == TYPE_FIRE);
}

SINGLE_BATTLE_TEST("Aura Guard halves damage from contact moves, including Fire-type moves", s16 damage)
{
    enum Move move;
    enum Ability ability;
    PARAMETRIZE { move = MOVE_SCRATCH; ability = ABILITY_KLUTZ; }
    PARAMETRIZE { move = MOVE_SCRATCH; ability = ABILITY_AURA_GUARD; }
    PARAMETRIZE { move = MOVE_FIRE_PUNCH; ability = ABILITY_KLUTZ; }
    PARAMETRIZE { move = MOVE_FIRE_PUNCH; ability = ABILITY_AURA_GUARD; }

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_STUFFUL) { Ability(ability); }
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(0.5), results[1].damage);
        EXPECT_MUL_EQ(results[2].damage, Q_4_12(0.5), results[3].damage);
    }
}

SINGLE_BATTLE_TEST("Aura Guard does not amplify Fire-type moves", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_KLUTZ; }
    PARAMETRIZE { ability = ABILITY_FLUFFY; }
    PARAMETRIZE { ability = ABILITY_AURA_GUARD; }

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_STUFFUL) { Ability(ability); }
    } WHEN {
        TURN { MOVE(player, MOVE_EMBER); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(2.0), results[1].damage);
        EXPECT_EQ(results[0].damage, results[2].damage);
    }
}
#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Mega Sol boosts Fire damage and halves Water damage", s16 damage)
{
    enum Move move;
    enum Ability ability;
    PARAMETRIZE { move = MOVE_EMBER; ability = ABILITY_KLUTZ; }
    PARAMETRIZE { move = MOVE_EMBER; ability = ABILITY_MEGA_SOL; }
    PARAMETRIZE { move = MOVE_WATER_GUN; ability = ABILITY_KLUTZ; }
    PARAMETRIZE { move = MOVE_WATER_GUN; ability = ABILITY_MEGA_SOL; }

    GIVEN {
        ASSUME(GetMoveType(MOVE_EMBER) == TYPE_FIRE);
        ASSUME(GetMoveType(MOVE_WATER_GUN) == TYPE_WATER);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.5), results[1].damage);
        EXPECT_MUL_EQ(results[2].damage, Q_4_12(0.5), results[3].damage);
    }
}

SINGLE_BATTLE_TEST("Mega Sol makes Weather Ball Fire-type")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_WEATHER_BALL) == EFFECT_WEATHER_BALL);
        ASSUME(GetSpeciesType(SPECIES_BELDUM, 0) == TYPE_STEEL || GetSpeciesType(SPECIES_BELDUM, 1) == TYPE_STEEL);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_MEGA_SOL); }
        OPPONENT(SPECIES_BELDUM);
    } WHEN {
        TURN { MOVE(player, MOVE_WEATHER_BALL); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WEATHER_BALL, player);
        MESSAGE("It's super effective!");
    }
}

SINGLE_BATTLE_TEST("Mega Sol ignores Sandstorm and Snow defensive boosts", s16 damage)
{
    enum Ability ability;
    enum Ability weatherAbility;
    u16 defender;
    enum Move move;
    PARAMETRIZE { ability = ABILITY_KLUTZ; weatherAbility = ABILITY_SAND_STREAM; defender = SPECIES_REGIROCK; move = MOVE_SHADOW_BALL; }
    PARAMETRIZE { ability = ABILITY_MEGA_SOL; weatherAbility = ABILITY_SAND_STREAM; defender = SPECIES_REGIROCK; move = MOVE_SHADOW_BALL; }
    PARAMETRIZE { ability = ABILITY_KLUTZ; weatherAbility = ABILITY_SNOW_WARNING; defender = SPECIES_VANILLUXE; move = MOVE_SCRATCH; }
    PARAMETRIZE { ability = ABILITY_MEGA_SOL; weatherAbility = ABILITY_SNOW_WARNING; defender = SPECIES_VANILLUXE; move = MOVE_SCRATCH; }

    GIVEN {
        ASSUME(GetMoveCategory(MOVE_SHADOW_BALL) == DAMAGE_CATEGORY_SPECIAL);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        OPPONENT(defender) { Ability(weatherAbility); }
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.5), results[1].damage);
        EXPECT_MUL_EQ(results[2].damage, Q_4_12(1.5), results[3].damage);
    }
}
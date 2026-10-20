#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Innate Magic Guard prevents burn residual damage")
{
    GIVEN {
        PLAYER(SPECIES_CLEFABLE) { Ability(ABILITY_CUTE_CHARM); Status1(STATUS1_BURN); HP(1), MaxHP(400); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        player->innates[0] = ABILITY_MAGIC_GUARD;
        TURN {}
    } SCENE {
        NOT HP_BAR(player);
    } THEN {
        EXPECT_EQ(player->hp, 1);
    }
}

SINGLE_BATTLE_TEST("Innate Immunity prevents Toxic")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_TOXIC) == EFFECT_NON_VOLATILE_STATUS);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_SNORLAX) { Ability(ABILITY_THICK_FAT); }
    } WHEN {
        opponent->innates[0] = ABILITY_RUN_AWAY;
        opponent->innates[1] = ABILITY_UNAWARE;
        opponent->innates[2] = ABILITY_IMMUNITY;
        TURN { MOVE(player, MOVE_TOXIC); }
    } SCENE {
        NOT STATUS_ICON(opponent, poison: TRUE);
    }
}

SINGLE_BATTLE_TEST("Innate Poison Heal heals poison damage")
{
    GIVEN {
        PLAYER(SPECIES_SHROOMISH) { Ability(ABILITY_EFFECT_SPORE); Status1(STATUS1_POISON); HP(1), MaxHP(400); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        player->innates[0] = ABILITY_POISON_HEAL;
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_POISON_HEAL);
        MESSAGE("The poisoning healed Shroomish a little bit!");
        HP_BAR(player, damage: -50);
    }
}

SINGLE_BATTLE_TEST("Poison Heal still activates alongside innate Magic Guard")
{
    GIVEN {
        PLAYER(SPECIES_SHROOMISH) { Ability(ABILITY_EFFECT_SPORE); Status1(STATUS1_POISON); HP(1), MaxHP(400); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        player->innates[0] = ABILITY_MAGIC_GUARD;
        player->innates[1] = ABILITY_POISON_HEAL;
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_POISON_HEAL);
        MESSAGE("The poisoning healed Shroomish a little bit!");
        HP_BAR(player, damage: -50);
    }
}

SINGLE_BATTLE_TEST("Innate Levitate prevents Ground-type damage")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_SNORLAX) { Ability(ABILITY_THICK_FAT); }
    } WHEN {
        opponent->innates[0] = ABILITY_RUN_AWAY;
        opponent->innates[1] = ABILITY_UNAWARE;
        opponent->innates[2] = ABILITY_LEVITATE;
        TURN { MOVE(player, MOVE_EARTHQUAKE); }
    } SCENE {
        NOT HP_BAR(opponent);
    } THEN {
        EXPECT_EQ(opponent->hp, opponent->maxHP);
    }
}

SINGLE_BATTLE_TEST("Innate Wonder Guard blocks non-super-effective damage")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_SNORLAX) { Ability(ABILITY_THICK_FAT); }
    } WHEN {
        opponent->innates[0] = ABILITY_WONDER_GUARD;
        TURN { MOVE(player, MOVE_EARTHQUAKE); }
    } SCENE {
        NOT HP_BAR(opponent);
    } THEN {
        EXPECT_EQ(opponent->hp, opponent->maxHP);
    }
}

SINGLE_BATTLE_TEST("Innate Mold Breaker bypasses an opposing innate Levitate")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_THICK_FAT); }
        OPPONENT(SPECIES_SNORLAX) { Ability(ABILITY_THICK_FAT); }
    } WHEN {
        player->innates[0] = ABILITY_MOLD_BREAKER;
        opponent->innates[0] = ABILITY_LEVITATE;
        TURN { MOVE(player, MOVE_EARTHQUAKE); }
    } SCENE {
        HP_BAR(opponent);
    } THEN {
        EXPECT_LT(opponent->hp, opponent->maxHP);
    }
}

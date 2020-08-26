#!/usr/bin/python

import collections
import itertools
import math

Fighter = collections.namedtuple('Fighter', ['health', 'attack'])

def ceil(a, b):
    return (a + b - 1) // b

def get_attacks(health, attack, B):
    attacks, previous_attacks = math.inf, math.inf
    for b in itertools.count():
        attacks = b + math.ceil(health / (attack + B * b))
        if attacks > previous_attacks:
            return previous_attacks
        previous_attacks = attacks
    return None

def get_debuff(health, attack, D):
    yield 0, (health - 1) // attack
    if D == 0:
        return
    debuffs, previous_debuffs = 1, 0
    while debuffs < ceil(attack, D):
        v = (health - 1) // (attack - debuffs * D)
        if v == 0:
            return
        yield debuffs, v
        v, previous_debuffs = v + 1, debuffs
        debuffs = ceil(v * attack - (health - 1), v * D)
        if debuffs - previous_debuffs > 1 and v == 2:
            return
    yield ceil(attack, D), math.inf

def compute_health(health, attack, start, end, D):
    start_attack, end_attack = attack - start * D, attack - end * D
    return health - (start_attack + end_attack) * (end - start + 1) // 2

def cure_debuff(dragon, attack, D, health, debuffs):
    def delta():
        return (2 * attack - D) ** 2 - 8 * health * D

    if debuffs == 0:
        return 0, health, attack - debuffs * D

    if health <= attack - D:
        pass
    elif delta() >= 0:
        shift = int((2 * attack - D - delta() ** 0.5) / (2 * D)) - 1
        health = compute_health(health, attack, 1, min(shift, debuffs), D)
        if shift < debuffs and health > attack - (shift + 1) * D:
            shift += 1
            health -= attack - shift * D
        if shift >= debuffs:
            return 0, health, attack - debuffs * D
        attack, debuffs = attack - shift * D, debuffs - shift
    else:
        return 0, compute_health(
            health, attack, 1, debuffs, D), attack - debuffs * D

    cures = 1
    cure_period, health = (dragon.health - 1) // attack, dragon.health - attack
    if 2 <= cure_period <= debuffs - 1:
        q = (debuffs - 2) // (cure_period - 1)
        cures, shift = cures + q, q * (cure_period - 1)
        attack, debuffs = attack - shift * D, debuffs - shift
        health = dragon.health - attack

    new_health = compute_health(health, attack, 1, debuffs, D)
    attack -= debuffs * D
    if new_health > 0:
        return cures, new_health, attack
    return cures + 1, compute_health(dragon.health, attack, -1, 0, D), attack

def cure_attack(health, attack, attacks, cure_period):
    if attack <= 0 or attacks - 1 <= (health - 1) // attack:
        return 0
    if cure_period <= 1:
        return math.inf
    return 1 + (attacks - 2 - (health - 1) // attack) // (cure_period - 1)

def solve(dragon, knight, B, D):
    attacks = get_attacks(knight.health, dragon.attack, B)
    out = math.inf
    cures_debuff = 0
    previous_debuffs, attack, health = 0, knight.attack, dragon.health
    for debuffs, cure_period in get_debuff(dragon.health, attack, D):
        if cure_period != math.inf:
            c, health, attack = cure_debuff(
                dragon, attack, D, health, debuffs - previous_debuffs)
            cures_debuff += c
        else:
            attack -= (debuffs - previous_debuffs) * D
        cures_attack = cure_attack(health, attack, attacks, cure_period)
        out = min(out, debuffs + cures_debuff + attacks + cures_attack)
        previous_debuffs = debuffs
    return out if out != math.inf else 'IMPOSSIBLE'

def run():
    T = int(input())
    for i in range(T):
        Hd, Ad, Hk, attack, B, D = (int(x) for x in input().split())
        dragon, knight = Fighter(Hd, Ad), Fighter(Hk, attack)
        print('Case #{0}: {1}'.format(i + 1, solve(dragon, knight, B, D)))

run()

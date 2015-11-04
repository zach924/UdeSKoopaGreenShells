#pragma once

struct AttackNotification
{
    bool AttackerIsDead;
    bool TargetIsDead;
    bool CanMove;
    int RiposteDamage;

    AttackNotification(int damage, bool targetDead, bool canMove) :
        RiposteDamage(damage),
        TargetIsDead(targetDead),
        AttackerIsDead(false),
        CanMove(canMove)
    {}
};
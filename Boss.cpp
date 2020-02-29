#include "stdafx.h"

Boss::Boss(MyObjectBuilder *mob, BossDesign &bd, int x, int y) :Monster(mob, x, y, bd.experience, bd.velocity, bd.health, bd.atk, bd.armor, bd.object, bd.range, bd.element_type) {}

MachineGril::MachineGril(int x, int y) : Boss(boss_image, boss1, x, y) {}
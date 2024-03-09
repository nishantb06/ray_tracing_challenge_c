#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "tuple.h"

typedef struct Projectile {
    Tuple position;
    Tuple velocity;
} Projectile;

typedef struct Environment {
    Tuple gravity;
    Tuple wind;
} Environment;

void tick(Environment *env, Projectile *proj){
    proj->position = Add(proj->position, proj->velocity);
    proj->velocity = Add(Add(proj->velocity, env->gravity), env->wind);
}

#endif
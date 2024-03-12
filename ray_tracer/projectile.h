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

//constructor for projectile
Projectile Projectile_(Tuple position, Tuple velocity){
    Projectile proj;
    proj.position = position;
    proj.velocity = velocity;
    return proj;
}

//constructor for environment
Environment Environment_(Tuple gravity, Tuple wind){
    Environment env;
    env.gravity = gravity;
    env.wind = wind;
    return env;
}

void tick(Environment *env, Projectile *proj){
    proj->position = Add(proj->position, proj->velocity);
    proj->velocity = Add(Add(proj->velocity, env->gravity), env->wind);
}

#endif
#ifndef LIGHT_H
#define LIGHT_H
#include "tuple.h"
#include "matrix.h"
#include "ray.h"
#include "canvas.h"
#include "transformation.h"

typedef struct Light {
    Tuple position;
    Color intensity;
} Light;

typedef struct Material {
    Color color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
} Material;

Light* Light_(Tuple position, Color intensity)
{
    Light* light = (Light*)malloc(sizeof(Light));
    light->position = position;
    light->intensity = intensity;
    return light;
}
Material* Material_(Color color, float ambient, float diffuse, float specular, float shininess)
{
    Material* material = (Material*)malloc(sizeof(Material));
    material->color = color;
    material->ambient = ambient;
    material->diffuse = diffuse;
    material->specular = specular;
    material->shininess = shininess;
    return material;
}

Color Lighting(Material* material, Light* light, Tuple point, Tuple eyev, Tuple normalv, bool inShadow)
{
    Color effective_color = Color_Multiply(material->color, light->intensity);
    Tuple lightv = Tuple_Normalize(Tuple_Sub(light->position, point));
    Color ambient = Color_Multiply(effective_color, material->ambient);
    float light_dot_normal = Tuple_Dot(lightv, normalv);
    Color diffuse = Color(0, 0, 0);
    Color specular = Color(0, 0, 0);
    if (light_dot_normal >= 0 && !inShadow)
    {
        diffuse = Color_Multiply(effective_color, material->diffuse * light_dot_normal);
        Tuple reflectv = Tuple_Reflect(Tuple_Negate(lightv), normalv);
        float reflect_dot_eye = Tuple_Dot(reflectv, eyev);
        if (reflect_dot_eye > 0)
        {
            float factor = pow(reflect_dot_eye, material->shininess);
            specular = Color_Multiply(light->intensity, material->specular * factor);
        }
    }
    return Color_Add(Color_Add(ambient, diffuse), specular);
}

#endif // LIGHT_H
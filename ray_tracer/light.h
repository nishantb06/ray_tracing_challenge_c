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

Material* DefaultMaterial()
{
    return Material_(Color_(1, 1, 1), 0.1, 0.9, 0.9, 200);
}

Tuple Reflect(Tuple *in, Tuple *normal)
{
    ScalerMultiply(normal, 2 * DotProduct(in, normal));
    Tuple result = Subtract(*in, *normal);
    return result;
}

Color Lighting(Material* material, Light* light, Tuple position, Tuple eyev, Tuple normalv)
{
    // combine the surface color with the light's color/intensity
    Color effective_color = MultiplyColor(material->color, light->intensity);

    // find the direction to the light source
    Tuple lightv = Subtract(light->position, position);
    Normalize(&lightv);

    // compute the ambient contribution
    Color ambient = effective_color;
    ScalarMultiplyColor(&ambient, material->ambient);

    // light_dot_normal represents the cosine of the angle between the light vector and the normal vector.
    // A negative number means the light is on the other side of the surface.
    float light_dot_normal = DotProduct(&lightv, &normalv);
    if (light_dot_normal < 0)
    {
        return ambient;
    }
    else
    {
        // compute the diffuse contribution
        Color diffuse = effective_color;
        ScalarMultiplyColor(&diffuse, material->diffuse * light_dot_normal);

        // reflect_dot_eye represents the cosine of the angle between the reflection vector and the eye vector.
        // A negative number means the light reflects away from the eye.
        Negate(&lightv);
        Tuple reflectv = Reflect(&lightv, &normalv);
        float reflect_dot_eye = DotProduct(&reflectv, &eyev);
        if (reflect_dot_eye <= 0)
        {
            return AddColor(ambient, diffuse);
        }
        else
        {
            // compute the specular contribution
            float factor = pow(reflect_dot_eye, material->shininess);
            Color specular = light->intensity;
            ScalarMultiplyColor(&specular, material->specular * factor);
            return AddColor(AddColor(ambient, diffuse), specular);
        }
    }

    
}

#endif // LIGHT_H
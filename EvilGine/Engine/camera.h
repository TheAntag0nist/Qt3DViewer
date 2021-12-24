#ifndef CAMERA_H
#define CAMERA_H

#include "data.h"

class Camera
{
public:
    Camera();

    void SetPosition(vec3);
    vec3 GetPosition();

    void SetDirection(vec3);
    vec3 GetDirection();

    void Move(vec3);
    void Rotate(ROT type, double angle);

private:
    vec3 position;
    vec3 direction;

};

#endif // CAMERA_H

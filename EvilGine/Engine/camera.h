#ifndef CAMERA_H
#define CAMERA_H

#include "data.h"

class Camera
{
public:
    Camera();
    ~Camera();

    void SetPosition(vec3);
    vec3 GetPosition();

    void SetDirection(vec3);
    vec3 GetDirection();

private:
    vec3 position;
    vec3 direction;

};

#endif // CAMERA_H

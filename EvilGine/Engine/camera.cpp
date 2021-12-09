#include "camera.h"

Camera::Camera(){

}

void Camera::SetPosition(vec3 pos){
    position = pos;
}

vec3 Camera::GetPosition(){
    return position;
}

void Camera::SetDirection(vec3 direct){
    direction = direct;
}

vec3 Camera::GetDirection(){
    return direction;
}

void Camera::Move(vec3 mv){
    position = position + mv;
}

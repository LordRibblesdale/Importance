#include "Camera.h"

Camera::Camera(Float3&  eye, Float3&  lookAt) : eye(std::move(eye)), lootAt(std::move(lookAt)),  up(std::move(Float3(0, 0, 1))) {}

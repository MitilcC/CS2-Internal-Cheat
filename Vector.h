#pragma once

struct Vector3
{
    float x, y, z;

    Vector3 operator+(Vector3 d);
    Vector3 operator-(Vector3 d);
    Vector3 operator*(Vector3 d);
    Vector3 operator*(float d);
};

struct Vector4
{
    float x, y, w, h;

    Vector4 operator+(Vector4 d);
    Vector4 operator-(Vector4 d);
    Vector4 operator*(Vector4 d);
    Vector4 operator*(float d);
};
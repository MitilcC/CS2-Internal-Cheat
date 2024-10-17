#include "Vector.h"

Vector3 Vector3::operator+(Vector3 d)
{
    return { x + d.x, y + d.y, z + d.z };
}

Vector3 Vector3::operator-(Vector3 d)
{
    return { x - d.x, y - d.y, z - d.z };
}

Vector3 Vector3::operator*(Vector3 d)
{
    return { x * d.x, y * d.y, z * d.z };
}

Vector3 Vector3::operator*(float d)
{
    return { x * d, y * d, z * d };
}

Vector4 Vector4::operator+(Vector4 d)
{
    return { x + d.x, y + d.y, w + d.w, h + d.h };
}

Vector4 Vector4::operator-(Vector4 d)
{
    return { x - d.x, y - d.y, w - d.w, h - d.h };
}

Vector4 Vector4::operator*(Vector4 d)
{
    return { x * d.x, y * d.y, w * d.w, h * d.h };
}

Vector4 Vector4::operator*(float d)
{
    return { x * d, y * d, w * d, h * d};
}
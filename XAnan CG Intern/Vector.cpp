#include "Vector.h"

Vector2 Vector2::operator+(Vector2 d)
{
    return { x + d.x, y + d.y};
}

Vector2 Vector2::operator-(Vector2 d)
{
    return { x - d.x, y - d.y};
}

Vector2 Vector2::operator*(Vector2 d)
{
    return { x * d.x, y * d.y};
}

Vector2 Vector2::operator*(float d)
{
    return { x * d, y * d};
}

Vector2 Vector2::operator/(float n)
{
    return { x / n,y / n };
}

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

Vector3  Vector3::operator/(float n)
{
    return { x / n,y / n,z / n };
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

Vector4 Vector4::operator/(float n)
{
    return { x / n,y / n,w / n,h / n };
}

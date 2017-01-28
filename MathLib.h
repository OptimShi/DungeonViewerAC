
#pragma once
#include <math.h>
#include "PackObj.h"

// #define F_EPSILON (0.0002f) 

class Frame;

class Vec2D
{
public:
    inline Vec2D() {
    }

    inline Vec2D(float _x, float _y) {
        x = _x;
        y = _y;
    }

    inline Vec2D& operator+=(const Vec2D& quant) {
        x += quant.x;
        y += quant.y;
        return *this;
    }

    ULONG pack_size();
    ULONG Pack(BYTE** ppData, ULONG iSize);
    BOOL UnPack(BYTE** ppData, ULONG iSize);

    float x, y;
};

class Vector
{
public:
    inline Vector() {
    }

    inline Vector(float _x, float _y, float _z) {
        x = _x;
        y = _y;
        z = _z;
    }


    inline Vector operator*(const float amount) const {
        return Vector(x * amount, y * amount, z * amount);
    }
    inline Vector operator*(const Vector& quant) const {
        return Vector(x * quant.x, y * quant.y, z * quant.z);
    }
    inline Vector& operator*=(const float amount) {
        x *= amount;
        y *= amount;
        z *= amount;
        return *this;
    }
    inline Vector& operator*=(const Vector& quant) {
        x *= quant.x;
        y *= quant.y;
        z *= quant.z;
        return *this;
    }

    inline Vector operator/(const float amount) const {
        return Vector(x / amount, y / amount, z / amount);
    }
    inline Vector& operator/=(const float amount) {
        x /= amount;
        y /= amount;
        z /= amount;
        return *this;
    }
    inline Vector& operator/=(const Vector& quant) {
        x /= quant.x;
        y /= quant.y;
        z /= quant.z;
        return *this;
    }

    inline Vector operator-(const Vector& quant) const {
        return Vector(x - quant.x, y - quant.y, z - quant.z);
    }
    inline Vector& operator-=(const Vector& quant) {
        x -= quant.x;
        y -= quant.y;
        z -= quant.z;
        return *this;
    }

    inline Vector operator+(const Vector& quant) const {
        return Vector(x + quant.x, y + quant.y, z + quant.z);
    }
    inline Vector& operator+=(const Vector& quant) {
        x += quant.x;
        y += quant.y;
        z += quant.z;
        return *this;
    }

    inline operator const float *() const {
        return &x;
    }
    inline operator float *() {
        return &x;
    }

    float magnitude() const {
        return (float)sqrt((x * x) + (y * y) + (z * z));
    }

    inline ULONG pack_size() {
        return(sizeof(float) * 3);
    }
    inline ULONG Pack(BYTE** ppData, ULONG iSize) {
        ULONG PackSize = pack_size();

        if (iSize >= PackSize) {
            PACK(float, x);
            PACK(float, y);
            PACK(float, z);
        }
        return PackSize;
    }
    inline BOOL UnPack(BYTE** ppData, ULONG iSize) {
        if (iSize < pack_size())
            return FALSE;

        UNPACK(float, x);
        UNPACK(float, y);
        UNPACK(float, z);

        return TRUE;
    }

    BOOL IsValid() const;
    float    dot_product(const Vector& v) const;
    Vector& normalize();
    BOOL    normalize_check_small();
    BOOL    is_zero() const;

    float x, y, z;
};

Vector cross_product(const Vector& v1, const Vector& v2);

// Imaginary class, either entirely inlined by Turbine or non-existant.
class Quaternion
{
public:
    inline Quaternion() {
    }

    inline Quaternion(float _w, float _x, float _y, float _z) {
        w = _w;
        x = _x;
        y = _y;
        z = _z;
    }

    // Should probably be renamed. It's not the length of the quaternion!!
    inline float magnitude() const {
        return (float)sqrt((x * x) + (y * y) + (z * z) + (w * w));
    }

    inline ULONG pack_size() {
        return(sizeof(float) * 4);
    }
    inline ULONG Pack(BYTE** ppData, ULONG iSize) {
        // The client performs no size check, but we will.
        ULONG PackSize = pack_size();

        if (iSize >= PackSize) {
            PACK(float, w);
            PACK(float, x);
            PACK(float, y);
            PACK(float, z);
        }
        return PackSize;
    }
    inline BOOL UnPack(BYTE** ppData, ULONG iSize) {
        if (iSize < pack_size())
            return FALSE;

        UNPACK(float, w);
        UNPACK(float, x);
        UNPACK(float, y);
        UNPACK(float, z);

        return TRUE;
    }

    BOOL IsValid() const;
    void normalize();
    float dot_product(const Quaternion& q) const;

    float w, x, y, z;
};

class Ray
{
public:
    Vector m_origin;
    Vector m_direction;
};

class Plane
{
public:
    // Constructors
    Plane();
    Plane(Vector& Vect1, Vector& Vect2);

    // Pack Functions
    ULONG pack_size();
    BOOL UnPack(BYTE** ppData, ULONG iSize);

    // Math Functions
    float dot_product(const Vector& point);
    int which_side(const Vector& point, float near_dist);
    BOOL compute_time_of_intersection(const Ray& ray, float *time);

    Vector m_normal;
    float m_dist;
};




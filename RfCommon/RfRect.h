#pragma once
#include"RfPoint.h"
class RfRect
{
public:

    RfRect();
    RfRect(float x,
        float y,
        float width,
        float height);

    RfRect(const RfPoint& location,
        const RfSize& size);

    RfRect* Clone() const;
    void SetXYWH(float x, float y, float w, float h);
    void SetLTRB(float l, float t, float r, float b);
    void GetLocation(RfPoint* point) const;

    void GetSize(RfSize* size) const;

    void GetBounds(RfRect* rect) const;

    float GetLeft() const;

    float GetTop() const;

    float GetRight() const;

    float GetBottom() const;

    bool IsEmptyArea() const;

    bool Equals(const RfRect& rect) const;

    bool Contains(float x,
        float y) const;

    bool Contains(const RfPoint& pt) const;

    bool Contains(const RfRect& rect) const;

    void Inflate(float dx,
        float dy);

    void Inflate(const RfPoint& point);

    bool Intersect(const RfRect& rect);

    static bool Intersect(RfRect& c,
        const RfRect& a,
        const RfRect& b);


    bool IntersectsWith(const RfRect& rect) const;

    static bool Union(RfRect& c,
        const RfRect& a,
        const RfRect& b);

    void Offset(const RfPoint& point);

    void Offset(float dx,
        float dy);
    void Print(const char* msg);
    void PrintLTRB(const char* msg);

public:

    float x = 0, y = 0, width = 0, height = 0;
};


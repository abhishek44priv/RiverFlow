#pragma once
#include"RfSize.h"
class RfPoint
{
public:
    RfPoint();

    RfPoint(const RfPoint& point);

    RfPoint(const RfSize& size);

    RfPoint(float x,
        float y);
    void Set(float x, float y);

    RfPoint operator+(const RfPoint& point) const
    {
        return RfPoint(x + point.x,
            y + point.y);
    }

    RfPoint operator-(const RfPoint& point) const
    {
        return RfPoint(x - point.x,
            y - point.y);
    }
    void Plus(RfPoint p)
    {
        x += p.x;
        y += p.y;
    }

    bool Equals(const RfPoint& point);

public:

    float x = 0;
    float y = 0;
};


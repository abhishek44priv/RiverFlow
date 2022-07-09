#pragma once
class RfSize
{
public:
    RfSize();

    RfSize(const RfSize& size);

    RfSize(float width,
        float height);

    RfSize operator+(const RfSize& sz) const
    {
        return RfSize(width + sz.width,
            height + sz.height);
    }

    RfSize operator-(const RfSize& sz) const
    {
        return RfSize(width - sz.width,
            height - sz.height);
    }

    bool Equals(const RfSize& sz) const;

    bool Empty() const;

public:

    float width;
    float height;
};


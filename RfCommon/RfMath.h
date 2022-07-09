#pragma once
class RfMath
{
public:
    static float PI;
    static float Rad2Deg;
    static float Deg2Rad;
    static float Sin(float rad);
    static float Cos(float rad);
    static float Tan(float rad);

    static float ASin(float ratio);
    static float ACos(float ratio);
    static float ATan(float ratio);

    static int Abs(int v);
    static float Abs(float v);
    static double Abs(double v);
    static long Abs(long v);
    /*ret small int >=x*/
    static int Ceil(float v);
    /*ret great int <=x*/
    static int Floor(float v);
    /*base e*/
    static float Log(float v);
    /*base 10*/
    static float Log10(float v);
    /*ret remainder*/
    static int Fmod(float divident, float divisor);
    static float SqRoot(float v);
    static float Square(float v);
    static float Power(float base, float exponent);
    /*ret frac part and set intpart*/
    static float ModF(float v, int& intPart);
    /*ret e^exponent*/
    static float Exp(float exponent);

    static int Max(int a, int b);
    static int Min(int a, int b);

    static float Max(float a, float b);
    static float Min(float a, float b);

    static float Normalize(float v, float maxValue);
    //triangle
    static float SqDist(float x, float y);
    static float Distance(float x, float y);
    //interpolate
    static float Clamp(float x, float lowerlimit, float upperlimit);
    static float Smoothstep(float edge0, float edge1, float x);

};


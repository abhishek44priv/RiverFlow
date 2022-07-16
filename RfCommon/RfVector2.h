#pragma once
class RfVector2
{
public:
	float x=0.0f, y=0.0f;
	RfVector2(){}
	RfVector2(float x,float y);
	void Plus(RfVector2 p);
	void Set(float x, float y);
	void Normalize();
	float SquareLength();
	float Length();
	void Rotate(float rad);
	void Scale(float sx, float sy);
	void Translate(float tx, float ty);
	RfVector2 GetNormal();
	static float Dot(RfVector2 a, RfVector2 b);
	//static RfVector2 Cross(RfVector2 a, RfVector2 b);
	static RfVector2 Lerp(RfVector2 a,RfVector2 b,
		float t);
	static float Angle(RfVector2 a, RfVector2 b);
	float Angle(RfVector2 b = {1.0f,0.0f});
	void Zero();
	RfVector2 operator -() const
	{
		RfVector2 v;
		v.Set(-x, -y);
		return v;
	}
	void operator +=(const RfVector2& v)
	{
		x += v.x;
		y += v.y;
	}
	void operator -=(const RfVector2& v)
	{
		x -= v.x;
		y -= v.y;
	}
	void operator *=( float a)
	{
		x *= a;
		y *= a;
	}
	RfVector2 operator + (RfVector2 const& v)
	{
		RfVector2 out;
		out.x =x+ v.x;
		out.y =y+ v.y;
		return out;
	}
	RfVector2 operator - (RfVector2 const& v)
	{
		RfVector2 out;
		out.x =x-v.x;
		out.y = y-v.y;
		return out;
	}
	RfVector2 operator * (float const& c)
	{
		RfVector2 out;
		out.x = x*c;
		out.y = y*c;
		return out;
	}
	RfVector2 operator * (RfVector2 const& v)
	{
		RfVector2 out;
		out.x =x* v.x;
		out.y = y*v.y;
		return out;
	}

};


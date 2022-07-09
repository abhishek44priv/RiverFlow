#pragma once
class RfVector2
{
public:
	float x=0.0f, y=0.0f;
	RfVector2(float x,float y);
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






};


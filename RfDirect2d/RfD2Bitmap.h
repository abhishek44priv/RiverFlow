#pragma once
class RfD2Render;
class RfD2Bitmap
{
public:
	RfD2Bitmap();
	RfD2Bitmap(RfD2Render* render, int w, int h, void* pixels);
	void Create(RfD2Render* render,int w,int h, void*pixels);
	~RfD2Bitmap();
	void* GetNative();
protected:
	void Destroy();
	void* n_native = nullptr;
};


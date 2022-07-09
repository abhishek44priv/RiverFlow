#pragma once
class RfD2Render;
class RfD2Brush
{
public:
	RfD2Brush();
	RfD2Brush(RfD2Render* render);
	~RfD2Brush();
	void* GetNativeBrush();
protected:
	void Destroy();
	struct Info
	{
		void* n_brush=nullptr;
	};
	Info info;
};


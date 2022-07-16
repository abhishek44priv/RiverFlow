#pragma once
class RfImage
{
public:
	int width=0, height=0,channel=0;
	void* pixels = nullptr;
	RfImage();
	~RfImage();
	void Load(std::string path);
	inline bool IsPixels() {
		if (width == 0 || height == 0)
			return false;
		return true;
	};
	void Print(std::string msg);
};


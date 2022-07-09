#pragma once
#include"pch.h"
class RfSTLHelper
{
public:
	template<typename A>
	static int Contains(std::vector<A>& v, A& elem)
	{

		for (size_t i = 0; i < v.size(); i++)
		{

			if (v[i] == elem)
				return i;
		}
		return -1;
	}
	template<typename A>
	static A Remove(std::vector<A>& v, size_t pos)
	{
		auto e = v[pos];
		v.erase(v.begin() + pos);
		return e;
	}
};

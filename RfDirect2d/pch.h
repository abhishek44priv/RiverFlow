// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#include<Windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <d2d1helper.h>
#include <wrl\client.h>
#include<iostream>
using namespace D2D1;
using namespace Microsoft::WRL;
#define _D2ColorF(c) ColorF(c.rgba>>8,(float)c.GetA()/255.f)
template<class T>
inline void SafeRelease(
	T** ppInterfaceToRelease
)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}

#endif //PCH_H

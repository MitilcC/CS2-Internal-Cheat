#pragma once
#include <cmath>
#include <d3d11.h>
#include "Vector.h"

namespace Utils
{
	bool WorldToScreen(Vector3 pWorldPos, Vector3& pScreenPos, float* pMatrixPtr, const FLOAT pWinWidth, const FLOAT pWinHeight);
	bool WorldToScreen2(Vector3 pWorldPos, Vector4& pScreenPos, float* pMatrixPtr, const FLOAT pWinWidth, const FLOAT pWinHeight, int& distance);

}

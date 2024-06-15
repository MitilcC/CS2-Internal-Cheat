#include "Ults.h"


bool Utils::WorldToScreen(Vector3 pWorldPos, Vector3& pScreenPos, float* pMatrixPtr, const FLOAT pWinWidth, const FLOAT pWinHeight)
{
	float matrix2[4][4];

	memcpy(matrix2, pMatrixPtr, 16 * sizeof(float));

	const float mX{ pWinWidth / 2 };
	const float mY{ pWinHeight / 2 };

	const float w{
		matrix2[3][0] * pWorldPos.x +
		matrix2[3][1] * pWorldPos.y +
		matrix2[3][2] * pWorldPos.z +
		matrix2[3][3] };

	if (w < 0.65f) return false;

	const float x{
		matrix2[0][0] * pWorldPos.x +
		matrix2[0][1] * pWorldPos.y +
		matrix2[0][2] * pWorldPos.z +
		matrix2[0][3] };

	const float y{
		matrix2[1][0] * pWorldPos.x +
		matrix2[1][1] * pWorldPos.y +
		matrix2[1][2] * pWorldPos.z +
		matrix2[1][3] };

	pScreenPos.x = (mX + mX * x / w);
	pScreenPos.y = (mY - mY * y / w);
	pScreenPos.z = 0;

	return true;
}

bool Utils::WorldToScreen2(Vector3 pWorldPos, Vector4& pScreenPos, float* pMatrixPtr, const FLOAT pWinWidth, const FLOAT pWinHeight, int& distance)
{
	float matrix2[4][4];

	memcpy(matrix2, pMatrixPtr, 16 * sizeof(float));

	float view = matrix2[2][0] * pWorldPos.x + matrix2[2][1] * pWorldPos.y + matrix2[2][2] * pWorldPos.z + matrix2[2][3] ;

	if (view < 0.01f) return false;

	view = 1 / view;

	float mX = pWinWidth / 2 + (matrix2[0][0] * pWorldPos.x + matrix2[0][1] * pWorldPos.y + matrix2[0][2] * pWorldPos.z + matrix2[0][3]) * view * pWinWidth / 2;

	float mY = pWinHeight / 2 - (matrix2[1][0] * pWorldPos.x + matrix2[1][1] * pWorldPos.y + matrix2[1][2] * (pWorldPos.z + 72) + matrix2[1][3]) * view * pWinHeight / 2;

	float mY2 = pWinHeight / 2 - (matrix2[1][0] * pWorldPos.x + matrix2[1][1] * pWorldPos.y + matrix2[1][2] * (pWorldPos.z - 1.5) + matrix2[1][3]) * view * pWinHeight / 2;

	float mH = mY2 - mY;

	pScreenPos.x = mX - mH / 4;
	pScreenPos.y = mY;
	pScreenPos.h = mH;
	pScreenPos.w = mH / 2;

	return true;
}
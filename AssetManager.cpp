#include "AssetManager.h"

BYTE* AssetManager::ReadFile(const wchar_t* fileName) {
	HANDLE hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD fileSize = GetFileSize(hFile, NULL);
	BYTE* fileData = new BYTE[fileSize];

	DWORD dwDiscard1 = 0;
	(void)::ReadFile(hFile, fileData, fileSize, &dwDiscard1, NULL);

	CloseHandle(hFile);
	return fileData;
}
ID2D1Bitmap* AssetManager::LoadBitmap(const Asset* asset, GameRenderer* gameRenderer) {
	UINT32 width = asset->width;
	UINT32 height = asset->height;
	UINT32 pitch = width * 4; // Also sometimes called stride.

	ID2D1Bitmap* pBitmap = nullptr;
	gameRenderer->GetWindowRenderTarget()->CreateBitmap(
		D2D1::SizeU(width, height),
		asset->buffer,
		pitch,
		D2D1::BitmapProperties(D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)),
		&pBitmap
	);

	return pBitmap;
}
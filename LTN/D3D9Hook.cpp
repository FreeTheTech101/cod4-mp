#include "stdafx.h"

bool g_bD3DInitialized = false;

typedef IDirect3D9*(WINAPI* Direct3DCreate9_t)(UINT);

myIDirect3D9*		g_pIDirect3D9;
Direct3DCreate9_t	g_myDirect3DCreate9;

IDirect3D9* WINAPI My_Direct3DCreate9(UINT SDKVersion)
{
	if (!g_bD3DInitialized)
	{
		char d3d9_dir[MAX_PATH];
		GetSystemDirectoryA(d3d9_dir, sizeof(d3d9_dir));

		strcat(d3d9_dir, "\\d3d9.dll");

		// Check if d3d9.dll exists first
		if (GetFileAttributesA(d3d9_dir) == INVALID_FILE_ATTRIBUTES)
		{
			MessageBoxA(NULL, "LTN-#0000: Unable to load D3D9.DLL. Make sure you have Direct3D9 installed.", "Error", MB_OK | MB_ICONERROR);
			_exit(0xBABE0000);
		}

		HMODULE hD3D9 = LoadLibraryA(d3d9_dir);

		if (!hD3D9)
		{
			MessageBoxA(NULL, "LTN-#0001: Unable to get module handle of D3D9.DLL. Make sure you have Direct3D9 installed correctly.", "Error", MB_OK | MB_ICONERROR);
			_exit(0xBABE0001);
		}

		g_myDirect3DCreate9 = (Direct3DCreate9_t)GetProcAddress(hD3D9, "Direct3DCreate9");

		g_bD3DInitialized = true;
	}

	IDirect3D9* orig_pIDirect3D9 = g_myDirect3DCreate9(SDKVersion);
	g_pIDirect3D9 = new myIDirect3D9(orig_pIDirect3D9);

	return g_pIDirect3D9;
}
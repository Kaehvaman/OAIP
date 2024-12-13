#pragma once

//#include <Windows.h>
//WINUSERAPI
//int
//WINAPI
//MessageBoxW(
//	_In_opt_ HWND hWnd,
//	_In_opt_ LPCWSTR lpText,
//	_In_opt_ LPCWSTR lpCaption,
//	_In_ UINT uType);
#define MB_ICONHAND                 0x00000010L
#define MB_ICONQUESTION             0x00000020L
#define MB_ICONEXCLAMATION          0x00000030L
#define MB_ICONASTERISK             0x00000040L
#define MB_USERICON                 0x00000080L
#define MB_ICONWARNING              MB_ICONEXCLAMATION
#define MB_ICONERROR                MB_ICONHAND
#define MB_ICONINFORMATION          MB_ICONASTERISK
#define MB_ICONSTOP                 MB_ICONHAND
extern __declspec(dllimport) int __stdcall MessageBoxA(void* hWnd, const char* lpText, const char* lpCaption, unsigned int uType);
extern __declspec(dllimport) int __stdcall MessageBoxW(void* hWnd, const wchar_t* lpText, const wchar_t* lpCaption, unsigned int uType);
extern __declspec(dllimport) struct HWND__ * __stdcall GetActiveWindow();
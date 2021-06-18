#pragma once

#ifdef V5_DLL
#define V5_API __declspec(dllexport)
#else
#define V5_API __declspec(dllimport)
#endif

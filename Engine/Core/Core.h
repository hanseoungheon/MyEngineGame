#pragma once
//#define BuildEngineDLL 0
#if BuildEngineDLL
#define Engine_API __declspec(dllexport)

#else
#define Engine_API __declspec(dllimport)
#endif



#pragma once
#include <winnt.h>
#include <minwindef.h>
template<typename out, class type>
inline out method(size_t index, type* self)
{
	return reinterpret_cast<out>((*reinterpret_cast<void***>(self))[index]);
}


template< typename Function > Function GetVFunc(PVOID Base, DWORD Index) // TODO: FIX GOWNOCODE
{
	PDWORD* VTablePointer = (PDWORD*)Base;
	PDWORD VTableFunctionBase = *VTablePointer;
	DWORD dwAddress = VTableFunctionBase[Index];
	return (Function)(dwAddress);
}
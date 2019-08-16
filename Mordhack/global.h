#pragma once
#include <Windows.h>
#include <Psapi.h>
#include "SDK.hpp"

namespace Global {
	SDK::UWorld** ppUWorld;
	SDK::TUObjectArray** pUObjects;
	SDK::ULocalPlayer* pLocalPlayer;
	HMODULE baseAddress;
	MODULEINFO info;
}
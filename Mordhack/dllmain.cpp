#include "pch.h"
#include "global.h"
#include <fstream>

#include "SDK/Mordhau_Basic.hpp"
#include "SDK/Mordhau_Basic.cpp"
#include "SDK/Mordhau_CoreUObject_classes.hpp"
#include "SDK/Mordhau_CoreUObject_functions.cpp"
#include "SDK/Mordhau_Engine_classes.hpp"
#include "SDK/Mordhau_Engine_functions.cpp"
#include "SDK/Mordhau_Mordhau_classes.hpp"
#include "SDK/Mordhau_Mordhau_functions.cpp"

#include "util.h"
#include "hookhelper.cpp"

//snip
//endsnip

auto hh = new ProcessEventHookHelper();

void hkMyPawnProcessEvent(SDK::UObject* obj, class SDK::UFunction* function, void* params)
{
	hh->logDistinct(obj, function);

	hh->getOriginalProcessEvent(obj)(obj, function, params);
}

void hkControllerProcessEvent(SDK::UObject* obj, class SDK::UFunction* function, void* params)
{
	hh->logDistinct(obj, function);

	hh->getOriginalProcessEvent(obj)(obj, function, params);
}

void init()
{
	Global::baseAddress = GetModuleHandle(L"Mordhau-Win64-Shipping.exe");
	GetModuleInformation(GetCurrentProcess(), Global::baseAddress, &Global::info, sizeof(Global::info));

	const auto gnameAddr = Util::FindPattern((PBYTE)Global::baseAddress, Global::info.SizeOfImage, (PBYTE)GNAME_SIG, (char*)GNAME_PAT, 0);
	auto offset = *(uint32_t*)(gnameAddr + 3);
	SDK::FName::GNames = (SDK::TNameEntryArray*)(*(uintptr_t*)(gnameAddr + 7 + offset));

	const auto totalObjectAddr = Util::FindPattern((PBYTE)Global::baseAddress, Global::info.SizeOfImage, (PBYTE)TOTAL_OBJECTS_SIG, (char*)TOTAL_OBJECTS_PAT, 0);
	offset = *(int32_t*)(totalObjectAddr + 3);
	SDK::TUObjectArray::g_total_objects = (uintptr_t)(totalObjectAddr + 7 + offset) - (uintptr_t)GetModuleHandleA(0);

	const auto objectsAddr = Util::FindPattern((PBYTE)Global::baseAddress, Global::info.SizeOfImage, (PBYTE)OBJECTS_SIG, (char*)OBJECTS_PAT, 0);
	offset = *(int32_t*)(objectsAddr + 3);
	SDK::TUObjectArray::g_objects = (uintptr_t)(objectsAddr + 7 + offset) - (uintptr_t)GetModuleHandleA(0);
	Global::pUObjects = reinterpret_cast<SDK::TUObjectArray * *>(objectsAddr + 7 + offset);

	const auto gWorldAddr = Util::FindPattern((PBYTE)Global::baseAddress, Global::info.SizeOfImage, (PBYTE)WORLD_SIG, (char*)WORLD_PAT, 0);
	auto btAddrUWorld = *reinterpret_cast<uint32_t*>(gWorldAddr + 3);
	Global::ppUWorld = reinterpret_cast<SDK::UWorld * *>(gWorldAddr + 7 + btAddrUWorld);
	Global::pLocalPlayer = (*Global::ppUWorld)->OwningGameInstance->LocalPlayers[0];

	//init ProcessEvent hooks
	auto pController = (*Global::ppUWorld)->OwningGameInstance->LocalPlayers[0]->PlayerController;
	hh->Hook(pController, hkControllerProcessEvent);

	auto pCurrentPlayer = (SDK::AMordhauCharacter*)(*Global::ppUWorld)->OwningGameInstance->LocalPlayers[0]->PlayerController->Pawn;

	//this pointer changes, so it needs to be re-hooked every time you spawn
	hh->Hook(pCurrentPlayer, hkMyPawnProcessEvent);

	std::cout << "BaseAddress: " << Global::baseAddress << std::endl;
	std::cout << "GNames: " << SDK::FName::GNames << std::endl;
	std::cout << "UObjects: " << *Global::pUObjects << std::endl;
	std::cout << "UWorld: " << *Global::ppUWorld << std::endl;
	std::cout << "LocalPlayer: " << Global::pLocalPlayer << std::endl;
}

DWORD WINAPI mordHack(HMODULE hModule) {

	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	init();

	while (true) {
		if (GetAsyncKeyState(VK_DELETE) & 1) {
			hh->UnhookAll();
			break;
		}
		Sleep(10);
	}

	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)mordHack, hModule, NULL, NULL);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
		//return TRUE;
	}
	return TRUE;
}

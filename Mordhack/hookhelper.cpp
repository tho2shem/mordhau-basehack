#include "pch.h"
#include <iostream>
#include <windows.h>
#include "SDK.hpp"
#include "vmthook.h"
#include <unordered_map>
#include <fstream>

typedef void (*tProcessEvent)(SDK::UObject*, class SDK::UFunction*, void*);

typedef std::unordered_map<std::string, bool> uniqueStringMap;

typedef struct {
	VMTHook* vmthook;
	tProcessEvent pOrig;
	uniqueStringMap* uniqueNames;
} vmth;

//could be generalized/templated
class ProcessEventHookHelper
{
public:

	std::unordered_map<SDK::UObject*, vmth*> hookMap;

	ProcessEventHookHelper() {
		this->hookMap = {};
	}

	//ayy leaks memory
	~ProcessEventHookHelper() {}

	void Hook(SDK::UObject* obj, void* hookFn) {

		VMTHook* vmthook = new VMTHook(obj);

		vmth* hookInfo = new vmth;
		hookInfo->vmthook = vmthook;
		hookInfo->pOrig = vmthook->GetOriginalFunction<tProcessEvent>(65);
		hookInfo->uniqueNames = new uniqueStringMap();

		vmthook->HookFunction(hookFn, 65);

		this->hookMap[obj] = hookInfo;
	}

	void Unhook(SDK::UObject* obj) {
		this->hookMap[obj]->vmthook->UnhookFunction(65);
	}

	void UnhookAll() {
		std::unordered_map<SDK::UObject*, vmth*>::iterator it = this->hookMap.begin();
		while (it != this->hookMap.end()) {
			it->second->vmthook->UnhookFunction(65);
		}

		this->hookMap = {};
	}

	tProcessEvent getOriginalProcessEvent(SDK::UObject* obj) {
		return this->hookMap[obj]->pOrig;
	}

	void log(SDK::UObject* obj, class SDK::UFunction* function) {
		std::cout << "ProcessEvent: " << obj->GetFullName() << " " << function->GetFullName() << std::endl;
	}

	void logDistinct(SDK::UObject* obj, class SDK::UFunction* function) {
		auto nameMap = this->hookMap[obj]->uniqueNames;
		if (function != nullptr) {
			auto name = function->GetFullName();
			if (nameMap->find(name) == nameMap->end()) {
				(*nameMap)[name] = true;
				std::cout << "ProcessEvent: " << obj->GetFullName() << " " << function->GetFullName() << std::endl;
			}
		}
	}
};
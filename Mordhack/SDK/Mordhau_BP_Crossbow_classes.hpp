#pragma once

// Mordhau (Dumped by Hinnie) SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_Crossbow.BP_Crossbow_C
// 0x0008 (0x0CC0 - 0x0CB8)
class ABP_Crossbow_C : public ABP_MissileEquipment_C
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0CB8(0x0008) (Transient, DuplicateTransient)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_Crossbow.BP_Crossbow_C");
		return ptr;
	}


	void UserConstructionScript();
	void OnLoadedChanged();
	void ReceiveBeginPlay();
	void ExecuteUbergraph_BP_Crossbow(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

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

// BlueprintGeneratedClass BP_CoatOfPlatesChestPlate.BP_CoatOfPlatesChestPlate_C
// 0x0000 (0x0210 - 0x0210)
class UBP_CoatOfPlatesChestPlate_C : public UBP_Tier2UpperChestWearable_C
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_CoatOfPlatesChestPlate.BP_CoatOfPlatesChestPlate_C");
		return ptr;
	}


	void UserConstructionScript();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

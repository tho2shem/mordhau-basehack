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

// BlueprintGeneratedClass BP_LeatherLamellarShoulders.BP_LeatherLamellarShoulders_C
// 0x0000 (0x0198 - 0x0198)
class UBP_LeatherLamellarShoulders_C : public UBP_MordhauWearable_C
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_LeatherLamellarShoulders.BP_LeatherLamellarShoulders_C");
		return ptr;
	}


	void UserConstructionScript();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

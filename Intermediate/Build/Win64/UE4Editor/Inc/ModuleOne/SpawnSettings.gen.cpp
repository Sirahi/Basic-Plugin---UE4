// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ModuleOne/Private/SpawnSettings.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSpawnSettings() {}
// Cross Module References
	MODULEONE_API UClass* Z_Construct_UClass_USpawnSettings_NoRegister();
	MODULEONE_API UClass* Z_Construct_UClass_USpawnSettings();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_ModuleOne();
// End Cross Module References
	void USpawnSettings::StaticRegisterNativesUSpawnSettings()
	{
	}
	UClass* Z_Construct_UClass_USpawnSettings_NoRegister()
	{
		return USpawnSettings::StaticClass();
	}
	struct Z_Construct_UClass_USpawnSettings_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_xValue_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_xValue;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_yValue_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_yValue;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_zValue_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_zValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USpawnSettings_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_ModuleOne,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USpawnSettings_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "SpawnSettings.h" },
		{ "ModuleRelativePath", "Private/SpawnSettings.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USpawnSettings_Statics::NewProp_xValue_MetaData[] = {
		{ "Category", "SpawnSettings" },
		{ "DisplayName", "X" },
		{ "ModuleRelativePath", "Private/SpawnSettings.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpawnSettings_Statics::NewProp_xValue = { "xValue", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(USpawnSettings, xValue), METADATA_PARAMS(Z_Construct_UClass_USpawnSettings_Statics::NewProp_xValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USpawnSettings_Statics::NewProp_xValue_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USpawnSettings_Statics::NewProp_yValue_MetaData[] = {
		{ "Category", "SpawnSettings" },
		{ "DisplayName", "Y" },
		{ "ModuleRelativePath", "Private/SpawnSettings.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpawnSettings_Statics::NewProp_yValue = { "yValue", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(USpawnSettings, yValue), METADATA_PARAMS(Z_Construct_UClass_USpawnSettings_Statics::NewProp_yValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USpawnSettings_Statics::NewProp_yValue_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USpawnSettings_Statics::NewProp_zValue_MetaData[] = {
		{ "Category", "SpawnSettings" },
		{ "DisplayName", "Z" },
		{ "ModuleRelativePath", "Private/SpawnSettings.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpawnSettings_Statics::NewProp_zValue = { "zValue", nullptr, (EPropertyFlags)0x0010000000004001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(USpawnSettings, zValue), METADATA_PARAMS(Z_Construct_UClass_USpawnSettings_Statics::NewProp_zValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USpawnSettings_Statics::NewProp_zValue_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USpawnSettings_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpawnSettings_Statics::NewProp_xValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpawnSettings_Statics::NewProp_yValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpawnSettings_Statics::NewProp_zValue,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_USpawnSettings_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USpawnSettings>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_USpawnSettings_Statics::ClassParams = {
		&USpawnSettings::StaticClass,
		"Editor",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_USpawnSettings_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_USpawnSettings_Statics::PropPointers),
		0,
		0x000000A4u,
		METADATA_PARAMS(Z_Construct_UClass_USpawnSettings_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USpawnSettings_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USpawnSettings()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_USpawnSettings_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USpawnSettings, 2143603037);
	template<> MODULEONE_API UClass* StaticClass<USpawnSettings>()
	{
		return USpawnSettings::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_USpawnSettings(Z_Construct_UClass_USpawnSettings, &USpawnSettings::StaticClass, TEXT("/Script/ModuleOne"), TEXT("USpawnSettings"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USpawnSettings);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif

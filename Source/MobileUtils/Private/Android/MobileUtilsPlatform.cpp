// Mobile Utils Plugin
// Created by Patryk Stepniewski
// Copyright (c) 2014-2017 gameDNA. All Rights Reserved.

#include "MobileUtilsPrivatePCH.h"
#include "MobileUtilsPlatform.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"


jmethodID FMobileUtilsPlatform::CheckInternetConnectionMethod;
jmethodID FMobileUtilsPlatform::CheckGooglePlayServicesMethod;
jmethodID FMobileUtilsPlatform::GetPersistentUniqueDeviceIdMethod;

FMobileUtilsPlatform::FMobileUtilsPlatform()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		CheckInternetConnectionMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_CheckInternetConnection", "()Z", false);
		CheckGooglePlayServicesMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_CheckGooglePlayServices", "()Z", false);
		GetPersistentUniqueDeviceIdMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_GetPersistentUniqueDeviceId", "()Ljava/lang/String;", false);
	}
}

FMobileUtilsPlatform::~FMobileUtilsPlatform()
{
}

bool FMobileUtilsPlatform::CheckInternetConnection()
{
	bool bResult = false;
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		bResult = FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, FMobileUtilsPlatform::CheckInternetConnectionMethod);
	}
	return bResult;
}

bool FMobileUtilsPlatform::CheckGooglePlayServices()
{
	bool bResult = false;
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		bResult = FJavaWrapper::CallBooleanMethod(Env, FJavaWrapper::GameActivityThis, FMobileUtilsPlatform::CheckGooglePlayServicesMethod);
	}
	return bResult;
}

FString FMobileUtilsPlatform::GetPersistentUniqueDeviceId()
{
	FString ResultDeviceId = FString("");
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring ResultDeviceIdString = (jstring)FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, FMobileUtilsPlatform::GetPersistentUniqueDeviceIdMethod);
		const char *nativeDeviceIdString = Env->GetStringUTFChars(ResultDeviceIdString, 0);
		ResultDeviceId = FString(nativeDeviceIdString);
		Env->ReleaseStringUTFChars(ResultDeviceIdString, nativeDeviceIdString);
		Env->DeleteLocalRef(ResultDeviceIdString);
	}
	return ResultDeviceId;
}

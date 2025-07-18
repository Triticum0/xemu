/*
 * Definitions for interacting with the NVAPI library from the NVIDIA NVAPI
 * SDK:
 *
 * SPDX-FileCopyrightText: Copyright (c) 2019-2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#ifndef NVAPI_DEFS_H
#define NVAPI_DEFS_H

// clang-format off

#include <stdint.h>

enum ESetting {
    OGL_THREAD_CONTROL_ID = 0x20C1221E,
};

enum EValues_OGL_THREAD_CONTROL {
    OGL_THREAD_CONTROL_ENABLE                            = 0x00000001,
    OGL_THREAD_CONTROL_DISABLE                           = 0x00000002,
    OGL_THREAD_CONTROL_NUM_VALUES = 2,
    OGL_THREAD_CONTROL_DEFAULT = 0U
};

typedef uint32_t NvU32;
typedef uint16_t NvU16;
typedef uint8_t NvU8;

#define MAKE_NVAPI_VERSION(typeName,ver) (NvU32)(sizeof(typeName) | ((ver)<<16))

#define NV_DECLARE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name

NV_DECLARE_HANDLE(NvDRSSessionHandle);
NV_DECLARE_HANDLE(NvDRSProfileHandle);

#define NVAPI_UNICODE_STRING_MAX                             2048
#define NVAPI_BINARY_DATA_MAX                                4096
typedef NvU16 NvAPI_UnicodeString[NVAPI_UNICODE_STRING_MAX];
typedef char NvAPI_ShortString[64];

#define NVAPI_SETTING_MAX_VALUES                             100

typedef enum _NVDRS_SETTING_TYPE
{
     NVDRS_DWORD_TYPE,
     NVDRS_BINARY_TYPE,
     NVDRS_STRING_TYPE,
     NVDRS_WSTRING_TYPE
} NVDRS_SETTING_TYPE;

typedef enum _NVDRS_SETTING_LOCATION
{
     NVDRS_CURRENT_PROFILE_LOCATION,
     NVDRS_GLOBAL_PROFILE_LOCATION,
     NVDRS_BASE_PROFILE_LOCATION,
     NVDRS_DEFAULT_PROFILE_LOCATION
} NVDRS_SETTING_LOCATION;

typedef struct _NVDRS_GPU_SUPPORT
{
    NvU32 geforce    :  1;
    NvU32 quadro     :  1;
    NvU32 nvs        :  1;
    NvU32 reserved4  :  1;
    NvU32 reserved5  :  1;
    NvU32 reserved6  :  1;
    NvU32 reserved7  :  1;
    NvU32 reserved8  :  1;
    NvU32 reserved9  :  1;
    NvU32 reserved10 :  1;
    NvU32 reserved11 :  1;
    NvU32 reserved12 :  1;
    NvU32 reserved13 :  1;
    NvU32 reserved14 :  1;
    NvU32 reserved15 :  1;
    NvU32 reserved16 :  1;
    NvU32 reserved17 :  1;
    NvU32 reserved18 :  1;
    NvU32 reserved19 :  1;
    NvU32 reserved20 :  1;
    NvU32 reserved21 :  1;
    NvU32 reserved22 :  1;
    NvU32 reserved23 :  1;
    NvU32 reserved24 :  1;
    NvU32 reserved25 :  1;
    NvU32 reserved26 :  1;
    NvU32 reserved27 :  1;
    NvU32 reserved28 :  1;
    NvU32 reserved29 :  1;
    NvU32 reserved30 :  1;
    NvU32 reserved31 :  1;
    NvU32 reserved32 :  1;
} NVDRS_GPU_SUPPORT;

//! Enum to decide on the datatype of setting value.
typedef struct _NVDRS_BINARY_SETTING
{
     NvU32                valueLength;               //!< valueLength should always be in number of bytes.
     NvU8                 valueData[NVAPI_BINARY_DATA_MAX];
} NVDRS_BINARY_SETTING;

typedef struct _NVDRS_SETTING_VALUES
{
     NvU32                      version;                //!< Structure Version
     NvU32                      numSettingValues;       //!< Total number of values available in a setting.
     NVDRS_SETTING_TYPE         settingType;            //!< Type of setting value.
     union                                              //!< Setting can hold either DWORD or Binary value or string. Not mixed types.
     {
         NvU32                      u32DefaultValue;    //!< Accessing default DWORD value of this setting.
         NVDRS_BINARY_SETTING       binaryDefaultValue; //!< Accessing default Binary value of this setting.
                                                        //!< Must be allocated by caller with valueLength specifying buffer size, or only valueLength will be filled in.
         NvAPI_UnicodeString        wszDefaultValue;    //!< Accessing default unicode string value of this setting.
     };
     union                                                //!< Setting values can be of either DWORD, Binary values or String type,
     {                                                    //!< NOT mixed types.
         NvU32                      u32Value;           //!< All possible DWORD values for a setting
         NVDRS_BINARY_SETTING       binaryValue;        //!< All possible Binary values for a setting
         NvAPI_UnicodeString        wszValue;           //!< Accessing current unicode string value of this setting.
     }settingValues[NVAPI_SETTING_MAX_VALUES];
} NVDRS_SETTING_VALUES;

//! Macro for constructing the version field of ::_NVDRS_SETTING_VALUES
#define NVDRS_SETTING_VALUES_VER    MAKE_NVAPI_VERSION(NVDRS_SETTING_VALUES,1)

typedef struct _NVDRS_SETTING_V1
{
     NvU32                      version;                //!< Structure Version
     NvAPI_UnicodeString        settingName;            //!< String name of setting
     NvU32                      settingId;              //!< 32 bit setting Id
     NVDRS_SETTING_TYPE         settingType;            //!< Type of setting value.
     NVDRS_SETTING_LOCATION     settingLocation;        //!< Describes where the value in CurrentValue comes from.
     NvU32                      isCurrentPredefined;    //!< It is different than 0 if the currentValue is a predefined Value,
                                                        //!< 0 if the currentValue is a user value.
     NvU32                      isPredefinedValid;      //!< It is different than 0 if the PredefinedValue union contains a valid value.
     union                                              //!< Setting can hold either DWORD or Binary value or string. Not mixed types.
     {
         NvU32                      u32PredefinedValue;    //!< Accessing default DWORD value of this setting.
         NVDRS_BINARY_SETTING       binaryPredefinedValue; //!< Accessing default Binary value of this setting.
                                                           //!< Must be allocated by caller with valueLength specifying buffer size,
                                                           //!< or only valueLength will be filled in.
         NvAPI_UnicodeString        wszPredefinedValue;    //!< Accessing default unicode string value of this setting.
     };
     union                                              //!< Setting can hold either DWORD or Binary value or string. Not mixed types.
     {
         NvU32                      u32CurrentValue;    //!< Accessing current DWORD value of this setting.
         NVDRS_BINARY_SETTING       binaryCurrentValue; //!< Accessing current Binary value of this setting.
                                                        //!< Must be allocated by caller with valueLength specifying buffer size,
                                                        //!< or only valueLength will be filled in.
         NvAPI_UnicodeString        wszCurrentValue;    //!< Accessing current unicode string value of this setting.
     };
} NVDRS_SETTING_V1;

//! Macro for constructing the version field of ::_NVDRS_SETTING
#define NVDRS_SETTING_VER1        MAKE_NVAPI_VERSION(NVDRS_SETTING_V1, 1)

typedef NVDRS_SETTING_V1          NVDRS_SETTING;
#define NVDRS_SETTING_VER         NVDRS_SETTING_VER1

typedef struct _NVDRS_APPLICATION_V4
{
     NvU32                      version;            //!< Structure Version
     NvU32                      isPredefined;       //!< Is the application userdefined/predefined
     NvAPI_UnicodeString        appName;            //!< String name of the Application
     NvAPI_UnicodeString        userFriendlyName;   //!< UserFriendly name of the Application
     NvAPI_UnicodeString        launcher;           //!< Indicates the name (if any) of the launcher that starts the Application
     NvAPI_UnicodeString        fileInFolder;       //!< Select this application only if this file is found.
                                                    //!< When specifying multiple files, separate them using the ':' character.
     NvU32                      isMetro:1;          //!< Windows 8 style app
     NvU32                      isCommandLine:1;    //!< Command line parsing for the application name
     NvU32                      reserved:30;        //!< Reserved. Should be 0.
     NvAPI_UnicodeString        commandLine;        //!< If isCommandLine is set to 0 this must be an empty. If isCommandLine is set to 1
                                                    //!< this contains application's command line as if it was returned by GetCommandLineW.
} NVDRS_APPLICATION_V4;

#define NVDRS_APPLICATION_VER_V4        MAKE_NVAPI_VERSION(NVDRS_APPLICATION_V4,4)

typedef NVDRS_APPLICATION_V4 NVDRS_APPLICATION;
#define NVDRS_APPLICATION_VER NVDRS_APPLICATION_VER_V4

typedef struct _NVDRS_PROFILE_V1
{
     NvU32                      version;            //!< Structure Version
     NvAPI_UnicodeString        profileName;        //!< String name of the Profile
     NVDRS_GPU_SUPPORT          gpuSupport;         //!< This read-only flag indicates the profile support on either
                                                    //!< Quadro, or Geforce, or both.
     NvU32                      isPredefined;       //!< Is the Profile user-defined, or predefined
     NvU32                      numOfApps;          //!< Total number of applications that belong to this profile. Read-only
     NvU32                      numOfSettings;      //!< Total number of settings applied for this Profile. Read-only
} NVDRS_PROFILE_V1;

typedef NVDRS_PROFILE_V1         NVDRS_PROFILE;

//! Macro for constructing the version field of ::NVDRS_PROFILE
#define NVDRS_PROFILE_VER1       MAKE_NVAPI_VERSION(NVDRS_PROFILE_V1,1)
#define NVDRS_PROFILE_VER        NVDRS_PROFILE_VER1

#define NVAPI_FUNCS_X(FUNC)                        \
    FUNC(NvAPI_DRS_CreateApplication, 0x4347A9DE)  \
    FUNC(NvAPI_DRS_CreateProfile, 0xCC176068)      \
    FUNC(NvAPI_DRS_CreateSession, 0x0694D52E)      \
    FUNC(NvAPI_DRS_DestroySession, 0xDAD9CFF8)     \
    FUNC(NvAPI_DRS_FindProfileByName, 0x7E4A9A0B)  \
    FUNC(NvAPI_DRS_GetApplicationInfo, 0xED1F8C69) \
    FUNC(NvAPI_DRS_LoadSettings, 0x375DBD6B)       \
    FUNC(NvAPI_DRS_SaveSettings, 0xFCBC7E14)       \
    FUNC(NvAPI_DRS_SetSetting, 0x577DD202)         \
    FUNC(NvAPI_Initialize, 0x0150E828)             \
    FUNC(NvAPI_Unload, 0xD22BDD7E)

typedef int(__cdecl *NvAPI_DRS_CreateApplication_t)(NvDRSSessionHandle, NvDRSProfileHandle, NVDRS_APPLICATION *);
typedef int(__cdecl *NvAPI_DRS_CreateProfile_t)(NvDRSSessionHandle, NVDRS_PROFILE *, NvDRSProfileHandle *);
typedef int(__cdecl *NvAPI_DRS_CreateSession_t)(NvDRSSessionHandle *);
typedef int(__cdecl *NvAPI_DRS_DestroySession_t)(NvDRSSessionHandle);
typedef int(__cdecl *NvAPI_DRS_FindProfileByName_t)(NvDRSSessionHandle, NvAPI_UnicodeString, NvDRSProfileHandle *);
typedef int(__cdecl *NvAPI_DRS_GetApplicationInfo_t)(NvDRSSessionHandle, NvDRSProfileHandle, NvAPI_UnicodeString, NVDRS_APPLICATION *);
typedef int(__cdecl *NvAPI_DRS_LoadSettings_t)(NvDRSSessionHandle);
typedef int(__cdecl *NvAPI_DRS_SaveSettings_t)(NvDRSSessionHandle);
typedef int(__cdecl *NvAPI_DRS_SetSetting_t)(NvDRSSessionHandle, NvDRSProfileHandle, NVDRS_SETTING *);
typedef int(__cdecl *NvAPI_Initialize_t)(void);
typedef int(__cdecl *NvAPI_Unload_t)(void);
typedef void *(__cdecl *NvAPI_QueryInterface_t)(unsigned int interface_id);

#endif

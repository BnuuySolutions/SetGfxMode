/*
 * UEFI:SIMPLE - UEFI development made easy
 * Copyright ©️ 2014-2023 Pete Batard <pete@akeo.ie> - Public Domain
 * See COPYING for the full licensing terms.
 */
#include <efi.h>
#include <efilib.h>
#include <libsmbios.h>

EFI_GUID gAppleGraphicsPolicyVariableGuid = { 0xfa4ce28d, 0xb62f, 0x4c99, { 0x9c, 0xc3, 0x68, 0x15, 0x68, 0x6e, 0x30, 0xf9 } };
EFI_GUID gAppleNVRAMVariableGuid = { 0x7c436110, 0xab2a, 0x4bbb, { 0xa8, 0x80, 0xfe, 0x41, 0x99, 0x5c, 0x9f, 0x82 } };

// Application entrypoint (must be set to 'efi_main' for gnu-efi crt0 compatibility)
EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
#if defined(_GNU_EFI)
	InitializeLib(ImageHandle, SystemTable);
#endif

	UINT32 GpuPowerPrefs = 1;
	SystemTable->RuntimeServices->SetVariable(L"gpu-power-prefs",
		&gAppleGraphicsPolicyVariableGuid,
		EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
		sizeof(UINT32),
		&GpuPowerPrefs);

	UINT32 GfxMode = 4;
	SystemTable->RuntimeServices->SetVariable(L"GfxMode",
		&gAppleNVRAMVariableGuid,
		EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
		sizeof(UINT32),
		&GfxMode);

	SystemTable->RuntimeServices->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);

	return EFI_SUCCESS;
}

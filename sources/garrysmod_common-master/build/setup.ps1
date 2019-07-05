# Fail if any unset variable is used
Set-StrictMode -Version Latest

Import-Module "$PSScriptRoot/functions.psm1"

ValidateVariableOrSetDefault "MODULE_NAME" -Default (Split-Path (Split-Path $PSScriptRoot -Parent) -Leaf)
ValidateVariableOrSetDefault "REPOSITORY_DIR" -Default "$PSScriptRoot"
ValidateVariableOrSetDefault "DEPENDENCIES" -Default "$REPOSITORY_DIR/dependencies"
ValidateVariableOrSetDefault "GARRYSMOD_COMMON_REPOSITORY" -Default "https://github.com/danielga/garrysmod_common.git"
ValidateVariableOrSetDefault "GARRYSMOD_COMMON" -Default "$DEPENDENCIES/garrysmod_common"
ValidateVariableOrSetDefault "TARGET_OS" -Default "windows"
ValidateVariableOrSetDefault "COMPILER_PLATFORM" -Default "vs2017"
ValidateVariableOrSetDefault "PREMAKE5_URL" -Default "https://github.com/premake/premake-core/releases/download/v5.0.0-alpha13/premake-5.0.0-alpha13-windows.zip"
ValidateVariableOrSetDefault "PREMAKE5_EXECUTABLE" -Default "premake5.exe"
ValidateVariableOrSetDefault "PREMAKE5" -Default "premake5.exe"
ValidateVariableOrSetDefault "PROJECT_OS" -Default "windows"

if (Test-Path env:SOURCE_SDK) {
    Set-Variable SOURCE_SDK -Value (Get-Item env:SOURCE_SDK).Value -Scope Global -ErrorAction Stop -Confirm:$false
}

CreateDirectoryForcefully $DEPENDENCIES

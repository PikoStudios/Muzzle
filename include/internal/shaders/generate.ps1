rm *.glsl.h

foreach ($File in (Get-ChildItem *.glsl).Name) {
	$data = xxd -i $File
	$full = "#ifndef MUZZLE_CORE_INTERNAL_SHADER_XXD_$($File.Replace(".", "_").ToUpper())_H`n#define MUZZLE_CORE_INTERNAL_SHADER_XXD_$($File.Replace(".", "_").ToUpper())_H`n`n$($data)`n`n#endif // This file was generated on $(Get-Date) using `generate.ps1`. Do not modify!"
	$full | Out-File -FilePath ".\$File.h" -Encoding "utf8"
	Write-Host "Generated $(Get-Location)\$File.h"
}
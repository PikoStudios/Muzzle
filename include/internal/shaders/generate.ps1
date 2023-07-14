foreach ($File in (Get-ChildItem *.glsl).Name) {
	$data = xxd -i $File
	$full = "#ifndef MUZZLE_CORE_INTERNAL_SHADER_XXI_$($File.Replace(".", "_").ToUpper())_H`n#define MUZZLE_CORE_INTERNAL_SHADER_XXI_$($File.Replace(".", "_").ToUpper())_H`n`n$($data)`n`n#endif // This file was generated on $(Get-Date) using xxd. Do not modify!"
	$full | Out-File -FilePath ".\$File.h" -Encoding "utf8"
}
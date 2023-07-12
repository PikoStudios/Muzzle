foreach ($File in (Get-ChildItem *.glsl).Name) {
	xxd -i $File | Out-File -FilePath ".\$File.h" -Encoding "utf8"
	Add-Content -Path ".\$File.h" -Value ("// This File was generated on {0} using xxd. Do not modify!" -f (Get-Date)) -Encoding "utf8"
}
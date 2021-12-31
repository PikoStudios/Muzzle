param($function)
$url="https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/" + $function + ".xhtml"

Start-Process -FilePath $url
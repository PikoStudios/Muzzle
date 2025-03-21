param(
    [string]$JarName
)

if ($JarName -eq $null) {
    $JarName = "muzzlejava.jar"
}

javac dev/pikostudios/muzzle/bridge/*.java
jar cf ($JarName) dev/pikostudios/muzzle/bridge/*.class

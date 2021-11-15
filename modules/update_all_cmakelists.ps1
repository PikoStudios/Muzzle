$base = "..\CMakeLists.txt"
$example_dir = "..\examples"

$examples = "..\examples\blank_window\", "..\examples\circle\", "..\examples\collision\", "..\examples\input\", "..\examples\moveable_square\", "..\examples\pong\", "..\examples\rectangle\", "..\examples\resizing\", "..\examples\sprites\", "..\examples\text\", "..\examples\hex_to_rgb\", "..\examples\playing_audio\"

Remove-Item -Path $example_dir\*\CMakeLists.txt -Verbose

for ($i = 0; $i -lt $examples.Count; $i++) {
    Copy-Item $base $examples[$i] -Verbose
}
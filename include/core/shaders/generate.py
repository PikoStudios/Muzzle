import typing as t
import subprocess
from pathlib import Path
from datetime import datetime
import json

XXD_BINARY: str = "xxd"

HEADER_TEMPLATE: str = """#ifndef MUZZLE_CORE_INTERNAL_SHADERS_GENERATED_{0}_H
#define MUZZLE_CORE_INTERNAL_SHADERS_GENERATED_{0}_H

{1}

#endif // This file was generated on {2} using `generate.py`. Do not modify!
"""

def generate(name: str, vertex: Path, fragment: Path) -> t.Tuple[str, str]:
	if not vertex.is_file():
		print(f"Error, Vertex path {vertex} not file")
		exit(-1)

	elif not fragment.is_file():
		print(f"Error, fragment path {fragment} not file")
		exit(-1)

	
	vertex_code: str = subprocess.run([XXD_BINARY, "-i", str(vertex)], stdout=subprocess.PIPE, text=True).stdout
	fragment_code: str = subprocess.run([XXD_BINARY, "-i", str(fragment)], stdout=subprocess.PIPE, text=True).stdout

	path_trans: t.Dict = str.maketrans({
		".": "_",
		"/": "_",
		"\\": "_"
	})

	vertex_var: str = str(vertex).translate(path_trans)
	fragment_var: str = str(fragment).translate(path_trans)
	
	return (
		vertex_code.replace(vertex_var, f"{name}_vertex_glsl").replace(vertex_var + "_len", f"{name}_vertex_glsl_len"),
		fragment_code.replace(fragment_var, f"{name}_fragment_glsl").replace(fragment_var + "_len", f"{name}_fragment_glsl_len"),
	)

def main() -> None:
	with open("build.json", "r") as fp:
		build_config: t.Dict = json.load(fp)

	shaders: t.List[t.Tuple[str, str]] = []

	# generate code
	for shader in build_config["shaders"]:
		shaders.append(generate(shader["name"], Path(shader["vertex"]), Path(shader["fragment"])))

	# flaten generated code into one string
	flatten_shaders: str = ""
	
	for shader in shaders:
		flatten_shaders += shader[0] + "\n" + shader[1] + "\n\n"

	# generate header
	header: str = HEADER_TEMPLATE.format(
	    build_config["guard_name"],
	    flatten_shaders,
	    datetime.now().strftime("%m/%d/%Y %H:%M:%S")
	)

	# write to file
	filepath: str = str(Path(build_config["filename"]))
	
	with open(filepath, "w") as fp:
		fp.write(header)

	print(f"Generated {filepath}")

if __name__ == "__main__":
	main()

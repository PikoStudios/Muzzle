import typing as t
import subprocess
from pathlib import Path
from datetime import datetime
from threading import Thread
import time
import json
import sys

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

def build() -> None:
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

def watch() -> None:
	with open("build.json", "r") as fp:
		build_config: t.Dict = json.load(fp)

	files: t.List[t.Dict[str, Path | float]] = []

	for shader in build_config["shaders"]:
		files.append({
		     "path": Path(shader["vertex"]),
		     "lastmod": Path(shader["vertex"]).stat().st_mtime
		})
		
		files.append({
		      "path": Path(shader["fragment"]),
		      "lastmod": Path(shader["fragment"]).stat().st_mtime
		})

	running: bool = True

	def worker(index: int) -> None:
		print(f"Watching {files[index]["path"]}")
		
		while running:
			currmod: float = files[index]["path"].stat().st_mtime

			if currmod != files[index]["lastmod"]:
				files[index]["lastmod"] = currmod
				print(f"Detected change in {files[index]['path']}, rebuilding...")
				build()

			time.sleep(1)

	threads: t.List[Thread] = []

	for i in range(len(files)):
		th = Thread(target=worker, daemon=True, args=(i,))
		threads.append(th)
		th.start()


	try:
		while True:
			pass
	except KeyboardInterrupt:
		print("Shutting down watcher threads")
		running = False
		
		for th in threads:
			th.join()

def help() -> None:
	print("Muzzle generate.py - GLSL Shader to C Header script\n\t[nothing] - build header file\n\t--watch/-w - watch files defined in build.json for changes and rebuild on change\n\t[else] - this help screen")

if __name__ == "__main__":
	if len(sys.argv) < 2:
		build()
	elif sys.argv[1] == "--watch" or sys.argv[1] == "-w":
		watch()
	else:
		help()

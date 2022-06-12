import re
import requests

		
languages = {
	"Bash": "https://github.com/tree-sitter/tree-sitter-bash",
	"C": "https://github.com/tree-sitter/tree-sitter-c",
	"C#": "https://github.com/tree-sitter/tree-sitter-c-sharp",
	"C++": "https://github.com/tree-sitter/tree-sitter-cpp",
	"CommonLisp": "https://github.com/theHamsta/tree-sitter-commonlisp",
	"CSS": "https://github.com/tree-sitter/tree-sitter-css",
	"CUDA": "https://github.com/theHamsta/tree-sitter-cuda",
	"DOT": "https://github.com/rydesun/tree-sitter-dot",
	"Elm": "https://github.com/elm-tooling/tree-sitter-elm",
	"EmacsLisp": "https://github.com/Wilfred/tree-sitter-elisp",
	"Eno": "https://github.com/eno-lang/tree-sitter-eno",
	"ERB/EJS": "https://github.com/tree-sitter/tree-sitter-embedded-template",
	"Fennel": "https://github.com/travonted/tree-sitter-fennel",
	"GLSL(OpenGLShadingLanguage)": "https://github.com/theHamsta/tree-sitter-glsl",
	"Go": "https://github.com/tree-sitter/tree-sitter-go",
	"HCL": "https://github.com/MichaHoffmann/tree-sitter-hcl",
	"HTML": "https://github.com/tree-sitter/tree-sitter-html",
	"Java": "https://github.com/tree-sitter/tree-sitter-java",
	"JavaScript": "https://github.com/tree-sitter/tree-sitter-javascript",
	"JSON": "https://github.com/tree-sitter/tree-sitter-json",
	"Lua": "https://github.com/Azganoth/tree-sitter-lua",
	"Make": "https://github.com/alemuller/tree-sitter-make",
	"Markdown": "https://github.com/ikatyang/tree-sitter-markdown",
	"OCaml": "https://github.com/tree-sitter/tree-sitter-ocaml",
	"PHP": "https://github.com/tree-sitter/tree-sitter-php",
	"Python": "https://github.com/tree-sitter/tree-sitter-python",
	"Ruby": "https://github.com/tree-sitter/tree-sitter-ruby",
	"Rust": "https://github.com/tree-sitter/tree-sitter-rust",
	"R": "https://github.com/r-lib/tree-sitter-r",
	"S-expressions": "https://github.com/AbstractMachinesLab/tree-sitter-sexp",
	"SPARQL": "https://github.com/BonaBeavis/tree-sitter-sparql",
	"SystemRDL": "https://github.com/SystemRDL/tree-sitter-systemrdl",
	"Svelte": "https://github.com/Himujjal/tree-sitter-svelte",
	"TOML": "https://github.com/ikatyang/tree-sitter-toml",
	"Turtle": "https://github.com/BonaBeavis/tree-sitter-turtle",
	"TypeScript": "https://github.com/tree-sitter/tree-sitter-typescript",
	"Verilog": "https://github.com/tree-sitter/tree-sitter-verilog",
	"VHDL": "https://github.com/alemuller/tree-sitter-vhdl",
	"Vue": "https://github.com/ikatyang/tree-sitter-vue",
	"YAML": "https://github.com/ikatyang/tree-sitter-yaml",
	"WASM": "https://github.com/wasm-lsp/tree-sitter-wasm",
	"WGSLWebGPUShadingLanguage": "https://github.com/mehmetoguzderin/tree-sitter-wgsl",
}

alt_langauge_names = {
	'cpp': 'C++'
}

for language in languages.keys():
	alt_langauge_names[language.lower()] = language

def get_langaue_parser(lang: str):
	base_url = languages[alt_langauge_names[lang]]
	url = base_url.replace('github.com', 'raw.githubusercontent.com') + '/master/src/parser.c'
	responce = requests.get(url)
	if (responce.status_code != requests.status_codes.codes['ok']):
		raise Exception("Invalid request url")
	return responce.text


def main(lang: str):
	source = get_langaue_parser(lang)

	with open(f'{lang}_parser.c', 'w') as file:
		file.write(source)

	lines = source.split('\n')

	enum_start = lines.index('enum {')
	enum_end = lines.index('};')

	symbols = {}
	symbols['ts_builtin_sym_error'] = -1
	symbols['ts_builtin_sym_end'] = 0
	for line in lines[enum_start+1:enum_end]:
		m = re.search('([a-zA-Z_0-9]+) = (\d+),', line)
		name, value = m.groups()
		symbols[name] = int(value)

	names_start = lines.index('static const char * const ts_symbol_names[] = {')
	names_end = lines[names_start:].index('};')

	with open(f'{lang}.hpp', 'w') as file:
		file.write(f'#pragma once\n\n')
		file.write(f'#include "symbol.hpp"\n')
		file.write(f'#include "tree_sitter/api.h"\n\n')
		file.write(f'extern "C" const TSLanguage *tree_sitter_{lang}(void);\n\n')
		file.write('namespace ts {\n\n')
		file.write('namespace ' + lang + ' {\n\n')
		file.write('const TSLanguage *language(void) {\n')
		file.write(f'\treturn tree_sitter_{lang}();\n')
		file.write('}\n\n')
		
	
		for line in lines[names_start+1:names_start+names_end]:
			m = re.search(r'\[([a-zA-Z_0-9]+)\] = (".*"),', line)
			name, string_value = m.groups()
			file.write(f'constexpr Symbol {name} = Symbol({symbols[name]}, {string_value});\n')

		file.write('\n}\n')
		file.write('\n}\n')

if __name__ == '__main__':
	main('go')
#!/usr/bin/env python3

import re
import requests
import sys
import json
import argparse

		
languages = {
	'Bash': ('tree-sitter', 'tree-sitter-bash'),
	'C': ('tree-sitter', 'tree-sitter-c'),
	'C#': ('tree-sitter', 'tree-sitter-c-sharp'),
	'C++': ('tree-sitter', 'tree-sitter-cpp'),
	'CommonLisp': ('theHamsta', 'tree-sitter-commonlisp'),
	'CSS': ('tree-sitter', 'tree-sitter-css'),
	'CUDA': ('theHamsta', 'tree-sitter-cuda'),
	'DOT': ('rydesun', 'tree-sitter-dot'),
	'Elm': ('elm-tooling', 'tree-sitter-elm'),
	'EmacsLisp': ('Wilfred', 'tree-sitter-elisp'),
	'Eno': ('eno-lang', 'tree-sitter-eno'),
	'ERB/EJS': ('tree-sitter', 'tree-sitter-embedded-template'),
	'Fennel': ('travonted', 'tree-sitter-fennel'),
	'GLSL': ('theHamsta', 'tree-sitter-glsl'),
	'Go': ('tree-sitter', 'tree-sitter-go'),
	'HCL': ('MichaHoffmann', 'tree-sitter-hcl'),
	'HTML': ('tree-sitter', 'tree-sitter-html'),
	'Java': ('tree-sitter', 'tree-sitter-java'),
	'JavaScript': ('tree-sitter', 'tree-sitter-javascript'),
	'JSON': ('tree-sitter', 'tree-sitter-json'),
	'Lua': ('Azganoth', 'tree-sitter-lua'),
	'Make': ('alemuller', 'tree-sitter-make'),
	'Markdown': ('ikatyang', 'tree-sitter-markdown'),
	'OCaml': ('tree-sitter', 'tree-sitter-ocaml'),
	'PHP': ('tree-sitter', 'tree-sitter-php'),
	'Python': ('tree-sitter', 'tree-sitter-python'),
	'Ruby': ('tree-sitter', 'tree-sitter-ruby'),
	'Rust': ('tree-sitter', 'tree-sitter-rust'),
	'R': ('r-lib', 'tree-sitter-r'),
	'S-expressions': ('AbstractMachinesLab', 'tree-sitter-sexp'),
	'SPARQL': ('BonaBeavis', 'tree-sitter-sparql'),
	'SystemRDL': ('SystemRDL', 'tree-sitter-systemrdl'),
	'Svelte': ('Himujjal', 'tree-sitter-svelte'),
	'TOML': ('ikatyang', 'tree-sitter-toml'),
	'Turtle': ('BonaBeavis', 'tree-sitter-turtle'),
	'TypeScript': ('tree-sitter', 'tree-sitter-typescript'),
	'Verilog': ('tree-sitter', 'tree-sitter-verilog'),
	'VHDL': ('alemuller', 'tree-sitter-vhdl'),
	'Vue': ('ikatyang', 'tree-sitter-vue'),
	'YAML': ('ikatyang', 'tree-sitter-yaml'),
	'WASM': ('wasm-lsp', 'tree-sitter-wasm'),
	'WGSL': ('mehmetoguzderin', 'tree-sitter-wgsl'),
}

alt_langauge_names = {
	'cpp': 'C++'
}

for language in languages.keys():
	alt_langauge_names[language.lower()] = language

def get_sources(lang: str):
	owener, reposotry = languages[alt_langauge_names[lang.lower()]]
	url = f'https://api.github.com/repos/{owener}/{reposotry}/contents/src'
	sources = []
	for source in json.loads(requests.get(url).text):
		# if source is a c or cpp source file
		if source['name'].split('.')[-1] in ['c', 'cc', 'cpp', 'c++']:
			sources.append(source['name'])
			with open(lang + '_' + source['name'], 'wb') as file:
				file.write(requests.get(source['download_url']).content)
	return sources


def get_langaue_parser(lang: str):
	base_url = languages[alt_langauge_names[lang]]
	url = base_url.replace('github.com', 'raw.githubusercontent.com') + '/master/src/parser.c'
	responce = requests.get(url)
	if (responce.status_code != requests.status_codes.codes['ok']):
		raise Exception("Invalid request url")
	return responce.text


def install(lang: str):
	
	with open(f'{lang}_parser.c') as file:
		source = file.read()

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
		file.write('inline const TSLanguage *language(void) {\n')
		file.write(f'\treturn tree_sitter_{lang}();\n')
		file.write('}\n\n')
		
	
		for line in lines[names_start+1:names_start+names_end]:
			m = re.search(r'\[([a-zA-Z_0-9]+)\] = (".*"),', line)
			name, string_value = m.groups()
			file.write(f'constexpr Symbol {name} = Symbol({symbols[name]}, {string_value});\n')

		file.write('\n}\n')
		file.write('\n}\n')

if __name__ == '__main__':
	parser = argparse.ArgumentParser(description='Manage tree sitter language packs')

	parser.add_argument('--install', action='store_true')
	parser.add_argument('--list', action='store_true')
	parser.add_argument('languages', nargs='?', type=str, default=[])

	args = parser.parse_args(sys.argv[1:])

	if args.list:
		print(' '.join(languages.keys()))
	elif args.install:
		if isinstance(args.languages, list):
			for language in args.languages:
				install(language)
		else:
			install(args.languages)
	else:
		if isinstance(args.languages, list):
			print('only one language is primmited on this operation')
			exit(1)
		print(' '.join(get_sources(args.languages)))
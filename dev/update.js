"use strict"
const fs = require('fs');
const clapPathPrefix = __dirname + "/clap/include/clap";

let includedFiles = {};

let cppHeader = `
/* Generated code - do not edit by hand.

This includes all the CLAP API typedefs and structs, but:
	* renamed clap_ -> wclap_
	* T * replaced by Pointer<T>
	* function pointers replaced by Function<Return, Args...>

You should be able to include this inside another namespace, as long as Function<> and Pointer<> are defined.  These must be simple wrappers around integers, and have the same size as pointers inside the WASM module.
*/

`;
function addCode(code) {
	code = code.replace(/(\s+|\()clap_/g, "$1wclap_");
	
	// Replace all value pointers with a `Pointer<>` template
	let prevCode;
	do {
		prevCode = code;
		code = code.replace(/(\w[a-zA-Z0-9_\s<>]+?)(\s*)\*/g, "Pointer<$1>$2");
	} while (prevCode != code);
	
	// Replace all function pointers
		code = code.replace(/(\w[a-zA-Z0-9_\s<>]+)\(\s*\*\s*([a-zA-Z0-9_]+)\s*\)\s*\(([^)]*)\)\s*;/g, "Function<$1,$3> $2;");
	
	cppHeader += code + "\n";
}

addDir("");
addDir("/factory");
addDir("/factory/draft");
addDir("/ext");
addDir("/ext/draft");

function addDir(path) {
	let files = fs.readdirSync(clapPathPrefix + path);
	files.forEach(file => {
		if (/\.h$/.test(file)) addFile(`${path}/${file}`);
	});
}

function addFile(path) {
	let code = fs.readFileSync(`${clapPathPrefix}${path}`, 'utf8');
	code = code.replaceAll(/\s*\/\/[^\n]*/g, ''); // remove comments
	code = code.replaceAll(/\s*CLAP_ABI\s+/g, '');
	
	code.replaceAll(/#include\s+("[^"]+")/g, (match, includePath) => {
		includePath = JSON.parse(includePath);
		if (/^private\//.test(includePath)) return;
		addFile(path.replace(/[^\/]*$/, '') + includePath);
	});

	// catch simple typedefs
	code.replaceAll(/typedef\s+([^\{\};]+)\s+([a-zA-Z_][a-zA-Z0-9_]*);/g, (match, typeName, alias) => {
		addCode(match);
	});
	
	// Catch typedef'd structs, which are the main API type
	let parts = code.split('\ntypedef struct ');
	parts.slice(1).forEach((code, sliceIndex) => {
		let name = code.split(/\s/, 1)[0];
		// Extract struct body - it will end with the `_t` name.
		let body = code.substr(name.length).split(name + '_t')[0].trim();

		addCode(`struct ${name} ${body.trim()};`);
	});
}

fs.writeFileSync("../include/wclap/_impl/wclap-generic.hpp", cppHeader);

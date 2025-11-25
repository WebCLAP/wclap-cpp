#pragma once

#include <cstdint>

namespace wclap32 {
	template<class T>
	struct Pointer {
		uint32_t wasmPointer;
	};
	template<class Return, class... Args>
	struct Function {
		uint32_t wasmPointer;
	};

	#include "./_impl/wclap-generic.hpp"
};

namespace wclap64 {
	template<class T>
	struct Pointer {
		uint64_t wasmPointer;
	};
	template<class Return, class... Args>
	struct Function {
		uint64_t wasmPointer;
	};

	#include "./_impl/wclap-generic.hpp"
};

# <b>Y</b>et <b>A</b>nother <b>B</b>rainfuck <b>I</b>mplementation
*Yabi*, unlike its name, is not just a brainfuck interpreter. It also attempts to provide a generic API to generate brainfuck-like language interpreters on compile time.

Currently, ```yabi``` is in alpha version; however it is able to interpret every brainfuck program, stably.

## Usage
After installing yabi, you can just call the brainfuck file as the binary's first argument:
	
	yabi file

Binary version of yabi is a quite simple program. It's essentially as simple as:
``` cpp
#include "yabi.h"

int main(int argc, char* argv[])
{
	yabi::BrainfuckFile file(argv[1],yabi::BrainfuckFile::in); /// Load file in first argument

	yabi::BrainfuckInterpreter<1024> bf(file); /// Create a BrainfuckInterpreter with 1024 byte stack size,
                                               	   /// initialized vy default input and output channels
                                                   /// and a buffer copied from `file`

	return static_cast<int>(bf.interpret()); /// Interpret file and return interpreter's state
}

```

## Installation
Installing ```yabi``` binary and yabi C++ headers is as simple as:

	make
	sudo make install

If you want to clean the source directory from binary file:
	
	make clean
	
You can also uninstall binary and C++ library header files by:

	sudo make uninstall

## API
Nothing about brainfuck is hardcoded in yabi library. Every token is defined as a ```constexpr``` value. Interpreter is generically created as:
``` cpp
namespace yabi
{
	template<Size size>
	using BrainfuckInterpreter = Interpreter<BrainfuckInterpreterStack<size>,
	                                         BrainfuckInterpreterTokens,
	                                         BrainfuckInterpreterBuffer,
	                                         BrainfuckInterpreterVector,
	                                         BrainfuckInterpreterFile,
	                                         BrainfuckInterpreterState,
	                                         decltype(std::cin),
	                                         decltype(std::cout),
	                                         BrainfuckInterpreterPointer,
	                                         BrainfuckInterpreterFlag,
	                                         BrainfuckInterpreterSize>;
}
```

Here, tokens are defined as:
``` cpp
namespace yabi
{
	typedef uint8_t Byte;
	// ...
	typedef Byte BrainfuckInterpreterFundamentalType;
	// ...
	struct BrainfuckInterpreterTokens
	{
		typedef BrainfuckInterpreterFundamentalType type;
		constexpr static const type move_right = '>';
		constexpr static const type move_left = '<';
		constexpr static const type increment = '+';
		constexpr static const type decrement = '-';
		constexpr static const type output = '.';
		constexpr static const type input = ',';
		constexpr static const type while_loop_begin = '[';
		constexpr static const type while_loop_end = ']';
		constexpr static const type stack_debug_symbol = '#';

		constexpr static const Error other_tokens_are_comments = Error::ignored; // Other characters are ignored
	};
}
```

## Supported Brainfuck Dialects
*Yabi* is designed to support some of the brainfuck dialects and some other languages in its library. Currently only `brainfuck` and `Ook!` languages are fully implemented. `Unary` is also partially-implemented. One create an `Ook!` interpreter bu using:

```
yabi::OokInterpreter<STACK_SIZE> ook/*(optional_buffer)*/;
ook(new_buffer);
auto state = ook.interpret(); // interpret current buffer and save state
```

## Other Languages
*Yabi*, unlike its name, is not a project only for brainfuck language. In fact, it is an attempt to generically create interpreters of Turing-complete languages that are based on specific tokens. Currently, brainfuck dialects *Unary* and *Ook!* are partially-implemented (and are under-development). Yabi will also attempt to generate interpreters of languages with more complex syntax, such as DNA sequences. By assigning a function to each (constexpr) token, yabi will try to generate the interpreter of such a language.

## ToDo
Yabi is still in its infancy. It will be working as a compile-time generated interpreter. Thus, not only the definitions of tokens, but also their behaviors will be generically parametric.

## License
Yabi is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Please see LICENSE for GPL version 3 license.


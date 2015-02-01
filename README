# <b>Y</b>et <b>A</b>nother <b>B</b>rainfuck <b>I</b>mplementation
*Yabi*, unlike its name, is not just a brainfuck interpreter. It also attempts to provide a generic API to generate brainfuck-like language interpreters on compile time.

Currently, ```yabi``` is in alpha version; however it is able to interpret every brainfuck file.

## Usage
After installing yabi, you can just call the brainfuck file as the binary's first argument:
	
	yabi file

Binary version of yabi is a quite simple program. It's essentially as simple as:
``` cpp
#include "yabi.h"

int main(int argc, char* argv[])
{
	yabi::BrainfuckFile file(argv[1],yabi::BrainfuckFile::in); // Load file in first argument

	yabi::BrainfuckInterpreter<1024> bf; // Create a BrainfuckInterpreter with 2014 byte stack size

	return static_cast<int>(bf(file)); // Interpret file and return interpreter's state
}

```

## Installation
Installing ```yabi``` binary and yabi C++ headers is as simple as:

	make
	sudo make install

## API
Nothing about brainfuck is hardcoded in yabi library. Every token defined as a ```constexpr``` value. Interpreter is generically created as:
``` cpp
template<Size size>
	using BrainfuckInterpreter = Interpreter<BrainfuckInterpreterStack<size>,
                                             BrainfuckInterpreterTokens,
                                             BrainfuckInterpreterBuffer,
                                             BrainfuckInterpreterVector,
                                             BrainfuckInterpreterFile,
                                             BrainfuckInterpreterState,
                                             BrainfuckInterpreterPointer,
                                             BrainfuckInterpreterFlag,
                                             BrainfuckInterpreterSize>;
```

Here, tokens are defined as:
``` cpp
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
};
```

## ToDo
Yabi is still in its infancy. It will be working as a compile-time generated interpreter. Thus, not only the definitions of tokens, but also their behaviors will be generically parametric.

## License
Yabi is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Please see LICENSE for GPL version 3 license.


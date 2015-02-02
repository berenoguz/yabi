/**
 * File      :  defines.h
 * Author    :  Beren Oguz (berenoguz@gmail.com)
 * Date      :  26 January 2015 (26/01/15)
 * Copyright :  (c) 2015, Beren Oguz (berenoguz.github.io)
 * License   :  This file is part of yabi.
 *
 * 				Yabi is free software: you can redistribute it and/or modify
 * 				it under the terms of the GNU General Public License as published by
 * 				the Free Software Foundation, either version 3 of the License, or
 * 				(at your option) any later version.
 *
 * 				Yabi is distributed in the hope that it will be useful,
 * 				but WITHOUT ANY WARRANTY; without even the implied warranty of
 * 				MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * 				GNU General Public License for more details.
 *
 * 				You should have received a copy of the GNU General Public License
 * 				along with yabi. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef YABI_DEFINES_H
#define YABI_DEFINES_H

#include <iostream>
#include <iterator>
#include <string>
#include <array>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include <sstream>
#include <bitset>
#include <type_traits>
#include <initializer_list>
#include <stack>
#include <stdint.h>

#include "static_if.hpp"
#include "interpreter_traits.hpp"

namespace yabi
{
	/// General Type definitions
	typedef uint8_t Byte;
	typedef bool Bit;
	typedef uint64_t Size;
	typedef int64_t Integer;
	typedef uint64_t Natural;
	typedef double Real;
	typedef intptr_t Pointer;
	typedef bool Flag;
	typedef std::string String;

	typedef std::ifstream File;

	template<typename Type, Size size> using Array = std::array<Type,size>;
	template<typename Type> using Vector = std::vector<Type>;
	template<typename Type> using Stack = std::stack<Type>;

	enum struct Error : Size
	{
	    ignored = 0,
	    parser_warning,
	    lexer_warning,
	    logical_warning,
	    parser_error,
	    lexer_error,
	    logical_error,
	    fatal_error
	};

	/// Brainfuck Interpreter types
	typedef Byte BrainfuckInterpreterFundamentalType;
	template<Size size> using BrainfuckInterpreterStack = Array<BrainfuckInterpreterFundamentalType,size>;
	template<typename Type> using BrainfuckInterpreterContainer = Stack<Type>;
	typedef Pointer BrainfuckInterpreterPointer;
	typedef Flag BrainfuckInterpreterFlag;
	typedef Size BrainfuckInterpreterSize;
	enum class BrainfuckInterpreterState : int
	{
		success = 0,
		failure
	};

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

        constexpr static const Error other_tokens_are_comments = Error::ignored;
	};

    typedef std::ifstream BrainfuckInterpreterFile;
    template<class Type> using BrainfuckInterpreterBuffer = Vector<Type>;
    template<class Type> using BrainfuckInterpreterStream = std::istreambuf_iterator<Type>;
}

#endif // YABI_DEFINES_H

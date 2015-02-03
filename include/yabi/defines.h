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
#include <cstdint>
#include <cstring>

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
	template<std::size_t N> using Bitset = std::bitset<N>;

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
	template<Size size> using BrainfuckInterpreterStack = Array<Byte,size>;
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
	    typedef Byte type;
	    typedef type RepresentativeType;
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

	/// Unary Interpreter types
	constexpr static const Size UnaryBitSize = 4;
	typedef Bitset<UnaryBitSize> UnaryInterpreterFundamentalType;
	template<Size size> using UnaryInterpreterStack = Array<Byte,size>;
	template<typename Type> using UnaryInterpreterContainer = Stack<Type>;
	typedef Pointer UnaryInterpreterPointer;
	typedef Flag UnaryInterpreterFlag;
	typedef Size UnaryInterpreterSize;
	enum class UnaryInterpreterState : int
	{
		success = 0,
		failure
	};

    typedef std::ifstream UnaryInterpreterFile;
    template<class Type> using UnaryInterpreterBuffer = Vector<Type>;
    template<class Type> using UnaryInterpreterStream = std::istreambuf_iterator<Type>;

	struct UnaryInterpreterTokens
	{
	    typedef UnaryInterpreterFundamentalType type;
	    typedef Byte RepresentativeType;
	    constexpr static const Byte move_right = 0;
	    constexpr static const Byte move_left = 1;
	    constexpr static const Byte increment = 2;
        constexpr static const Byte decrement = 3;
	    constexpr static const Byte output = 4;
	    constexpr static const Byte input = 5;
        constexpr static const Byte while_loop_begin = 6;
        constexpr static const Byte while_loop_end = 7;

        constexpr static const Error other_tokens_are_comments = Error::ignored;

        constexpr static const Size bit_size = UnaryBitSize;
	};

	/// Ook Interpreter types
	typedef char* OokInterpreterFundamentalType;
	template<Size size> using OokInterpreterStack = Array<Byte,size>;
	template<typename Type> using OokInterpreterContainer = Stack<Type>;
	typedef Pointer OokInterpreterPointer;
	typedef Flag OokInterpreterFlag;
	typedef Size OokInterpreterSize;
	enum class OokInterpreterState : int
	{
		success = 0,
		failure
	};

    typedef std::ifstream OokInterpreterFile;
    template<class Type> using OokInterpreterBuffer = Vector<typename std::remove_pointer<OokInterpreterFundamentalType>::type>;
    template<class Type> using OokInterpreterStream = std::istreambuf_iterator<Type>;

	struct OokInterpreterTokens
	{
	    typedef OokInterpreterFundamentalType type;
	    typedef typename std::remove_pointer<type>::type RepresentativeType;
	    constexpr static const type move_right = "Ook. Ook?";
	    constexpr static const type move_left = "Ook? Ook.";
	    constexpr static const type increment = "Ook. Ook.";
        constexpr static const type decrement = "Ook! Ook!";
	    constexpr static const type output = "Ook! Ook.";
	    constexpr static const type input = "Ook. Ook!";
        constexpr static const type while_loop_begin = "Ook! Ook?";
        constexpr static const type while_loop_end = "Ook? Ook!";

        constexpr static const Error other_tokens_are_comments = Error::ignored;
	};
}

#include "interpreter_traits.hpp"
#include "instruction_set.hpp"

#endif // YABI_DEFINES_H

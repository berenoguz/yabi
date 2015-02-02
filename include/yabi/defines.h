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

	/// Yabi bitset

	template<Size size>
	struct Bitset : public std::bitset<size>
	{
	    Bitset() noexcept : std::bitset<size>() {}
	    Bitset(unsigned long val) : std::bitset<size>(val) {}
	    template<class CharType, class Traits, class Allocator>
	    explicit Bitset(const std::basic_string<CharType, Traits, Allocator>& str,
                        typename std::basic_string<CharType, Traits, Allocator>::size_type pos = 0,
                        typename std::basic_string<CharType, Traits, Allocator>::size_type n =
                                 std::basic_string<CharType, Traits, Allocator>::npos,
                        CharType zero = CharType('0'),
                        CharType one = CharType('1'))
                        : std::bitset<size>(str, pos, n, zero, one) {}
	    template<class CharType>
	    explicit Bitset(const CharType* str,
                        typename std::basic_string<CharType>::size_type n =
                                 std::basic_string<CharType>::npos,
                        CharType zero = CharType('0'),
                        CharType one = CharType('1'))
                        : std::bitset<size>(str, n, zero, one) {}


	    operator unsigned long () const
	    {
	        return this->to_ulong();
	    }
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
	constexpr static const Size UnaryBitSize = 3;
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
}

#include "interpreter_traits.hpp"
#include "instruction_set.hpp"

#endif // YABI_DEFINES_H

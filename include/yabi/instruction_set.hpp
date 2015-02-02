/**
 * File      :  instruction_set.hpp
 * Author    :  Beren Oguz (berenoguz@gmail.com)
 * Date      :  2 February 2015 (02/02/15)
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

#ifndef YABI_INSTRUCTION_SET_HPP
#define YABI_INSTRUCTION_SET_HPP

namespace yabi
{
    template<class TokensType>
    struct ElementsFromFileToBuffer
    {
        template<class BufferType, class ValueType, class... Any>
        static inline void instruct(BufferType& buffer, const ValueType& value, Any...)
        {
            buffer.push_back(value);
        }
    };

    template<class TokensType>
    struct BitsFromFileToBuffer
    {
        template<class BufferType, class ValueType>
        static inline void instruct(BufferType& buffer, const ValueType& value)
        {
            for(Integer i = 0; (i+TokensType::bit_size) <= 8; i+= TokensType::bit_size)
            {
                typename TokensType::type bitset;
                for(Integer j=0; j < TokensType::bit_size; j++)
                {
                    bitset[j] = std::bitset<sizeof(ValueType)*8>(value)[(i+j)%8];
                }
                buffer.push_back(bitset);
            }
        }
    };

    template<class TokensType>
    struct EmptyInstruction
    {
        template<class... Any>
        static inline void instruct(const Any&...)
        {

        }
    };

    template<class TokensType>
    struct Increment
    {
        template<class IteratorType, class StackType, class PointerType>
        static inline void instruct(const IteratorType& iterator, StackType& stack, const PointerType& pointer)
        {
            if(*iterator == static_cast<typename TokensType::type>(TokensType::increment))
            {
                stack[pointer]++;
            }
        }
    };

    template<class TokensType>
    struct Decrement
    {
        template<class IteratorType, class StackType, class PointerType>
        static inline void instruct(const IteratorType& iterator, StackType& stack, const PointerType& pointer)
        {
            if(*iterator == static_cast<typename TokensType::type>(TokensType::decrement))
            {
                stack[pointer]--;
            }
        }
    };

    template<class TokensType>
    struct MoveRight
    {
        template<class IteratorType, class PointerType>
        static inline void instruct(const IteratorType& iterator, PointerType& pointer)
        {
            if(*iterator == static_cast<typename TokensType::type>(TokensType::move_right))
            {
                pointer++;
            }
        }
    };

    template<class TokensType>
    struct MoveLeft
    {
        template<class IteratorType, class PointerType>
        static inline void instruct(const IteratorType& iterator, PointerType& pointer)
        {
            if(*iterator == static_cast<typename TokensType::type>(TokensType::move_left))
            {
                pointer--;
            }
        }
    };

    template<class TokensType>
    struct Output
    {
        template<class IteratorType, class OutputChannelType, class StackType, class PointerType>
        static inline void instruct(const IteratorType& iterator, OutputChannelType& output, const StackType& stack, const PointerType& pointer)
        {
            if(*iterator == static_cast<typename TokensType::type>(TokensType::output))
            {
                output << stack[pointer];
            }
        }
    };

    template<class TokensType>
    struct Input
    {
        template<class IteratorType, class InputChannelType, class StackType, class PointerType>
        static inline void instruct(const IteratorType& iterator, InputChannelType& input, StackType& stack, const PointerType& pointer)
        {
            if(*iterator == static_cast<typename TokensType::type>(TokensType::input))
            {
                input >> stack[pointer];
            }
        }
    };

    template<class TokensType>
    struct WhileLoopBegin
    {
        template<class IteratorType, class StackType, class PointerType, class ContainerType, class FlagType, class IntegralType>
        static inline void instruct(const IteratorType& iterator, const StackType& stack, const PointerType& pointer, ContainerType& jump_locations, FlagType& locked, IntegralType& lock_count)
        {
            if(*iterator == static_cast<typename TokensType::type>(TokensType::while_loop_begin))
            {
                if(stack[pointer])
                {
                    jump_locations.push(iterator);
                }
                else
                {
                    locked = true;
                    lock_count++;
                }
            }
        }
    };

    template<class TokensType>
    struct WhileLoopEnd
    {
        template<class IteratorType, class StackType, class PointerType, class ContainerType>
        static inline void instruct(IteratorType& iterator, const StackType& stack, const PointerType& pointer, ContainerType& jump_locations)
        {
            if(*iterator == static_cast<typename TokensType::type>(TokensType::while_loop_end))
            {
                if(stack[pointer])
                {
                    iterator = jump_locations.top();
                }
                else
                {
                    jump_locations.pop();
                }
            }
        }
    };

    template<class TokensType>
    struct CheckIfWhileLoopEnd
    {
        template<class IteratorType, class FlagType, class IntegralType>
        static inline void instruct(const IteratorType& iterator, FlagType& locked, IntegralType& lock_count)
        {
            if(*iterator == static_cast<typename TokensType::type>(TokensType::while_loop_end))
            {
                if(--lock_count == 0)
                {
                    locked = false;
                }
            }
        }
    };

    template<class TokensType>
    struct CheckIfWhileLoopBegin
    {
        template<class IteratorType, class IntegralType>
        static inline void instruct(const IteratorType& iterator, IntegralType& lock_count)
        {
            if(*iterator == static_cast<typename TokensType::type>(TokensType::while_loop_begin))
            {
                lock_count++;
            }
        }
    };

    template<class TokensType>
    struct StackDebugSymbol
    {
        template<class IteratorType, class OutputChannelType, class BufferType, class StackType, class PointerType>
        static inline void instruct(const IteratorType& iterator, OutputChannelType& output, const BufferType& buffer, const StackType& stack, const PointerType& pointer)
        {
            if(*iterator == static_cast<typename TokensType::type>(TokensType::stack_debug_symbol))
            {
                output << "Position of code: " << iterator - buffer.begin() << std::endl;
                output << "Pointer: " << pointer << std::endl;
                output << "Value at pointer: " << (int)stack[pointer] << std::endl;
            }
        }
    };
}

#endif // YABI_INSTRUCTION_SET_HPP

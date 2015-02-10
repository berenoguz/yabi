/**
 * File      :  yabi.h
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
#ifndef YABI_H
#define YABI_H

#include "yabi/defines.h"

namespace yabi
{
	template<typename StackType,
             typename TokensType,
			 template<class Type> class BasicBufferType,
			 template<class Type> class ContainerType,
			 typename FileType,
			 typename StateType,
			 typename InputChannelType,
			 typename OutputChannelType,
			 typename PointerType,
			 typename FlagType,
			 typename SizeType,
			 Flag throwable = false>
	class Interpreter
	{
		private:
			typedef typename TokensType::type UnderlyingTypeOfTokensType;
			typedef BasicBufferType<UnderlyingTypeOfTokensType> BufferType;


			StackType stack;
			BufferType buffer;
			InputChannelType& input;
			OutputChannelType& output;

			const StateType process(const BufferType& buffer, InputChannelType& input, OutputChannelType& output)
			{
			    StateType interpreter_state = StateType::success;
				PointerType pointer = 0;
				ContainerType<typename BufferType::const_iterator> jump_locations;
				FlagType while_locked;
				SizeType while_lock_count = 0;
				for(typename BufferType::const_iterator iterator = buffer.begin(); iterator != buffer.end(); ++iterator)
				{
                    if(!while_locked)
                    {
                        std::conditional<has_increment<TokensType>::value,Increment<TokensType>,EmptyInstruction<TokensType>>::type::instruct(iterator,stack,pointer);
                        std::conditional<has_decrement<TokensType>::value,Decrement<TokensType>,EmptyInstruction<TokensType>>::type::instruct(iterator,stack,pointer);
                        std::conditional<has_move_right<TokensType>::value,MoveRight<TokensType>,EmptyInstruction<TokensType>>::type::instruct(iterator,pointer);
                        std::conditional<has_move_left<TokensType>::value,MoveLeft<TokensType>,EmptyInstruction<TokensType>>::type::instruct(iterator,pointer);
                        std::conditional<has_output<TokensType>::value,Output<TokensType>,EmptyInstruction<TokensType>>::type::instruct(iterator,output,stack,pointer);
                        std::conditional<has_input<TokensType>::value,Input<TokensType>,EmptyInstruction<TokensType>>::type::instruct(iterator,input,stack,pointer);
                        std::conditional<has_while_loop_begin<TokensType>::value,WhileLoopBegin<TokensType>,EmptyInstruction<TokensType>>::type::instruct(iterator,stack,pointer,jump_locations,while_locked,while_lock_count);
                        std::conditional<has_while_loop_end<TokensType>::value,WhileLoopEnd<TokensType>,EmptyInstruction<TokensType>>::type::instruct(iterator,stack,pointer,jump_locations);
                        std::conditional<has_stack_debug_symbol<TokensType>::value,StackDebugSymbol<TokensType>,EmptyInstruction<TokensType>>::type::instruct(iterator,output,buffer,stack,pointer);
                    }
                    else if(while_locked)
                    {
                        std::conditional<has_while_loop_end<TokensType>::value,CheckIfWhileLoopEnd<TokensType>,EmptyInstruction<TokensType>>::type::instruct(iterator,while_locked,while_lock_count);
                        std::conditional<has_while_loop_begin<TokensType>::value,CheckIfWhileLoopBegin<TokensType>,EmptyInstruction<TokensType>>::type::instruct(iterator,while_lock_count);
                    }
				}

			 	return interpreter_state;
			}

		public:
			void operator () (const BufferType& buffer)
			{
			    this->buffer = buffer;
			}

			void operator () (FileType& file)
			{
                for(auto& element: stack)
                {
                    element = 0;
                }

				BufferType buffer;
			 	typename TokensType::RepresentativeType value;
			 	file >> std::noskipws;
                while(file >> value)
                {
                    std::conditional<has_bit_size<TokensType>::value,BitsFromFileToBuffer<TokensType>,ElementsFromFileToBuffer<TokensType>>::type::instruct(buffer,value);
                }
			    this->buffer = buffer;
			}

			Interpreter(const BufferType& buffer, InputChannelType& in = std::cin, OutputChannelType& out = std::cout):input(in),output(out)
			{
                this->operator()(buffer);
			}

			Interpreter(FileType& file, InputChannelType& in = std::cin, OutputChannelType& out = std::cout):input(in),output(out)
			{
                this->operator()(file);
			}

			Interpreter(InputChannelType& in = std::cin, OutputChannelType& out = std::cout):input(in),output(out)
			{
                for(auto& element: stack)
                {
                    element = 0;
                }
			}

			const StateType interpret()
			{
				return this->process(this->buffer, this->input, this->output);
			}
	};

    template<Size size>
	using BrainfuckInterpreter = Interpreter<BrainfuckInterpreterStack<size>,
                                             BrainfuckInterpreterTokens,
                                             BrainfuckInterpreterBuffer,
                                             BrainfuckInterpreterContainer ,
                                             BrainfuckInterpreterFile,
                                             BrainfuckInterpreterState,
                                             decltype(std::cin),
                                             decltype(std::cout),
                                             BrainfuckInterpreterPointer,
                                             BrainfuckInterpreterFlag,
                                             BrainfuckInterpreterSize>;

    typedef BrainfuckInterpreterFile BrainfuckFile;

    template<Size size>
	using UnaryInterpreter = Interpreter<UnaryInterpreterStack<size>,
                                         UnaryInterpreterTokens,
                                         UnaryInterpreterBuffer,
                                         UnaryInterpreterContainer,
                                         UnaryInterpreterFile,
                                         UnaryInterpreterState,
                                         decltype(std::cin),
                                         decltype(std::cout),
                                         UnaryInterpreterPointer,
                                         UnaryInterpreterFlag,
                                         UnaryInterpreterSize>;

    template<Size size>
	using OokInterpreter = Interpreter<OokInterpreterStack<size>,
                                         OokInterpreterTokens,
                                         OokInterpreterBuffer,
                                         OokInterpreterContainer,
                                         OokInterpreterFile,
                                         OokInterpreterState,
                                         decltype(std::cin),
                                         decltype(std::cout),
                                         OokInterpreterPointer,
                                         OokInterpreterFlag,
                                         OokInterpreterSize>;

    typedef BrainfuckInterpreterFile BrainfuckFile;
    typedef UnaryInterpreterFile UnaryFile;
    typedef OokInterpreterFile OokFile;
}

#endif // YABI_H

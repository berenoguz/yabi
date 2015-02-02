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
			 typename PointerType,
			 typename FlagType,
			 typename SizeType>
	class Interpreter
	{
		private:
			StackType stack;

			typedef typename TokensType::type UnderlyingTypeOfTokensType;
			typedef BasicBufferType<UnderlyingTypeOfTokensType> BufferType;

			const StateType process(const BufferType& buffer)
			{
				PointerType pointer = 0;
				ContainerType<typename BufferType::const_iterator> jump_locations;
				FlagType locked;
				SizeType lock_count = 0;
				for(typename BufferType::const_iterator iterator = buffer.begin(); iterator != buffer.end(); ++iterator)
				{
					 if(!locked)
					 {
						 switch(*iterator)
						 {
						     if(has_increment<TokensType>::value)
                             {
                                 case static_cast<UnderlyingTypeOfTokensType>(TokensType::increment):
                                 {
                                     stack[pointer]++;
                                     break;
                                 }
                             }
                             if(has_decrement<TokensType>::value)
                             {
                                 case static_cast<UnderlyingTypeOfTokensType>(TokensType::decrement):
                                 {
                                     stack[pointer]--;
                                     break;
                                 }
                             }
                             if(has_move_right<TokensType>::value)
                             {
                                 case static_cast<UnderlyingTypeOfTokensType>(TokensType::move_right):
                                 {
                                     pointer++;
                                     break;
                                 }
                             }
                             if(has_move_left<TokensType>::value)
                             {
                                 case static_cast<UnderlyingTypeOfTokensType>(TokensType::move_left):
                                 {
                                     pointer--;
                                     break;
                                 }
                             }
                             if(has_output<TokensType>::value)
                             {
                                 case static_cast<UnderlyingTypeOfTokensType>(TokensType::output):
                                 {
                                     std::cout << stack[pointer];
                                     break;
                                 }
                             }
                             if(has_input<TokensType>::value)
                             {
                                 case static_cast<UnderlyingTypeOfTokensType>(TokensType::input):
                                 {
                                     std::cin >> stack[pointer];
                                     break;
                                 }
                             }
                             if(has_while_loop_begin<TokensType>::value)
                             {
                                 case static_cast<UnderlyingTypeOfTokensType>(TokensType::while_loop_begin):
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
                                     break;
                                 }
                             }
                             if(has_while_loop_end<TokensType>::value)
                             {
                                 case static_cast<UnderlyingTypeOfTokensType>(TokensType::while_loop_end):
                                 {
                                     if(stack[pointer])
                                     {
                                         iterator = jump_locations.top();
                                     }
                                     else
                                     {
                                         jump_locations.pop();
                                     }
                                     break;
                                 }
                             }
                             if(has_stack_debug_symbol<TokensType>::value)
                             {
                                 case static_cast<UnderlyingTypeOfTokensType>(TokensType::stack_debug_symbol):
                                 {
                                     std::cout << "Position of code: " << iterator - buffer.begin() << std::endl;
                                     std::cout << "Pointer: " << pointer << std::endl;
                                     std::cout << "Value at pointer: " << (int)stack[pointer] << std::endl;
                                     break;
                                 }
                             }
                             default:
                             {
                                 break;
                             }
                         }
                     }
                     else
                     {
                         if(*iterator == static_cast<UnderlyingTypeOfTokensType>(TokensType::while_loop_end))
                         {
                             if(--lock_count == 0)
                             {
                                 locked = false;
                             }
                         }
                         else if(*iterator == static_cast<UnderlyingTypeOfTokensType>(TokensType::while_loop_begin))
                         {
                             lock_count++;
                         }
                     }
                }

			 	return StateType::success;
			}

		public:
			const StateType operator () (const BufferType& buffer)
			{
				return this->process(buffer);
			}

			const StateType operator () (FileType& file)
			{
				BufferType buffer;
			    UnderlyingTypeOfTokensType value;
				while(file >> value)
                {
                    buffer.push_back(value);
                }
				return this->process(buffer);
			}
	};

    template<Size size>
	using BrainfuckInterpreter = Interpreter<BrainfuckInterpreterStack<size>,
                                             BrainfuckInterpreterTokens,
                                             BrainfuckInterpreterBuffer,
                                             BrainfuckInterpreterContainer ,
                                             BrainfuckInterpreterFile,
                                             BrainfuckInterpreterState,
                                             BrainfuckInterpreterPointer,
                                             BrainfuckInterpreterFlag,
                                             BrainfuckInterpreterSize>;

    typedef BrainfuckInterpreterFile BrainfuckFile;
}

#endif // YABI_H

/**
 * File      :  interpreter_traits.hpp
 * Author    :  Beren Oguz (berenoguz@gmail.com)
 * Date      :  28 January 2015 (28/01/15)
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

#ifndef YABI_INTERPRETER_TRAITS_HPP
#define YABI_INTERPRETER_TRAITS_HPP

namespace yabi
{
    template<typename Type>
    struct is_type
    {
        constexpr static bool value = true;
        typedef Type type;
    };

    #define has_(func) \
    template<typename Interpreter> \
    struct has_ ## func \
    { \
        private: \
            template<typename Type> \
            static constexpr auto check(Type*) -> typename std::integral_constant<bool,is_type<decltype(Type:: func )>::value>; \
             \
            template<typename> \
            static constexpr std::false_type check(...); \
             \
            typedef decltype(check<Interpreter>(0)) type; \
             \
        public: \
            static constexpr bool value = type::value; \
    }

    has_(move_right);
    has_(move_left);
    has_(increment);
    has_(decrement);
    has_(output);
    has_(input);
    has_(while_loop_begin);
    has_(while_loop_end);
    has_(stack_debug_symbol);

    has_(bit_size);

    #undef has_
}

#endif // YABI_INTERPRETER_TRAITS_HPP

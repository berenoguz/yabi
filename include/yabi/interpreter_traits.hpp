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

template<class Type>
struct is_type
{
    constexpr static const bool value = true;
};

template<class TokensType>
struct has_move_right
{
    constexpr static const bool value(decltype(TokensType::move_right) a = 0)
    {
        return true;
    }

    constexpr static const bool value()
    {
        return false;
    }
};

#endif // YABI_INTERPRETER_TRAITS_HPP

/**
 * File      :  static_if.hpp
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

#ifndef YABI_STATIC_IF_HPP
#define YABI_STATIC_IF_HPP

template<bool condition>
struct static_if_helper
{

};

template<>
struct static_if_helper<true>
{
    constexpr static_if_helper()
    {

    }

    template<class FunctionType>
    constexpr inline void operator << (FunctionType lambda)
    {
        lambda();
    }
};

template<>
struct static_if_helper<false>
{
    constexpr static_if_helper()
    {

    }

    template<class FunctionType>
    constexpr inline void operator << (FunctionType lambda)
    {

    }
};

#define static_if(condition) static_if_helper<condition>() << [&]

/*
template<bool condition>
struct static_else_bool_helper
{
    constexpr static_else_bool_helper()
    {

    }
};

template<bool condition>
struct static_if_helper
{

};

template<>
struct static_if_helper<true>
{
    struct static_else_helper;

    struct static_else_if_helper
    {
        constexpr static_else_if_helper()
        {

        }

        template<class OtherFunctionType>
        constexpr inline static_else_helper operator << (OtherFunctionType lambda)
        {
            return static_else_helper();
        }
    };

    struct static_else_helper
    {
        constexpr static_else_helper()
        {

        }

        template<class OtherFunctionType>
        constexpr inline static_else_if_helper operator << (OtherFunctionType lambda)
        {
            return static_else_if_helper();
        }

        constexpr inline static_else_helper operator << (static_else_bool_helper<true> else_if)
        {
            return static_else_helper();
        }

        constexpr inline static_else_if_helper operator << (static_else_bool_helper<false> else_if)
        {
            return static_else_if_helper();
        }
    };

    constexpr static_if_helper()
    {

    }

    template<class FunctionType>
    constexpr inline static_else_helper operator << (FunctionType lambda)
    {
        return (lambda(),true?static_else_helper():static_else_helper());
    }
};

template<>
struct static_if_helper<false>
{
    struct static_else_helper;

    struct static_else_if_helper
    {
        constexpr static_else_if_helper()
        {

        }

        template<class OtherFunctionType>
        constexpr inline static_if_helper<true>::static_else_helper operator << (OtherFunctionType lambda)
        {
            return (true?static_if_helper<true>::static_else_helper():static_if_helper<true>::static_else_helper());
        }
    };

    struct static_else_helper
    {
        constexpr static_else_helper()
        {

        }

        template<class OtherFunctionType>
        constexpr inline static_else_if_helper operator << (OtherFunctionType lambda)
        {
            return (lambda(),true?static_else_if_helper():static_else_if_helper());
        }

        constexpr inline static_else_if_helper operator << (static_else_bool_helper<true> else_if)
        {
            return static_else_if_helper();
        }

        constexpr inline static_else_helper operator << (static_else_bool_helper<false> else_if)
        {
            return static_else_helper();
        }
    };

    constexpr static_if_helper()
    {

    }

    template<class FunctionType>
    constexpr inline static_else_helper operator << (FunctionType lambda)
    {
        return static_else_helper();
    }
};
*/


#endif // YABI_STATIC_IF_HPP

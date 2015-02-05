/**
 * File      :  main.cpp
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

#include "yabi.h"

int main(int argc, char* argv[])
{

	yabi::BrainfuckFile file(argv[1],yabi::BrainfuckFile::in); /// Load file in first argument

	yabi::BrainfuckInterpreter<1024> bf(file); /// Create a BrainfuckInterpreter with 1024 byte stack size,
                                               	   /// initialized vy default input and output channels
                                                   /// and a buffer copied from `file`

	return static_cast<int>(bf.interpret()); /// Interpret file and return interpreter's state
}

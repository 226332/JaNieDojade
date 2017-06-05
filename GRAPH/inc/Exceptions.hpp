/*
 * Exceptions.hpp
 *
 *  Created on: Jun 5, 2017
 *      Author: 226332
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GRAPH_INC_EXCEPTIONS_HPP_
#define GRAPH_INC_EXCEPTIONS_HPP_
#include "includes.hpp"
class No_Node_Exception: public std::runtime_error {
  No_Node_Exception(const std::string &m) :
      std::runtime_error("Node: " + m + " Not found!"){
  }

}

#endif /* GRAPH_INC_EXCEPTIONS_HPP_ */

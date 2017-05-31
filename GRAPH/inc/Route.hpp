/*
 * Route.hpp
 *
 *  Created on: May 31, 2017
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

#ifndef GUI_INC_ROUTE_HPP_
#define GUI_INC_ROUTE_HPP_
#include "Includes.hpp"
#include "Vertex.hpp"

class Route {
  std::vector<both<pointer<Vertex>,int>> stations;//station,absolute time
  std::string name;
  char type;
  char var; //variation
public:
  Route(std::string const &n, char const &t, char const &v) :
      name(n), type(t), var(v){
  }

  void addEdge(pointer<Edge> const &s){
    stations.push_back(s);
  }

  char getType(){
    return type;
  }

  char getVariation(){
    return var;
  }

  const std::string &getName(){
    return name;
  }

  const std::vector<both<pointer<Vertex>,int>> &getStations(){
    return stations;
  }

};




#endif /* GUI_INC_ROUTE_HPP_ */

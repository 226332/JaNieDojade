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
  std::vector<std::pair<std::string, int>> stations; //name,absolute time
  std::string name, direction; //name of a line and station is heading to
  char type;
  int var; //variation
public:
  Route(std::string const &n, std::string const &d, char const &t,
      int const &v) :
      name(n), direction(d), type(t), var(v){
  }

  void addStop(const std::string &n, const int &wgt){
    stations.push_back(std::pair<std::string, int>(n, wgt));
  }

  char getType(){
    return type;
  }

  int getVariation(){
    return var;
  }

  const std::string &getName(){
    return name;
  }
  const std::string &getDirection(){
    return direction;
  }

  const std::vector<std::pair<std::string, int>> &getStations(){
    return stations;
  }

};

#endif /* GUI_INC_ROUTE_HPP_ */

/*
 * Node.hpp
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
//just normal bus/tram stop
#ifndef GUI_INC_VERTEX_HPP_
#define GUI_INC_VERTEX_HPP_
#include "Includes.hpp"


class Vertex {
  std::vector<std::pair<std::string, int>> adjacency;
  std::vector<std::string> id;
  std::string name;
  std::pair<double, double> cords;

public:
  Vertex(const std::string &i, const std::string &n, const double &lon,
      const double &lat) :
      id(i), name(n), cords(lon, lat){
  }

  const std::string &getName() const{
    return name;
  }
     
  const std::string &getId() const{
    return id;
  }

  const std::vector<std::pair<std::string, int>> &getNeighbours(){
    return adjacency;
  }

  const std::pair<double, double> &getCords(){
    return cords;
  }

  void addNeighbour(const std::string &n,const int &wgt){
    adjacency.push_back(std::pair<std::string,int>(n,wgt));
  }

  void addID(const std::string &I){
    id.push_back(I);
  }

  bool hasID(const std::string &I){
    return find(id.begin(),id.end(),I)!= id.end();
  }

};

#endif /* GUI_INC_VERTEX_HPP_ */

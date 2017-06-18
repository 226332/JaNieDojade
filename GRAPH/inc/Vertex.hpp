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
  std::map<std::string, int> adjacency;
  std::set<std::string> id;
  std::string name;
  std::pair<double, double> cords; //longitude, latitude

public:
  Vertex(const std::string &i, const std::string &n, const double &lon,
      const double &lat) :
      adjacency { }, id { i }, name(n), cords(lon, lat){
  }

  Vertex(const Vertex &v) :
      adjacency(v.adjacency), id(v.id), name(v.name), cords(v.cords){
  }

  Vertex() :
      id { }, name { }, cords { }{
  }

  const std::string &getName() const{
    return name;
  }

  const std::set<std::string> &getIDs() const{
    return id;
  }

  const std::map<std::string, int> &getNeighbours() const{
    return adjacency;
  }

  const int &getWeight(const std::string &s) const{
    return adjacency.at(s);
  }

  const std::pair<double, double> &getCords() const{
    return cords;
  }

  void addNeighbour(const std::string &n, const int &wgt){
    adjacency[n] = wgt;
  }

  void addID(const std::string &I){
    id.insert(I);
  }

  bool hasID(const std::string &I) const{
    return id.find(I) != id.end();
  }

};

#endif /* GUI_INC_VERTEX_HPP_ */

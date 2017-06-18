/*
 * Igraph.hpp
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

#ifndef GRAPH_INC_IGRAPH_HPP_
#define GRAPH_INC_IGRAPH_HPP_
#include "Includes.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Ipathfinder.hpp"

class Ipathfinder;

class Igraph {
public:
//must add vertex with full ID list or else it will be a mess

  virtual void addVertex(const Vertex &v)=0;

  virtual void addEdge(const Edge &e)=0;

  virtual const Vertex& find_Vertex(const std::string &n) const=0;

  virtual const std::vector<std::string> &findPath(const Ipathfinder &ptf,
      const Vertex &start, const Vertex &finish) const =0; //accept Visitor

  virtual ~Igraph(){
  }
  ;

};
#endif /* GRAPH_INC_IGRAPH_HPP_ */

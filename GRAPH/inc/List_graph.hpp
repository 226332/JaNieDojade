/*
 * List_graph.hpp
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

#ifndef GRAPH_INC_LIST_GRAPH_HPP_
#define GRAPH_INC_LIST_GRAPH_HPP_
#include "Includes.hpp"
#include "Igraph.hpp"
#include "Ipathfinder.hpp"

class List_graph: public Igraph {

  std::map<std::string, Vertex> nodes;

public:

  List_graph() :
      nodes { }{
  }

  void addVertex(const Vertex &v){
    nodes.insert(std::make_pair(v.getName(), v));
  }


  void addEdge(const Edge &e){
    if (nodes.find(e.getSource()) != nodes.end()){
      nodes[e.getSource()].addNeighbour(e.getDestination(), e.getWeight());
    } else{
      throw No_Node_Exception(e.getSource());
    }
  }

  const Vertex& find_Vertex(const std::string &n) const{
    return nodes.at(n);
  }

  const std::map<std::string, Vertex>& getVertexes() const{
    return nodes;
  }

  const std::vector<std::string> findPath(const Ipathfinder &ptf,
      const Vertex &start, const Vertex &finish) const override{
    return std::move(ptf.find_path(start, finish,*this));
  }

  void print_nodes()const{
    for (auto &i:nodes){
      std::cout<<i.first<<std::endl;
    }
  }

  ~List_graph(){
  }
  ;
};

#endif /* GRAPH_INC_LIST_GRAPH_HPP_ */

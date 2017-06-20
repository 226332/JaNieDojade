/*
 * Fascade_graph.hpp
 *
 *  Created on: Jun 19, 2017
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

#ifndef GRAPH_INC_FASCADE_GRAPH_HPP_
#define GRAPH_INC_FASCADE_GRAPH_HPP_
#include "Includes.hpp"
#include "List_graph.hpp"
#include "Route_matcher.hpp"
#include "Astar.hpp"
//if using fascade, remember to catch exceptions!
class Fascade_graph {
  List_graph graph;
  Route_matcher router;
  Astar pathfinder;
public:

  void add_stations(std::map<std::string, Vertex> &&s){
    graph.addVertexes(std::move(s));
  }

  const Vertex &find_station(const std::string &s){
    return graph.find_Vertex(s);
  }

  void add_routes(std::vector<Route> &&r){
    router.add_Routes(std::move(r));
  }

  std::vector<Route> get_to(const std::string &start, const std::string &finish){
    return router.match_route(
        graph.findPath(pathfinder, graph.find_Vertex(start),
            graph.find_Vertex(finish)));

  }

};

#endif /* GRAPH_INC_FASCADE_GRAPH_HPP_ */

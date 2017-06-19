/*
 * Route_finder.hpp
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

#ifndef GRAPH_INC_ROUTE_MATCHER_HPP_
#define GRAPH_INC_ROUTE_MATCHER_HPP_
#include "Includes.hpp"
#include "Route.hpp"

class Route_matcher {
  std::vector<Route> routes;

public:
  Route_matcher(){
  }
  ;

  void add_Route(Route &&r){ //must add fully filled route!!!!
    routes.push_back(r);
  }

  void add_Routes(std::vector<Route> &&r){ //must add fully filled route!!!!
    routes.insert(routes.end(), r.begin(), r.end());
  }

  const std::vector<Route> &getRoutes() const{
    return routes;
  }

  std::vector<Route> match_route(const std::vector<std::string>& path){
    std::vector<Route> result { };
    auto current_station = path.begin();
    for (auto i=routes.begin();i<routes.end();i++){
      for(auto j=i->getStations().begin();j<i->getStations().end();j++){
        if(j->first==*current_station){
          Route route(i->getName(),i->getDirection(),i->getType(),i->getVariation());
          while(j->first==*current_station){
            route.addStop(j->first,j->second);
            j++;
            current_station++;
          }
          result.push_back(route);
          break;
        }
      }
      if(current_station==path.end()){
        break;
      }
    }
    return result;
  }

  ~Route_matcher(){
  }
  ;

};

#endif /* GRAPH_INC_ROUTE_MATCHER_HPP_ */

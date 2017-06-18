/*
 * Astar.cpp
 *
 *  Created on: Jun 16, 2017
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
#include "../inc/Astar.hpp"

int Astar::h_cost(const Vertex &start, const Vertex &finish){

  double lat1 = (PI / 180) * start.getCords().second;
  double lat2 = (PI / 180) * finish.getCords().second;
  double lon1 = (PI / 180) * start.getCords().first;
  double lon2 = (PI / 180) * finish.getCords().first;

  double delta_Lat = std::abs(lat1 - lat2);
  double delta_Lon = std::abs(lon1 - lon2);

  double a = (sin(delta_Lat / 2) * sin(delta_Lat / 2))
      + (cos(lat1) * cos(lat2) * sin(delta_Lon / 2) * sin(delta_Lon / 2));

  double c = 2 * atan2(sqrt(a), sqrt(1 - a));

  return (int) round(R * c / (AVG_TRAM_SPEED * KPH_TO_MPM));
}

std::vector<std::string> Astar::find_path(const Vertex &start,
    const Vertex &finish, const Igraph &graph) const{

  std::set<std::string> closed_Set { };
  std::set<std::string> open_Set { start.getName() };

  std::map<std::string, const Vertex*> came_From { };

  std::map<std::string, int> g_Score { };
  std::map<std::string, int> f_Score { };

  for (auto&i : graph.getVertexes()){
    g_Score[i.first] = INT_MAX;
    f_Score[i.first] = INT_MAX;
  }

  g_Score[start.getName()] = 0;
  f_Score[start.getName()] = h_cost(start, finish);
  const Vertex *current { };
  while (!open_Set.empty()){

    int minscore = INT_MAX;
    for (auto& i : open_Set){
      if (minscore > f_Score.at(i)){
        minscore = f_Score.at(i);
        current = &graph.find_Vertex(i);
      }
    }
    if (current == &finish){
      return reconstruct_path(came_From, current);
    }
    open_Set.erase(current->getName());
    closed_Set.insert(current->getName());

    for (auto &i : current->getNeighbours()){
      if (closed_Set.count(i.first)){
        continue;
      } else{
        open_Set.insert(i.first);
      }

      int tentative_g_Score = g_Score.at(current->getName())
          + current->getWeight(i.first);

      if (tentative_g_Score >= g_Score.at(i.first)){
        continue;
      }

      came_From[i.first] = current;
      g_Score.at(i.first) = tentative_g_Score;
      f_Score.at(i.first) = g_Score.at(i.first)
          + h_cost(graph.find_Vertex(i.first), finish);


    }
  }
  throw No_Route_Found_Exception(start.getName(), finish.getName());
}

std::vector<std::string> Astar::reconstruct_path(
    std::map<std::string, const Vertex*> &cf, const Vertex *curr) const{
  std::list<std::string> total_path { curr->getName() };
  while (cf.count(curr->getName())){
    curr = cf[curr->getName()];
    total_path.push_front(curr->getName());
  }

  return std::vector<std::string>(total_path.begin(),total_path.end());
}


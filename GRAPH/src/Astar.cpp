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

std::vector<std::string> &Astar::find_path(const Vertex &start,
    const Vertex &finish){

  std::set<&Vertex> closed_Set { };
  std::set<&Vertex> open_Set { start };
  std::map<&std::string, int> came_From { };

  std::map<&std::string, int> g_Score { { start.getName(), 0 } };
  std::map<&std::string, int> f_Score {
      { start.getName(), h_cost(start, finish) } };

  while (!open_Set.empty()){
    Vertex *current { };
    int minscore = INT_MAX;
    for (auto& i : open_Set){
      if (minscore > f_score(i.getName())){
        minscore = f_score(i.getName());
        current = i;
      }
    }
    if (current == finish){
      return reconstruct_path(came_From, current);
    }
    open_Set.erase(current);
    closed_Set.insert(current);

    for (auto &i : current->getNeighbours()){
      if (closed_Set.find(i)){
        continue;
      } else{
        open_Set.insert(i);
      }

      auto tentative_g_Score = g_Score[current]
          + std::find(current->getNeighbours().begin(),
              current->getNeighbours().end(), i)->second;
      if (tentative_g_Score >= g_Score[i.first]){
        continue;
      }
      came_From[i.first] = *current;
      g_Score[i.first] = tentative_g_Score;
      f_Score[i.first] = g_Score[i.first]
          + h_cost(open_Set().find(i.first), finish);
    }

    throw No_Route_Found_Exception(start.getName, finish.getName());

  }

}

std::vector<std::string> reconstruct_path(const std::map<&std::string, int> &cf,
    Vertex *curr){
  std::vector<std::string> total_path { curr };
  while (cf.count(curr->getName())){
    curr = cf[curr->getName()];
    total_path.push_back(curr->getName());
  }
  return total_path;
}

int Astar::h_cost(const Vertex &start, const Vertex &finish){

  double lat1 = (PI / 180) * start.getCords().second;
  double lat2 = (PI / 180) * finish.getCords().second;
  double lon1 = (PI / 180) * start.getCords().first;
  double lon2 = (PI / 180) * finish.getCords().first;

  double delta_Lat = abs(lat1 - lat2);
  double delta_Lon = abs(lon1 - lon2);

  double a = (sin(delta_Lat / 2) * sin(delta_Lat / 2))
      + (cos(lat1) * cos(lat2) * sin(delta_Lon / 2) * sin(delta_Lon / 2));
  double c = 2 * atan2(sqrt(a), sqrt(1 - a));

  return round(R * c / (AVG_TRAM_SPEED * KMH_TO_MPM));
}


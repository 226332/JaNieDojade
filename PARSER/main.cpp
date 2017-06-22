#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include "../GRAPH/inc/Includes.hpp"
#include "../GRAPH/inc/Vertex.hpp"
#include "../GRAPH/inc/Route.hpp"
#include "../GRAPH/inc/Fascade_graph.hpp"
using namespace std;
int main(){

  ifstream vertexfile("../Datafiles/GTFS/stops.txt", ifstream::in);
  ifstream timefile("../Datafiles/GTFS/stop_times.txt", ifstream::in);
  ifstream routefile("../Datafiles/GTFS/trips.txt", ifstream::in);

  map<string, string> stations; //id, name of vertex
  map<string, Vertex> vertexes; //name, vertex
  map<string, Route> routes; // id, route

  string line;
  getline(vertexfile, line);
  //getline(timefile, line);
  //getline(routefile, line);

  while (getline(vertexfile, line)){
    std::istringstream ss(line);
    string var;
    string ID;
    string name;
    double lat;
    double lon;

    getline(ss, var, ',');
    ID = var;
    getline(ss, var, ',');
    getline(ss, var, ',');
    name = var;
    getline(ss, var, ',');
    lat = atof(var.c_str());
    getline(ss, var, ',');
    lon = atof(var.c_str());

    Vertex tmp(ID, name, lon, lat);

    stations[ID] = name;
    vertexes[name] = tmp;
  }

  while (getline(routefile, line)){
    std::istringstream ss(line);
    string var;
    string name;
    string ID;
    string dir;
    char type;

    getline(ss, var, ',');
    name = var;
    getline(ss, var, ',');
    getline(ss, var, ',');
    ID = var;
    getline(ss, var, ',');
    dir = var;
    getline(ss, var, ',');
    getline(ss, var, ',');
    getline(ss, var, ',');
    if (var == "12" || var == "28" || var == "34" || var == "36"){
      type = TRAM;
    } else{
      type = BUS;
    }
    getline(ss, var, ',');

    Route tmp(name, dir, type, var);
    routes.insert(pair<string, Route>(ID, tmp));
  }
  string previous_route_id = "";
  string previous_stop_id = "";
  time_t base_time { };
  time_t previous_time { };

  while (getline(timefile, line)){
    std::istringstream ss(line);
    struct std::tm tm;
    string var;
    string route_id;
    string stop_id;
    string dir;

    getline(ss, var, ',');
    route_id = var;
    getline(ss, var, ',');
    getline(ss, var, ',');
    std::istringstream sss(var);
    sss >> std::get_time(&tm, "%H:%M:%S");
    std::time_t time = mktime(&tm);
    getline(ss, var, ',');
    stop_id = var;

    if (previous_route_id != route_id){
      base_time = time;
      previous_time = time;
      previous_route_id = "";
    }

    if (previous_route_id != ""){
      vertexes.at(stations.at(previous_stop_id)).addNeighbour(
          stations.at(stop_id), (int) difftime(time, previous_time) / 60);
    }

    routes.at(route_id).addStop(stations[stop_id],
        (int) difftime(time, base_time) / 60);

    previous_route_id = route_id;
    previous_time = time;
    previous_stop_id = stop_id;
  }

  Fascade_graph fg;
  vector<Route> vec;
  fg.add_stations(std::move(vertexes));
  for (auto&i : routes){
    vec.push_back(i.second);
  }
  fg.add_routes(std::move(vec));

  for (auto&i : fg.get_to("\"PL. GRUNWALDZKI\"", "\"DŁUGA (Politechnika)\"")){
    cout << "Linia: " << i.getName() << "Kierunek: " << i.getDirection()
        << "typ:" << i.getType() << endl;
    for(auto &j:i.getStations()){
      cout<<"przystanek: "<<j.first<<"Czas: "<<j.second<<endl;
    }
  }

  return 0;
}

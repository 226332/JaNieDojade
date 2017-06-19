/*
 * Tests.cpp
 *
 *  Created on: Jun 6, 2017
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
// THIS FILE REQUIRES BOOST TO WORK CORRECTLY!
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE MyTest
#if !defined( WIN32 )
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

#include "../inc/List_graph.hpp"
#include "../inc/Astar.hpp"
#include "../inc/Fascade_graph.hpp"

namespace {
struct Fixture {
  List_graph g;
};

BOOST_FIXTURE_TEST_SUITE(GraphTests,Fixture)

BOOST_AUTO_TEST_CASE(Are_basic_things_working){
  Vertex test("69789", "testowy", 57.4, 67.5);
  g.addVertex(test);
  BOOST_REQUIRE_EQUAL(g.find_Vertex(test.getName()).getName(), "testowy");
  BOOST_REQUIRE_EQUAL(g.find_Vertex(test.getName()).getCords().first, 57.4);
  BOOST_REQUIRE_EQUAL(g.find_Vertex(test.getName()).getCords().second, 67.5);

  test.addID("335462");
  List_graph k;
  k.addVertex(test);
  std::set<std::string> IDtest { "69789", "335462" };
  auto start = k.find_Vertex(test.getName()).getIDs().begin();
  BOOST_REQUIRE_EQUAL(
      std::equal(IDtest.begin(), IDtest.end(), start,
          [](const std::string &a, const std::string &b)->bool{return a==b;}),
      true);
}

BOOST_AUTO_TEST_CASE(Can_calculate_weight){
  Vertex test("69789", "testowy", 57.4, 67.5);
  Vertex test2("63455", "testowy2", 50, 61.5);
  int result = Astar::h_cost(test, test2);
  BOOST_REQUIRE_EQUAL(result, round(754200 / (AVG_TRAM_SPEED * KPH_TO_MPM)));
}

BOOST_AUTO_TEST_CASE(Can_find_a_path){
  Vertex test("0000", "testowy", 0, 0);
  Vertex test1("1111", "testowy1", 1, 1);
  Vertex test2("2222", "testowy2", 2, 2);
  Vertex test3("3333", "testowy3", 3, 3);
  Vertex test4("4444", "testowy4", 4, 4);
  Vertex test5("5555", "testowy5", 5, 5);

  test.addNeighbour("testowy1", 1);
  test1.addNeighbour("testowy2", 1);
  test2.addNeighbour("testowy3", 1);
  test3.addNeighbour("testowy4", 1);
  test4.addNeighbour("testowy5", 1);

  g.addVertex(test);
  g.addVertex(test1);
  g.addVertex(test2);
  g.addVertex(test3);
  g.addVertex(test4);
  g.addVertex(test5);

  Astar astor { };
  auto tested = g.findPath(astor, g.find_Vertex("testowy3"),
      g.find_Vertex("testowy5"));
  decltype(tested) target { "testowy3", "testowy4", "testowy5" };

  bool result = std::equal(tested.begin(), tested.end(), target.begin());

  BOOST_REQUIRE_EQUAL(result, true);
}

BOOST_AUTO_TEST_CASE(does_fascade_work){
  std::map<std::string, Vertex> stations { };
  std::vector<Route> routes { };
  for (int i = 0; i < 200; i++){
    Vertex station(std::to_string(i), "testowy" + std::to_string(i), i, i);
    station.addNeighbour("testowy" + std::to_string(i + 1), 1);
    stations["testowy" + std::to_string(i)] = station;
  }
  for (int i = 0; i < 3; i++){
    Route route("testowa"+std::to_string(i),"dokads", TRAM, i);
    for (int j = i*66; j < 66*i+67; j++){
      route.addStop("testowy" + std::to_string(j),1);
    }

    routes.push_back(std::move(route));
  }


  Fascade_graph fg;
  fg.add_routes(std::move(routes));
  fg.add_stations(std::move(stations));
  auto result = fg.get_to("testowy1", "testowy150");

  for (auto&i : result){
    std::cout <<"-----Linia: "<< i.getName() <<" Kierunek: "<< i.getDirection()<<" ---------"<< std::endl;
    for (auto&j : i.getStations())
      std::cout << j.first << std::endl;
  }

}

BOOST_AUTO_TEST_SUITE_END()}


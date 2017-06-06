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
#if !defined( WIN32 )
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include "../inc/List_graph.hpp"

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

BOOST_AUTO_TEST_SUITE_END()}


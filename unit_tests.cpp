#define CATCH_CONFIG_MAIN

#include "catch.hpp" 

#include <iostream>
#include <vector>

#include <time.h>
#include <cstdlib>
#include <algorithm>

#include "image.hpp"

#include "edge.hpp"
#include "point.hpp"

#include "grid.hpp"
#include "disjoint_sets.hpp"

#include "maze.hpp"

#include "maze_generator.hpp"

#define CONTAINS(v, e) (std::find(v.begin(), v.end(), e) != v.end())

TEST_CASE("Edge, Sorting Test", "Edge") {
    
    srand(time(NULL));

    std::vector<Edge> edges;
    for (int i = 0; i < 25; i++) {
        edges.push_back(Edge((size_t)(rand() % 30)));
    }

    std::sort(edges.begin(), edges.end());
    for (int i = 1; i < 25; i++) {
        bool is_less_than = edges[i - 1] < edges[i];
        bool is_equal_to = edges[i - 1] == edges[i];
        bool is_monotonic = is_less_than or is_equal_to;
        REQUIRE(is_monotonic);
    }


}

TEST_CASE("Grid, Default Construction", "[Grid]") {
    
    Grid grid;
    std::vector<Point> neighbors;

    // top left
    neighbors = grid.get_neighbors_of(0, 0);
    REQUIRE(CONTAINS(neighbors, Point(0, 1)));
    REQUIRE(CONTAINS(neighbors, Point(1, 0)));

    // top right
    neighbors = grid.get_neighbors_of(9, 0);
    REQUIRE(CONTAINS(neighbors, Point(8, 0)));
    REQUIRE(CONTAINS(neighbors, Point(9, 1)));

    // bottom left
    neighbors = grid.get_neighbors_of(0, 9);
    REQUIRE(CONTAINS(neighbors, Point(1, 9)));
    REQUIRE(CONTAINS(neighbors, Point(0, 8)));
    
    // bottom right
    neighbors = grid.get_neighbors_of(9, 9);
    REQUIRE(CONTAINS(neighbors, Point(8, 9)));
    REQUIRE(CONTAINS(neighbors, Point(9, 8)));

    neighbors = grid.get_neighbors_of(5, 5);
    REQUIRE(CONTAINS(neighbors, Point(4, 5)));
    REQUIRE(CONTAINS(neighbors, Point(6, 5)));
    REQUIRE(CONTAINS(neighbors, Point(5, 4)));
    REQUIRE(CONTAINS(neighbors, Point(5, 6)));
    
    uint32_t rand_x = (uint32_t)(1 + (rand() % 8));
    uint32_t rand_y = (uint32_t)(1 + (rand() % 8));

    neighbors = grid.get_neighbors_of(rand_x, rand_y);
    REQUIRE(CONTAINS(neighbors, Point(rand_x - 1, rand_y    )));
    REQUIRE(CONTAINS(neighbors, Point(rand_x + 1, rand_y    )));
    REQUIRE(CONTAINS(neighbors, Point(rand_x    , rand_y - 1)));
    REQUIRE(CONTAINS(neighbors, Point(rand_x    , rand_y + 1)));

    // left border
    neighbors = grid.get_neighbors_of(0, 5);
    REQUIRE(CONTAINS(neighbors, Point(1, 5)));
    REQUIRE(CONTAINS(neighbors, Point(0, 4)));
    REQUIRE(CONTAINS(neighbors, Point(0, 6)));

    // top border
    neighbors = grid.get_neighbors_of(5, 0);
    REQUIRE(CONTAINS(neighbors, Point(5, 1)));
    REQUIRE(CONTAINS(neighbors, Point(4, 0)));
    REQUIRE(CONTAINS(neighbors, Point(6, 0)));

    // bottom border
    neighbors = grid.get_neighbors_of(5, 9);
    REQUIRE(CONTAINS(neighbors, Point(5, 8)));
    REQUIRE(CONTAINS(neighbors, Point(4, 9)));
    REQUIRE(CONTAINS(neighbors, Point(6, 9)));

    // right border
    neighbors = grid.get_neighbors_of(9, 5);
    REQUIRE(CONTAINS(neighbors, Point(8, 5)));
    REQUIRE(CONTAINS(neighbors, Point(9, 4)));
    REQUIRE(CONTAINS(neighbors, Point(9, 6)));
}

TEST_CASE("Grid, Random Manual Construction", "[Grid]") {
    
    const uint32_t MAX_GRID_LENGTH = 100;
    const size_t TRIALS = 100;
    const size_t PROBES_PER_TRIAL = 30;

    std::vector<Point> neighbors;

    for (size_t trial = 0; trial < TRIALS; trial++) {

        uint32_t width  = (uint32_t)(10 + (rand() % MAX_GRID_LENGTH));
        uint32_t height = (uint32_t)(10 + (rand() % MAX_GRID_LENGTH));

        Grid grid = Grid(width, height);

        // Testing corners
        // --------------------------------------------------------------------
        
        // top left
        neighbors = grid.get_neighbors_of(0, 0);
        REQUIRE(CONTAINS(neighbors, Point(0, 1)));
        REQUIRE(CONTAINS(neighbors, Point(1, 0)));

        // top right
        neighbors = grid.get_neighbors_of(width - 1, 0);
        REQUIRE(CONTAINS(neighbors, Point(width - 2, 0)));
        REQUIRE(CONTAINS(neighbors, Point(width - 1, 1)));

        // bottom left
        neighbors = grid.get_neighbors_of(0, height - 1);
        REQUIRE(CONTAINS(neighbors, Point(1, height - 1)));
        REQUIRE(CONTAINS(neighbors, Point(0, height - 2)));
        
        // bottom right
        neighbors = grid.get_neighbors_of(width - 1, height - 1);
        REQUIRE(CONTAINS(neighbors, Point(width - 2, height - 1)));
        REQUIRE(CONTAINS(neighbors, Point(width - 1, height - 2)));

        // Testing borders
        for (size_t probe = 0; probe < PROBES_PER_TRIAL; probe++) {
            
            uint32_t probe_x = (uint32_t)(1 + (rand() % (width -  2)));
            uint32_t probe_y = (uint32_t)(1 + (rand() % (height - 2)));
            
            // left border
            neighbors = grid.get_neighbors_of(0, probe_y);
            REQUIRE(CONTAINS(neighbors, Point(1, probe_y    )));
            REQUIRE(CONTAINS(neighbors, Point(0, probe_y - 1)));
            REQUIRE(CONTAINS(neighbors, Point(0, probe_y + 1)));

            // top border
            neighbors = grid.get_neighbors_of(probe_x, 0);
            REQUIRE(CONTAINS(neighbors, Point(probe_x    , 1)));
            REQUIRE(CONTAINS(neighbors, Point(probe_x - 1, 0)));
            REQUIRE(CONTAINS(neighbors, Point(probe_x + 1, 0)));

            // bottom border
            neighbors = grid.get_neighbors_of(probe_x, height - 1);
            REQUIRE(CONTAINS(neighbors, Point(probe_x    , height - 2)));
            REQUIRE(CONTAINS(neighbors, Point(probe_x - 1, height - 1)));
            REQUIRE(CONTAINS(neighbors, Point(probe_x + 1, height - 1)));

            // right border
            neighbors = grid.get_neighbors_of(width - 1, probe_y);
            REQUIRE(CONTAINS(neighbors, Point(width - 2, probe_y    )));
            REQUIRE(CONTAINS(neighbors, Point(width - 1, probe_y - 1)));
            REQUIRE(CONTAINS(neighbors, Point(width - 1, probe_y + 1)));
        }

        // Testing random middle samples
        for (size_t probe = 0; probe < PROBES_PER_TRIAL; probe++) {

            uint32_t probe_x = (uint32_t)(1 + (rand() % (width -  2)));
            uint32_t probe_y = (uint32_t)(1 + (rand() % (height - 2)));

            neighbors = grid.get_neighbors_of(probe_x, probe_y);
            REQUIRE(CONTAINS(neighbors, Point(probe_x - 1, probe_y    )));
            REQUIRE(CONTAINS(neighbors, Point(probe_x + 1, probe_y    )));
            REQUIRE(CONTAINS(neighbors, Point(probe_x    , probe_y - 1)));
            REQUIRE(CONTAINS(neighbors, Point(probe_x    , probe_y + 1)));
        }
    }
}

TEST_CASE("Disjoint Sets, Basic Functionality", "[Disjoint Sets]") {

    const uint32_t MAX_SET_LENGTH = 50;
    DisjointSets sets = DisjointSets(rand() % MAX_SET_LENGTH , rand() % MAX_SET_LENGTH);

    std::vector<std::vector<Point>> partitioned_sets 
        = std::vector<std::vector<Point>>(1 + (rand() % (sets.get_width() - 1)));
    
    for (uint32_t x = 0; x < partitioned_sets.size(); x++) {
        partitioned_sets[x].push_back(Point(x, 0));
    }

    for (uint32_t x = 0; x < sets.get_width(); x++) {
        for (uint32_t y = 1; y < sets.get_height(); y++) {
            uint32_t idx = (uint32_t)(rand() % partitioned_sets.size());
            partitioned_sets[idx].push_back(Point(x, y));
        }
    }

    for (uint32_t i = 0; i < partitioned_sets.size(); i++) {
        for (uint32_t j = 1; j < partitioned_sets[i].size(); j++) {
            sets.join(partitioned_sets[i][j], partitioned_sets[i][j - 1]);
        }
    }

    for (uint32_t i = 0; i < partitioned_sets.size(); i++) {
        for (uint32_t j = 1; j < partitioned_sets[i].size(); j++) {

            REQUIRE(sets.is_joined(partitioned_sets[i][j],     partitioned_sets[i][j - 1]));
            REQUIRE(sets.is_joined(partitioned_sets[i][j - 1], partitioned_sets[i][j]    ));
        }
    }

    for (uint32_t i1 = 0; i1 < partitioned_sets.size(); i1++) {
        for (uint32_t i2 = 0; i2 < partitioned_sets.size(); i2++) {
            
            if (i1 == i2) continue;
            
            for (Point p1 : partitioned_sets[i1]) {
                for (Point p2 : partitioned_sets[i2]) {
                    REQUIRE_FALSE(sets.is_joined(p1, p2));
                }
            }
        }
    }
}

TEST_CASE("Maze, Default Constructor", "[Maze]") {
    
    Maze maze;
    std::vector<std::vector<Tile>> result = maze.get_result();
    
    for (uint32_t x = 0; x < maze.get_width(); x++) {
        for (uint32_t y = 0; y < maze.get_height(); y++) {
            if (x == 1 and y == 0) {
                REQUIRE(result[x][y] == Tile::Start);
            }
            else if (x == maze.get_width() - 2 and y == maze.get_height() - 1) {
                REQUIRE(result[x][y] == Tile::End);
            }
            else if (x % 2 == 1 and y % 2 == 1) {
                REQUIRE(result[x][y] == Tile::Floor);
            }
            else {
                REQUIRE(result[x][y] == Tile::Wall);
            }
        }
    }
}

TEST_CASE("Maze, Random Manual Construction", "[Maze]") {
    
    const uint32_t MAX_GRID_LENGTH = 100;
    const size_t TRIALS = 100;
    
    Maze maze;
    std::vector<std::vector<Tile>> result;

    for (size_t trial = 0; trial < TRIALS; trial++) {
        
        maze = Maze(rand() % MAX_GRID_LENGTH, rand() % MAX_GRID_LENGTH);
        result = maze.get_result();

        for (uint32_t x = 0; x < maze.get_width(); x++) {
            for (uint32_t y = 0; y < maze.get_height(); y++) {
                if (x == 1 and y == 0) {
                    REQUIRE(result[x][y] == Tile::Start);
                }
                else if (x == maze.get_width() - 2 and y == maze.get_height() - 1) {
                    REQUIRE(result[x][y] == Tile::End);
                }
                else if (x % 2 == 1 and y % 2 == 1) {
                    REQUIRE(result[x][y] == Tile::Floor);
                }
                else {
                    REQUIRE(result[x][y] == Tile::Wall);
                }
            }
        }
    }
} 

TEST_CASE("Maze, Solution Highlighter",  "[Maze]") {
    
    const size_t TRIALS = 100;

    for (size_t trial = 0; trial < TRIALS; trial++) {
        
        Maze maze;

        maze.generate_using_backtracker();
        maze.add_solution();
        
        std::vector<std::vector<Tile>> result = maze.get_result();
        Point cursor = Point(maze.get_width() - 2, maze.get_height() - 2);
        
        bool can_continue = true;
        
        while (can_continue) {
            
            std::vector<Point> neighbors;
            
            neighbors.push_back(cursor.up()   );
            neighbors.push_back(cursor.down() );
            neighbors.push_back(cursor.left() );
            neighbors.push_back(cursor.right());
            
            can_continue = false;
            for (Point neighbor : neighbors) {
                if (result[neighbor.x][neighbor.y] == Tile::Solution) {
                    result[cursor.x][cursor.y] = Tile::Floor;
                    cursor = neighbor;
                    can_continue = true;
                    break;
                }
            }
        }

        REQUIRE(cursor == Point(1, 1));
    }
}

TEST_CASE("Maze, Backtracker / DFS Generation", "[Maze]") {

    const uint32_t MAX_GRID_LENGTH = 50;
    const size_t TRIALS = 100;
    
    for (size_t trial = 0; trial < TRIALS; trial++) {
        Maze maze;
        
        REQUIRE_NOTHROW(maze.generate_using_backtracker());
        REQUIRE_NOTHROW(maze.add_solution());
    }
}

TEST_CASE("Maze, Kruskal's Algorithm Generation", "[Maze]") {
    
    const uint32_t MAX_GRID_LENGTH = 50;
    const size_t TRIALS = 100;
    
    for (size_t trial = 0; trial < TRIALS; trial++) {
        Maze maze;

        REQUIRE_NOTHROW(maze.generate_using_kruskals());
        REQUIRE_NOTHROW(maze.add_solution());
    }
}

TEST_CASE("Maze, Prim's Algorithm Generation", "[Maze]") {

    const uint32_t MAX_GRID_LENGTH = 50;
    const size_t TRIALS = 100;
    
    for (size_t trial = 0; trial < TRIALS; trial++) {
        Maze maze;

        REQUIRE_NOTHROW(maze.generate_using_prims());
        REQUIRE_NOTHROW(maze.add_solution());
    }
}

TEST_CASE("Maze, Binary Tree Generation", "[Maze]") {

    const uint32_t MAX_GRID_LENGTH = 50;
    const size_t TRIALS = 100;
    
    for (size_t trial = 0; trial < TRIALS; trial++) {
        Maze maze;

        REQUIRE_NOTHROW(maze.generate_using_binary_tree());
        REQUIRE_NOTHROW(maze.add_solution());
    }
}

TEST_CASE("Maze, Eller's Generation", "[Maze]") {

    const uint32_t MAX_GRID_LENGTH = 50;
    const size_t TRIALS = 100;
    
    for (size_t trial = 0; trial < TRIALS; trial++) {
        Maze maze;

        REQUIRE_NOTHROW(maze.generate_using_ellers());
        REQUIRE_NOTHROW(maze.add_solution());
    }
}

TEST_CASE("Maze Generator, All Algorithms", "[Maze Generator]") {
    
    MazeGenerator maze_generator;
    std::string bad_method = "bad_method";
    REQUIRE_THROWS_AS(maze_generator.generate(bad_method), std::runtime_error);
    REQUIRE_THROWS_AS(maze_generator.solve(), std::runtime_error);

    for (std::string generation_algorithm : maze_generator.get_algorithms()) {
        REQUIRE_NOTHROW(maze_generator.generate(generation_algorithm));
        REQUIRE_NOTHROW(maze_generator.solve());
    }
}

// TEST_CASE("Standard Output Demo") {
// 
//     Maze maze;   
//     maze.generate_using_ellers();
//     std::cout << maze << std::endl;
//     maze.add_solution();
//     std::cout << maze << std::endl;
// }

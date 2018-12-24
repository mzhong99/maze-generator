void MazeGenerator::setup_function_map() {

    generators["DFS"        ] = &Maze::generate_using_backtracker;
    generators["dfs"        ] = &Maze::generate_using_backtracker;
    generators["backtracker"] = &Maze::generate_using_backtracker;

    generators["kruskal"    ] = &Maze::generate_using_kruskals;
    generators["kruskals"   ] = &Maze::generate_using_kruskals;

    generators["prim"       ] = &Maze::generate_using_prims;
    generators["prims"      ] = &Maze::generate_using_prims;

    generators["tree"       ] = &Maze::generate_using_binary_tree;
    generators["binary_tree"] = &Maze::generate_using_binary_tree;

    generators["eller"      ] = &Maze::generate_using_ellers;
    generators["ellers"     ] = &Maze::generate_using_ellers;
}

MazeGenerator::MazeGenerator() {
    setup_function_map();
}

MazeGenerator::MazeGenerator(uint32_t width, uint32_t height) {
    maze = Maze(width, height);
    setup_function_map();
}

void MazeGenerator::generate(std::string generation_algorithm) {
    if (generators.find(generation_algorithm) == generators.end()) {
        throw std::runtime_error("Maze Generator: algorithm does not exist.");
    }

    void(Maze::*algorithm_ptr)() = generators[generation_algorithm];
    (maze.*algorithm_ptr)();
}

void MazeGenerator::solve() {
    maze.add_solution();
}

void MazeGenerator::display() const {
    std::cout << maze << std::endl;
}

void MazeGenerator::print_to(std::string filename) const {
    
    Image image = Image(maze.get_width(), maze.get_height());
    
    for (uint32_t x = 0; x < maze.get_width(); x++) {
        for (uint32_t y = 0; y < maze.get_height(); y++) {
            Tile tile = maze.get_tile_at(x, y);
            if (tile == Tile::Floor) {
                image.set(x, y, CommonColors::WHITE);
            }
            else if (tile == Tile::Wall) {
                image.set(x, y, CommonColors::BLACK);
            }
            else if (tile == Tile::Start) {
                image.set(x, y, CommonColors::RED);
            }
            else if (tile == Tile::End) {
                image.set(x, y, CommonColors::GREEN);
            }
            else if (tile == Tile::Solution) {
                image.set(x, y, CommonColors::BLUE);
            }
            else {
                throw std::logic_error("Maze Generator: invalid tile parsed");
            }
        }
    }

    image.write_to_file(filename);
}

std::string MazeGenerator::attributes() const {
    std::stringstream ss;
    ss << "Maze Generator with attributes:" << std::endl;
    ss << "    Width:  " << maze.get_width() << std::endl;
    ss << "    Height: " << maze.get_height();
    return ss.str();
}

std::vector<std::string> MazeGenerator::get_algorithms() {
    std::vector<std::string> algorithms;
    for (auto kv : generators) {
        algorithms.push_back(kv.first);
    }
    return algorithms;
}

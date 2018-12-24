void Maze::reset_result() {

    result = std::vector<std::vector<Tile>>(width);

    for (uint32_t x = 0; x < width; x++) {
        result[x] = std::vector<Tile>(height);
    }

    for (uint32_t x = 0; x < width; x++) {
        for (uint32_t y = 0; y < height; y++) {
            result[x][y] = Tile::Wall;
        }
    }

    for (uint32_t x = 1; x < width; x += 2) {
        for (uint32_t y = 1; y < height; y += 2) {
            result[x][y] = Tile::Floor;
        }
    }

    result[1][0]                  = Tile::Start;
    result[width - 2][height - 1] = Tile::End;
    has_valid_solution = false;
}

uint32_t Maze::coordinate_to_index(uint32_t coord) {
    return 1 + (2 * coord);
}

void Maze::build_floor(const Point& lhs, const Point& rhs) {
    
    uint32_t index_lhs_x = coordinate_to_index(lhs.x);
    uint32_t index_lhs_y = coordinate_to_index(lhs.y);

    uint32_t index_rhs_x = coordinate_to_index(rhs.x);
    uint32_t index_rhs_y = coordinate_to_index(rhs.y);

    uint32_t index_between_x = (index_rhs_x + index_lhs_x) / 2;
    uint32_t index_between_y = (index_rhs_y + index_lhs_y) / 2;

    result[index_between_x][index_between_y] = Tile::Floor;
}

Maze::Maze() {
    this->has_valid_solution = false;
    this->grid   = Grid();
    this->width  = 1 + (2 * grid.get_width());
    this->height = 1 + (2 * grid.get_height());

    reset_result();
}

Maze::Maze(uint32_t width, uint32_t height) {
    this->has_valid_solution = false;
    this->grid   = Grid(width, height);
    this->width  = 1 + (2 * grid.get_width());
    this->height = 1 + (2 * grid.get_height());
    
    reset_result();
}

std::vector<std::vector<Tile>> Maze::get_result() const {
    return result;
}

uint32_t Maze::get_width() const {
    return width;
}

uint32_t Maze::get_height() const {
    return height;
}

void Maze::generate_using_backtracker() {
    
    reset_result();
    
    std::vector<std::vector<bool>> seen = std::vector<std::vector<bool>>(grid.get_width());
    for (uint32_t x = 0; x < grid.get_width(); x++) {
        seen[x] = std::vector<bool>(grid.get_height());
    }

    Point seed = Point(0, 0);
    seen[0][0] = true;
    std::stack<Point> dfs; dfs.push(seed);

    while (!dfs.empty()) {

        Point curr = dfs.top(); dfs.pop();
        
        std::vector<Point> neighbors = grid.get_neighbors_of(curr.x, curr.y);
        std::random_shuffle(neighbors.begin(), neighbors.end());

        for (Point neighbor : neighbors) {
            
            if (not seen[neighbor.x][neighbor.y]) {
                
                dfs.push(neighbor);
                build_floor(curr, neighbor);
                seen[neighbor.x][neighbor.y] = true;
            }
        }
    }

    has_valid_solution = true;
}

void Maze::generate_using_kruskals() {
    
    reset_result();

    std::vector<Edge> randomized_edges = grid.get_randomized_edges();
    DisjointSets sets = DisjointSets(grid.get_width(), grid.get_height());

    for (Edge edge : randomized_edges) {
        
        Point p1 = edge.from;
        Point p2 = edge.to;
        
        if (!sets.is_joined(p1, p2)) {
            build_floor(p1, p2);
            sets.join(p1, p2);
        }
    }

    has_valid_solution = true;
}

void Maze::generate_using_prims() {
    
    reset_result();

    std::vector<std::vector<std::vector<Edge>>> adjacency = grid.get_randomized_adjacency();

    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> frontier;
    Point seed = Point(rand() % grid.get_width(), rand() % grid.get_height());

    std::unordered_set<std::string> mst_points;
    
    for (Edge edge : adjacency[seed.x][seed.y]) {
        frontier.push(edge);
    }

    while (mst_points.size() < grid.get_width() * grid.get_height()) {
        
        Edge chosen = frontier.top(); frontier.pop();
        Point p1 = chosen.from;
        Point p2 = chosen.to;
        
        if (SET_CONTAINS(mst_points, p1.to_string()) and 
            SET_CONTAINS(mst_points, p2.to_string())) {
            continue;
        }

        mst_points.insert(p1.to_string());
        mst_points.insert(p2.to_string());

        build_floor(p1, p2);

        for (Edge edge : adjacency[p1.x][p1.y]) {
            frontier.push(edge);
        }

        for (Edge edge : adjacency[p2.x][p2.y]) {
            frontier.push(edge);
        }
    }

    has_valid_solution = true;
}

void Maze::generate_using_binary_tree() {
    
    reset_result();
    
    for (uint32_t x = 1; x < grid.get_width(); x++) {
        for (uint32_t y = 1; y < grid.get_height(); y++) {
            Point from = Point(x, y);
            Point to   = rand() % 2 ? from.up() : from.left();
            build_floor(from, to);
        }
    }

    for (uint32_t x = 1; x < grid.get_width(); x++) {
        Point from = Point(x, 0);
        build_floor(from, from.left());
    }

    for (uint32_t y = 1; y < grid.get_height(); y++) {
        Point from = Point(0, y);
        build_floor(from, from.up());
    }

    has_valid_solution = true;
}

void Maze::generate_using_ellers() {
    
    reset_result();

    DisjointSets sets = DisjointSets(grid.get_width(), grid.get_height());

    for (uint32_t y = 0; y < grid.get_height() - 1; y++) {
        
        std::unordered_set<size_t> touched_sets;

        for (uint32_t x = 0; x < grid.get_width() - 1; x++) {
            
            Point cursor = Point(x, y);
            
            if (rand() % 2 == 1 and (not sets.is_joined(cursor, cursor.right()))) {
                
                build_floor(cursor, cursor.right());
                sets.join(cursor, cursor.right());
            }
        }

        for (uint32_t x = 0; x < grid.get_width(); x++) {
            
            Point cursor = Point(x, y);
            touched_sets.insert(sets.find(cursor));
        }

        for (size_t set_number : touched_sets) {
            
            std::vector<Point> unfiltered = sets.elements(set_number);
            std::vector<Point> frontier;

            for (Point point : unfiltered) {
                if (point.y == y) {
                    frontier.push_back(point);
                }
            }

            std::vector<size_t> indexes_to_choose;
            for (size_t i = 0; i < frontier.size(); i++) {
                indexes_to_choose.push_back(i);
            }

            std::random_shuffle(indexes_to_choose.begin(), indexes_to_choose.end());
            
            size_t number_to_expand = 1;
            
            if (frontier.size() > 1) {
                number_to_expand = 1 + (rand() % (frontier.size() - 1)); 
            }
            
            for (size_t i = 0; i < number_to_expand; i++) {
                
                size_t idx = indexes_to_choose[i];
                Point chosen = frontier[idx];
                
                build_floor(chosen, chosen.down());
                sets.join(chosen, chosen.down());
            }
        }
    }

    for (uint32_t x = 0; x < grid.get_width() - 1; x++) {
        
        Point cursor = Point(x, grid.get_height() - 1);
        
        if (not sets.is_joined(cursor, cursor.right())) {
            
            build_floor(cursor, cursor.right());
            sets.join(cursor, cursor.right());
        }
    }

    has_valid_solution = true;
}

void Maze::add_solution() {
    
    if (not has_valid_solution) {
        throw std::runtime_error("Maze: attempted to solve blank maze");
    }

    // not seen == parent[x][y] is pointing at (0, 0)
    std::vector<std::vector<Point>> parent = std::vector<std::vector<Point>>(width);
    for (uint32_t x = 0; x < width; x++) {
        parent[x] = std::vector<Point>(height);
    }

    for (uint32_t x = 0; x < width; x++) {
        for (uint32_t y = 0; y < height; y++) {
            parent[x][y] = Point(0, 0);
        }
    }

    parent[1][1] = Point(1, 0);

    Point seed = Point(1, 1);
    Point target = Point(width - 2, height - 2);
    
    std::queue<Point> bfs; bfs.push(seed);
    
    while (not bfs.empty()) {
        
        Point cursor = bfs.front(); bfs.pop();

        if (cursor == target) break;

        std::vector<Point> adj;
        adj.push_back(Point(cursor.right()));
        adj.push_back(Point(cursor.left() ));
        adj.push_back(Point(cursor.down() ));
        adj.push_back(Point(cursor.up()   ));
        
        for (Point neighbor : adj) {
            if (result[neighbor.x][neighbor.y] == Tile::Floor and
                parent[neighbor.x][neighbor.y] == Point(0, 0)) {
                
                bfs.push(neighbor);
                parent[neighbor.x][neighbor.y] = cursor;
            }
        }
    }

    for (Point point = target; point != Point(1, 0); point = parent[point.x][point.y]) {
        result[point.x][point.y] = Tile::Solution;
    }
}

Tile Maze::get_tile_at(uint32_t x, uint32_t y) const {
    if (x >= width or y >= height) {
        throw std::range_error("Maze: tile access out of range");
    }
    return result[x][y];
}

std::ostream& operator<<(std::ostream& out, const Maze& maze) {
    out << maze.to_string();
    return out;
}

std::string Maze::to_string() const {
    
    std::stringstream ss;

    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            if (result[x][y] == Tile::Wall    ) ss << "#";
            if (result[x][y] == Tile::Floor   ) ss << " ";
            if (result[x][y] == Tile::Start   ) ss << "S";
            if (result[x][y] == Tile::End     ) ss << "E";
            if (result[x][y] == Tile::Solution) ss << ".";
        }
        ss << std::endl;
    }

    return ss.str();
}


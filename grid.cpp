
bool Grid::preconditions_met() {
    return width > 0 and height > 0;
}

void Grid::setup_adjacency() {
    
    if (not preconditions_met()) {
        throw std::logic_error("Grid: attempting to setup adjacency of zero size grid");
    }

    adjacency = std::vector<std::vector<std::vector<Edge>>>(width);
    for (uint32_t x = 0; x < width; x++) {
        adjacency[x] = std::vector<std::vector<Edge>>(height);
    }

    // center values can be set without worrying about boundaries
    for (uint32_t x = 1; x < width - 1; x++) {
        for (uint32_t y = 1; y < height - 1; y++) {
            
            std::vector<Edge> neighbors;
            
            Point from = Point(x, y);

            neighbors.push_back(Edge(from, from.right()));
            neighbors.push_back(Edge(from, from.left() ));
            neighbors.push_back(Edge(from, from.down() ));
            neighbors.push_back(Edge(from, from.up()   ));
            
            adjacency[x][y] = neighbors;
        }
    }

    // top and bottom borders, excluding corners
    for (uint32_t x = 1; x < width - 1; x++) {
        std::vector<Edge> neighbors_zero;
        std::vector<Edge> neighbors_long;

        Point from_zero = Point(x, 0);
        Point from_long = Point(x, height - 1);

        neighbors_zero.push_back(Edge(from_zero, from_zero.right()));
        neighbors_zero.push_back(Edge(from_zero, from_zero.left() ));
        neighbors_zero.push_back(Edge(from_zero, from_zero.down() ));
        
        neighbors_long.push_back(Edge(from_long, from_long.right()));
        neighbors_long.push_back(Edge(from_long, from_long.left() ));
        neighbors_long.push_back(Edge(from_long, from_long.up()   ));

        adjacency[from_zero.x][from_zero.y] = neighbors_zero;
        adjacency[from_long.x][from_long.y] = neighbors_long;
    }

    // left and right borders, excluding corners
    for (uint32_t y = 1; y < height - 1; y++) {
        std::vector<Edge> neighbors_zero;
        std::vector<Edge> neighbors_long;

        Point from_zero = Point(0, y);
        Point from_long = Point(width - 1, y);

        neighbors_zero.push_back(Edge(from_zero, from_zero.down() ));
        neighbors_zero.push_back(Edge(from_zero, from_zero.up()   ));
        neighbors_zero.push_back(Edge(from_zero, from_zero.right()));

        neighbors_long.push_back(Edge(from_long, from_long.down() ));
        neighbors_long.push_back(Edge(from_long, from_long.up()   ));
        neighbors_long.push_back(Edge(from_long, from_long.left() ));

        adjacency[from_zero.x][from_zero.y] = neighbors_zero;
        adjacency[from_long.x][from_long.y] = neighbors_long;
    }

    // actual corners now
    std::vector<Edge> neighbors_top_left;
    Point top_left = Point(0, 0);
    neighbors_top_left.push_back(Edge(top_left, top_left.right())); // right
    neighbors_top_left.push_back(Edge(top_left, top_left.down() )); // down
    
    std::vector<Edge> neighbors_top_right;
    Point top_right = Point(width - 1, 0);
    neighbors_top_right.push_back(Edge(top_right, top_right.left())); // left
    neighbors_top_right.push_back(Edge(top_right, top_right.down())); // down

    std::vector<Edge> neighbors_bottom_left;
    Point bottom_left = Point(0, height - 1);
    neighbors_bottom_left.push_back(Edge(bottom_left, bottom_left.up()   )); // up
    neighbors_bottom_left.push_back(Edge(bottom_left, bottom_left.right())); // right

    std::vector<Edge> neighbors_bottom_right;
    Point bottom_right = Point(width - 1, height - 1);
    neighbors_bottom_right.push_back(Edge(bottom_right, bottom_right.left())); // left
    neighbors_bottom_right.push_back(Edge(bottom_right, bottom_right.up()  )); // up

    adjacency[top_left.x    ][top_left.y    ] = neighbors_top_left;
    adjacency[bottom_left.x ][bottom_left.y ] = neighbors_bottom_left;
    adjacency[top_right.x   ][top_right.y   ] = neighbors_top_right;
    adjacency[bottom_right.x][bottom_right.y] = neighbors_bottom_right;
}

void Grid::setup_randomized_adjacency() {

    const size_t MAX_EDGE_WEIGHT = 1000;
    randomized_adjacency = adjacency;

    for (uint32_t x = 0; x < width; x++) {
        for (uint32_t y = 0; y < height; y++) {
            for (uint32_t i = 0; i < adjacency[x][y].size(); i++) {
                randomized_adjacency[x][y][i].weight = (size_t)(1 + (rand() % MAX_EDGE_WEIGHT));
            }
        }
    }
}

Grid::Grid() {
    this->width  = 10;
    this->height = 10;

    setup_adjacency();
    setup_randomized_adjacency();
}

Grid::Grid(uint32_t width, uint32_t height) {
    this->width  = width;
    this->height = height;

    if (not preconditions_met()) {
        this->width  = 10;
        this->height = 10;
    }
    
    setup_adjacency();
    setup_randomized_adjacency();
}

std::vector<Edge> Grid::get_randomized_edges() {
    
    std::vector<Edge> all_edges;

    for (uint32_t x = 0; x < width; x++) {
        for (uint32_t y = 0; y < height; y++) {
            for (Edge randomized : randomized_adjacency[x][y]) {
                all_edges.push_back(randomized);
            }
        }
    }

    std::sort(all_edges.begin(), all_edges.end());

    std::vector<Edge> unique_edges;
    std::unordered_set<std::string> serialized_edges;

    for (Edge edge : all_edges) {
        
        if (!SET_CONTAINS(serialized_edges, edge.to_string())) {
            
            unique_edges.push_back(edge);
            
            serialized_edges.insert(edge.to_string());
            serialized_edges.insert(edge.reverse().to_string());
        }
    }

    return unique_edges;
}

std::vector<std::vector<std::vector<Edge>>> Grid::get_randomized_adjacency() {
    return this->randomized_adjacency;
}

uint32_t Grid::get_width() {
    return this->width;
}

uint32_t Grid::get_height() {
    return this->height;
}

std::vector<Point> Grid::get_neighbors_of(uint32_t x, uint32_t y) {
    
    if (x >= width or y >= height) {
        throw std::range_error("Grid: attempted to get neighbors of point out of bounds");
    }

    std::vector<Point> neighbors;
    for (Edge edge : adjacency[x][y]) {
        neighbors.push_back(edge.to);
    }
    
    return neighbors;
}


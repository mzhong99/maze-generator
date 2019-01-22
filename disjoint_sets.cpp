void DisjointSets::fill_sets() {

    sets = std::vector<std::vector<size_t>>(width);
    for (uint32_t x = 0; x < width; x++) {
        sets[x] = std::vector<size_t>(height);
    }

    size_t set_number = 0;
    for (uint32_t x = 0; x < width; x++) {
        for (uint32_t y = 0; y < height; y++) {
            sets[x][y] = set_number++;
        }
    }

    number_of_sets = set_number;
}   

DisjointSets::DisjointSets() {
    this->width  = 10;
    this->height = 10;
    
    fill_sets();
}

DisjointSets::DisjointSets(uint32_t width, uint32_t height) {
    this->width  = width;
    this->height = height;
    
    if (width == 0 || height == 0) {
        this->width  = 10;
        this->height = 10;
    }

    fill_sets();
}

void DisjointSets::join(const Point& p1, const Point& p2) {

    size_t old_set = sets[p2.x][p2.y];
    size_t new_set = sets[p1.x][p1.y];

    for (uint32_t x = 0; x < width; x++) {
        for (uint32_t y = 0; y < height; y++) {
            if (sets[x][y] == old_set) {
                sets[x][y] = new_set;
            }
        }
    }
}

bool DisjointSets::is_joined(const Point& p1, const Point& p2) const {
    return find(p1) == find(p2);
}

size_t DisjointSets::find(const Point& point) const {
    return sets[point.x][point.y];
}

std::vector<Point> DisjointSets::elements(const size_t set_number) const {
    
    std::vector<Point> disjoint_set;
    
    for (uint32_t x = 0; x < width; x++) {
        for (uint32_t y = 0; y < height; y++) {
            if (sets[x][y] == set_number) {
                disjoint_set.push_back(Point(x, y));
            }
        }
    }
    
    return disjoint_set;
}
uint32_t DisjointSets::get_width() const {
    return width;
}

uint32_t DisjointSets::get_height() const {
    return height;
}

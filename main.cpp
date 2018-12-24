#include <iostream>
#include <string>

#include <stdexcept>

#include <cstdint>
#include <cstdlib>

#include <time.h>

#include "maze_generator.hpp"

int main(int argc, char** argv) {

    srand(time(NULL));

    if (argc != 3 and argc != 5) {
        std::cout << "Usage: ./maze_generator <algorithm> <output_name>" << std::endl;
        std::cout << "Usage: ./maze_generator <width> <height>" 
                  << " <algorithm> <output_name>" << std::endl;

        return EXIT_FAILURE;
    }

    MazeGenerator generator;

    if (argc == 5) {
        
        uint32_t width  = abs(atoi(argv[1]));
        uint32_t height = abs(atoi(argv[2]));
        
        generator = MazeGenerator(width, height);
    }

    try {
        generator.generate(std::string(argv[argc - 2]));
    }
    catch (std::runtime_error ex) {
        
        std::cout << "Invalid algorithm key. Try again." << std::endl;
        std::cout << "Valid keys: " << std::endl;
        
        for (std::string s: generator.get_algorithms()) {
            std::cout << "    " << s << std::endl;
        }
        
        return EXIT_FAILURE;
    }

    std::cout << generator.attributes() << std::endl;
    
    std::string filename = argv[argc - 1];
    std::string problem_filename = filename + ".png";
    std::string solution_filename = filename + "_solution.png";

    generator.print_to(problem_filename);
    generator.solve();
    generator.print_to(solution_filename);

    std::cout << "Printing completed!" << std::endl;

    std::cout << "Problem Image: "  << problem_filename  << std::endl;
    std::cout << "Solution Image: " << solution_filename << std::endl;

    return EXIT_SUCCESS;
}


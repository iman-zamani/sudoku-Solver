# Sudoku Solver

## Description
Sudoku Solver is a desktop application developed using C++ and the Qt framework. This application allows users to input Sudoku puzzles and solve them using a backtracking algorithm. It features a user-friendly interface for easy interaction with the puzzle.

![Unsolved Sudoku](images/unsolved.png) ![Solved Sudoku](images/solved.png)

## Features
- Interactive grid for entering Sudoku puzzles.
- "Solve" button to automatically find a solution.
- "Reset" button to clear the grid and start over.

## System Requirements
- Qt 5 or Qt 6
- C++17 compiler (e.g., GCC, Clang, MSVC)

## Getting Started

### Prerequisites
Make sure you have Qt installed on your system. You can download it from [Qt's official website](https://www.qt.io/download).

### Building the Application
This project uses CMake for building. Follow these steps to compile the application:

1. Clone the repository:
   ```
   git clone https://github.com/iman-zamani/sudoku-Solver.git
   cd sudoku-solver
   ```

2. Create a build directory:
   ```
   mkdir build
   cd build
   ```

3. Run CMake and build the project:
   ```
   cmake ..
   cmake --build .
   ```

### Running the Application
After building the project, you can run the application directly from the build directory:
```
./sudoku
```

## Contributing
Contributions to Sudoku Solver are welcome! Feel free to fork the repository, make changes, and submit pull requests.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

# -VUT-ICP
The C++ Programming Language - 2D robot simulator

After launch, the program prompts the user to load a JSON file. Once a valid JSON file is selected, the simulation is loaded in a paused state.
The user can add robots or obstacles and then start the simulation.
Autonomous robots have a fixed size, while the robot controlled by the user can have its size changed. The user-controlled robot is always pink. The color of autonomous robots can be changed.
Obstacles are always red squares, but their size and rotation angle can be adjusted.

### Compilation:
- make – compiles the program (the executable will be located in the src/)
- make run – compiles the program and starts the simulation
- make clean – deletes generated files
- make pack – creates a compressed archive
- make doxygen – runs Doxygen and generates documentation

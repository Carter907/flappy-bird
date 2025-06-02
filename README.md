### Run it
1. clone the repo
2. navigate to the root of the project
3. use the following commands
```
cmake -S src -B build
cmake --build build
./build/flappy-bird
```
### How to Play
- press space to flap the bird
- you end your round in the following ways:
    - fly to high
    - hit the ground
    - hit a pipe
- each time a pipe reaches the back of the screen, your score increments by 1


### Features
- collision detection
- gravity
- best score tracker

# Some Project

Build instructions
```bash
git pull https://github.com/Flinner/Hello_SFML.git
cd Hello_SFML

# With Ninja:
cmake -B build -G Ninja && ninja -C build

# Without Ninja
cmake -B build
cmake --build build

```

Run:

```bash
./build/walking
# and
./build/spiral
```

make sure to run in root project directory, as `assets` are in the root

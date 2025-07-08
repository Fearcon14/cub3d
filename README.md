# Cub3D

A 3D raycasting engine inspired by Wolfenstein 3D, built with MLX42 graphics library. This project implements a first-person 3D game engine with texture mapping, collision detection, mouse and keyboard controls, and interactive features like doors and a gun system.

## 🎮 Features

- **3D Raycasting Engine**: Real-time 3D rendering using raycasting algorithm
- **Texture Mapping**: Support for different wall textures (North, South, East, West)
- **Player Movement**: WASD keys for movement with collision detection
- **Mouse Controls**: Mouse look with customizable sensitivity
- **Interactive Doors**: Click to open/close doors in the environment
- **Gun System**: Animated gun with shooting mechanics
- **Minimap**: Real-time 2D minimap showing player position and vision cone
- **Map Validation**: Comprehensive map file validation system
- **Garbage Collection**: Automatic memory management system

## 🏗️ Architecture

The project is organized into several modules:

- **Parser**: Map file parsing and validation
- **Renderer**: 3D raycasting and texture rendering
- **Input**: Keyboard, mouse, and movement handling
- **Minimap**: 2D minimap rendering and updates
- **Door**: Interactive door system
- **HUD**: Gun rendering and animations
- **Utils**: Helper functions and utilities
- **GarbageCollector**: Memory management system

## 🗺️ Map Format

Maps are defined in `.cub` files with the following format:

```
NO ./path/to/north_texture.png
SO ./path/to/south_texture.png
WE ./path/to/west_texture.png
EA ./path/to/east_texture.png
F R,G,B
C R,G,B

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000000001
10000000000000001100000010101
10000000000000001101010010001
11000001110101011111011010N0111
11110111 1110101 100000010001
11111111 1111111 111111111111
```

### Map Elements:
- `0`: Empty space (floor)
- `1`: Wall
- `2`: Door
- `N/S/E/W`: Player spawn position and direction
- ` `: Space (ignored)

### Texture Configuration:
- `NO`: North wall texture
- `SO`: South wall texture
- `WE`: West wall texture
- `EA`: East wall texture
- `F`: Floor color (RGB format)
- `C`: Ceiling color (RGB format)

## 🎯 Controls

- **WASD**: Move forward, backward, left, right
- **Mouse/← →**: Look around
- **Left Click**: Shoot gun
- **E**: Interact with doors
- **ESC**: Exit game

## 🚀 Installation & Setup

### Prerequisites

#### Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential libx11-dev libglfw3-dev libglfw3 xorg-dev cmake
```

#### Arch Linux:
```bash
sudo pacman -S glfw-x11 cmake
```

### Building the Project

1. **Clone the repository:**
```bash
git clone https://github.com/Raainshe/cub3d
cd cub3d
```

2. **Build the project:**
```bash
make
```

This will automatically:
- Build the libft library
- Build the MLX42 graphics library
- Compile the cub3d executable

### Alternative Build Options

- **Debug build:**
```bash
make debug
```

- **Clean build:**
```bash
make clean
make fclean
```

- **Rebuild everything:**
```bash
make re
```

## 🎮 How to Run

Run the game with a map file:

```bash
./cub3d maps/map1.cub
```

### Available Maps

The project includes several example maps:
- `maps/map1.cub` - Basic map with walls and doors
- `maps/map2.cub` - Map with multiple doors
- `maps/map3.cub` - Simple test map
- `maps/map4.cub` - Another test configuration
- `maps/map5.cub` - Additional test map
- `maps/map6.cub` - Test map variant
- `maps/map7.cub` - Another test configuration

## 🔧 Technical Details

### Performance Optimizations

The project includes several performance optimizations:
- **Compiler flags**: `-O3`, `-march=native`, `-flto`, `-ffast-math`
- **Loop unrolling**: `-funroll-loops`
- **Function inlining**: `-finline-functions`
- **Frame pointer omission**: `-fomit-frame-pointer`

### Memory Management

The project uses a custom garbage collector system that automatically manages memory allocation and deallocation, preventing memory leaks.

### Graphics

- **Resolution**: 1024x768
- **Field of View**: 60 degrees
- **Texture Support**: PNG format textures
- **Rendering**: Real-time raycasting with texture mapping

## 🐛 Debugging

To build with debug flags and memory checking:

```bash
make debug
./cub3d maps/map1.cub
```

This enables:
- Address sanitizer (`-fsanitize=address`)
- Undefined behavior sanitizer (`-fsanitize=undefined`)
- Debug symbols (`-g`)

## 📁 Project Structure

```
cub3d/
├── src/
│   ├── Parser/          # Map parsing and validation
│   ├── Renderer/        # 3D rendering engine
│   ├── Input/           # User input handling
│   ├── Minimap/         # 2D minimap system
│   ├── Door/            # Interactive door system
│   ├── HUD/             # Gun and UI elements
│   ├── Utils/           # Utility functions
│   ├── Initialize/      # Game initialization
│   └── GarbageCollector/ # Memory management
├── includes/            # Header files
├── maps/               # Example map files
├── assets/             # Textures and sprites
│   ├── textures/       # Wall textures
│   └── gun/           # Gun animation frames
├── libraries/          # External libraries
│   ├── libft/         # Custom C library
│   └── MLX42/         # Graphics library
└── Makefile           # Build configuration
```

## 🤝 Contributing

This is a 42 school project. The code follows the 42 coding standards and includes comprehensive error handling and memory management.

## 📄 License

This project is part of the 42 curriculum and follows the 42 coding standards.

---

**Enjoy exploring the 3D world!** 🎮
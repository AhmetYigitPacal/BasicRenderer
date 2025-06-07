# Basic Renderer
A simple OpenGL program for rendering Wavefront '.obj' files.

## Project Structure
BasicRenderer/
├── build.bat # Windows build script
├── build.sh # Linux/macOS build script
├── CMakeLists.txt # Project build configuration
├── include/ # Project header files
├── lib/ # External libraries as git submodules
│ ├── glfw/ # GLFW library
│ ├── glad/ # GLAD library
│ └── glm/ # GLM library
├── src/ # Source files
├── build/ # Build output directory
│ └── BasicRenderer.exe # Executable
└── README.md

## Dependencies
- [GLFW](https://github.com/glfw/glfw) (added as git submodule)  
- [GLAD](https://github.com/Dav1dde/glad) (added as git submodule)  
- [GLM](https://github.com/g-truc/glm) (added as git submodule)  
- OpenGL (system installed)  
- CMake (>= 3.10)  
- Ninja (recommended build system)  

## Setup & Build

### 1. Clone the repository **with submodules**
```bash
git clone --recurse-submodules https://github.com/yourusername/BasicRenderer.git
```

On Linux/MacOS
```bash
chmod +x build.sh
./build.sh
```

On Windows
from Command Prompt
```bash
build.bat
```

Or from PowerShell
```bash
./build.bat
```

## Run
After building the project you can run the executable from the build directory
On Linux/MacOS
```bash
./build/BasicRenderer [path/to/model.obj]
```

On Windows (Command Prompt or PowerShell)
```bash
.\build/BasicRenderer.exe [path/to/model.obj]
```

## Clean
On Linux/MacOS
```bash
rm -rf build
```

On Windows
from Command Prompt
```bash
rmdir /S /Q build
```

Or from PowerShell
```bash
Remove-Item -Force -Recurse build
```

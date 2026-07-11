
## Setup

### Prerequisites
- **Git** — for cloning the repository
- **MSYS2** — [download here](https://www.msys2.org/) (provides `pacman`, a C++ compiler, CMake, and Qt6 all in one place)

### Install dependencies via pacman
Open the **MSYS2 MinGW 64-bit** terminal (not the plain MSYS2 terminal) and run:

```bash
pacman -Syu
```

Restart the terminal if prompted, then run:
```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-qt6-base mingw-w64-x86_64-qt6-tools
```

This installs:
- `mingw-w64-x86_64-gcc` — C++ compiler
- `mingw-w64-x86_64-cmake` — CMake
- `mingw-w64-x86_64-qt6-base` — Qt6 Widgets and core modules
- `mingw-w64-x86_64-qt6-tools` — Qt's dev tools (includes `moc`)

### Configure System Path
To ensure standard terminals (like Git Bash, VSCode, or Command Prompt) and IDEs can find these tools, you must add the MinGW binaries to your system's `PATH`.

1. Open Windows Search and type **Edit the system environment variables**.
2. Click **Environment Variables...** at the bottom.
3. Under System Variables (or User Variables), find `Path` and click **Edit**.
4. Add the following path: `C:\msys64\mingw64\bin` 
5. Click OK and restart any open terminals or IDEs.

### Clone the repository
```bash
git clone https://github.com/codyn06/CookBook
cd CookBook
```

### Download the dataset
- Download the dataset from [https://recipenlg.cs.put.poznan.pl/](https://recipenlg.cs.put.poznan.pl/).
- Unzip it into the project root. This should create a directory called `dataset/` containing `full_dataset.csv`.

### Build the project
Run these from the **MSYS2 MinGW 64-bit** terminal (or a regular terminal if `mingw64/bin` is on your `PATH`):

```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:/msys64/mingw64"
cmake --build . --target CookBook -j 16
```
Replace `16` with your CPU's thread count (terminal commands below):
- **PowerShell:** `$env:NUMBER_OF_PROCESSORS`
- **Command Prompt:** `echo %NUMBER_OF_PROCESSORS%`
- **MSYS2/Git Bash:** `nproc`

### Run
```bash
./CookBook.exe
```

## Project Structure

```
CookBook/  
├── dataset/           # Raw dataset (gitignored — see Setup)  
│ └── full_dataset.csv  
├── src/  
│ ├── main.cpp  
│ ├── data/            # CSV loading & parsing  
│ ├── gui/             # Qt interface (IngredientInput, FlowLayout, etc.)  
│ └── structures/  
│ ├── Structure.h      # Shared interface for hash map & graph  
│ ├── graph/           # Bipartite graph implementation  
│ └── hashmap/         # Inverted hash map implementation  
├── tests/
├── .gitignore  
├── CMakeLists.txt  
└── README.md
```

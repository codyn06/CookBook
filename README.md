# CookBook
Find recipes using ingredients you have on hand.

## Workflow
### Setup
 - Navigate to a directory in which you will clone the repository.
 - Use the terminal and use the command ``git clone https://github.com/codyn06/CookBook``.
 - Download the dataset from [https://recipenlg.cs.put.poznan.pl/](https://recipenlg.cs.put.poznan.pl/).
 - Unzip the dataset into the project. This should create a directory called ``dataset/`` with a file named ``full_dataset.csv`` within.
### Contributing
 - Find an issue under the ``Issue`` tab found on the top bar of the GitHub.
 - Under ``Assignees`` in the right sidebar of the issue, assign yourself.
 - If applicable, click on the ``Parent`` issue located under the issue title.
 -  Under ``Development``, if there is no branch for the issue, create one and name it appropriately. 
 - In your code editor or IDE, navigate to the project and use command ``git checkout [branch name]``.
#### Notes
- Before starting work, ensure to ``git pull`` for the latest updates. (``git pull origin main`` if needed)
- Ensure to``git add [filepath or .]`` and git ``git commit -m "[message]"`` every time you make marginal progress.
- Use ``git push`` when your changes are ready to be pushed to the branch.
- Document all methods and functions in [this documentation](https://docs.google.com/document/d/1wpaZSOx3Bql3ahKisEiDF4Ub_wttGJqreJTHL9evK2c/edit?tab=t.4vus17tgb0ye) with a short description and their **input (parameters/arguments)** and **output (return value)**.
- Do not push directly to ``main`` with substantial changes. Instead, go to the ``Pull requests`` tab, and create a ``New pull request`` from the branch to main. Ensure that the changes are ready. Request a review from a teammate.
## Project Structure
```
CookBook/
├── dataset/                  # Raw dataset (gitignored — see Setup)
│   └── full_dataset.csv
├── src/
│   ├── main.cpp
│   ├── data/                 # CSV loading & parsing
│   │   ├── data.h
│   │   └── data.cpp
│   ├── structures/
│   │   ├── hashmap/          # Inverted hash map implementation
│   │   └── graph/            # Bipartite graph implementation
│   ├── gui/                  # Qt interface
│   └── benchmark/            # Runtime/memory comparison tools
├── tests/                    # Unit tests
├── .gitignore
├── CMakeLists.txt
└── README.md
```

- **``data/``** — Loads ``dataset/full_dataset.csv``, parses list-style fields, produces``Recipe`` structs for the data structures to consume.
- **``structures/hashmap/``** — Inverted hash map: ingredient → recipe IDs, with match scoring and top-N extraction.
- **``structures/graph/``** — Bipartite graph: recipe/ingredient nodes and edges, with match scoring and top-N extraction.
- **``gui/``** — Qt-based interface (ingredient input, data structure selection, results display).
- **``benchmark/``** — Compares runtime and memory usage between the hash map and graph implementations on the full dataset.

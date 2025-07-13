# Project Structure

```
seminar/
├── Jungnickel/
│   ├── lib/
│   ├── <projects>/
│   ├── Makefile
│   ├── newmain.sh
│   └── print_graph.py
├── .gitignore
└── README.md
```

**Note:**
This project (especially Jungnickel/Makefile) is intended to be run in a Bash environment.

---

## How to Compile

```bash
cd ./Jungnickel
make
```

This will compile all projects.

Each project has its own Makefile, so you can compile each one separately by running `make` in the corresponding directory.

```bash
bash newmain.sh <name>
```

This command will create a new project, initialized for convenience.

```bash
python print_graph.py <name>
```

You can visualize some graph written in adjacency matrix format.
You can write a matrix to a file by write_adjacent_matrix function.

---

## VS Code Settings

just a recommendation for code coloring ;p

<details>
<summary>Click to expand</summary>

```
"editor.acceptSuggestionOnEnter": "off",
"editor.tokenColorCustomizations": {
    "textMateRules": [
        {
            "scope": "entity.name.type",
            "settings": {
                "foreground": "#81C784"
            }
        },
        {
            "scope": "variable.other",
            "settings": {
                "foreground": "#879cb5",
                "fontStyle": "italic"
            }
        },
        {
            "scope": "variable.parameter",
            "settings": {
                "foreground": "#c9d9ed",
                "fontStyle": "italic"
            }
        },
        {
            "scope": "keyword",
            "settings": {
                "foreground": "#d07124"
            }
        }
    ]
}
```
</details>

---

RANK...ズレそうなので飛ばす
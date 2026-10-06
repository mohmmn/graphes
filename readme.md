# Graphes en C++ : DFS & BFS avec héritage

Mini-projet personnel (réalisé **sans IA**) qui relie deux cours : **C++ (programmation orientée objet)** et **algorithmique des graphes**.

Défis : implémenter une classe `Graph` de base en C++, dont héritent un graphe **orienté** (`OrientedGraph`) et un graphe **non orienté** (`NonOrientedGraph`), puis y appliquer les parcours **DFS** et **BFS**. Des modifications sur ce projets vont (peut être) être effectuées au cours du temps.

---

## Sommaire

1. [Objectif](#objectif)
2. [Notions révisées](#notions-révisées)
3. [Architecture du projet](#architecture-du-projet)
4. [Conception orientée objet](#conception-orientée-objet)
5. [Algorithmes de parcours](#algorithmes-de-parcours)
6. [Comment lancer le programme](#comment-lancer-le-programme)
7. [Exemple d'utilisation](#exemple-dutilisation)
8. [Pistes d'amélioration](#pistes-damélioration)

---

## Objectif

Mettre en pratique, sur un seul petit projet, ce qui a été vu en cours :

- côté **algorithmique** : représenter un graphe et le parcourir en profondeur et en largeur ;
- côté **C++** : structurer le code avec des classes, de l'héritage et du polymorphisme.

---

## Notions révisées

### Graphes & algorithmes

| Notion | Où c'est utilisé |
|---|---|
| Représentation d'un graphe par **liste d'adjacence** | Attribut `adjacencyList` de la classe `Graph` |
| Graphe **orienté** vs **non orienté** | Différence de comportement dans `addEdge()` |
| **DFS** (parcours en profondeur) | `Graph::dfs()` — pile / récursivité |
| **BFS** (parcours en largeur) | `Graph::bfs()` — file |
| Gestion des **sommets visités** | Tableau de booléens `visited` |
| Complexité en **O(V + E)** | Les deux parcours visitent chaque sommet et chaque arête une fois |

### C++ & programmation orientée objet

| Notion | Où c'est utilisé |
|---|---|
| **Classe** et **visibilité** (`private` / `protected` / `public`) | Classe `Graph` |
| **Héritage** | `OrientedGraph` et `NonOrientedGraph` héritent de `Graph` |
| **Méthode virtuelle** (`virtual`) et **polymorphisme** | `addEdge()` redéfinie dans chaque classe fille |
| **Classe abstraite** (méthode virtuelle pure `= 0`) | `Graph` ne peut pas être instanciée directement |
| **Constructeurs / destructeurs** | Initialisation du nombre de sommets, destruction propre |
| **Structures de donnée** : `vector`, `queue`, `stack` | Listes d'adjacence, parcours BFS / DFS |
| **Séparation `.h` / `.cpp`** | Déclarations et implémentations dans des fichiers distincts |

---

## Architecture du projet

```
.
├── headers/
│   ├── graph.h              # Classe abstraite de base
│   ├── orientedGraph.h      # Graphe orienté (hérite de Graph)
│   └── nonOrientedGraph.h   # Graphe non orienté (hérite de Graph)
├── src/
│   ├── Graph.cpp              # Implémentation commune + DFS / BFS
│   ├── OrientedGraph.cpp
│   ├── NonOrientedGraph.cpp
│   └── main.cpp               # Programme de test
├── Makefile
└── README.md
```

> Adapte l'arborescence si ton projet est organisé différemment (par exemple tout à la racine).

---

## Conception orientée objet

```
            ┌──────────────────────┐
            │   Graph (abstraite)  │
            │──────────────────────│
            │ # numberOfNodes         │
            │ # adjacencyList      │
            │──────────────────────│
            │ + addEdge() = 0      │ 
            │ + dfs(start)         │
            │ + bfs(start)         │
            │ + display()          │
            └──────────▲───────────┘
                       │ hérite
          ┌────────────┴─────────────┐
          │                          │
┌─────────┴──────────┐   ┌───────────┴────────────┐
│   OrientedGraph    │   │   NonOrientedGraph     │
│────────────────────│   │────────────────────────│
│ + addEdge(u, v)    │   │ + addEdge(u, v)        │
│   u → v seulement  │   │   u → v ET v → u       │
└────────────────────┘   └────────────────────────┘
```

**Pourquoi cette organisation ?**

- Tout ce qui est **commun** (stockage, DFS, BFS, affichage) est écrit **une seule fois** dans `Graph`.
- Seul ce qui **diffère** est redéfini dans les classes filles : la façon d'ajouter une arête.
  - Graphe orienté : on ajoute `v` dans la liste de `u`.
  - Graphe non orienté : on ajoute `v` dans la liste de `u` **et** `u` dans la liste de `v`.
- Les parcours DFS et BFS fonctionnent **sans modification** car ils parcourent les arrêtes. 

---

## Algorithmes de parcours

### DFS — Depth-First Search (parcours en profondeur)

- **Principe** : on s'enfonce le plus loin possible dans une branche avant de revenir en arrière.
- **Structure utilisée** : une pile implicitement via la récursivité.

```
dfs(s):
    marquer s comme visité
    afficher s
    pour chaque voisin v de s:
        si v n'est pas visité:
            dfs(v)
```

### BFS — Breadth-First Search (parcours en largeur)

- **Principe** : on explore les sommets niveau par niveau, du plus proche au plus éloigné.
- **Structure utilisée** : une file (`queue`).

```
bfs(s):
    marquer s comme visité
    enfiler s
    tant que la file n'est pas vide:
        u = défiler
        afficher u
        pour chaque voisin v de u:
            si v n'est pas visité:
                marquer v comme visité
                enfiler v
```

## Comment lancer le programme

Prérequis : `g++` supportant C++17 (sous Windows, MinGW — par exemple celui fourni avec CLion — ou MSYS2).

Depuis la racine du projet :

```bash
# 1. Compilation de tous les fichiers sources (graph, orientedGraph, nonOrientedGraph et main)
g++ -std=c++17 -Wall -Wextra src/*.cpp -o graph

# 2. Exécution
./graph        # Linux / macOS / Git Bash
graph.exe      # Invite de commandes Windows
```

> Sous PowerShell, `src/*.cpp` n'est pas développé automatiquement : liste les fichiers à la main
> (`g++ -std=c++17 -Wall -Wextra src/graph.cpp src/orientedGraph.cpp src/nonOrientedGraph.cpp src/main.cpp -o graph`)
> puis lance `.\graph.exe`.

Le programme `src/main.cpp` construit un graphe non orienté et un graphe orienté de 5 sommets, puis affiche pour chacun
sa liste d'adjacence, son nombre de sommets et d'arêtes, et ses parcours DFS / BFS :

```

**Sortie attendue (graphe non orienté ci-dessus) :**

```
DFS : 0 1 3 2 4
BFS : 0 1 2 3 4
```

On voit bien la différence : le DFS descend jusqu'à `3` avant de revenir vers `2`, tandis que le BFS visite d'abord tous les voisins de `0` (`1` et `2`).

---

## Pistes d'amélioration

- Ajouter des **poids** sur les arêtes (graphes pondérés), afin de connaître la distance d'un parcours.
- Ajouter des objets noeuds ?
- Calcul des **composantes connexes** (non orienté) et **fortement connexes** (orienté).
- Afficher une matrice d'adjacence d'un graphe
- Chargement d'un graphe depuis un **fichier**.

---

## Auteur

Mohamed Mimouni
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
## Arbre couvrant de poids minimal :

Un ACPM (arbre couvrant de poids minimal) est un graphe obtenu en déduisant les arrêtes "lourdes" pour ne garder que les plus "légères" qui permettent de couvrir tout le graphe, c'est à dire conserver la connexité.

Il a quelques particularités notamment : 
1- Le nombre de noeuds d'arbre couvrant de poids minimal est le même que celui du graphe de base tel que : 
ACPM(V) = Graph(V)

2- Le nombre d'arrêtes du graphe couvrant de poids minimal est égal au nombre de noeuds - 1 du graphe de base tel que : ACPM(E) = Graph(V) - 1 

3- Un ACPM ne contient pas de cycles

4- Il est possible qu'il y ai différents arbres couvrant de poids minimaux au sein d'un même graphe, il suffirait d'interchanger deux arrêtes **de même poids** qui conservent la règle 2 et 3 pour en obtenir un autre.

Il existe plusieurs algorithmes qui permettent de déduire l'arbre couvrant de poids minimal d'un graphe, nous verrons ici Kruskal & Prim, et on les comparera. 

## Algorithme de Kruskal 

**Principe :** Si on connaît le poids de chaque arête du graphe, alors on peut les trier par ordre croissant et choisir les plus petites, tout en évitant de créer des cycles, jusqu'à obtenir un arbre couvrant de poids minimal (ACPM).

**Algo :**
- On dispose d'un tableau trié contenant les arêtes du graphe.
- Tant que le nombre d'arêtes de l'ACPM est inférieur à \(V - 1\) et que le tableau n'est pas entièrement parcouru :
  - On prend la prochaine arête du tableau.
  - Si elle ne crée pas de cycle, on l'ajoute à l'ACPM.
  - Sinon, on la refuse et on passe à la suivante.
- On retourne l'ACPM.

**Comment l'implémenter ?**

**Étape 1 :** Écrire une méthode qui trie les arêtes du graphe selon leur poids et les place dans un tableau par ordre croissant.

**Étape 2 :** Définir des méthodes Union() et Find() ainsi qu'un tableau pour gérer les groupes de sommets et détecter les cycles. C'est la partie la plus tricky mais une fois qu'on comprends le principe c'est très facile.

**Étape 3 :** Créer un nouveau graphe contenant les mêmes sommets, mais aucune arête. Ce graphe servira à construire l'ACPM.

**Étape 4 :** Initialiser une boucle principale qui parcourt le tableau trié tant que le nombre d'arêtes de l'ACPM est inférieur à \(V - 1\) et que toutes les arêtes n'ont pas été parcourues.

**Étape 5 :** Pour chaque arête, utiliser *Union-Find* pour vérifier si ses deux sommets appartiennent déjà au même groupe. Si c'est le cas, l'ajout de l'arête créerait un cycle.

**Étape 6 :** Si les deux sommets appartiennent à des groupes différents, ajouter l'arête à l'ACPM et fusionner leurs groupes avec la méthode Union(). Sinon, passer à l'arête suivante.

**Étape 7 :** Retourner l'ACPM obtenu.

Inconvénient :

Kruskal est un algorithme "Aveugle", il n'a pas vraiment de visibilité sur l'ensemble du graphe.

Kruskal n'est pas très efficace en terme de complexité algorithmique quand on travail sur des graphes très denses, c'est pour cela qu'on va s'attaquer à Prim.
### 

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
# Graphes en C++ : parcours, héritage et arbres couvrants

Mini-projet personnel (réalisé **sans IA**) qui relie deux cours : **C++ (programmation orientée objet)** et **algorithmique des graphes**.

Défis : implémenter une classe `Graph` de base en C++, dont héritent un graphe **orienté** (`OrientedGraph`) et un graphe **non orienté** (`NonOrientedGraph`), y appliquer les parcours **DFS** et **BFS**, puis calculer un **arbre couvrant de poids minimal** (ACPM) avec l'algorithme de **Kruskal**. Le projet continue d'évoluer au fil du temps (Prim est la prochaine étape).

---

## Sommaire

1. [Objectif](#objectif)
2. [Notions révisées](#notions-révisées)
3. [Architecture du projet](#architecture-du-projet)
4. [Conception orientée objet](#conception-orientée-objet)
5. [Algorithmes de parcours](#algorithmes-de-parcours)
6. [Arbre couvrant de poids minimal](#arbre-couvrant-de-poids-minimal)
7. [Algorithme de Kruskal](#algorithme-de-kruskal)
8. [Comment lancer le programme](#comment-lancer-le-programme)
9. [Exemple d'utilisation](#exemple-dutilisation)
10. [Pistes d'amélioration](#pistes-damélioration)

---

## Objectif

Mettre en pratique, sur un seul petit projet, ce qui a été vu en cours :

- côté **algorithmique** : représenter un graphe pondéré, le parcourir en profondeur et en largeur, et en extraire un arbre couvrant de poids minimal ;
- côté **C++** : structurer le code avec des classes, de l'héritage et du polymorphisme.

---

## Notions révisées

### Graphes & algorithmes

| Notion | Où c'est utilisé |
|---|---|
| Représentation d'un graphe par **liste d'adjacence** | Attribut `adjacencyList` de la classe `Graph` |
| Graphe **pondéré** (une distance par arête) | Structure `Edge { to, dist }` |
| Graphe **orienté** vs **non orienté** | Différence de comportement dans `addEdge()` |
| **DFS** (parcours en profondeur) | `Graph::DFS()` et `Graph::dfsRec()` — récursivité |
| **BFS** (parcours en largeur) | `Graph::BFS()` — file |
| Gestion des **sommets visités** | Tableau de booléens `visited` |
| Complexité en **O(V + E)** | Les deux parcours visitent chaque sommet et chaque arête une fois |
| **Tri par insertion** | `Graph::sortFullEdges()` — tri des arêtes par poids croissant |
| **Union-Find** (détection de cycles) | Fonctions `find()`, `unite()` et `initParents()` |
| **Arbre couvrant de poids minimal** | `Graph::Kruskal()` qui renvoie un `ACPM` |

### C++ & programmation orientée objet

| Notion | Où c'est utilisé |
|---|---|
| **Classe** et **visibilité** (`private` / `protected` / `public`) | Classe `Graph` |
| **Héritage** (sur plusieurs niveaux) | `OrientedGraph` et `NonOrientedGraph` héritent de `Graph`, `ACPM` hérite de `NonOrientedGraph` |
| **Méthode virtuelle** (`virtual`) et **polymorphisme** | `addEdge()` redéfinie dans chaque classe fille |
| **Classe abstraite** (méthode virtuelle pure `= 0`) | `Graph` ne peut pas être instanciée directement |
| **Constructeurs / destructeurs** | Initialisation du nombre de sommets, destruction propre |
| **Structures** (`struct`) | `Edge` et `FullEdge` |
| **Références** et **pointeurs** (`&`, `*`, `this`) | Passage de `parents` par référence, `*this` dans `Kruskal()` |
| **Déclaration anticipée** (*forward declaration*) | `class ACPM;` dans `graph.h` pour éviter une inclusion circulaire |
| **Structures de données** : `vector`, `queue` | Listes d'adjacence, parcours BFS, tableau `parents` |
| **Séparation `.h` / `.cpp`** | Déclarations et implémentations dans des fichiers distincts |

---

## Architecture du projet

```
.
├── headers/
│   ├── graph.h              # Classe abstraite de base + structs Edge / FullEdge
│   ├── orientedGraph.h      # Graphe orienté (hérite de Graph)
│   ├── nonOrientedGraph.h   # Graphe non orienté (hérite de Graph)
│   └── acpm.h               # Arbre couvrant de poids minimal (hérite de NonOrientedGraph)
├── src/
│   ├── graph.cpp            # Implémentation commune : DFS / BFS, tri, Union-Find, Kruskal
│   ├── orientedGraph.cpp
│   ├── nonOrientedGraph.cpp
│   ├── acpm.cpp
│   └── main.cpp             # Programme de test
└── readme.md
```

---

## Conception orientée objet

```
             ┌──────────────────────────┐
             │    Graph (abstraite)     │
             │──────────────────────────│
             │ # numberOfNodes          │
             │ # adjacencyList          │
             │──────────────────────────│
             │ + addEdge(u, v, d) = 0   │
             │ + DFS(start)             │
             │ + BFS(start)             │
             │ + sortFullEdges()        │
             │ + Kruskal() : ACPM       │
             └────────────▲─────────────┘
                          │ hérite
            ┌─────────────┴──────────────┐
            │                            │
┌───────────┴──────────┐   ┌─────────────┴────────────┐
│    OrientedGraph     │   │     NonOrientedGraph     │
│──────────────────────│   │──────────────────────────│
│ + addEdge(u, v, d)   │   │ + addEdge(u, v, d)       │
│   u → v seulement    │   │   u → v ET v → u         │
└──────────────────────┘   └─────────────▲────────────┘
                                         │ hérite
                           ┌─────────────┴────────────┐
                           │           ACPM           │
                           │──────────────────────────│
                           │ n sommets, V − 1 arêtes  │
                           └──────────────────────────┘
```

**Pourquoi cette organisation ?**

- Tout ce qui est **commun** (stockage, DFS, BFS, tri, Kruskal) est écrit **une seule fois** dans `Graph`.
- Seul ce qui **diffère** est redéfini dans les classes filles : la façon d'ajouter une arête.
  - Graphe orienté : on ajoute `v` dans la liste de `u`.
  - Graphe non orienté : on ajoute `v` dans la liste de `u` **et** `u` dans la liste de `v`.
- Les parcours DFS et BFS fonctionnent **sans modification** dans les deux cas, car ils se contentent de suivre les arêtes stockées.
- Un ACPM est un graphe **non orienté** : `ACPM` hérite donc de `NonOrientedGraph` et réutilise directement son `addEdge()` et son `getNumberOfEdges()`.

---

## Algorithmes de parcours

### DFS — Depth-First Search (parcours en profondeur)

- **Principe** : on s'enfonce le plus loin possible dans une branche avant de revenir en arrière.
- **Structure utilisée** : une pile, implicitement, via la récursivité.

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

---

## Arbre couvrant de poids minimal

Un ACPM (arbre couvrant de poids minimal) d'un graphe connexe, non orienté et pondéré est un sous-graphe obtenu en écartant les arêtes « lourdes » pour ne garder que les plus « légères » qui permettent de **relier tous les sommets**, c'est-à-dire de conserver la connexité, avec un **poids total minimal**.

Il a quelques particularités :

1. Il contient **tous les sommets** du graphe de base (c'est le sens de « couvrant ») : `ACPM(V) = Graph(V)`.
2. Il contient exactement **V − 1 arêtes** : `ACPM(E) = Graph(V) − 1`.
3. Il ne contient **aucun cycle** (c'est un arbre).
4. Un même graphe peut avoir **plusieurs ACPM différents** lorsque certaines arêtes ont le même poids : on peut parfois échanger une arête contre une autre **de même poids** tout en respectant les règles 2 et 3. Si tous les poids sont distincts, l'ACPM est unique.

Il existe plusieurs algorithmes pour construire l'arbre couvrant de poids minimal d'un graphe. On verra ici **Kruskal** et **Prim**, puis on les comparera.

---

## Algorithme de Kruskal

**Principe :** si on connaît le poids de chaque arête du graphe, on peut les trier par ordre croissant et choisir les plus petites, tout en évitant de créer des cycles, jusqu'à obtenir un arbre couvrant de poids minimal.

**Algo :**

- On dispose d'un tableau trié contenant les arêtes du graphe.
- Tant que le nombre d'arêtes de l'ACPM est inférieur à `V − 1` et que le tableau n'est pas entièrement parcouru :
  - on prend la prochaine arête du tableau ;
  - si elle ne crée pas de cycle, on l'ajoute à l'ACPM ;
  - sinon, on la refuse et on passe à la suivante.
- On retourne l'ACPM.

**Comment l'implémenter ?**

**Étape 1 :** écrire une méthode qui trie les arêtes du graphe selon leur poids et les place dans un tableau par ordre croissant (`sortFullEdges()`).

**Étape 2 :** définir les fonctions `find()` et `unite()`, ainsi qu'un tableau `parents`, pour gérer les groupes de sommets et détecter les cycles. C'est la partie la plus délicate, mais une fois le principe compris, c'est très simple :

- `parents[x]` désigne le sommet « au-dessus » de `x` dans son groupe ; si `parents[x] == x`, alors `x` est le chef (la racine) du groupe ;
- `find(x)` remonte de parent en parent jusqu'au chef ;
- `unite(x, y)` accroche le chef d'un groupe sous le chef de l'autre.

**Étape 3 :** créer un nouveau graphe contenant les mêmes sommets, mais aucune arête. Ce graphe servira à construire l'ACPM.

**Étape 4 :** écrire une boucle principale qui parcourt le tableau trié tant que le nombre d'arêtes de l'ACPM est inférieur à `V − 1` et que toutes les arêtes n'ont pas été parcourues.

**Étape 5 :** pour chaque arête, utiliser `find()` pour vérifier si ses deux sommets appartiennent déjà au même groupe. Si c'est le cas, l'ajout de l'arête créerait un cycle.

**Étape 6 :** si les deux sommets appartiennent à des groupes différents, ajouter l'arête à l'ACPM et fusionner leurs groupes avec `unite()`. Sinon, passer à l'arête suivante.

**Étape 7 :** retourner l'ACPM obtenu.

**Limites :**

- Kruskal raisonne arête par arête sans construire un arbre unique au fur et à mesure : pendant l'exécution, on a une **forêt** de petits morceaux qui finissent par se rejoindre. Prim, au contraire, fait grandir un seul arbre à partir d'un sommet de départ.
- Sa complexité est dominée par le **tri des arêtes** (O(E log E) avec un tri efficace ; le tri par insertion utilisé ici est en O(E²)). Sur des graphes très **denses** (E proche de V²), Prim devient plus intéressant : c'est pour cela qu'on va s'y attaquer ensuite.

---

## Comment lancer le programme

Prérequis : `g++` supportant C++17 (sous Windows, MinGW — par exemple celui fourni avec CLion — ou MSYS2).

Depuis la racine du projet :

```bash
# 1. Compilation de tous les fichiers sources (graph, orientedGraph, nonOrientedGraph, acpm et main)
g++ -std=c++17 -Wall -Wextra src/*.cpp -o graph

# 2. Exécution
./graph        # Linux / macOS / Git Bash
graph.exe      # Invite de commandes Windows
```

> Sous PowerShell, `src/*.cpp` n'est pas développé automatiquement : liste les fichiers à la main
> (`g++ -std=c++17 -Wall -Wextra src/graph.cpp src/orientedGraph.cpp src/nonOrientedGraph.cpp src/acpm.cpp src/main.cpp -o graph`)
> puis lance `.\graph.exe`.

---

## Exemple d'utilisation

Le programme `src/main.cpp` construit trois graphes de 5 sommets :

1. un graphe **non orienté** ;
2. un graphe **orienté** ;
3. un graphe **non orienté** sur lequel on lance **Kruskal**.

Pour chacun, il affiche la liste d'adjacence (sous la forme `voisin(distance)`), le nombre de sommets et d'arêtes, et les parcours DFS / BFS.

**Parcours sur le graphe non orienté :**

```
Liste d'adjacence :
  0 -> 1(4) 2(1)
  1 -> 0(4) 3(2)
  2 -> 0(1) 4(5)
  3 -> 1(2)
  4 -> 2(5)
DFS depuis 0      : 0 1 3 2 4
BFS depuis 0      : 0 1 2 3 4
```

On voit bien la différence : le DFS descend jusqu'à `3` avant de revenir vers `2`, tandis que le BFS visite d'abord tous les voisins de `0` (`1` et `2`).

**Kruskal :** à partir du graphe suivant (7 arêtes) :

```
0-1 (4)   0-2 (1)   1-2 (2)   1-3 (5)
2-3 (8)   3-4 (3)   2-4 (9)
```

l'ACPM obtenu contient les arêtes `0-2`, `1-2`, `3-4` et `1-3`, pour un poids total de **11** :

```
Liste d'adjacence :
  0 -> 2(1)
  1 -> 2(2) 3(5)
  2 -> 0(1) 1(2)
  3 -> 4(3) 1(5)
  4 -> 3(3)
Nombre de sommets : 5
Nombre d'aretes   : 4
```

L'arête `0-1` (poids 4) est refusée : au moment où on la considère, `0` et `1` sont déjà reliés via `2`, donc l'ajouter créerait un cycle.

---

## Pistes d'amélioration

- Implémenter l'algorithme de **Prim** et le comparer à Kruskal.
- Gérer les graphes **non connexes** (Kruskal renvoie alors une **forêt** couvrante, avec moins de V − 1 arêtes).
- Optimiser l'Union-Find (**compression de chemin**, **union par rang**).
- Remplacer le tri par insertion par un tri plus efficace (tri fusion, tri rapide).
- Ajouter des objets nœuds ?
- Calcul des **composantes connexes** (non orienté) et **fortement connexes** (orienté).
- Afficher la **matrice d'adjacence** d'un graphe.
- Chargement d'un graphe depuis un **fichier**.

---

## Auteur

Mohamed Mimouni

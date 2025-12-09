# Kruskalův vs. Jarníkův algoritmus

Semestrální práce B6B36PCC - Martin Kindl @ ČVUT

**Implementace algoritmů pro hledání minimální kostry souvislého, neorientovaného grafu s ohodnocenými hranami.**

---

## Popis řešených algoritmů
### Kruskalův algoritmus
Algoritmus pracuje s hranami grafu:
1. Seřadí všechny hrany grafu podle váhy od nejmenší po největší.
2. Postupně prochází seřazené hrany a přidává je do kostry pouze tehdy, pokud přidání hrany nevytvoří cyklus.
3. Pro efektivní detekci cyklů se využívá datová struktura **Union-Find** (Disjoint Set Union), která sleduje, zda jsou dva vrcholy již propojeny.

### Primův algoritmus
Algoritmus pracuje s vrcholy:
1. Začíná v libovolném vrcholu.
2. V každém kroku vybere hranu s nejmenší vahou, která spojuje vrchol již zahrnutý v kostře s vrcholem, který v kostře ještě není.
3. Tento postup se opakuje, dokud nejsou připojeny všechny vrcholy.

## Popis implementace

### Implementované třídy/moduly
- Třída **Graph** (`Graph.hpp`,`Graph.cpp`) - reprezentuje graf pomocí seznamu hran. Obsahuje metody pro přidávání hran a získání seznamu hran.
  - Struktura **Edge** - reprezentuje (ohodnocenou) hranu grafu.
- Třída **UnionFind** (`UnionFind.hpp`,`UnionFind.cpp`) - datová strukturu Union-Find (Disjoint Set) pro detekci cyklů.
- Modul **MST** (`MST.hpp`,`MST.cpp`) obsahující implementace Kruskalova a Primova algoritmu.

#### Třída Graph
- Vnitřní struktura **Edge**:
  - `u` a `v` - vrcholy hrany.
  - `weight` - váha (cena) hrany.
- Atributy:
  - `edges` - Množina hran.
  - `numVertices` - Množina vrcholů.
- Metody:
  - `static getRandomGraph(numEdges, maxWeight)` - generuje náhodný graf souvislý graf s `numEdges` hranami a maximální váhou `maxWeight`.
  - `addEdge(u, v, weight)` - přidá hranu mezi vrcholy `u` a `v` s danou váhou `weight`.
  - `getEdges()` - vrátí množinu hran
  - `hasEdge(u, v)` - zkontroluje, zda hrana mezi vrcholy `u` a `v` existuje
  - `getVertexCount()` - vrátí počet vrcholů

#### Třída UnionFind
- Metody:
  - `find(x)` - vrátí reprezentanta množiny obsahující prvek `x`.
  - `addElement(x)` - přidá nový prvek `x` do struktury.
  - `unite(x, y)` - spojí množiny obsahující prvky `x` a `y`.
  - `getSetCount()` - vrátí počet disjunktních množin.

#### Modul MST
- Funkce:
  - `kruskal(graph)` - implementace Kruskalova algoritmu pro nalezení minimální kostry grafu.
  - `prim(graph)` - implementace Primova algoritmu pro nalezení minimální kostry grafu.

### Sestavení (build) programu
V adresáři:
```bash
cmake . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

## Ovládání programu

Ovládání programů je možné pomocí argumentů v příkazové řádce.

### Spuštění výpočtů

Očekávané pořadí argumentů je následující:
1. Flag(y) nebo jejich kombinace (viz tabulka níže)
2. Název souboru, případně počet hran pro generování grafu.
```shell
  ./kxp [flag(y)] [název souboru]
```

Spuštění bez flagů vypočítá minimální kostru pomocí obou algoritmů pro graf zadaný v souboru `název_souboru`.

| Flag               | Druhý argument            | Popis                                          |
|--------------------|---------------------------|------------------------------------------------|
| `--help`           | Žádný                     | Zobrazí nápovědu k použití programu.           |
| `-k`/`--kruskal`   | Vstupní soubor s grafem*  | Spustí pouze Kruskalův algoritmus.             |
| `-p`/`--prim`      | Vstupní soubor s grafem*  | Spustí pouze Jarníkův (Primův) algoritmus.     |
| `-s`/`--silent`    | Vstupní soubor s grafem*  | Vypíše pouze čas výpočtu (bez koster)          |
| `-f`/`--formatted` | Vstupní soubor s grafem*  | Vypíše výsledné kostry v přehlednějším formátu |

\*Název vstupního souboru (např.: `./graph.txt` nebo `./data/myGraph`, apod.)

#### Vstupní soubor
Požadovaný formát vstupního souboru je seznam hran (edge list) ve tvaru:"
```
<u1> <v1> <váha1>
<u2> <v2> <váha2>
...
<un> <vn> <váhan>
```

> [!Warning]
> Program **není** optimalizován pro prácí s kódováním `UTF-16`. Při práci na **Windows** použijte konverzi do UTF-8 nebo ASCII:
```shell
  Get-Content .\graph.txt | Set-Content -Encoding utf8 graph-utf8.txt
```

### Spuštění generátoru náhodných grafů
Generátor je dostupný použitím flagu `--generate` nebo `-g`. Vyžaduje dva povinné argumenty:
- Počet hran - kladné celé číslo.
- Hustotu grafu - čílso mezi 0 a 1.

```shell
  ./kxp --generate [počet hran] [hustota grafu]
```
Při použití chybných hodnot argumentů program použije výchozí hodnoty (20 hran a hustota 0.5).

Při jiné chybě program skončí s chybou `Invalid arguments`.

## Testování
V projektu jsou obsaženy jednotkové testy pro klíčové komponenty:
- Testy pro třídu **Graph** (`tests/TestGraph.cpp`)
  - Součástí jsou testy generátoru náhodných grafů.
- Testy pro třídu **UnionFind** (`tests/TestUnionFind.cpp`)
- Testy pro modul **MST** (`tests/TestMST.cpp`)

> [!Note]
> Některé jednotkové testy mohou být časově náročné - např. kontrola zda je kostra minimální má složitost O(n²).

## Srovnání algoritmů
> [!Tip]
> Použité grafy jsou k nalezení v adresáři `/tests/graphs`.

> [!Note]
> Program byl sestaven pomocí CMake v Release módu. A spuštěn na Intel Core Ultra 5 + 32GM RAM

Srovnání provedeme na několika grafech o různé velikosti a hustotě hran.

### 1. Kompletní grafy

> Relativní odchylka měření, vypočtená ze vzorku 20 opakovaných běhů, činí 6,24 % u Kruskalova algoritmu a 4,64 % u Jarníkova algoritmu.

| Graf                | Počet vrcholů | Počet hran  | Kruskalův čas | Jarníkův čas |
|---------------------|---------------|-------------|---------------|--------------|
| `complete-200.txt`  | 200           | 39 800      | ~3ms          | ~9ms         |
| `complete-400.txt`  | 400           | 159 600     | ~28ms         | ~40ms        |
| `complete-600.txt`  | 600           | 359 400     | ~100ms        | ~151ms       |
| `complete-800.txt`  | 800           | 639 200     | ~200ms        | ~315ms       |
| `complete-1000.txt` | 1000          | 999 000     | ~326ms        | ~462ms       |

Výše uvedené měření si můžete ověřit pomocí příkazu ` ./kxp -s tests/complete-n.txt `, například:
```shell
  ./kxp -s tests/complete-800.txt
```

### 2. Velmi husté grafy (hustota ~0.9)

> [!Important]
> **Použité grafy nejsou součástí repozitáře kvůli jejich velikosti. Lze je vygenerovat pomocí generátoru.**

| Počet hran | Počet vrcholů | Kruskalův čas | Jarníkův čas |
|------------|---------------|---------------|--------------|
| 100 000    | 472           | ~9ms          | ~7ms         |
| 1 000 000  | 1 492         | ~89ms         | ~449ms       |
| 10 000 000 | 4 715         | ~971ms        | ~4 578ms     |

### 3. Husté grafy (hustota ~0.1)

| Počet hran | Počet vrcholů | Kruskalův čas | Jarníkův čas |
|------------|---------------|---------------|--------------|
| 100 000    | 1 415         | ~15ms         | ~58ms        |
| 1 000 000  | 4 473         | ~93ms         | ~599ms       |
| 10 000 000 | 14 143        | ~919ms        | ~7 257ms     |

### 4. Řídké grafy (hustota ~0.001)

| Počet hran | Počet vrcholů | Kruskalův čas | Jarníkův čas |
|------------|---------------|---------------|--------------|
| 100 000    | 14 143        | ~27ms         | ~127ms       |
| 1 000 000  | 44 722        | ~206ms        | ~1 581ms     |
| 10 000 000 | 141 422       | ~3 604ms      | ~29 455ms    |

## Zdroje

**Kruskalův algoritmus:**
- [GeeksForGeeks - Kruskal's Minimum Spanning Tree Algorithm](https://www.geeksforgeeks.org/dsa/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/)
- [W3Schools - DSA - Kruskal's Algorithm](https://www.w3schools.com/dsa/dsa_algo_mst_kruskal.php)
- [J. Tišer - Teorie grafů (Graph2019.pdf)](https://moodle.fel.cvut.cz/pluginfile.php/491011/course/section/77327/Graph2019.pdf?time=1733849371628)

**Jarníkův algoritmus:**
- [Wikipedia - Jarníkův algoritmus](https://cs.wikipedia.org/wiki/Jarn%C3%ADk%C5%AFv_algoritmus)
- [GeeksForGeeks - Prim's MST](https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/)

**Datová struktura Union-Find:**
- [GeeksForGeeks - Introduction to disjoint set data structure](https://www.geeksforgeeks.org/dsa/introduction-to-disjoint-set-data-structure-or-union-find-algorithm/)

**Další:**
- [Rishabh Singh - Heap Data Structure and Priority Queue in C++](https://medium.com/@RobuRishabh/heap-data-structure-and-priority-queue-in-c-d2fe7a569c86)

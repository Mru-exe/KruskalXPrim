# Kruskalův vs. Jarníkův algoritmus {#custom-id}

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

## Popis rešení

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

## Ovládání programu

Ovládání programů je možné pomocí argumentů v příkazové řádce.

### CLI Argumenty

Očekávané pořadí argumentů je následující:
1. Flag(y) nebo jejich kombinace (viz tabulka níže)
2. Druhý (hlavní) argument - název souboru, případně počet hran pro generování grafu.
```shell
  ./kxp [flag(y)] [druhý_argument]
```

Spuštění bez flagů vypočítá minimální kostru pomocí obou algoritmů pro graf zadaný v souboru `název_souboru`.

| Flag               | Vyžaduje druhý argument   | Popis                                          |
|--------------------|---------------------------|------------------------------------------------|
| `--help`           | Žádný                     | Zobrazí nápovědu k použití programu.           |
| `-k`/`--kruskal`   | Vstupní soubor s grafem*  | Spustí pouze Kruskalův algoritmus.             |
| `-p`/`--prim`      | Vstupní soubor s grafem*  | Spustí pouze Jarníkův (Primův) algoritmus.     |
| `-s`/`--silent`    | Vstupní soubor s grafem*  | Vypíše pouze čas výpočtu (bez koster)          |
| `-f`/`--formatted` | Vstupní soubor s grafem*  | Vypíše výsledné kostry v přehlednějším formátu |
| `-g`/`--generate`  | Počet hran (výchozí = 20) | Vygeneruje náhodný souvislý graf               |

\*Název vstupního souboru (např.: `./graph.txt` nebo `./data/myGraph`, apod.)

### Vstupní soubor
Požadovaný formát vstupního souboru je seznam hran (edge list) ve tvaru:"
```
<u1> <v1> <váha1>
<u2> <v2> <váha2>
...
<un> <vn> <váhan>
```

**Upozornění:** Program **není** optimalizován pro prácí s kódováním `UTF-16`. Při práci na windows použijte konverzi do **UTF-8** nebo **ASCII**:
```shell
  Get-Content .\graph.txt | Set-Content -Encoding utf8 graph-utf8.txt
```

//TODO:
### Testování
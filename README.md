# Filmu katalogas (C++)

## Paskirtis
Konsoline programa, leidzianti tvarkyti filmu kataloga: prideti, perziureti, redaguoti, salinti, ieskoti ir rikiuoti filmus. Duomenys saugomi tekstiniame faile `filmai.txt`.

## Failai
- `filmu_katalogas.cpp` - pagrindinis programos kodas.
- `filmai.txt` - duomenu failas (sukuriamas automatiskai, jei nerastas, su 15 pradiniu irasu). Formatas: `Pavadinimas;Zanras;Metai;Rezisierius;Ivertinimas`.
- `README.md` - sis aprasas.

## Kompiliavimas
```
g++ -std=c++17 -O2 -o filmu_katalogas filmu_katalogas.cpp
```

## Paleidimas
```
./filmu_katalogas
```
(Windows: `filmu_katalogas.exe`)

## Funkcijos
- `nuskaitytiIsFailo` - nuskaito duomenis is `filmai.txt`.
- `issaugotiIFaila` - iraso visus duomenis i faila (kvieciama po kiekvieno pakeitimo).
- `sukurtiPradiniFaila` - sukuria pradini faila su 15 irasu.
- `rodytiVisus`, `rodytiVienaFilma` - Read operacijos.
- `pridetiFilma` - Create.
- `redaguotiFilma` - Update.
- `salintiFilma` - Delete.
- `paieska` - paieska pagal zanra arba rezisieriu.
- `rikiavimas` - rikiavimas pagal ivertinima arba metus.

## Meniu
Programos paleidimo metu rodomas meniu su pasirinkimais 0-7. Naudojamas `while` ciklas su `switch` viduje.

**FOLDERUL "Tema 1" TREBUIE PUS IN FOLDERUL "Source" DIN ARHIVA DIN "utils"**

Geometrie:
Astronaut: triunghi echilateral verde
Platforma de stationare: dreptunghi rosu
Plaforma de reflexie: dreptunghi albastru
Platforma finala: dreptunghi verde
Asteroid1: cerc galben cu rotatie
Asteroid2: cerc mov cu translatie
Asteroid3: cerc roz cu scalare

Marginile ferestrei le-am considerat drept platfome de stationare. Cand astronautul ar iesi din fereastra, este
asezat pe margine si orientat corespunzator.

Coliziunile cu asteroizii le-am tratat la fel ca in link-ul dat. Verific ca distanta dintre centru astronautului
si centrul astronautului este mai mica decat suma razelor celor doua. Pentru asteroizi raza este salvata in variabile,
iar pentru astronaut, "raza" este 2 * inaltime / 3, asa cum ar fi daca am inconjura triunghiul cu un cerc imaginar.

Pentru coliziunea cu platformele, am verificat ca coordonatele centrului astronautului + "raza" (2 * inalime / 3) sa 
se afle pe marginile platformelor. Pentru reflexie am negat componenta pasului corespunzatoare directiei din care venea
astronautul. De exemplu, daca astronautul vine de jos si face coliziune cu platforma de reflexie, voi nega componenta
y a pasului de miscare al astronautului.
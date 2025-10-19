Projekt ICP 2023/2024 - Simulátor robotů

Autoři:
Josef Susík (xsusik00)
Vladyslav Tverdokhlib (xtverd01)

Popis programu:
Po spuštění program požádá uživatele o načtení JSON souboru. Poté co uživatel zvolí validní JSON soubor se načte simulace v zastaveném stavu. Uživatel může přidat roboty, či překážky poté spustit simulaci.
Autonomní roboti mají statickou velikost, zatímco u robota kterého ovládá uživatel, lze změnit. Uživatelem ovládaný robot je vždy růžový. U autonomních robotů lze měnit barvu.
Překážky jsou vždy červené čtverce, lze však zvolit jejich velikost a úhel otočení.

Příkazy makefilu:
make         = přeloží program (poté se nachází se složce src/)
make run     = přeloží program a spustí simulaci
make clean   = vymaže vygenerované soubory
make pack    = vytvoří komprimovaný soubor
make doxygen = spustí doxygen a vytvoří dokumentaci

Odevzdané soubory:
README.txt
Makefile
doc/Doxyfile

examples/example1.json
examples/.json

src/icp.pro
src/main.cpp
src/mainwindow.cpp
src/mainwindow.h
src/mainwindow.ui
src/obstacle.cpp
src/obstacle.h
src/robot.cpp
src/robot.h
src/simulation.cpp
src/simulation.h
src/userRobot.cpp
src/userRobot.h
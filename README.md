# Non-Gravitar
Progetto d'esame del corso di programmazione (a.a 2018/2019) basato sul gioco "Gravitar" con caratteristiche diverse rispetto all'originale.

** Differenze **
- Nessuna gravità
- Generazione del terreno e strutture a runtime
- Aggiunte tipologie di bunker con varie modalità d'attacco
- Aggiunte tipologie di carburante con varie quantità di rifornimento

** Differenze di piattaforma **
- Colori supportati su terminale se eseguito su piattaforme che supportano i codici di escape ANSI, altrimenti risulteranno in bianco e nero
	- su Windows i colori non sono supportati a partire da e versioni successive a Windows XP e precenti a Windows 10 Anniversary Update
	- su piattaforme non Windows, il gioco funzionerà visualmente adeguatamente solo se i codici di escape ANSI sono supportati dal terminale

# Funzionamento
Il giocatore controlla una navicella che può muovere utilizzando le freccie direzionali oppure i tasti W A S D ( tasti e direzioni associati alle relative frecce direzionali ).
Il movimento della navicella consuma carburante, che può essere ricaricato da taniche di carburante generate nei pianeti.
Il gioco inizia in una schermata di un sistema solare nel quale sono presenti dei pianeti che il giocatore può "invadere" muovendosi con la navicella verso il pianeta stesso.
Il gioco cambia dunque dalla visuale del sistema solare a quella del pianeta, in questa visuale viene generato casualmente il terreno dove sono presenti bunker che il giocatore deve distruggere e taniche di carburante che il giocatore deve raccogliere.
Per distruggere i Bunker il giocatore può sparare nella direzione di movimento utilizzando il tasto F e per raccogliere il carburante il tasto R utilizzando il raggio traente.
Durante lo spostamento della navicella, essa potrebbe collidere contro il terreno o i bunker stessi, causando danni mortali alla navicella.
I bunker esistono di varie tipologie, con diverse modalità di attacco, ed i carburanti possono fornire diverse quantità di rifornimenti.
Nella visuale del pianeta andando a sinistra/destra dello schermo è visualizzata la parte precedente/successiva del pianeta durante lo spostamento della navicella.
Il giocatore può uscire da un pianeta in qualsiasi momento dirigendosi verso il cielo del pianeta, ritornando nel punto del sistema solare, da cui era entrato nel pianeta.
Se il giocatore esce dal pianeta quando i bunker sono stati tutti distrutti, il pianeta sarà distrutto e non lo potrà più rivisitare.
Se il giocatore ha distrutto tutti i pianeti del sistema solare, la navicella si dirigerà al centro di esso e si trasferirà in un altro dove saranno generati altri pianeti.
Il gioco termina quando la vita del giocatore scende a zero oppure quando esaurisce il carburante.

# Piattaforme
Attualmente è garantito il suo funzionamento su piattaforme Windows con ambiente di compilazione MinGW64, ma potrebbe funzionare anche su altre piattaforme come ad esempio linux con GCC (G++).

# Installazione
Il gioco richiede:
 - librerie standard C/C++,
 - libreria non standard conio ( solo per kbhit() e getch() )
 - librerie Windows API (Windows.h) se viene compilato su windows.

** Prerequisiti **
- Piattaforma Windows ( funzionamento non testato su altre non Windows ma potrebbe funzionare se supportano i codici ESCAPE su terminale )
- Installazione di un ambiente di compilazione ( consigliato e sviluppato con [MinGW64](https://mingw-w64.org) e fornisce libreria conio )
- Installazione di [CMake](https://cmake.org/download/)

** Guida alla compilazione **
1. Generazione MakeFile: Su linea di comando dirigersi nella cartella root del progetto, dove è presente il file  ```CMakeLists.txt``` e inserire il comando ```cmake -G "MinGW Makefiles" -S . -B build``` ( Dove "MinGW Makefiles" può essere sostituito da un altro ambiente di compilazione; per ulteriori informazioni sui generatori di MakeFile vedere ```cmake -G``` ). Questa operazione genererà i file necessari per CMake e il Makefile per compilare nella cartella `build` i sorgenti della cartella attuale.
2. Compilazione: Su linea di comando dirigersi nella cartella ```build```, dove è presente il Makefile, e digitare il comando ```make``` (```mingw32-make``` su compilatore mingw, mingw64 )
3. Avviare l'eseguibile compilato nella cartella ```build```

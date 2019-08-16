# Non-Gravitar
Progetto d'esame del corso di programmazione (a.a 2018/2019) basato sul gioco "Gravitar" con feature ridotte rispetto all'originale, priva di gravità.

#Funzionamento
Il giocatore controlla una navicella che può muovere utilizzando i tasti W A S D, oppure le freccie direzionali; il movimento della navicella consuma carburante, che può essere ricaricato da taniche generate nei pianeti.
Il gioco inizia in una schermata di un sistema solare nella quale sono presenti dei pianeti che il giocatore può "invadere" muovendosi con la navicella verso il pianeta stesso.
Il gioco cambia dunque dalla visuale del pianeta solare alla visuale del pianeta, in questa visuale viene generato casualmente il terreno dove sono presenti Bunker che il giocatore deve distruggere e taniche di carburante che il giocatore deve raccogliere.
Per distruggere i Bunker il giocatore può sparare utilizzando il tasto F e per raccogliere il fuel può utilizzare il tasto R.
Nella visuale del pianeta andando a destra/sinistra dello schermo viene visualizzata la parte successiva/precedente del pianeta. Il giocatore può uscire da un pianeta in qualsiasi momento dirigendosi verso il cielo del pianeta, ritornando nel punto del sistema solare, da cui era entrato nel pianeta.
Una volta distrutti tutti i bunker di un pianeta il giocatore distrugge il pianeta (che non potrà rivisitare), distrutti tutti i pianeti la navicella si dirigerà al centro del sistema solare, e si trasferirà in un altro dove saranno generati altri pianeti.
Il gioco termina quando la vita del giocatore scende a zero oppure quando esaurisce il carburante.

#Piattaforme
Attualmente è garantito il suo funzionamento su piattaforme Windows con compilatore MinGW64, ma potrebbe funzionare anche su altre piattaforme come linux con qualsiasi compilatore

#Installazione
Il gioco utilizza le librerie standard C/C++ le librerie WINDOWS API se viene compilato su windows.
Per generare il MakeFile del gioco occorre utilizzare [CMake](https://cmake.org/download/): dirigersi via linea di comando nella cartella root prcedente a ```src``` e digitare e confermare ```cmake -G "MinGW Makefiles" -S . -B build```.
Per compilare dirigersi sulla cartella ```build``` e digitare il comando ```make``` (```mingw32-make``` su compilatore mingw)

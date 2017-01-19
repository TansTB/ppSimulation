# ppSimulation

Questo programma si prefigge l'obiettivo di simulare la ricostruzione del vertice di un'interazione data da un urto tra due particelle.

Il software è progettato per essere il più modulare e personalizzabile possibile.

Tre sono gli oggetti fondamentali nel programma: Point, Hit e Track.

Il primo è il tradizionale punto nello spazio, individuato da tre coordinate cartesiane, con le loro funzioni di set e get. Un hit invece è un punto individuato in coordinate cilindriche dall'angolo azimutale phi, compreso tra -Pi e Pi e da una coordinata z, parallela all'asse del cilindro individuato dal beam pipe e dai rivelatori. Il raggio a cui si trova il punto è superfluo, per come è progettato il programma, poiché vi è la necessità di distinguere gli hit in diversi TClonesArray per ogni layer di rivelazione e per il beam pipe. Anche per economia di memoria, si cerca così di evitare di memorizzare in ogni hit alcuni raggi sempre uguali per tutti gli oggetti dello stesso TClonesArray. Ad ogni hit è inoltre assegnato un label, ovvero un numero intero che individua la particella che lo ha generato. Una track infine è un oggetto caratterizzato da un angolo polare (tra 0 e Pi) e un angolo azimutale (tra -Pi e Pi). Essa rappresenta un versore nello spazio, ovvero la direzione in cui una particella si sta muovendo durante una delle fasi di trasporto.

Il cuore del programma è costituito da un generatore di eventi (singoli urti), di nome "EventGenerator", il quale gestisce la simulazione di un urto per mezzo di tre generatori: 
-Vertex Generator: genera un oggetto di tipo vertice, seguendo alcune distribuzioni preimpostate o una distribuzione custom. E' la posizione in cui le due particelle primarie urtano nella verità Monte Carlo.
-Multiplicity Generator: fornisce il numero di particelle prodotte dall'urto, implementando nuovamente alcune distribuzioni o la possibilità di utilizzare una distribuzione personalizzata.
-Track Generator: genera le track iniziali di un numero di particelle pari alla molteplicità, consentendo sempre l'utilizzo di distribuzioni ad hoc.

Il generatore di eventi si occupa quindi di simulare il trasporto delle particelle (tenendo conto o meno del multiple scattering) e le loro interazioni con i due strati di rivelazione, calcolando i punti di intersezione. Nel caso in cui il multiple scattering venga simulato, la direzione (track) associata ad ogni particella è aggiornata ogni volta che viene attraversato un strato di materiale. 
Un quarto generatore,Noise, aggiunge ulteriori hit spuri a quelli già calcolati, simulando il rumore intrinseco degli apparati, qualora richiesto. Viene simulato inoltre uno smearing gaussiano di ogni hit, così da tener conto anche della risoluzione del detector.
Tutti gli hit, divisi in TClonesArray diversi per layer di impatto, i vertici e le molteplicità vengono salvati in un file .root di output.

Studiando la differenza tra le phi di ogni hit al primo strato di rivelazione e quelle all'ultimo, si può stimare quanto valga la deviazione media dovuta a tutti i processi simulati (DeltaPhi)
Questa quantità svolge un ruolo fondamentale nella seconda parte del software, ovvero la ricostruzione del vertice.

Vengono letti gli hit salvati e per ogni hit nel primo layer di rivelazione si cercano hit nel secondo layer aventi una phi che si discosta di una quantità inferiore al doppio di DeltaPhi. Per ogni coppia trovata viene ricostruita la coordinata z del vertice che è poi inserita in un istogramma. Vengono quindi individuati il bin contenente il numero massimo di vertici ricostruiti ed il secondo massimo. Imponendo una condizione sugli eventi contenuti nel massimo e nei primi bin adiacenti, rispetto a quelli del secondo massimo e dei primi bin adiacenti, l'algoritmo di ricostruzione decide se il massimo trovato rappresenti davvero un punto di aggregazione di tanti vertici ricostruiti. Qualora ciò avvenga viene effettuata una media delle coordinate z dei vertici ricostruite all'interno del bin massimo ed il risultato è considerato il vertice ricostruito. Nel caso contrario al vertice ricostruito viene assegnato un valore dummy (-999999) e l'evento è segnalato come non ricostruito.

Tutto il processo è coordinato dal Run Manager che, sulla base del contenuto di un file di configurazione (che deve avere la struttura di Config.txt), genera gli eventi richiesti, calcola i parametri necessari per la ricostruzione e ricostruisce il vertice per ogni singolo evento, coordinando così l'intero processo di simulazione. Il Run Manager fornisce inoltre alcune informazioni sul tempo impiegato dal calcolatore per le varie fasi del processo.


E'possibile compilare il programma per mezzo di un makefile e lanciarlo direttamente dall'eseguibile (da shell), una volta modificato secondo le proprie necessità il file di configurazione. 
I comandi sono i seguenti:

make -> Per compilare il programma da shell

./ppSimulation <b>ConfigFile</b>     (sostituire <b>ConfigFile</b> con il nome del file di configurazione da utilizzare, è necessario che rispetti la struttura di Config.txt) -> per lanciare la simulazione

In alternativa il programma può essere compilato e lanciato direttamente da Root:

.x ppSimulationCompiler.C -> per compilare il programma di simulazione

ppSimulation("<b>ConfigFile</b>") -> per lanciare la simulazione stessa

L'output della simulazione (<b>OutputFile</b>) è un file ".root", il quale può essere letto da un'apposita macro (Displayer.cxx) che consente di visualizzare i risultati della simulazione:

Digitando in ambiente root <b>.x DisplayerCompiler.C</b> si compila la macro Displayer.cxx e tutti i suoi prerequisiti.

Con i seguenti comandi è quindi possibile visualizzare dei grafici riassuntivi della simulazione, mentre ulteriori informazioni si possono ottenere osservando da TBrowser l'<b>OutputFile</b>

ResolutionHistogram("<b>OutputFile</b>") -> plot della risoluzione del processo di ricostruzione del vertice

ResolutionVsGeneratedZHistogram("<b>OutputFile</b>") -> plot della risoluzione rispetto alla coordinata z generata

ResolutionVsMultiplicityHistogram("<b>OutputFile</b>",Int_t numero_bin_istogramma) -> plot della risoluzione in funzione della molteplicità dell'evento

EfficiencyVsMultiplicityHistogram("<b>OutputFile</b>") -> plot dell'efficienza in funzione della molteplicità dell'evento

EfficiencyVsMultiplicityHistogram1Sigma("<b>OutputFile</b>") -> plot dell'efficienza in funzione della molteplicità dell'evento solo per particelle generate entro un sigma dal valore medio della distribuzione con cui sono state generate

EfficiencyVsNoiseHistogram("<b>OutputFile</b>") -> plot dell'efficienza in funzione del numero di hit spuri generati su ogni layer di rivelazione

In allegato sono presenti in formato pdf alcuni plot da noi generati.

Il comando <b>make clean</b> permette infine di pulire la cartella in cui il simulatore è stato compilato da tutti i file di compilazione, lasciando soltanto i file sorgente e l'<b>OutputFile</b>





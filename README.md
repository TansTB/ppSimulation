# ppSimulation
Questo programma si prefigge l'obiettivo di simulare la ricostruzione del vertice di un'interazione data da un urto tra due particelle.
Il software è progettato per essere il più modulare e personalizzabile possibile. 
E'costituito da un generatore di eventi (singoli urti), il quale utilizza tre generatori: 
-Vertex Generator: genera un oggetto di tipo vertice, seguendo alcune distribuzioni preimpostate o una distribuzione custom.
-Multiplicity Generator: fornisce il numero di particelle prodotte in un singolo urto, implementando nuovamente alcune distribuzioni o la possibilità di utilizzare una distribuzione personalizzata.
-Track Generator: genera le traiettorie iniziali delle particelle, consentendo sempre l'utilizzo di distribuzioni ad hoc.
Il generatore di eventi si occupa quindi di simulare il trasporto delle particelle (multiple scattering) e le loro interazioni con i due strati di rivelazione, calcolando i punti di intersezione (hit). 
Un quarto generatore,Noise, aggiunge ulteriori hit spuri a quelli già calcolati, simulando il rumore intrinseco degli apparati.
La seconda componente del software è dedicata alla ricostruzione del vertice.
Tutto il processo è coordinato dal Run Manager che, sulla base del contenuto del file di configurazione (Config.txt), genera gli eventi richiesti, calcola i parametri necessari per la ricostruzione e ricostruisce il vertice per ogni singolo evento.

E'possibile compilare il programma per mezzo di un makefile e lanciarlo direttamente dall'eseguibile (da shell), una volta modificato secondo le proprie necessità il file di configurazione . I comandi sono i seguenti:

make

./ppSimulation <b>ConfigFile</b>     (sostituire <b>ConfigFile</b> con il nome del file di configurazione da utilizzare, è necessario che rispetti la struttura di Config.txt)

In alternativa il programma può essere compilato e lanciato direttamente da Root:

.x ppSimulationCompiler.C

ppSimulation("<b>ConfigFile</b>")

L'output della simulazione (<b>OutputFile</b>) è un file ".root", il quale può essere letto da un'apposita macro (Displayer.cxx) che consente di visualizzare i risultati della simulazione:

Digitando in ambiente root <b>.x DisplayerCompiler.C</b> si compila la macro Displayer.cxx e tutti i suoi prerequisiti.

Con i seguenti comandi è quindi possibile visualizzare dei grafici riassuntivi della simulazione, mentre ulteriori informazioni si possono ottenere osservando da TBrowser l'<b>OutputFile</b>

ResolutionHistogram("<b>OutputFile</b>")                 

ResolutionVsGeneratedZHistogram("<b>OutputFile</b>")      

ResolutionVsMultiplicityHistogram("<b>OutputFile</b>",Int_t numero_bin_istogramma)

EfficiencyVsMultiplicityHistogram("<b>OutputFile</b>")

EfficiencyVsMultiplicityHistogram1Sigma("<b>OutputFile</b>")

EfficiencyVsNoiseHistogram("<b>OutputFile</b>")

In allegato sono presenti in formato pdf i plot da noi generati.

Il comando <b>make clean</b> permette infine di pulire la cartella in cui il simulatore è stato compilato da tutti i file di compilazione, lasciando soltanto i file sorgente e l'<b>OutputFile</b>





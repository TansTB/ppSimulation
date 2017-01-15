# ppSimulation
Questo programma si prefigge l'obiettivo di simulare la ricostruzione del vertice di un'interazione data da un urto tra due particelle.
Il software è progettato per essere il più modulare e personalizzabile possibile. 
E' costituito da un generatore di eventi (singoli urti), il quale utilizza tre generatori: 
-Vertex Generator: genera un oggetto di tipo vertice, seguendo alcune distribuzioni preimpostate o una distribuzione custom
-Multiplicity Generator: fornisce il numero di particelle prodotte in un singolo urto, implementando nuovamente alcune distribuzioni o la possibilità di utilizzare una distribuzione personalizzata
-Track Generator: genera le traiettorie iniziali delle particelle, consentendo sempre l'utilizzo di distribuzioni ad hoc
Il generatore di eventi si occupa quindi di simulare il trasporto delle particelle (multiple scattering) e le loro interazioni con i due strati di rivelazione, calcolando i punti di intersezione (hit). 
Un quarto generatore, Noise Generator, aggiunge ulteriori hit spuri a quelli già calcolati, simulando il rumore intrinseco degli apparati.
La seconda componente del software è dedicata alla ricostruzione del vertice.
Tutto il processo è coordinato dal Run Manager, che prende la configurazione di tutta la simulazione da un file (Config.txt), genera gli eventi richiesti, calcola i parametri necessari per la ricostruzione e ricostruisce il vertice per ogni singolo evento.
E' possibile compilare il programma per mezzo di un makefile e lanciarlo direttamente dall'eseguibile, una volta modificato secondo le proprie necessità il Config File con il comando "./ppSimulation <ConfigFile>" (sostituire <ConfigFile> con il nome del file di configurazione da utilizzare. 
L'output della simulazione è un file ".root", il quale può essere letto da alcune macro (Displayer) che consentono di visualizzare i risultati della simulazione.

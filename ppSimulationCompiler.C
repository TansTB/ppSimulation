//Macro to compile the simulator and all his prerequisites
#if !defined (__CINT__) || defined(__ROOTCINT__)
#include "TROOT.h"
#endif

void ppSimulationCompiler(){
    gROOT->ProcessLine(".L MyParser.cxx+");
    gROOT->ProcessLine(".L Point.cxx+");
    gROOT->ProcessLine(".L Hit.cxx+");
    gROOT->ProcessLine(".L Track.cxx+");
    gROOT->ProcessLine(".L VtxGenerator.cxx+");
    gROOT->ProcessLine(".L MultiplicityGenerator.cxx+");
    gROOT->ProcessLine(".L TrackGenerator.cxx+");
    gROOT->ProcessLine(".L Noise.cxx+");
    gROOT->ProcessLine(".L EventGenerator.cxx+");
    gROOT->ProcessLine(".L Reco.cxx+");
    gROOT->ProcessLine(".L RunManager.cxx+");
    
}

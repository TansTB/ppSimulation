//Macro to compile the displayer and all his prerequisites
#if !defined (__CINT__) || defined(__ROOTCINT__)
#include "TROOT.h"
#endif

void DisplayerCompiler(){
    gROOT->ProcessLine(".L Point.cxx+");
    gROOT->ProcessLine(".L Hit.cxx+");
    gROOT->ProcessLine(".L Displayer.cxx+");
}

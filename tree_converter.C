// Code to convert the ASCII output of STARlight into ROOT trees
// Make sure ROOT is installed
// Run using `root -l tree_converter.C`
// LCVR
#include "TFile.h"
#include "TTree.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

void tree_converter(const char* inFileName = "slight.out", const char* outFileName = "starlight_output.root") {
    std::ifstream infile(inFileName);
    if (!infile.is_open()) {
        std::cerr << "Error: Could not open " << inFileName << std::endl;
        return;
    }

    TFile *fOut = new TFile(outFileName, "RECREATE");
    TTree *tree = new TTree("upc", "STARlight Dimuon Events");

    // Flat branches for exactly 2 tracks
    double px1, py1, pz1, m1;
    double px2, py2, pz2, m2;
    int pid1, pid2;

    tree->Branch("pid1", &pid1);
    tree->Branch("px1", &px1);
    tree->Branch("py1", &py1);
    tree->Branch("pz1", &pz1);
    tree->Branch("m1",  &m1);

    tree->Branch("pid2", &pid2);
    tree->Branch("px2", &px2);
    tree->Branch("py2", &py2);
    tree->Branch("pz2", &pz2);
    tree->Branch("m2",  &m2);

    std::string line;
    std::string token;
    int trackCount = 0;

    // STARlight muon mass in GeV
    const double muonMass = 0.105658;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        iss >> token;

        // Ignore everything unless the line starts with EVENT: or TRACK:
        if (token == "EVENT:") {
            // Fill the tree once collected both tracks from the previous event
            if (trackCount == 2) {
                tree->Fill();
            }
            trackCount = 0; // Reset for the new event
        }
        else if (token == "TRACK:") {
            int trkIdx, dummy1, dummy2, dummy3, pid;
            double px, py, pz;

            // Parse the 8 columns following "TRACK:" in slight.out format
            iss >> trkIdx >> px >> py >> pz >> dummy1 >> dummy2 >> dummy3 >> pid;

            if (trackCount == 0) {
                pid1 = pid; px1 = px; py1 = py; pz1 = pz; m1 = muonMass;
            } else if (trackCount == 1) {
                pid2 = pid; px2 = px; py2 = py; pz2 = pz; m2 = muonMass;
            }
            trackCount++;
        }
    }

    if (trackCount == 2) {
        tree->Fill();
    }

    fOut->Write();
    long nEvents = tree->GetEntries();
    std::cout << "Successfully converted " << tree -> GetEntries() << " events to " << outFileName << std::endl;
    fOut->Close();
}

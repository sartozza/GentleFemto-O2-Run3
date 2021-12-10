#include "TROOT.h"
#include "ReadDreamFile.h"
#include "DreamCF.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TSystem.h"
#include <iostream>
/// Input arguments
/// 1. filename: name and path to the root file
/// 2. prefix: prefix indicating the type of task you want to analyse (e.g "track-track")
/// 3. addon: additional strings in the folders/histograms typically used for systematics or user-chosen label
/// for output file
/// 4. Norm1 and Norm2: interval of normalization for SE and ME
void GetCorrelations_pp(const char *filename,
                        const char *prefix, const char *addon = "",
                        double_t norm1 = 0.24,
                        double_t norm2 = 0.34)
{
  ReadDreamFile* DreamFile = new ReadDreamFile(1, 1);/// number of pairs you are analysing -> DUMMY!!
  DreamFile->SetAnalysisFile(filename, prefix, addon);

  DreamCF* CF_pp = new DreamCF();
  DreamPair* pp = new DreamPair("PartPart", norm1, norm2);

  std::cout << "=========================" << std::endl;
  std::cout << "========Pair Set=========" << std::endl;
  std::cout << "=========================" << std::endl;
  pp->SetPair(DreamFile->GetPairDistributions(""));

  std::cout << "=========================" << std::endl;
  std::cout << "======Pair Shifted=======" << std::endl;
  std::cout << "=========================" << std::endl;
  pp->ShiftForEmpty(pp->GetPair());

  std::cout << "=========================" << std::endl;
  std::cout << "====Pair Fix Shifted=====" << std::endl;
  std::cout << "=========================" << std::endl;
  pp->FixShift(pp->GetPairShiftedEmpty(0), pp->GetPairShiftedEmpty(0),
               pp->GetFirstBin());

  std::cout << "=========================" << std::endl;
  std::cout << "==Rebinning & Weighting==" << std::endl;
  std::cout << "=========================" << std::endl;
  std::vector<int> rebinVec = {{1, 2, 4, 8}};
  for (size_t iReb = 0; iReb < rebinVec.size(); ++iReb)
  {
    std::cout << "==Rebinning==" << std::endl;
    pp->Rebin(pp->GetPairFixShifted(0), rebinVec[iReb]);
    std::cout << "==Weighting==" << std::endl;
    pp->ReweightMixedEvent(pp->GetPairRebinned(iReb), 0.2, 0.9);
  }

    std::cout << "=========================" << std::endl;
    std::cout << "=========CFs=============" << std::endl;
    std::cout << "=========================" << std::endl;

    TString foldername = filename;
    foldername.ReplaceAll("AnalysisResults.root", "");
    std::cout << "==========CF pp===============" << std::endl;
    CF_pp->SetPairs(pp, nullptr);
    CF_pp->GetCorrelations();
    CF_pp->WriteOutput(Form("%s/CFOutput_pp_%s.root", foldername.Data(), addon));
  }

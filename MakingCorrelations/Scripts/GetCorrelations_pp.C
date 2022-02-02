#include "TROOT.h"
#include "ReadDreamFile.h"
#include "DreamCF.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TSystem.h"
#include <iostream>
/// Input arguments
/// 1. filename: name and path to the root file
///     - particle (e.g protons): base wagon (no addon typically)
///     - antiparticle (e.g antiprotons): subwagon with user addon (e.g _ap_ap)
/// 2. prefix: prefix indicating the type of task you want to analyse (e.g "track-track")
/// 3. subwag: additional strings in the folders/histograms typically used for subwagons with user-chosen label
/// for output file
///   - subwagons (user name): eg. _ap_ap
/// 4. Norm1 and Norm2: interval of normalization for SE and ME
void GetCorrelations_pp(const char *filename,
                        const char *prefix, const char *subwag = "",
                        double_t norm1 = 0.24,
                        double_t norm2 = 0.34)
{
  /// Creating to ReadDreamFile objects: for particle and antiparticle
  ReadDreamFile *DreamFile1 = new ReadDreamFile(1, 1); /// number of pairs you are analysing -> DUMMY!!
  ReadDreamFile *DreamFile2 = new ReadDreamFile(1, 1); /// number of pairs you are analysing -> DUMMY!!

  DreamFile1->SetAnalysisFile(filename, prefix, ""); //base wagon does not have label
  DreamFile2->SetAnalysisFile(filename, prefix, TString::Format("_%s", subwag));

  DreamCF *CF_pp = new DreamCF();
  DreamCF *CF_ApAp = new DreamCF();
  DreamCF *CF_tot = new DreamCF();
  DreamPair *pp = new DreamPair("PartPart", norm1, norm2);
  DreamPair *ApAp = new DreamPair("APartAPart", norm1, norm2);

  std::cout << "=========================" << std::endl;
  std::cout << "========Pair Set=========" << std::endl;
  std::cout << "=========================" << std::endl;
  pp->SetPair(DreamFile1->GetPairDistributions(""));
  ApAp->SetPair(DreamFile2->GetPairDistributions(""));

  std::cout << "=========================" << std::endl;
  std::cout << "======Pair Shifted=======" << std::endl;
  std::cout << "=========================" << std::endl;
  // pp->ShiftForEmpty(pp->GetPair());
  // ApAp->ShiftForEmpty(ApAp->GetPair());

  std::cout << "=========================" << std::endl;
  std::cout << "====Pair Fix Shifted=====" << std::endl;
  std::cout << "=========================" << std::endl;
  // pp->FixShift(pp->GetPairShiftedEmpty(0), ApAp->GetPairShiftedEmpty(0),
  //              ApAp->GetFirstBin());
  // ApAp->FixShift(ApAp->GetPairShiftedEmpty(0), pp->GetPairShiftedEmpty(0),
  //                pp->GetFirstBin());
  std::cout << "=========================" << std::endl;
  std::cout << "==Rebinning & Weighting==" << std::endl;
  std::cout << "=========================" << std::endl;

  std::vector<int> rebinVec = {{1, 2, 3, 4}}; //not needed for p-p
  for (size_t iReb = 0; iReb < rebinVec.size(); ++iReb)
  {
    std::cout << "==Rebinning==" << std::endl;
    pp->Rebin(pp->GetPair(), rebinVec[iReb]);
    std::cout << "==Weighting==" << std::endl;
    pp->ReweightMixedEvent(pp->GetPairRebinned(iReb), 0.2, 0.9);

    std::cout << "==Rebinning==" << std::endl;
    ApAp->Rebin(ApAp->GetPair(), rebinVec[iReb]);
    std::cout << "==Weighting==" << std::endl;
    ApAp->ReweightMixedEvent(ApAp->GetPairRebinned(iReb), 0.2, 0.9);
  }

  std::cout << "=========================" << std::endl;
  std::cout << "=========CFs=============" << std::endl;
  std::cout << "=========================" << std::endl;

  TString foldername = filename;
  foldername.ReplaceAll("AnalysisResults.root", "");

  std::cout << "==========CF pp===============" << std::endl;
  CF_pp->SetPairs(pp, nullptr);
  CF_pp->GetCorrelations();
  CF_pp->WriteOutput(Form("%s/CFOutput_pp_.root", foldername.Data()));

  std::cout << "==========CF ApAp===============" << std::endl;
  CF_ApAp->SetPairs(ApAp, nullptr);
  CF_ApAp->GetCorrelations();
  CF_ApAp->WriteOutput(Form("%s/CFOutput_ApAp_.root", foldername.Data()));

  std::cout << "==========CF Tot===============" << std::endl;
  CF_tot->SetPairs(pp, ApAp);
  CF_tot->GetCorrelations();
  CF_tot->WriteOutput(Form("%s/CFOutput_Tot_.root", foldername.Data()));
}

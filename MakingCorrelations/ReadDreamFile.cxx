/*
 * ReadDreamFile.cxx
 *
 *  Created on: Aug 21, 2018
 *      Author: hohlweger
 */
#include "ReadDreamFile.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TStyle.h"
#include "TLegend.h"
#include <iostream>
#include <iostream>
#include "stdlib.h"

ReadDreamFile::ReadDreamFile(int nPart1, int nPart2)
    : fQuiet(false),
      fNPart1(nPart1),
      fNPart2(nPart2),
      fSE(nullptr),
      fSEMult(nullptr),
      fME(nullptr),
      fMEMult(nullptr)
{
  TH1::AddDirectory(kFALSE);
  TH2::AddDirectory(kFALSE);
}

ReadDreamFile::~ReadDreamFile() {}

void ReadDreamFile::SetAnalysisFile(const char *PathAnalysisFile,
                                    const char *Prefix, const char *Addon)
{
  std::cout << "You are accessing the following analysis file:" << std::endl;
  std::cout << "PathAnalysisFile: " << PathAnalysisFile << '\t' << " Prefix: "
            << Prefix << '\t' << " Addon: " << Addon << std::endl;
  TFile *_file0 = TFile::Open(PathAnalysisFile, "READ");
  if (!_file0)
  {
    std::cout << "no file available" << std::endl;
  }

  TDirectoryFile *dirResults = (TDirectoryFile *)(_file0->FindObjectAny(
      TString::Format("femto-dream-pair-task-%s%s", Prefix, Addon).Data()));
  if (!dirResults)
  {
    std::cout << "no dir results "
              << TString::Format("femto-dream-pair-task-%s%s", Prefix, Addon).Data()
              << std::endl;
  }

  TDirectoryFile *ResultsSame = (TDirectoryFile *)(dirResults->FindObjectAny(
      TString::Format("SameEvent")));
  if (!ResultsSame)
  {
    std::cout << "No results folder for Same Event"
              << TString::Format("SameEvent")
              << std::endl;
    ResultsSame->ls();
    return;
  }

  TDirectoryFile *ResultsMixed = (TDirectoryFile *)(dirResults->FindObjectAny(
      TString::Format("MixedEvent")));
  if (!ResultsMixed)
  {
    std::cout << "No results folder for Mixed Event"
              << TString::Format("MixedEvent")
              << std::endl;
    ResultsMixed->ls();
    return;
  }

  ExtractResults(ResultsSame, ResultsMixed);
  ResultsSame->Delete();
  ResultsMixed->Delete();
  dirResults->Close();
  _file0->Close();
  delete _file0;
}

void ReadDreamFile::ExtractResults(const TDirectoryFile *ResultsSame, const TDirectoryFile *ResultsMixed)
{
  /// Same event histograms
  fSE = nullptr;
  TString histoDistr_name = TString::Format("relPairDist");
  auto hist_SE = ResultsSame->FindObjectAny(histoDistr_name.Data());
  if (!hist_SE)
  {
    if (!fQuiet)
    {
      std::cout << "SE Histogram " << histoDistr_name.Data() << " missing"
                << std::endl;
    }
  }
  else
  {
    fSE = (TH1F *)hist_SE->Clone(Form("SE%s_clone", hist_SE->GetName()));
    fSE->Sumw2();
  }
  fSEMult = nullptr;
  TString histoDistrMult_name = TString::Format("relPairkstarMult");
  auto hist_SEMult = ResultsSame->FindObjectAny(histoDistrMult_name.Data());
  if (!hist_SEMult)
  {
    if (!fQuiet)
    {
      std::cout << "SE Multiplicity Histogram " << histoDistrMult_name.Data() << " missing"
                << std::endl;
    }
  }
  else
  {
    fSEMult = (TH2F *)hist_SEMult->Clone(Form("%s_clone", hist_SEMult->GetName()));
    fSEMult->Sumw2();
  }

  /// Mixed event histograms
  fME = nullptr;
  auto hist_ME = ResultsMixed->FindObjectAny(histoDistr_name.Data());
  if (!hist_ME)
  {
    if (!fQuiet)
    {
      std::cout << "ME Histogram " << histoDistr_name.Data() << " missing"
                << std::endl;
    }
  }
  else
  {
    fME = (TH1F *)hist_ME->Clone(Form("ME%s_clone", hist_ME->GetName()));
    fME->Sumw2();
  }

  fMEMult = nullptr;
  auto hist_MEMult = ResultsMixed->FindObjectAny(histoDistrMult_name.Data());
  if (!hist_MEMult)
  {
    if (!fQuiet)
    {
      std::cout << "ME Multiplicity Histogram " << histoDistrMult_name.Data() << " missing"
                << std::endl;
    }
  }
  else
  {
    fMEMult = (TH2F *)hist_MEMult->Clone(Form("%s_clone", hist_MEMult->GetName()));
    fMEMult->Sumw2();
  }
}

DreamDist *ReadDreamFile::GetPairDistributions(const char *name)
{
  DreamDist *pair = new DreamDist();
  pair->SetSEDist(fSE, name);
  pair->SetSEMultDist(fSEMult, name);
  pair->SetMEDist(fME, name);
  pair->SetMEMultDist(fMEMult, name);
  return pair;
}
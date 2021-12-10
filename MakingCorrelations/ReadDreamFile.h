/*
 * ReadDreamFile.h
 *
 *  Created on: Aug 21, 2018
 *      Author: hohlweger
 */

#ifndef DREAMFUNCTION_READDREAMFILE_H_
#define DREAMFUNCTION_READDREAMFILE_H_
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"

#include "DreamKayTee.h"
#include "DreamDist.h"
#include "DreamdEtadPhi.h"

class ReadDreamFile {
 public:
  ReadDreamFile(int nPart1, int nPart2);
  virtual ~ReadDreamFile();
  void SetAnalysisFile(const char* AnalysisFile, const char* prefix,
                       const char* Addon = "");
  void ExtractResults(const TDirectoryFile *ResultsSame, const TDirectoryFile* ResultsMixed);

  DreamDist *GetPairDistributions(const char *name);

  void SetQuite() { fQuiet = true;}
  const int fNPart1;
  const int fNPart2;
 private:
  bool fQuiet;
  TH1F* fSE;
  TH2F* fSEMult;
  TH1F *fME;
  TH2F *fMEMult;
};

#endif /* DREAMFUNCTION_READDREAMFILE_H_ */

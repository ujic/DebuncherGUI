//#define FASTERFILE "debunch4_0001.fast"

// std includes
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include "math.h"
#include <fstream>


//  root includes
#include <TGFrame.h>
#include <TRootEmbeddedCanvas.h>
#include <TApplication.h>
#include <TGClient.h>
#include <TGButton.h>
//#include <TGCheckButton.h>
//#include <TGFileBrowser.h>
#include <TGTextEntry.h>
#include <TGLabel.h>
#include <TGNumberEntry.h>

#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1I.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TH2.h"


//  fasterac includes
#include "fasterac/fasterac.h"
#include "fasterac/fast_data.h"
#include "fasterac/qdc_caras.h"
#include "fasterac/qtdc.h"

using namespace std;



void example(int, char**);

class MyMainFrame : public TGMainFrame {
private:
   TRootEmbeddedCanvas *fEcanvas;
TGTextEntry *fileNameTG;
	TGGC   *uGC;
	TGFont *ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1"); // will reflect user font changes
	TH1I *bunchHist, *bunchHistTotal, *bcgHist;
	TH1F *integralDistribution;
	TCanvas *fCanvas;
	TGLabel *fileL, *TimeL;
	TGNumberEntry *jumpTrig, *shift, *histLeft, *histRight, *BCGLeft, *BCGRight, *offsetRamp, *endRamp, *samplesNo, *NBins; //*trigFrequency, 
	//TGFileBrowser* pBrowser;
	TGCheckButton *TxtButonDraw;

  	char filefast1[20]="debunch4_0001.fast";
	float ToF = 0.015; // [ms] Time of flight from a debuncher to the MCP
	bool firstEvent, previousEvent, trigRead, bFileOpen, previousEventTrigger;
	bool EOF1, EOF2;
	int counterwhile, eventCounter, trigCounter, IonSum;
	Float_t mean, rms, timestamp, timestampRef, timestampPrev, timestampFirst, charge;

	TString fName1;


  //  faster file reader
  faster_file_reader_p   reader;
  //  faster data
  faster_data_p          data;
  unsigned char          alias;
  unsigned short         label;
	Double_t		clockt;
  	qdc_t_x1    q_tdc;
	qdc_counter q_count;



public:
   MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h);
   virtual ~MyMainFrame() ;
   void MakeInverse();
   int DoDraw();
	void Open();
	void histChange();
   ClassDef(MyMainFrame,0);
};


#include "debuncher_GUI2.h"

// this version has a option to calculate the inverse distribution of the debunched ions by a ramp potential 



int main(int argc, char **argv) {

/*public float traptime, ejecttime;
char* fasterFile;
	
	fasterFile=argv[1];
	traptime = atof(argv[2]);
	ejecttime= atof(argv[3]);
*/
   TApplication theApp("App",&argc,argv);
   example(argc, argv);
   theApp.Run();

   return 0;
}


MyMainFrame::MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h)
   : TGMainFrame(p,w,h){

	bFileOpen=false;
previousEventTrigger=false; 
   timestampRef=timestampFirst=timestampPrev=0; 
	float traptime=5.;
	float ejecttime=0.02;

	firstEvent=true;


   GCValues_t valEntry1069;
   valEntry1069.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
   gClient->GetColorByName("#000000",valEntry1069.fForeground);
   gClient->GetColorByName("#e8e8e8",valEntry1069.fBackground);
   valEntry1069.fFillStyle = kFillSolid;
   valEntry1069.fFont = ufont->GetFontHandle();
   valEntry1069.fGraphicsExposures = kFALSE;
   uGC = gClient->GetGC(&valEntry1069, kTRUE);


   // Creates widgets of the example
   fEcanvas = new TRootEmbeddedCanvas ("Ecanvas",this,1000,600);
   
      fCanvas = fEcanvas->GetCanvas();
    fCanvas->SetBorderSize(0);
    fCanvas->Divide(1,2);
    fCanvas->cd(1);
    gPad->SetBorderMode(0);
    gPad->SetTopMargin(0.01);
    gPad->SetRightMargin(0.16);
    gPad->SetLeftMargin(0.1);
    fCanvas->cd(2);
    gPad->SetBorderMode(0);
    gPad->SetTopMargin(0.01);
    gPad->SetRightMargin(0.16);
    gPad->SetLeftMargin(0.1);
   
   AddFrame(fEcanvas, new TGLayoutHints(kLHintsExpandX |
                                    kLHintsExpandY, 10,10,10,1));
   TGHorizontalFrame *hframe=new TGHorizontalFrame(this, 1000,40);

	TimeL = new TGLabel(hframe, "  Time elapsed = 0                    ");
	hframe->AddFrame(TimeL, new TGLayoutHints(kLHintsCenterX,5,5,3,4));

/*
	TGLabel *TrigFrL = new TGLabel(hframe, "Trig.Frequency");
	hframe->AddFrame(TrigFrL, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
	trigFrequency = new TGNumberEntry(hframe, 0);
   hframe->AddFrame(trigFrequency, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
*/

   TGTextButton *draw = new TGTextButton(hframe,"&Draw");
   draw->Connect("Clicked()","MyMainFrame",this,"DoDraw()");
   hframe->AddFrame(draw, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
   
   TxtButonDraw = new TGCheckButton(hframe,"Draw?");
   TxtButonDraw->SetTextJustify(36);
   TxtButonDraw->SetMargins(0,0,0,0);
   TxtButonDraw->SetWrapLength(-1);
   	hframe->AddFrame(TxtButonDraw, new TGLayoutHints(kLHintsCenterX,5,5,3,4));

	jumpTrig = new TGNumberEntry(hframe, -1.);
   hframe->AddFrame(jumpTrig, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
	TGLabel *TrigL = new TGLabel(hframe, "[s]");
	hframe->AddFrame(TrigL, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
	

/// Add how many seconds to the next bunch ...................................................................


	TGTextButton *open = new TGTextButton(hframe,"&Open ");
	open->Connect("Clicked()","MyMainFrame",this,"Open()");
   hframe->AddFrame(open, new TGLayoutHints(kLHintsCenterX,
                                            5,5,3,4));
   
   fileNameTG = new TGTextEntry(hframe, new TGTextBuffer(50),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   fileNameTG->SetMaxLength(200);
   fileNameTG->SetAlignment(kTextLeft);
   fileNameTG->SetText("runs/");
   fileNameTG->Resize(92,fileNameTG->GetDefaultHeight());
   hframe->AddFrame(fileNameTG, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	//cout<<trigFreq->GetText()<<endl;
  	fileL = new TGLabel(hframe, "FILE?                                            ");
  	//fileL->SetTextFont(ft);
	hframe->AddFrame(fileL, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));

	TGTextButton *exit = new TGTextButton(hframe,"&Exit ",
                                "gApplication->Terminate()");
   hframe->AddFrame(exit, new TGLayoutHints(kLHintsCenterX,
                                            5,5,3,4));

	AddFrame(hframe,new TGLayoutHints(kLHintsCenterX,2,2,2,2));

  TGHorizontalFrame *hframe2 = new TGHorizontalFrame(this,1000,40);

	TGLabel *shiftL = new TGLabel(hframe2, "Shift");
	hframe2->AddFrame(shiftL, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
	shift = new TGNumberEntry(hframe2, 0);
   hframe2->AddFrame(shift, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
   
  	TGLabel *histLeftL = new TGLabel(hframe2, "Shift");
	hframe2->AddFrame(histLeftL, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
	histLeft = new TGNumberEntry(hframe2, 0);
   hframe2->AddFrame(histLeft, new TGLayoutHints(kLHintsCenterX,5,5,3,4)); 

	TGLabel *HistRightL = new TGLabel(hframe2, "Hist.right");
	hframe2->AddFrame(HistRightL, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
	histRight = new TGNumberEntry(hframe2, 1000);
   hframe2->AddFrame(histRight, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
   
	TGLabel *NBinsL = new TGLabel(hframe2, "NofBins");
	hframe2->AddFrame(NBinsL, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
	NBins = new TGNumberEntry(hframe2, 100);
   hframe2->AddFrame(NBins, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
    
   TGLabel *BCGLeftL = new TGLabel(hframe2, "BCG.left");
	hframe2->AddFrame(BCGLeftL, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
	BCGLeft = new TGNumberEntry(hframe2, 820);
   hframe2->AddFrame(BCGLeft, new TGLayoutHints(kLHintsCenterX,5,5,3,4));

	TGLabel *BCGRightL = new TGLabel(hframe2, "BCG.right");
	hframe2->AddFrame(BCGRightL, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
	BCGRight = new TGNumberEntry(hframe2, 1000);
   hframe2->AddFrame(BCGRight, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
    

	TGTextButton *applyHistChange = new TGTextButton(hframe2,"&Apply hist change");
	applyHistChange->Connect("Clicked()","MyMainFrame",this,"histChange()");
   hframe2->AddFrame(applyHistChange, new TGLayoutHints(kLHintsCenterX,
                                          5,5,3,4));
AddFrame(hframe2,new TGLayoutHints(kLHintsCenterX,1,1,1,1));





  TGHorizontalFrame *hframe3 = new TGHorizontalFrame(this,1000,40);

	TGLabel *offsetRampL = new TGLabel(hframe3, "Offset ramp");
	hframe3->AddFrame(offsetRampL, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
	offsetRamp = new TGNumberEntry(hframe3, 0);
   hframe3->AddFrame(offsetRamp, new TGLayoutHints(kLHintsCenterX,5,5,3,4));

	TGLabel *endRampL = new TGLabel(hframe3, "Ending ramp voltage");
	hframe3->AddFrame(endRampL, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
	endRamp = new TGNumberEntry(hframe3, 5);
   hframe3->AddFrame(endRamp, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
   
 	TGLabel *samplesNoL = new TGLabel(hframe3, "Number of samples");
	hframe3->AddFrame(samplesNoL, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
	samplesNo = new TGNumberEntry(hframe3, 250);
   hframe3->AddFrame(samplesNo, new TGLayoutHints(kLHintsCenterX,5,5,3,4));  

	TGTextButton *invFuncCalc = new TGTextButton(hframe3,"&Calculate inv. func.");
	invFuncCalc->Connect("Clicked()","MyMainFrame",this,"MakeInverse()");
   hframe3->AddFrame(invFuncCalc, new TGLayoutHints(kLHintsCenterX,
                                          5,5,3,4));
                                          
                                
                                          
AddFrame(hframe3,new TGLayoutHints(kLHintsCenterX,1,1,1,1));



	
	//reader = faster_file_reader_open (filefast1);
	bunchHist = new TH1I("Bunch", "Bunch", NBins->GetNumber(), histLeft->GetNumber(), histRight->GetNumber());
	bunchHistTotal = new TH1I("BunchTotal", "BunchTotal", NBins->GetNumber(), histLeft->GetNumber(), histRight->GetNumber());
	integralDistribution = new TH1F("IntegralDistribution", "Integral Distribtion", NBins->GetNumber(), histLeft->GetNumber(), histRight->GetNumber());
	bcgHist = new TH1I("bcgHist", "Background", NBins->GetNumber()*(histRight->GetNumber()-histLeft->GetNumber())/(BCGRight->GetNumber()-BCGLeft->GetNumber()), BCGLeft->GetNumber(), BCGRight->GetNumber());


   // Sets window name and shows the main frame
   SetWindowName("Simple Example");
   MapSubwindows();
   Resize(GetDefaultSize());
   MapWindow();

	//pBrowser = new TGFileBrowser(this);

  // SetEditable(kFALSE);
   //pBrowser->AddFSDirectory("/", "/");
   //pBrowser->GotoDir(gSystem->pwd());
   //MapSubwindows();
   //Layout();

}

void MyMainFrame::Open()
{
cout<<fileNameTG->GetText()<<endl;
//reader = faster_file_reader_open (filefast1);
if ((reader = faster_file_reader_open (fileNameTG->GetText()))!=NULL){
	 fileL->SetText(Form("open file: %s", fileNameTG->GetText()));
	bFileOpen=true;
}
else {
	fileL->SetText("NOT EXISTING FILE !!!");
	bFileOpen=false;
}
}

void MyMainFrame::histChange(){

if (bunchHist != NULL) delete bunchHist;
if (bunchHistTotal != NULL) delete bunchHistTotal;
if (integralDistribution != NULL) delete integralDistribution;
if (bcgHist != NULL) delete bcgHist;

	bunchHist = new TH1I("Bunch", "Bunch", NBins->GetNumber(), histLeft->GetNumber(), histRight->GetNumber());
	bunchHistTotal = new TH1I("BunchTotal", "BunchTotal", NBins->GetNumber(), histLeft->GetNumber(), histRight->GetNumber());
	integralDistribution = new TH1F("IntegralDistribution", "Integral Distribtion", NBins->GetNumber(), histLeft->GetNumber(), histRight->GetNumber());
	bcgHist = new TH1I("bcgHist", "Background", NBins->GetNumber()*(histRight->GetNumber()-histLeft->GetNumber())/(BCGRight->GetNumber()-BCGLeft->GetNumber()), BCGLeft->GetNumber(), BCGRight->GetNumber());


}

int MyMainFrame::DoDraw() {


if (!bFileOpen) { fileL->SetText("FILE NOT OPEN !!!"); return -1;}

bunchHist->Reset();
trigRead = false;

//cout<<trigFreq->GetText()<<endl;


      EOF1=((data = faster_file_reader_next (reader)) == NULL) ;

      if (!EOF1){
        alias = faster_data_type_alias (data);  
        label = faster_data_label      (data);
        clockt = faster_data_clock_sec  (data);
      }
	else {fileL->SetText("END OF FILE REACHED !!!"); return 1;}

//previousEvent=true;
timestampPrev=timestamp;

while(((timestamp-timestampPrev)/1e9)<(jumpTrig->GetNumber())){

//cout<<"timestamp-timestampPrev> "<<(timestamp-timestampPrev)/1e9<<endl;

    if ((alias == QDC_TDC_X1_TYPE_ALIAS)&&((label==1)||(label==2)))
	{
		faster_data_load (data, &q_tdc);
		if (firstEvent) {
			timestampFirst = clockt * 1e9 + qdc_conv_dt_ns (q_tdc.tdc);
			firstEvent=false;
		}
		else timestamp = clockt * 1e9 + qdc_conv_dt_ns (q_tdc.tdc); 

	}
previousEventTrigger=false;

     EOF1=((data = faster_file_reader_next (reader)) == NULL) ;

      if (!EOF1){
        alias = faster_data_type_alias (data);  
        label = faster_data_label      (data);
        clockt = faster_data_clock_sec  (data);
      }
	else {fileL->SetText("END OF FILE REACHED !!!"); return 1;}
}

counterwhile=0;
//cout<<" before while "<<endl<<flush;
  // main loop
//firstEvent=true;
eventCounter = 0;
trigRead=false;
bool stayinloop=false; // this will secure that the next while loop doesn't exit in the case you read array of label2, than come label1 and it exit
					// it should write upcoming label2 until next label1 comes, which will act as previousEventTrigger
					// this happens in the first event and in the jumpTrig events

while ((label!=1)||(!trigRead)||(stayinloop)) 
{                    //  read each data
	if (counterwhile>0){ // don't do it, just at the first entrance, because it is already read
      EOF1=((data = faster_file_reader_next (reader)) == NULL) ;

      if (!EOF1){
        alias = faster_data_type_alias (data);  
        label = faster_data_label      (data);
        clockt = faster_data_clock_sec  (data);
      }
		else {fileL->SetText("END OF FILE REACHED !!!"); return 1;}
	}

//cout<<"while:"<<flush<<endl;
    counterwhile++;



    if ((alias == QDC_TDC_X1_TYPE_ALIAS)&&(label==1))
	{
		if (firstEvent) {
			timestampFirst = clockt * 1e9 + qdc_conv_dt_ns (q_tdc.tdc);
			firstEvent=false;
		}
		if (stayinloop) stayinloop=false;
		else stayinloop=true; // we need to stay in the loop to collect following label2 events
		previousEventTrigger=true; // this is for the events of label2 if they come and this is true, then it keeps previous timestampRef for them
		trigRead=true;
		trigCounter++;
/*
		if (eventCounter>0) {
			mean=bunchHist->GetMean();
			rms =bunchHist->GetRMS();
			myfile<<trigCounter<<"\t"<<eventCounter<<"\t"<<mean<<"\t"<<rms<<endl;
			
			bunchStatHist->Fill(mean,rms);
			
			bunchHist->Reset();
			IonSum+=eventCounter;
			
		}
*/
      	faster_data_load (data, &q_tdc);
      	timestampRef = clockt * 1e9 + qdc_conv_dt_ns (q_tdc.tdc);   // long double
		charge = qdc_conv_q_mVns (q_tdc.q1); // in mV.ns
//cout<<"alias: "<<"QDC_TDC_X1"<<", label:"<<label<<", clockt:"<<clockt<<", timestamp:"<<timestampRef<<endl;

		eventCounter=0; // reset the number of events - counting started
		//firstEvent=true; // after this we have a first event

//    if (q_tdc.q1_saturated) printf ("        saturated : q1");
//      printf ("\n");
	}



    if ((alias == QDC_TDC_X1_TYPE_ALIAS)&&(label==2))
	{
		if (firstEvent) {
			timestampFirst = clockt * 1e9 + qdc_conv_dt_ns (q_tdc.tdc);
			firstEvent=false;
		}
		if (previousEventTrigger) {trigRead=true; stayinloop=true;}
		previousEventTrigger=false;
      	faster_data_load (data, &q_tdc);
      	timestamp = clockt * 1e9 + qdc_conv_dt_ns (q_tdc.tdc);   // long double
//cout<<"alias: "<<"QDC_TDC_X1"<<", label:"<<label<<", clockt:"<<clockt<<", timestamp:"<<timestamp<<endl;


		//firstEvent=false;
		charge = qdc_conv_q_mVns (q_tdc.q1); // in mV.ns
		eventCounter++;
//    if (q_tdc.q1_saturated) printf ("        saturated : q1");
//      printf ("\n");
	}

/***************************

CONDITION TO ACCEPT ONLY CERTAIN EVENT REGARDING THE DISTANCE FROM THE timestampRef

*************************** */

// fill histogram of current bunch (or total bunch)

	if (trigRead) {
		if ((alias == QDC_TDC_X1_TYPE_ALIAS)&&(label==2)) // secures not to write the counters
		{
			bunchHist->Fill((timestamp-timestampRef)/1e6); // it will write only events after the trigger (label=1)
			bunchHistTotal->Fill((timestamp-timestampRef)/1e6);
			bcgHist->Fill((timestamp-timestampRef)/1e6);
		}
	}

}// end while

//cout<<setprecision(9)<<"timestamp> "<<timestamp/1e9<<", timestampFirst> "<<timestampFirst/1e9<<endl;
	TimeL->SetText(Form("Time elapsed = %f3.3", (timestamp-timestampFirst)/1e9));

   fCanvas->cd(1);
	if (TxtButonDraw->IsOn()) 	bunchHist->Draw();
    if	(TxtButonDraw->IsOn())   fCanvas->Update();

return 0;
}
MyMainFrame::~MyMainFrame() {
   // Clean up used widgets: frames, buttons, layout hints
   //fMain->Cleanup();
   //delete fMain;
}

void MyMainFrame::MakeInverse(){
	
	if (bFileOpen) {
		faster_file_reader_close (reader); //this will insure to start from the beggining
		bunchHist->Reset();
		bunchHistTotal->Reset();
		jumpTrig->SetNumber(-1);
		bFileOpen=false;		
	}
	cout<<fileNameTG->GetText()<<endl;
//reader = faster_file_reader_open (filefast1);
if ((reader = faster_file_reader_open (fileNameTG->GetText()))!=NULL){
	 fileL->SetText(Form("open file: %s", fileNameTG->GetText()));
	bFileOpen=true;
}
else {
	fileL->SetText("NOT EXISTING FILE !!!");
	bFileOpen=false;
	return;
}
	int cnt(0), i;
	bool status;
	TF1 *ff = new TF1("ff","1", 0., histRight->GetNumber());
	

   fCanvas->cd(1);


	
	while (status=DoDraw()==0) cnt++;
	
	// making integral of the distribution
	
	Int_t bcgBins = Int_t(Float_t(NBins->GetNumber())*(histRight->GetNumber()-histLeft->GetNumber())/(BCGRight->GetNumber()-BCGLeft->GetNumber()));
	Int_t avg=0;
	//for (i=1; i<=bcgBins; i++) avg+=bcgHist->GetBinContent(i);
	//avg= Int_t(Float_t(avg)/Float_t(bcgBins));
	//avg=200;
	cout<<"avg= "<<avg<<endl;
	for (i=1; i<=NBins->GetNumber();i++) {
		bunchHistTotal->SetBinContent(i, bunchHistTotal->GetBinContent(i)-avg);//-avg);
		cout<<i<<": "<<bunchHistTotal->GetBinContent(i)<<endl;
	}
	
	for (i=1; i<=NBins->GetNumber(); i++){   
		integralDistribution -> SetBinContent(i, bunchHistTotal->Integral(1,i));
	}
	integralDistribution -> Scale(1/bunchHistTotal->Integral(1,NBins->GetNumber()));
	
	// 19.1.2017. for checking
	TH1F *tmpIntDist = (TH1F*) integralDistribution->Clone();
	
	// end checking 19.1.2017.
	
	TH1F *inverseDistFunc = new TH1F("InverseDistribution","Inverse Distribution", samplesNo->GetNumber(), 0, histRight->GetNumber());
	
	Float_t Ystep=1./samplesNo->GetNumber();
	cout<<"Ystep="<<Ystep<<endl;
	Float_t Xstep,x1,x2;
	Float_t y1, y2;
	Int_t bin;
	Int_t shift = Int_t(shift->GetNumber()/(histRight->GetNumber()/samplesNo->GetNumber()));
	
	cout<<"shift = "<<shift<<endl;
	
	for (i=1; i<=shift;i++) inverseDistFunc->SetBinContent(i, 0);
	
	
	for (i=1+shift; i<(samplesNo->GetNumber()+1); i++){
		
		bin = integralDistribution->FindFirstBinAbove(Ystep);
		y2=integralDistribution->GetBinContent(bin);
		if (bin>1) y1=integralDistribution->GetBinContent(bin-1);
		else y1=0;
		
		//cout<<"bin: "<<bin<<", intDist(bin)="<<y2<<", intDist(bin-1)="<<y1<<endl;
		
		x2 = integralDistribution->GetXaxis()->GetBinCenter(bin);
		x1 = integralDistribution->GetXaxis()->GetBinCenter(bin-1);
		Xstep =x2-x1;
		//cout<<"x2="<<x2<<", x1="<<x1<<endl;
				
		if ((y2-y1)!=0) inverseDistFunc->SetBinContent(i, x2 - (x2-x1)*(y2-Ystep)/(y2-y1)); // change 17.1.2017.
		else {
			//put the content of the previous
			inverseDistFunc->SetBinContent(i, inverseDistFunc->GetBinContent(i-1));
			cout<<"Warning !!! putting the content of the previous bin in the bin "<< i <<" !!!"<<endl;
		}
		//inverseDistFunc->SetBinContent(i, x2 - (x2-x1)*(y2-Ystep)/(y2-y1));
		
		
		integralDistribution->Add(ff, -Ystep); // Add (TF1 *f1, c1) -> this = this +c1*f1
		fCanvas->cd(1);
		integralDistribution -> Draw();
		fCanvas->Update();
	}
		// the last bin must finish with 1, always
	inverseDistFunc->SetBinContent(samplesNo->GetNumber(), 1); // change 17.1.2017.
	
	
	//inverseDistFunc is normalized on 1, now it should be normalized to the expected ramping
	
	inverseDistFunc -> Multiply(ff, (endRamp->GetNumber()-offsetRamp->GetNumber())/(histRight->GetNumber()-shift->GetNumber())); // Multiply(TF1* f1, c1) -> this = this*f1*c1;
	inverseDistFunc -> Add(ff, offsetRamp->GetNumber());
	fCanvas->cd(2);
	inverseDistFunc -> Draw();
	fCanvas->cd(1);
	bunchHistTotal->Draw();
	
	fCanvas->Update();
	//integralDistribution -> Draw();
	
	ofstream myfile; // textual analysis file
	string str1(fileNameTG->GetText());
	str1.erase(str1.end()-5, str1.end());
	str1.append("_InvDistFunc.dat");
	const char * c1 = str1.c_str();
	myfile.open (c1);

/*		
	if (shift->GetNumber()>0) {
		fileL->SetText("HISTOGRAM MUST START FROM 0 !!!!");
		TimeL->SetText("HISTOGRAM MUST START FROM 0 !!!!");
		return;
	}
*/		


// check 19.1.2018
myfile<<"Total Bunch histogram \n\n\n\n\n";

	for (i=1; i<(NBins->GetNumber()+1); i++){
		myfile<<bunchHistTotal->GetBinContent(i)<<endl;
	}
	
	myfile<<"\n\n\n\n\n\n Integral Distribution \n\n\n\n\n";

	for (i=1; i<(NBins->GetNumber()+1); i++){
		myfile<<tmpIntDist->GetBinContent(i)<<endl;
	}
	myfile<<"\n\n\n\n\n";
	
// end of check 19.1.2018


	myfile<<"# Sample rate:    "<<int(1./(1e-3*float(histRight->GetNumber())/float(samplesNo->GetNumber())))<<endl;
	// 1e-3 because the histRight->GetNumber() is in ms
	myfile<<"# Samples :       "<<samplesNo->GetNumber()<<endl;
	for (i=1; i<(samplesNo->GetNumber()+1); i++){
		myfile<<inverseDistFunc->GetBinContent(i)<<endl;
		
	}
	
	myfile.close();
		
}
	

void example(int argc, char **argv) {
   // Popup the GUI...
   new MyMainFrame(gClient->GetRoot(),1000,1000);
}



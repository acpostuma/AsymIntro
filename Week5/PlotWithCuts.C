void PlotWithCuts(){
	//fill in this section: values of your PID cuts
	Double_t HMS_cer_min = 0;
	Double_t HMS_cal_min = 0;
	Double_t SHMS_cal_min = 0;
	Double_t SHMS_aero_min = 0;
	Double_t SHMS_hgcer_min = 0;
	Double_t CoinTime = 2;

	//read in some data: first load the files
	TFile *datafile = new TFile("Q3W2p32center_cointime_pos.root");
	TFile *simcfile = new TFile("Prod_Delta_Q3p0W2p32center_highe.root");
	//then get trees from the files
	TTree *data = (TTree*)datafile->Get("Cut_Pion_Events_All_Pos");
	TTree *simc = (TTree*)simcfile->Get("h10");

	//create a TCut object to hold all of our data cuts
	TCut pidcut = Form("H_cal_etottracknorm>%f && H_cer_npeSum>%f && P_cal_etottracknorm>%f && P_aero_npeSum>%f && P_hgcer_npeSum>%f && abs(CTime_ePiCoinTime_ROC1)<%f",HMS_cal_min,HMS_cer_min, SHMS_cal_min, SHMS_aero_min, SHMS_hgcer_min, CoinTime);
	//also create a cut for acceptance of SIMC: don't worry about this part
	TCut accept ="abs(hsxpfp)<0.08 && abs(hsypfp)<0.045 && abs(hsdelta)<8 &&  abs(ssxpfp)<0.06 && abs(ssypfp)<0.04 && ssdelta>-10 && ssdelta<20";

	//draw data missing mass spectrum with PID cuts
	////may want to change bins, shift of data (offset)
	data->Draw("MMpi+0.016>>temp1(200,1.1,1.4)",pidcut);
	//draw SIMC missing mass spectrum with acceptance
	simc->Draw("missmass>>temp2(200,1.1,1.4)","(Weight)"*(accept),"same");

	//save these as proper histogram objects
	TH1F* h1 = (TH1F*)gPad->GetPrimitive("temp1");
	TH1F* h2 = (TH1F*)gPad->GetPrimitive("temp2");

	//scale SIMC to the data
	Double_t x,y,z;
	Int_t normlow = h1->FindBin(1.21);
	Int_t normhigh = h1->FindBin(1.25);
	x = h1->Integral(normlow, normhigh);
	y = h2->Integral(normlow, normhigh);
	z = x/y;
	h2->Scale(z);


	//can now add axis labels, format lines and fill, add legend, etc.
	//we would like to see: where do data and SIMC overlap?
	//how can we isolate the delta events?
}

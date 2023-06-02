void FirstAsym(){
	//fill in this section: values of your PID cuts
	//currently set up for pi-neutron: run to see my first result, then calculate your own
	Double_t HMS_cer_min = 1.5;
	Double_t HMS_cal_min = 0.8;
	Double_t SHMS_cal_min = 0.05;
	Double_t SHMS_aero_min = 1.5;
	Double_t SHMS_hgcer_min = 0;
	Double_t MMpi_min = 0.91;
	Double_t MMpi_max = 0.95;
	Double_t CoinTime = 2;

	//read in some data: first load the files
	TFile *posfile = new TFile("Q3W2p32center_cointime_pos.root");
	TFile *negfile = new TFile("Q3W2p32center_cointime_neg.root");
	//then get trees from the files
	TTree *posdat = (TTree*)posfile->Get("Cut_Pion_Events_All_Pos");
	TTree *negdat = (TTree*)negfile->Get("Cut_Pion_Events_All_Neg");

	//create a TCut object to hold all of our data cuts
	TCut pidcut = Form("H_cal_etottracknorm>%f && H_cer_npeSum>%f && P_cal_etottracknorm>%f && P_aero_npeSum>%f && P_hgcer_npeSum>%f && MMpi>%f && MMpi<%f && abs(CTime_ePiCoinTime_ROC1)<%f",HMS_cal_min,HMS_cer_min, SHMS_cal_min, SHMS_aero_min, SHMS_hgcer_min, MMpi_min, MMpi_max, CoinTime);

	//draw phi with PID cuts
	posdat->Draw("ph_q>>temp1(16,-3.14,3.14",pidcut);
	//draw SIMC missing mass spectrum with acceptance
	negdat->Draw("ph_q>>temp2(16,-3.14,3.14)",pidcut,"same");

	//save these as proper histogram objects
	TH1F* h1 = (TH1F*)gPad->GetPrimitive("temp1");
	TH1F* h2 = (TH1F*)gPad->GetPrimitive("temp2");

	//can stop here and just draw the two helicity yields to see how they compare

	//calculate asymmetry:
	//need to do this or errors are done wrong
	h1->Sumw2();
	//add h1 and h2
	TH1F* sum = (TH1F*)h1->Clone();
	sum->Add(h2);
	//subtract h1 and h2
	TH1F* diff = (TH1F*)h1->Clone();
	diff->Add(h2,-1);
	//now divide diff by sum to get asym
	TH1F* asym = (TH1F*)diff->Clone();
	asym->Divide(sum);
	//draw the asymmetry
	asym->Draw("E1"); //draw option shows error bars

	//how does it look? We expect a sin curve, possibly modulated by cosine terms
	//to do: fit with sin curve and full asymmetry fit

}

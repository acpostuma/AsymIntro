//let's apply a simple PID cuts and see how another variable changes
void TestCut(){
	TFile *datfile = new TFile("Q3W2p32center_pos.root");
	TTree *data = (TTree*)datfile->Get("Cut_Pion_Events_Prompt_Pos");

	//look at HMS cerenkov:
	
	//draw a variable into a histogram, controlling axis limits
	data->Draw("H_cer_npeSum>>temp1(100,0,25)");
	//get it as a histogram
	TH1F* h1 = (TH1F*)gDirectory->Get("temp1");

	//now draw the same data but with a cut on the HMS calorimeter
	data->Draw("H_cer_npeSum>>temp2(100,0,25)","H_cal_etottracknorm>0.8","same");
	//get hist
	TH1F* h2 = (TH1F*)gDirectory->Get("temp2");

	//now to make it clear what we are looking at, let's add a legend
	//first, change one line color
	h2->SetLineColor(2);
	//now create the legend
	TLegend *leg = new TLegend(0.8,0.8,1,1); //arguments are position xlow, ylow, xhigh, yhigh
	//add entries to the legend
	leg->AddEntry(h1,"No cuts","l"); //arguments are object, title, style
	leg->AddEntry(h2,"HMS cal cut","l"); //"l" style means draw a line
	//and draw the legend!
	leg->Draw();

	//look at the differences between the two histograms
	//does this make sense given what we know about the variables involved?

	//no task here, but note that this code might be useful in doing the task in the "PlotPhi.C" file
}


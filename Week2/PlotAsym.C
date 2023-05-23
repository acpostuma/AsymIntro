//plot one set of asymmetry histograms
void PlotAsym(){
	//load in the file
	TFile *f1 = new TFile("Q3W2p32center_highe_out_hists.root");
	//read histogram from file
	TH1F *h1 = (TH1F*)f1->Get("Bin1");

	//create a canvas
	TCanvas *c1 = new TCanvas("c1","Asymmetry plots");
	//divide the canvas to draw multiple plots
	c1->Divide(2,2);
	c1->cd(1); //go to the first subplot
	h1->Draw(); //draw first bin

	//now define a function and fit to the data
	//asymmetry is generally sinusoidal, so let's fit a sin curve
	TF1 *sinfit = new TF1("sinfit","[0]*sin(x)",0,180); //arguments are name, function, and domain of function
	//do the fitting
	h1->Fit("sinfit");

	//challenge for you!
	//1. Draw bins 2,3, and 4 in the empty subplots of the canvas
	//2. Fit the sin function to these bins as well
	//3. Format the histograms to look nice - look at the TH1F drawing options
	// this means clearly visible data points, proper axis labels, and error bars
}


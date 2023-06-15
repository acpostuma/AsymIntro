//This macro does a weighted average of three histograms
//Note that the 3 input hists need to have the same number of bins
//You define the input files and histograms or this will not run!
//Go to Plot() below to do this

//the actual calculation: don't change this part
TH1F* WeightAvg(TH1F* hleft, TH1F* hright, TH1F* hcenter){

	Int_t nbins = hcenter->GetNbinsX(); //get number of bins
	
	//define variables
	Double_t nleft, nright, ncenter; //number of counts in bin
	Double_t sleft, sright, scenter; //error on bin
	Double_t wleft, wright, wcenter; //weight of bin
	Double_t avg, avg_err; //weighted average results
	
	//define histogram to fill:
	TH1F* asym = new TH1F("asym","Weighted Asymmetry",nbins,-3.14,3.14);
	
	//loop over each bin:
	for (int i=0; i<nbins; i++){
		//get content from L, R, and C
		nleft=hleft->GetBinContent(i);
		nright=hright->GetBinContent(i);
		ncenter=hcenter->GetBinContent(i);
		//get error from L, R, and C
		sleft=hleft->GetBinError(i);
		sright=hright->GetBinError(i);
		scenter=hcenter->GetBinError(i);
		//compute weights
		wleft=1/(sleft*sleft);
		wright=1/(sright*sright);
		wcenter=1/(scenter*scenter);
		//get rid of divide by zero:
		if (sleft==0)wleft=0;
		if (sright==0)wright=0;
		if (scenter==0)wcenter=0;
		//now compute the weighted average
		avg = (nleft*wleft + nright*wright + ncenter*wcenter)/(wleft + wright + wcenter);
		//and the error on the average
		avg_err = sqrt(1/(wleft + wright + wcenter));
		//fill the new histogram with this data:
		asym->SetBinContent(i,avg);
		asym->SetBinError(i,avg_err);
	}
	
	return asym;
}

//Change this part
//Need to define the histograms that you pass to the function above
void Plot(){
	//define h1, h2, h3
	//they should be: asym from center, left, and right data sets
	
	TH1F* havg = WeightAvg(h1,h2,h3); //then call the weight avg function
	havg->Draw(); //and draw that
	//then you can play with the histogram as usual
}


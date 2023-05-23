void MakeHist(){
	//lets make a simple histogram
	//something called phase space: we will uniformly sample in cos(theta), then convert back to theta and plot that
	//randomly generating events often results in a phase space distribution
	
	//define the histogram
	TH1F* h1 = new TH1F("h1","Phase Space",180,0,180); //arguments are name, title, number of bins, low, high
	
	Double_t costheta, theta;

	//loop over large number of events
	for (int i=0; i<100000; i++){ 
		costheta = gRandom->Uniform(-1,1); //pick random number between -1 and 1
		theta = acos(costheta); //take arc cosine
		theta*=180/3.14; //convert to degrees
		h1->Fill(theta); //fill the histogram!
	}

	h1->Draw(); //draw the histogram to see what has happened
	
	//challenge for you
	//1. can you save the histogram to a root file and then re-open it from the file?
	//2. can you define a second histogram that calculates the compton scattered energy at the randomly distributed angle?
	//3. can you define a 2D histogram (TH2F) which saves both angle and energy?
}

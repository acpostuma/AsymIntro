void ComptonHists(Double_t KE = 200, Int_t nevents = 100000){
	//make a few histograms
	//again using Compton scattering as an example

	//create file to save results in
	TFile *f1 = new TFile("Compton_data.root","RECREATE");

	//define the histograms
	//a bunch of 1D ones
	TH1F* h1 = new TH1F("h1","Scattering Angle",180,0,180); //arguments are name, title, number of bins, low, high
	TH1F* h2 = new TH1F("h2","Scattering Energy",500,0,500);
	TH1F* h3 = new TH1F("h3","Recoil Energy",500,0,500);
	TH1F* h4 = new TH1F("h4","Recoil Angle",360,-180,180);

	//now a few 2D ones
	TH2F* h5 = new TH2F("h5","Scattered photon energy:angle",180,0,180,500,0,500);
	TH2F* h6 = new TH2F("h6","Recoil energy:angle",180,0,180,500,0,500);

	//also going to make a tree!
	TTree *cdata = new TTree("cdata","Compton Data");
	
	//define some variables to use
	Double_t costheta, theta, energy, recoil, phi;
	
	//associate some of the variables with tree branches
	cdata->Branch("q_energy",&energy,"q_energy/D");
	cdata->Branch("q_theta",&theta,"q_theta/D");
	cdata->Branch("p_energy",&recoil,"p_energy/D");
	cdata->Branch("p_theta",&phi,"p_theta/D");

	//loop over large number of events
	for (int i=0; i<nevents; i++){ 
		//randomly sample angle
		costheta = gRandom->Uniform(-1,1); //pick random number between -1 and 1
		theta = acos(costheta); //take arc cosine
		
		//calculate other quantities from angles
		energy = KE/(1+(KE/938.28)*(1-cos(theta))); //Compton Scattering energy formula
		recoil = KE + 938.28 - energy; //recoil energy from conservation of energy
		phi = atan((KE-energy*sin(theta))/(energy*cos(theta))); //recoil angle - I derived this on paper
		theta*=180/3.14; //convert to degrees
		phi*=180/3.14;
		
		//fill histograms: 1D
		h1->Fill(theta);
		h2->Fill(energy);
		h3->Fill(recoil);
		h4->Fill(phi);

		//fill histograms: 2D 
		h5->Fill(theta,energy);
		h6->Fill(phi,recoil);

		cdata->Fill();
	}

	//write histograms to file
	f1->WriteObject(h1,"h1");
	f1->WriteObject(h2,"h2");
	f1->WriteObject(h3,"h3");
	f1->WriteObject(h4,"h4");
	f1->WriteObject(h5,"h5");
	f1->WriteObject(h6,"h6");
	f1->WriteObject(cdata,"CDATA");
}

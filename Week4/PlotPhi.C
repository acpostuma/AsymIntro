void PlotPhi(){
	//load in the file, as before
	TFile *datfile = new TFile("Q3W2p32center_pos.root");
	//now take a tree from the file
	//this should look similar to the code to take a histogram 
	TTree *data = (TTree*)datfile->Get("Cut_Pion_Events_Prompt_Pos");

	//we can now draw a branch from the tree
	data->Draw("ph_q>>h1");
	//get this into a regular histogram
	TH1F *phi = (TH1F*)gDirectory->Get("h1");

	//now we can use the typical histogram commands
	phi->SetTitle("Scattering Plane Angle");

	//tasks:
	//1. plot the variable "MMpi" from the above tree
	//2. the neutron peak is right around the neutron mass, 0.94 GeV
	//pick some cuts to isolate the neutron
	//3. draw phi again with the misssing mass cuts
	//how does the distribution change?
}

/*
****Compton Scattering*****
*
*Graphs scattered photon energy, recoil proton kinetic energy, recoil proton angle,
*for set incident photon energy over a range of scattered photon angles.
*
* ****Alicia Postuma, Mount Allison University, 2020*****
*/

#include "physics.h"

//function for finding momentum from energy and mass
Double_t momentum(Double_t energy, Double_t mass){
  if (energy>=mass) { //necessary condition for particle
    return(sqrt(energy*energy - mass*mass));
  } else {
    return(-1); //error
  }
}

//function for finding energy from momentum and mass
Double_t energy(Double_t momentum, Double_t mass){
  return(sqrt(momentum*momentum+mass*mass));
}



//macro to draw plots of these quantities over a range of scattering angles
void ComptonPlot(Double_t kE=200){

  //define variables
  Int_t n=180; //initialize counter
  Double_t qth[n], rad[n], qE[n], p1E[n], arcsin[n], p1th[n]; //array of n doubles

  //loop through to do calculation at every point
  for(int i=0; i<=n; i++){ //for every degree from 0 to n (180)
    qth[i]=i; //define scattered photon angle
    rad[i]=qth[i]*kD2R; //convert angle to radians
    qE[i]=kE/(1+((kE/kMP_MEV)*(1-cos(rad[i])))); //calculate scattered photon energy
    p1E[i]=(kE*kE)*((1-cos(rad[i]))/(kMP_MEV+kE*(1-cos(rad[i])))); //calculate recoil proton energy
    arcsin[i]=(qE[i]*sin(rad[i]))/(sqrt(((p1E[i]+kMP_MEV)*(p1E[i]+kMP_MEV))-(kMP_MEV*kMP_MEV))); //intermediate step
    p1th[i]=asin(arcsin[i])/kD2R; //calculate recoil proton angle
  }

  //create three graphs, all as a function of scattered photon angle theta
  TGraph *qE_graph = new TGraph(n,qth,qE); //scattered photon energy
  TGraph *p1E_graph = new TGraph(n,qth,p1E); //recoil proton energy
  TGraph *p1th_graph = new TGraph(n,qth,p1th); //recoil proton angle

  //set up canvas
  TCanvas *c1 = new TCanvas("c1", "Compton Scattering Kinematics");
  c1->Divide(1,3); //3 vertical pads
  c1->SetCanvasSize(725,650);

  //format and draw first graph
  qE_graph->SetLineColor(2);
  qE_graph->SetLineWidth(2);
  qE_graph->RemovePoint(0);
  qE_graph->SetMinimum(0);
  qE_graph->SetMaximum(kE+10);
  qE_graph->GetXaxis()->SetLimits(0,180);
  qE_graph->SetTitle("Scattered Photon Energy; Theta (degrees); Energy (MeV)");
    c1->cd(1);
   qE_graph->Draw("AC");

  //format and draw second graph
  p1E_graph->SetLineColor(4);
  p1E_graph->SetLineWidth(2);
  p1E_graph->RemovePoint(0);
  p1E_graph->SetMinimum(0);
  Double_t p1E_max = (kE*kE)*((1-cos(180*kD2R))/(kMP_MEV+kE*(1-cos(180*kD2R))))+10;
  p1E_graph->SetMaximum(p1E_max);
  p1E_graph->GetXaxis()->SetLimits(0,180);
  p1E_graph->SetTitle("Recoil Proton Kinetic Energy in Compton Scattering;Scattered Photon Angle (degrees);Recoil Proton Kinetic Energy (MeV)");
    c1->cd(2);
    p1E_graph->Draw("AC");

  //format and draw third graph
  p1th_graph->SetLineColor(6);
  p1th_graph->SetLineWidth(2);
  p1th_graph->RemovePoint(0); //this point will be infinity, adding it makes the graph look ugly
  p1th_graph->SetMaximum(100);
  p1th_graph->GetXaxis()->SetLimits(0,180);
  p1th_graph->SetTitle("Recoil Proton Angles in Compton Scattering;Scattered Photon Angle (degrees);Recoil Proton Angle (degrees)");
    c1->cd(3);
    p1th_graph->Draw("AC");
}




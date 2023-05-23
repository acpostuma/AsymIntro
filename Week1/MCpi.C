/*
****Monte Carlo Estimation of Pi*****
*
* Estimates the value of pi by generating points inside a unit square.
* The ratio of points inside a quarter of the unit circle to all points 
* generated is assumed to be a quarter of pi.
*
* ****Alicia Postuma, Mount Allison University, 2020*****
*/

void MCpi(){
  Double_t x,y,r; //declare some variables that will be used
  Int_t total = 100000; //how many points to use
  Size_t inside=0; //number of points inside unit circle - start at 0
  for (size_t i = 0; i < total; i++) { //repeat the following process
    x=gRandom->Rndm(); //pick a random number as the x value
    y=gRandom->Rndm(); //pick a random number as the y value
    //gRandom is a root class, Rndm() is a function in this class that picks a random number between 0 and 1
    r=x*x+y*y; //calculate distance from origin
    if (r<=1) { //if the point falls within the unit circle
      inside++; //add one to counter of points inside the circle
    }
  }
  Double_t ratio=inside/total; //calculate ratio of points inside circle to total points
  Double_t pi=ratio*4; //we only looked at one quarter of the circle, so multiply by 4
  cout<<pi<<endl;
}

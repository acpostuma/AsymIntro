/***** Example Root Macros *****
 * This is a file containing some very simple root code with a lot of comments.
 * ***** Alicia Postuma 2021 *****/


//To load this file in root, run ".L Examples.C" from the same directory
//Otherwise, specify the path to the directory: e.g. ".L ~/opt/root/macros/Examples.C"

//A hello world program because it's classic
//This macro requires no arguments: to run enter "Hello()" in root
void Hello(){ //start
	cout<<"Hello World!"<<endl; //print some text to terminal
} //end

//Returns the square of a number
//The macro takes one double as an argument
//To run, put something like "Square(8)" or "Square(9.75)"
void Square(Double_t x){ //run the macro on a variable x
	Double_t y = x*x; //declare a variable y equal to x squared
	cout<<x<<"^2="<<y<<endl; //print the result
}

//Returns the product of a complex number and its conjugate
//This one takes two integers
//So we can run "SquareComplex(3,5)" but not "SquareComplex(4.89,7.902)"
void SquareComplex(Int_t a, Int_t b){
	Int_t square=a*a+b*b;
	cout<<"|("<<a<<"+"<<b<<"i)|^2="<<square<<endl;
}

//Returns the solutions to a quadratic equation with coefficients a,b,c
//This takes three floats as input
//A float has more precision than an integer but not as much as a double
void Quadratic(Float_t a, Float_t b, Float_t c){
	Double_t solution_1 = ((-b)+sqrt(b*b-4*a*c))/(2*a);
	Double_t solution_2 = ((-b)-sqrt(b*b-4*a*c))/(2*a);
	cout<<"The solutions to "<<a<<"x^2+"<<b<<"x+"<<c<<"=0 are "<<solution_1<<" and "<<solution_2<<endl;
}

//This macro requires no arguments, but will prompt you for input while running
//Start with "Grade()", then enter numbers when prompted
void Grade(){
	//With a lot of variables, it's good practice to define them all up front
	Float_t assign, lab, midterm, exam; //your grades on parts of the course
	Float_t assign_weight, lab_weight, midterm_weight, exam_weight; //how much each thing is worth
	Float_t grade, points;
	//define the grading scheme
	assign_weight=15;
	lab_weight=20;
	midterm_weight=15;
	exam_weight=50;
	//prompt to enter grades
	cout<<"Please enter your assignment average: "; //text printed to terminal
	cin>>assign; //take input from command line
	cout<<"Please enter your lab average: ";
	cin>>lab;
	cout<<"Please enter your midterm mark: ";
	cin>>midterm;
	cout<<"Please enter your desired grade in the course: ";
	cin>>grade;
	//calculate exam grade needed to get this mark in the course
	points=assign*assign_weight+lab*lab_weight+midterm*midterm_weight;
	exam=(points-grade)/exam_weight;
	cout<<"You need "<<exam<<" on the exam."<<endl;
}
	

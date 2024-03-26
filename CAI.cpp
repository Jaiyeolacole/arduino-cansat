#include <iostream>
#include <random>

 using namespace std;
 
 int randomNum(int min, int max){
 	
 	static random_device rd;
 	
 	static mt19937 gen(rd());
 	
 	uniform_int_distribution <> distribution(min, max);
 	
 	return distribution(gen);
 	
 }
 
 /*
 Computers are playing an increasing role in education. The use of computers in education is
referred to as computer-assisted instruction (CAI). Write a program that will help an elementary
school student learn multiplication
*/
 void CAI(){
 	
 	while(1){
 		
 		int num1 = randomNum(1, 9);
 	    int num2 = randomNum(1, 9);
 	    
 	    int product = num1 * num2;
 	    
 	    int answer;
 	    retry:
 	    	
 	    cout << "\n \n \t \t The product of " << num1 << " and " << num2 << " is: ";
 	    cin >> answer;
 	    if(answer == product){
 	    	
 	    	cout << "\a \t\t\t YOU ARE CORRECT!!!" << endl;
 	    	
		 }
		 else{
		 	
		 	cout << "\t \t \t NO! LET'S TRY AGAIN \n";
		 	goto retry;
		 	
		 }
	 }
 	
 	
 	
 }

int main(){
	
	cout << "\t \t \t COMPUTER ASSISTED INSTRUCTION THAT GUIDES YOU TO LEARN THE MULTIPLICATION TABLE \n";
	CAI();
		
	return 0;
}



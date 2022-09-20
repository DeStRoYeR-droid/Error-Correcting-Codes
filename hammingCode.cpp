// Hamming Code by DeStRoYeR4
#include <iostream>

using namespace std;

bool isPower(int n , const int base){
	/*
	Params :
		n		:	the number which needs to be tested
		base	: 	the base which needs to be tested for
	
	Return : 
		A boolean which signifies if n is a power of the base or not

	Functionality :
		Constantly divides n by the base until remainder = 0 and n > base
	*/

	if (n < 1) return false;			// Edge cases
	if (n == 1) return true;			// 1 is always a power
	while (n > base && n % base == 0) n = n / base;		// Looping till n > base and remainder != 0
	
	if (n % base) return false;			// Return false if remainder != 0
	return true;						// Return true otherwise
}

int Power(const int base, const int exponent){
	/*
	Params :
		base		: 	base of the exponent
		exponent	: 	power of the exponent
	
	Returns :
		The value of base ^ exponent
	*/
	int result = 1;	
	for (int i = 0; i < exponent; i++) result = result * base;
	return result;
}

class HammingCode{
	private:
		int* msg;		// Bits of the array
		int length;		// Length of the array
		bool parity;	// Boolean to store the partiy
		
	public:
		// Constructor
		// Accepts input via cin, but you can make it accept parameterized message as well
		HammingCode(int msgBits , bool evenParity, bool encodeMode = true){
			int parityBits = 0;
			while (Power(2, parityBits) < (parityBits + msgBits + 1)) parityBits++;

			this->length = encodeMode? msgBits + parityBits + 1 : msgBits + 1;
			this->msg = new int[length];
			this->parity = !evenParity;

			if (encodeMode){
				for (int i = 1; i <length; i++){
					if (isPower(i , 2)) this->msg[i] = -1;
					else{
						cout << "Please enter element " << i << " of the message ";
						cin >> this->msg[i];
					}
				}
			}
			else{
				for (int i = 1; i < length; i++){
					cout << "Please enter element " << i << " of the message ";
					cin >> this->msg[i];
				}
			}

		}
		
		// Method to encode the message stored in integer array to hamming code valid 
		void encode(){
			/*
			Params :
				None
			Returns :
				None
			Functionality :
				Changes the integer array so as to result in Hamming Code compatible message
			*/
			
			// Step 1 - Loop through the message array
			for (int i = 1; i < length; i++){
				// If iterator is a power of 2, do the following
				if (isPower(i , 2)){
					// Get the partiy bit
					bool value = this->parity;
					// Store value of iterator in another variable
					int j = i;
					// Loop while variable is less than length of the array
					while (j < length){
						// Initialise pick to be 0
						int pick = 0;
						// Pick iterator number of values
						while (pick < i){
							// Check if value being picked == 0
							// If not, use XOR
							value = (j+pick == i)? value : (value ^ this->msg[j+pick]);
							pick++; 
						}
						// Set value of variable to self + iterator + pick
						j = j + i + pick;
					}
					// Set value of ith index as the result from the parity
					this->msg[i] = value;
				}
			}
		}
		
		void decode(){
			/*
			Params :
				None
			Returns :
				None ( but you make it return a boolean if you want to )
			Functionality :
				Validates the message passed with respect to the parameters
			*/

			// Boolean to check if there is any error
			bool error = false;
			// Integer to store where the wrong value occurred
			int wrongValue = 0;

			// Step 1 - Loop through the message array
			for (int i = 1; i < length; i++){
				// If iterator is a power of 2, do the following
				if (isPower(i , 2)){
					// Get the partiy bit
					bool value = this->parity;
					// Store value of iterator in another variable
					int j = i;
					// Loop while variable is less than length of the array
					while (j < length){
						// Initialise pick to be 0
						int pick = 0;
						// Pick iterator number of values
						while (pick < i){
							// Check if value being picked == 0
							// If not, use XOR
							value = (j+pick == i)? value : (value ^ this->msg[j+pick]);
							pick++; 
						}
						// Set value of variable to self + iterator + pick
						j = j + i + pick;
					}
					// Check if the value == the ith value of the message
					if (this->msg[i] != value){
						// Add value of i to the index of wrongValue
						wrongValue += i;
						// Put error as true
						error = true;
					}
				}
			}

			// Print error message according to the situation
			if (error){
				cout << "Error at position " << wrongValue << endl;
			}
			else{
				cout << "No error" << endl;
			}
		}

		// Overloading << operator		
		friend ostream& operator << (ostream& out, const HammingCode& obj){
			for (int i = obj.length-1; i > 0; i--){
				out << obj.msg[i];
				out << " ";
			}
			out << endl;
			return out;
		}
};

int main(){
	HammingCode x(4, true);
	x.encode();
	cout << x;
	HammingCode y(7, true, false);
	y.decode();
	return 0;
}

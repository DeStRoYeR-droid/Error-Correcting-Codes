// Hamming Code by DeStRoYeR4
#include <iostream>

using namespace std;

bool isPower(const int n , const int base){
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
		int* msg;
		int length;
		bool parity;
		
	public:
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
		
		void encode(){
			for (int i = 1; i < length; i++){
				if (isPower(i , 2)){
					bool value = this->parity;
					int j = i;
					while (j < length){
						int pick = 0;
						while (pick < i){
							value = (j+pick == i)? value : (value ^ this->msg[j+pick]);
							pick++; 
						}
						j = j + i + pick;
					}
					this->msg[i] = value;
				}
			}
		}
		
		void decode(){
			bool error = false;
			int wrongValue = 0;
			for (int i = 1; i < length; i++){
				if (isPower(i , 2)){
					bool value = this->parity;
					int j = i;
					while (j < length){
						int pick = 0;
						while (pick < i){
							value = (j+pick == i)? value : (value ^ this->msg[j+pick]);
							pick++; 
						}
						j = j + i + pick;
					}
					if (this->msg[i] != value){
						wrongValue += i;
						error = true;
					}
				}
			}
			if (error){
				cout << "Error at position " << wrongValue << endl;
			}
			else{
				cout << "No error" << endl;
			}
		}

		
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

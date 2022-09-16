// Hamming Code by DeStRoYeR4
#include <iostream>

using namespace std;


bool isPower(int n , int base){
	if (n < 1) return false;
	if (n == 1) return true;
	while (n > base && n % base == 0){
		n = n / base;
	}
	
	if (n % base) return false;
	return true;
}

class HammingCode{
	private:
		int* msg;
		int length;
		bool parity;
		
	public:
		HammingCode(int msgbits, int paritybits, bool evenParity = true){
			this->length = msgbits + paritybits + 1;
			this->msg = new int[length];
			this->parity = !evenParity;
			
			int x = 0;
			for (int i = 1; i <length; i++){
				if (isPower(i , 2)) this->msg[i] = -1;
				else{
					cout << "Please enter element " << i << " of the message ";
					cin >> this->msg[i];
				}
			}
		}
		
		HammingCode(int totalbits){
			this->length = totalbits+1;
			this->msg = new int[length];
			
			for (int i = 1; i < length; i++){
				cout << "Please enter element " << i << " of the message ";
				cin >> this->msg[i];
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
	HammingCode x(4, 3);
	x.encode();
	cout << x;
	HammingCode y(7);
	y.decode();
	return 0;
}

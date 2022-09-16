// CRC (Cyclic Redundancy Check) by DeStRoYeR4
#include <iostream>

using namespace std;

void display_boolean(bool * arr , int length){
	/*
	Params :
		arr 	: 	boolean array
		length	: 	length of the boolean array

	Returns :
		NA
	
	Functionality :
		Prints out the boolean array as a string of 0s and 1s
	*/
	for (int i = 0; i < length; i++){
		if (arr[i]) cout << "1";
		else cout << "0";
	}
	cout << endl;
}

int convert_to_number(bool *arr , int length){
	/*
	Params 	:
		arr		: 	boolean array
		length	: 	length of the boolean array
	
	Returns :
		integer showing the decimal value of the defined by the values of the boolean array
		eg -
		{1 , 0 , 0} = 4
	*/
	int result = 0;
	for (int i = 0; i < length-1; i++){
		if (arr[i]) result++;
		result = result << 1;
	}
	result = result + arr[length-1];
	return result;
}

// Class where CRC is implemented
class CRC{
private:
	int len_gen;	// Length of the generating function
	int len_div;	// Length of the dividend
	bool *div;		// Boolean array to store the dividend
	bool *gen;		// Boolean array to store the generating function 

public:
	// Constructor
	CRC(){}

	// Overloading >> operator
	friend istream& operator>> (istream &in, CRC &input){
		cout << "Please enter the length of generating function ";
		in >> input.len_gen;

		cout << "Please enter the length of dividend ";
		in >> input.len_div;
		
		input.gen = new bool[input.len_gen];
		input.div = new bool[input.len_div + input.len_gen - 1];
		
		for (int i = 0; i < input.len_gen; i++){
			in >> input.gen[i];
		}
		
		for (int i = 0; i < (input.len_div); i++){
			in >> input.div[i];
		}
	}
	
	// Overloading << operator
	friend ostream& operator << (ostream &out , const CRC &input){
		out << "Generating function = ";
		for (int i = 0; i < input.len_gen; i++){
			if (input.gen[i]) cout << "1";
			else cout << "0";
		}
		out << endl;
		
		out << "Dividend = ";
		for (int i = 0; i < (input.len_div); i++){
			if (input.div[i]) cout << "1";
			else cout << "0";
		}
		out << endl;
	}
	
	// Method to encode the dividend using the generating function
	int encode(){
		int result = 0;
		
		bool* div_extended = new bool[len_div + len_gen - 1];
		for (int i = 0; i < (len_div + len_gen -1); i++){
			if (i >= len_div) div_extended[i] = false;
			else div_extended[i] = div[i];
		}
		
		bool * temp = new bool[len_gen];
		for (int i = 0; i < len_gen; i++){
			temp[i] = div_extended[i];
		}
		
		int cur_pointer = len_gen;
		while (cur_pointer <= len_gen + len_div - 1){
			if (temp[0]){
				result = result + 1;
			
				for (int i = 0; i < len_gen; i++){
					temp[i] = temp[i] ^ gen[i];
				}
			} 
			
			else{
				for (int i = 0; i < len_gen; i++){
					temp[i] = temp[i] ^ 0;
				}
			}
			
			for (int i = 0; i < len_gen-1; i++){
				temp[i] = temp[i+1];
			}
			temp[len_gen - 1] = div_extended[cur_pointer];
			result = result << 1;
			cur_pointer++;
		}
		
		int encoded_value = convert_to_number(div_extended , len_gen + len_div -1) + convert_to_number(temp , len_gen - 1);
		for (int i = len_div; i < len_div + len_gen -1; i++){
			div_extended[i] = temp[i - (len_div)];
		}
		
		cout << "Encoded value = ";
		display_boolean(div_extended , len_div + len_gen -1);
		return encoded_value ;
	}
	
	// Method to decode the given the dividend using the generating function
	bool decode(){
		bool *temp = new bool[len_gen];
		for (int i = 0; i < len_gen; i++){
			temp[i] = div[i];
		}
		
		int cur_pointer = len_gen;
		while (cur_pointer <= len_div){
			if (temp[0]){
				for (int i = 0; i < len_gen; i++){
					temp[i] = temp[i] ^ gen[i];
				}
			} 
			
			else{
				for (int i = 0; i < len_gen; i++){
					temp[i] = temp[i] ^ 0;
				}
			}
			
			for (int i = 0; i < len_gen-1; i++){
				temp[i] = temp[i+1];
			}
			temp[len_gen - 1] = div[cur_pointer];
			
			cur_pointer++;
		}
		
		for (int i = 0; i < len_gen; i++){
			if (temp[i])  return false;
		}
		return true;
	}
};

int main(){
	CRC example;
	
	cin >> example;
	cout << example;
	cout << example.decode() << endl;
	
	return 0;
}

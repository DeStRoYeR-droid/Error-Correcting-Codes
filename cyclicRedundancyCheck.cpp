// CRC (Cyclic Redundancy Check) by DeStRoYeR4
#include <iostream>

using namespace std;

void display_boolean(const bool * arr , const int length){
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

int convert_to_number(const bool *arr , const int length){
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
	// Constructor (empty...)
	CRC(){
		cout << "Please enter the length of generating function ";
		cin >> this->len_gen;

		cout << "Please enter the length of dividend ";
		cin >> this->len_div;
		
		this->gen = new bool[this->len_gen];
		this->div = new bool[this->len_div + this->len_gen - 1];
		
		for (int i = 0; i < this->len_gen; i++){
			cin >> this->gen[i];
		}
		
		for (int i = 0; i < (this->len_div); i++){
			cin >> this->div[i];
		}
	}
	// Or you can make a proper parameterized constructor

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
		return in;
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
		return out;
	}
	
	// Method to encode the dividend using the generating function
	int encode() const{
		/*
		Params :
			None
		Returns :
			An integer (base 10) signifying the value of the code after encoding with the generating function
		*/

		// Step 1 - Initialise variable to store the result (remainder).
		int result = 0;
		
		// Step 2 - Add length(generating function) - 1 0's to the end of dividend
		bool* div_extended = new bool[len_div + len_gen - 1];
		for (int i = 0; i < (len_div + len_gen -1); i++){
			if (i >= len_div) div_extended[i] = false;
			else div_extended[i] = div[i];
		}
		
		// Step 3 - Get the first length(generating function) bits of the dividend
		bool * temp = new bool[len_gen];
		for (int i = 0; i < len_gen; i++){
			temp[i] = div_extended[i];
		}
		
		// Step 3.5 - Initialise a pointer variable to know which index of the extended dividend we are working with
		int cur_pointer = len_gen;

		// Step 4 - Loop while the pointer variable initialised is less than length of extended dividend
		while (cur_pointer <= len_gen + len_div - 1){
			// Perform bit-wise XOR on the basis of the first value of the dividend
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
			
			// Remove the first bit of the dividend and add the bit at the pointer variable to the mix
			for (int i = 0; i < len_gen-1; i++){
				temp[i] = temp[i+1];
			}
			temp[len_gen - 1] = div_extended[cur_pointer];
			
			// Bit shift result to 1
			result = result << 1;
			// Increase the value of pointer variable
			cur_pointer++;
		}
		
		// Step 5 - Convert the binary value to a decimal value
		int encoded_value = convert_to_number(div_extended , len_gen + len_div -1) + convert_to_number(temp , len_gen - 1);
		
		// Step 6 - Add the remainder to the end of the dividend
		for (int i = len_div; i < len_div + len_gen -1; i++){
			div_extended[i] = temp[i - (len_div)];
		}
		
		// Display the encoded value
		cout << "Encoded value = ";
		display_boolean(div_extended , len_div + len_gen -1);

		// Return its decimal equivalent 
		return encoded_value ;
	}
	
	// Method to decode the given the dividend using the generating function
	bool decode() const{
		/*
		Params :
			None
		Returns :
			A boolean specifying whether the dividend is correct or not on the basis of the generating function
		*/

		// Step 1 - Get the first length(generating function) bits of the dividend
		bool *temp = new bool[len_gen];
		for (int i = 0; i < len_gen; i++){
			temp[i] = div[i];
		}
		
		// Step 1.5 - Initialise a pointer variable to know which index of the extended dividend we are working with
		int cur_pointer = len_gen;

		// Step 2 - Loop while the pointer variable initialised is less than length of extended dividend
		while (cur_pointer <= len_div){
			// Perform bit-wise XOR on the basis of the first value of the dividend
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

			// Remove the first bit of the dividend and add the bit at the pointer variable to the mix
			for (int i = 0; i < len_gen-1; i++){
				temp[i] = temp[i+1];
			}
			temp[len_gen - 1] = div[cur_pointer];
			
			// Increment the value of pointer variable
			cur_pointer++;
		}
		
		// If any of the value after performing the iterative XOR is 1, return false.
		for (int i = 0; i < len_gen; i++){
			if (temp[i])  return false;
		}

		// Else return true
		return true;
	}
};

int main(){
	CRC example;

	cout << example;
	example.encode();

	cin >> example;
	cout << example.decode() << endl;
	
	return 0;
}

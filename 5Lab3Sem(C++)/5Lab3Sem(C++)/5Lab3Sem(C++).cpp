
#include <iostream>
#include <string>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;
int table_size = 4;
double const A = 0.6180339887;
int int_key = 1;
string str_key = "some";



int division_hash(int key) {
	return key % table_size;
}
int multiplication_hash(int key) {
	double fractional = fmod(key * A,1);
	return table_size * fractional;
}
int string_hash(string key) {
	const int a = 29;
	const int string_length = key.length();
	int128_t  hash_value = 0;
	for (int i = 0; i < string_length; i++)
	{
		hash_value = (hash_value + int128_t(key[i] * pow(a, i)));
	}
	return  int(hash_value % table_size);

}


bool interface() {
		bool result;
		int action;
		cout << "INFO: \nINTEGER KEY is: [" << int_key << "] \nSTRING KEY is: ["<<str_key<<"] \nTable size is: [" << table_size <<"]\n\n";

		std::cout << "Choose your action (from 1 to 4).\n"
			"1 is edit INTEGER key for hashing\n"
			"2 is edit STRING key for hashing\n"
			"3 is use hash fuctions\n"
			"4 is edit table size\n"
			"0 if you want to finish the program " << endl;

		cin >> action;
		cout << endl;
		switch (action) {
		case 1:

			cout << "Input integer key: " << endl;
			cin >> int_key;
			break;
			
		case 2:
			cout << "Input string key: " << endl;
			getline(cin>> ws, str_key);
			break;
		case 3:
			cout << "Using DIVISION hashing\nFor key: [" << int_key << "] HASH value: " << division_hash(int_key) << "\n\n";
			cout << "Using hashing by MULTIPLICATION\nFor key: [" << int_key << "] HASH value: " << multiplication_hash(int_key) << "\n\n";
			cout << "Using STRING hashing\nFor key: [" << str_key << "] HASH value: " << string_hash(str_key) << "\n\n";
			break;
		case 4:
			cout << "Input size for a table: " << endl;
			cin >> table_size;
			break;
		case 0:
			std::cout << "Thanks for using, bye bye";
			return false;
			break;
		default:
			cout << "Wrong number!!!";
		}
		cout << "\n\n";
		return true;
	
}

int main()
{
	bool result;
	do {
		result = interface();
	} while (result != false);




}


#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> dec_to_bin(unsigned int x){

	vector<int> a(23);
	
	for(int i = 0; x > 0; ++i){    
		a[i] = x % 2;    
		x = x / 2;  
	}   

	return a;
}

void print_bin(vector<int> a){
	for(int i = a.size() - 10 ; i >= 0 ; --i){    
		cout << a[i];    
	}    
}

int get_opcode(unsigned int op) {
	return op >> (32 - 6);
}

int get_rs(unsigned int op) {
	return (op >> (32 - 11)) & 31;
}

int get_rt(unsigned int op) {
	return (op >> (32 - 16)) & 31;
}

int get_rd(unsigned int op) {
	return (op >> (32 - 21)) & 31;
}

int get_addr(unsigned int op) {
	return (op >> (32 - 16)) & 31;
}

int get_addr_j(unsigned int op) { 
	return (op << 6) >> 6;
}


int main(){

    vector<unsigned int> vs;

    fstream input("mips-test.bin", fstream::binary | fstream::in);

    unsigned int v;
    while(input.read(reinterpret_cast<char*>(&v), sizeof(v)))
        vs.push_back(v);

    input.close();

    // Now each element in vs is a single opcode.
    // vs[0] = the MIPS instruction

	for(unsigned int op : vs) {

		vector<int> a = dec_to_bin(get_rs(op));
		vector<int> b = dec_to_bin(get_rt(op));
		vector<int> c = dec_to_bin(get_rd(op));
		vector<int> d = dec_to_bin(get_addr(op));
		vector<int> e = dec_to_bin(get_addr_j(op));
		vector<int> f = dec_to_bin(get_opcode(op));
	
		if(get_opcode(op) == 0) {
			// R-format: get_rs, get_rt, get_rd
			cout << "R-Format" << endl;
			cout << "Opcode: "; print_bin(f); cout << endl;
			cout << "RS: "; print_bin(a); cout << endl;
			cout << "RT: "; print_bin(b); cout << endl;
			cout << "RD: "; print_bin(c); cout << endl;
			cout << endl;
			
		}

		else if(get_opcode(op) == 2 || get_opcode(op) == 3){
			// J-format: get_addr_j
			cout << "J-Format" << endl;
			cout << "Opcode: "; print_bin(f); cout << endl;
			cout << "Address: "; print_bin(e); cout << endl;
			cout << endl;
			
		}

		else{
			// I-format: get_rs, get_rd, get_addr
			cout << "I-Format" << endl;
			cout << "Opcode: "; print_bin(f); cout << endl;
			cout << "RS: "; print_bin(a); cout << endl;
			cout << "RD: "; print_bin(c); cout << endl;
			cout << "Address: "; print_bin(d); cout << endl;
			cout << endl;
			
		}
	}
    
	return 0;

}
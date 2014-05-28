#include <cstdlib>
#include <iostream>

using namespace std;

int main() {

	size_t amount = 1000 * 150;
	int arr[amount]; 
	for(size_t c=0; c < amount; c++) {
		arr[c] = rand();	
	}

	for (size_t c = 0; c < amount; c++) {
		int dcounter = 0;
		int cur = arr[c];
		for(size_t j =0; j < amount; j++) {
			if (cur == arr[j])
				dcounter ++;
		}
		
		if (dcounter > 1) {
			cout << "Duplication: " << cur << " - " << dcounter << endl;
		}
	} 
}

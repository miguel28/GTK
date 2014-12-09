#include <iostream>
#include <cstdlib>
using namespace std;

void getmin(int *decimal, int *unitary, int num){
	*decimal = num/10;
	*unitary=num-(*decimal*10);
	
}

int main (int argc, char * const argv[]) {
    int i,j,dif,multi,suma, dec, uni;
	
	for(i=0;i<24;i++)
		for(j=0; j<60; j++){
			dif=60-j;
			multi=dif*j;
			getmin(&dec,&uni,j);
			suma=dec+uni;
			
			if(suma==i && j==i*dif){
				cout << "Hora -> "<<i<<":"<<j<<endl;
			}
		}
	
	system("pause");
    return 0;
}


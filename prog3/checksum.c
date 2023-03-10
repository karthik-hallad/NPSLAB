#include<stdio.h>

unsigned short getChecksum(char* type) {
	unsigned int field[9];
	printf("Enter the 9 16bit fields for %s packet (excluding checksum) :\n", type);
	int sum = 0, i;	
	for(i=0;i<9;i++) {
		scanf("%x",&field[i]);
		sum+=field[i];
		while(sum>>16) 
			sum = (sum&0xffff) + (sum>>16);
	}
	sum = (~sum&0xffff);
	printf("Checksum of %s packet : %x\n\n", type,sum);
	return sum;
}

int main() {
	int sum1 = getChecksum("sent");
	int sum2 = getChecksum("received");
	if(sum1==sum2) printf("No Error!\n");
	else printf("Error Detected!\n");
	return 0;
}


#include"encDec.h"
int main(void)
{
    char *text,*t2;
    long length,l2;
    FILE *fp,*fo;
    char *binary,*crc_encoded;
    char *polynomial = "100000100110000010001110110110111";
    char *crc_checksum,*unpaddedbinary;
	int textLength, binaryLength;

	fp = fopen("input.inpf", "r");  
 	fseek(fp, 0, SEEK_END);		 //Find end of the file 
 	length = ftell(fp);    //find file data length 
    l2 =length;
 	fseek(fp, 0, SEEK_SET);   //sets the cursor 
 	text = malloc(length + 1);
    t2 = malloc(length + 1);
 	fread(text, length, 1, fp); //read data
    printf("\n%s\n",text);
 	fclose(fp);

	textLength = strlen(text);
    binaryLength = textLength * 8;      // 8 binary digits + 1 space separator
    binary = malloc(binaryLength + 1);  // + 1 null terminator
    crc_encoded = malloc(binaryLength + 1+32);
    unpaddedbinary = malloc(binaryLength + 1);
    if(binary == NULL)
        exit(1);
    
    textToBinary(text, textLength, binary, binaryLength);
    for (int i =0;i<binaryLength;i++){
        *(crc_encoded+i) = *(binary +i); 
        //*(unpaddedbinary+i) = *(binary+i);
    }
    printf("Please provide 1 for CRC and 2 for Hamming:");
    int errortype ;
    int error_added ;

    scanf("%d",&errortype);
    if(errortype == 1){
        char *temp = binary;
        crc_checksum =  crc_remainder(binary,binaryLength, polynomial);
        for (int i = 0;i<32;i++){
            *(crc_encoded+binaryLength+i) = *(crc_checksum+i);
        }
        printf("Your crc_checksum encoding is:\n%s\n", crc_encoded);
        printf("\nWould you like to insert an error bit 1) Yes or 2) No:");
        scanf("%d",&error_added);
        if (error_added == 1){
            *(crc_encoded + 4) =  *(crc_encoded + 4) == '1'?'0':'1';
            printf("\n Error bit inserted at position 4:\n");
        } else if(error_added == 2){
            printf(" Opted for NO ERROR INSERTION\n");
        }
        int status = crc_error_detection(crc_encoded,binaryLength, polynomial);
        printf("Return Status from CRC is : %d",status);
        free(binary);
    } else if(errortype == 2){
        for (int i =0;i<binaryLength;i++){
            *(unpaddedbinary+i) = *(binary+i);
        }
       char *p = Hammig(binaryLength, unpaddedbinary);
        printf("\nWould you like to insert an error bit 1) Yes or 2) No:");
        int err;
        scanf("%d",&err);
        if(err == 1){
            printf("\nProvide a bit position to manipulate and generate error:");
            int manipulated_bit;
            scanf("%d",&manipulated_bit);
            printf("Before Manupation: %c\n",*(p+manipulated_bit));
            *(p+manipulated_bit) = *(p+manipulated_bit)=='1'?'0':'1';
            printf("After Manupation: %c\n",*(p+manipulated_bit));


        }else {
            printf("\nOpted for NO ERROR INSERTION\n");
        }
        char *q = Hamming_Detection_Correction(strlen(p), p);

    } else {
        printf("Invalid Input");
        exit(1);
    }
    if ((errortype != 1 && error_added !=1 )){
        printf("\n%s\n",text);
        fo = fopen("output.inpf", "w");
        fprintf(fo, text, length);  
        fclose(fo);
    }
	return 0;
}

void textToBinary(char *text, int textLength, char *binary, int binaryLength)
{
    char *octet = malloc(9);
    char *zero = malloc(1);
    *zero = '0';
    if(octet == NULL)
        exit(1);
    while(*text)
    {
        decimalToBinary(*text, octet);
        while(*octet)
            *binary++ = *octet++;

        ++text;
        octet -= 8;
    }
    for (int i=0;i<32;i++){
        *binary++ = *zero;      //Padding Zeros here 
    }
    *binary = '\0';

    binary = binary -(binaryLength+32);
    printf("Padded :%s\n",binary);
    free(octet);
}

void decimalToBinary(int decimal, char *octet)
{
	octet += 8;
	*octet = '\0';
	if(decimal == 0)
	{
		octet -= 8;
		octet = "00000000";
	}
	else
	{
		while(decimal > 0)
		{
			--octet;
			*octet = decimal % 2 + '0';
			decimal = decimal / 2;
		}
	}
    while(strlen(octet) < 8)
    {
        --octet;
        *octet = '0';
    }

}
char *crc_remainder(char *binary, int binaryLength, char *polynomial){
    //printf("\nnn %s \n",binary);
    char *tempBinary = binary;
    for (int i = 0; i < binaryLength ; i++){
        if (*tempBinary == '1'){
            for (int j = 0;j<32;j++){
                int a,b ;
                a = *(tempBinary+j) == '1'?1:0;
                b = *(polynomial+j) == '1'?1:0;

                *(tempBinary+j) = ((a^b) == 1)?'1':'0';
            }
        }
        tempBinary++;
    }
        //printf("\nnn %s \n",binary);

        return tempBinary;

}

int crc_error_detection(char *binary, int binaryLength, char *polynomial){
    char *tempBinary = binary;
    long unsigned int length = strlen(binary);
    char *check = malloc(length);
    char *resp;
    int q=0;
    for ( q =0;q< length-32;q++){
        *(check+q) = *(tempBinary+q);
    }
    int pos = q;
    while(q<length){
        *(check+q) = '0';
        q++;
    }
    resp = crc_remainder(check, binaryLength, polynomial);
    //printf("\n%s\n%s",binary,check);
    for (int k = pos;k<length;k++){
        if(*(tempBinary+k) != *(check+k)){
            printf("\nError in data\n");
            return 0;
        }
    }
    printf("\nNo Error data is transmitted\n");
    free(check);
    return 1;

}


char *Hammig(int dataLength, char *data){
    int twoPower = 1,parityBits=0;
    while(twoPower <= (1+ parityBits + dataLength)){    //This will calculate the  number of parity bits
        parityBits++;
        twoPower *= 2;
    }
    printf("parity bits :%d \n",parityBits);

    int hammingLength = dataLength + parityBits;
    //printf("Hamming Length = %d\n", hammingLength);
    char *hammingcode;
    hammingcode = malloc(hammingLength);

    twoPower = 1;
    int j =0,i;
    char *temp = hammingcode;

    for ( i = 0 ; i < hammingLength ; i++) {
        if(i == twoPower - 1){
            twoPower *= 2;
            *(hammingcode + i) = 'p';
            continue;
        }
        *(hammingcode + i) = *(data + j);
        j++;

    }
    printf("%s", hammingcode);
    int initial,final,power =1;
    int xor = 0 ;
    printf("\n");
    for (int parity = 1 ; parity <= parityBits ; parity++){
        
        initial = power - 1;
        final = hammingLength;
        power *= 2;
        for(int z = initial ; z <= final ; z += parity*2 ){
            //printf("\n %d %d ",z,parity);
            for (int y = z ; y < z+parity && y< hammingLength; y++){
                if(*(hammingcode + y) == 'p')
                    continue;
                int a = *(hammingcode + y) == '0'? 0:1;
                //printf(" %d ",a);
                xor = (a^xor);
            }     
        }
        *(hammingcode + initial) = xor == 1 ?'1':'0'; 
        printf("%c",*(hammingcode + initial));
        xor = 0;
    }
    printf("\n\n%s\n\n",hammingcode);


    return hammingcode;
}

char *Hamming_Detection_Correction(int dataLength, char *hammingcode){
    
    int twoPower = 1,parityBits=0;
    while(twoPower <= (1 + dataLength)){    //This will calculate the  number of parity bits
        parityBits++;
        twoPower *= 2;
    }
    twoPower = 1;
    int newLength =dataLength-parityBits;
    char *newhamming = malloc(newLength);
    twoPower = 1;
    int w =0;
    for (int i =0 ; i < dataLength ; i++){
        if(w == twoPower-1){
            w++;
            i--;
            twoPower *= 2;
            continue;;
        }
        *(newhamming+i) = *(hammingcode+w);
        w++;
        //printf("\n%c\n",*(newhamming+i));

    }
    char *p = Hammig(newLength, newhamming);
    printf("\n%s\n",p);
    twoPower = 1;
    int po =0;
    int count  = 0;
    for (int i=0 ; i < dataLength ;i++){
        if(i== twoPower -1){
            po++;
            if(*(p+i) != *(hammingcode+i)){
                count += po;
            }
            twoPower *=2;
        }
    }
    printf("Bit  :%d is Manipulated\n",count);

    if(count == 0){
        printf("\nNo Error in transmitted data\n");
    }
    return NULL;
}


 #include <c8051f020.h> 
sbit ALE	=	P3^4;
sbit OE		=P3^7;
sbit START	=	P3^5;
sbit EOC		=P3^6;
sbit SEL_A		=P3^1;
sbit SEL_B		=P3^2;
sbit SEL_C		=P3^3;
sbit ADC_DATA	=P1;
 sbit high = P3^0;
sbit low = P3^1;
sbit notch = P3^7;
 sfr DAC = 0xA0;
 
 unsigned int x[11] = {0,0,0,0,0,0,0,0,0,0,0};

 
 
 void delay(unsigned int count)  // Function to provide time delay in msec.
{
int i,j;
for(i=0;i<count;i++)
for(j=0;j<1275;j++);
} 


void main()
{
	/* Data port to input */
	ADC_DATA = 0xFF ;
 
	EOC = 1 ; /* EOC as input */
	ALE = 0 ;
 OE = 0 ;
	START = 0 ;
			/* Select channel 1 */
		SEL_A = 1; /* LSB */
		SEL_B = 0;
		SEL_C = 0; /* MSB */
	while (1) {
		x[1] =x [0] ;
		x[2]=x[1];
		x[3]=x[2];
		x[4]=x[3];
		x[5] =x [4] ;
		x[6]=x[5];
		x[7]=x[6];
		x[8]=x[7];
		x[9]=x[8];
		x[10]=x[9];
		/* Latch channel select/address */
		ALE = 1;
 
		/* Start conversion */
		START = 1;
 
		ALE = 0;
		START = 0;
	
		/* Wait for end of conversion */
		while (EOC == 1);
		while (EOC == 0);
 
		/* Assert Read signal */
		OE = 1;
	
		/* Read Data */
	x[0] = P1;
	if (!high) 
				 DAC= -0.1490 *P1 -0.1490 *x[10]-0.0644*x[1]-0.0644*x[9]-0.0741 *x[2]-0.0741 *x[8]-0.0817*x[3]-0.0817*x[7] -0.0864  *x[4] -0.0864*x[6]+ 0.9119*x[5];

	else if(!low) 
		 DAC= 0.2514*P1 +0.2514*x[10]+ 0.0024 *x[1]+0.0024 *x[9]+0.0024   *x[2]+0.0024 *x[8]+0.0025 *x[3]+0.0025 *x[7]  +0.0024  *x[4] +0.0024 *x[6]+ 0.0025*x[5];

	
	else if (!low & !high) 
				 DAC= 0.0813 *P1 +0.0813 *x[10]-0.2236*x[1]-0.2236*x[9]-0.0728 *x[2]-0.0728 *x[8]-0.0238*x[3]-0.0238*x[7] -0.0085  *x[4] -0.0085 *x[6]-0.0051 *x[5];
  else 
		DAC =P1;



OE = 0;


	}
}
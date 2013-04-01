

#include<reg51.h>
sfr lcd_P2=0xA0;	 //direccion puerto 2 en el micro
sbit rs=P3^0;  
sbit rw=P3^1;  
sbit en=P3^6; 
sbit puerto=P0^1;
int e,dec;
dispdir=0x80; //valor de posision del disparo

void delay(unsigned int contador)  
{
int i,j;
for(i=0;i<contador;i++)
for(j=0;j<1275;j++);
}

void lcd_comando(unsigned char comm)  //Funcion para enviar comandos al lcd
{
lcd_P2=comm;
en=1;
rs=0;
rw=0;
delay(1);
en=0;
}           

void lcd_dato(unsigned char disp)  //funcion para enviar datos al lcd
{
lcd_P2=disp;
en=1;
rs=1;
rw=0;
delay(1);
en=0;
}

void lcd_ini()  //funcion para inicializar el lcd
{
lcd_comando(0x38); 
delay(200);
lcd_comando(0x0F); 
delay(200);
 
}

void enemigo()  //funcion del enemigo
{
 e=9;
 dec=0x89;
 dispdir=0x80;
for(e;e>1;e--)
 {
 lcd_comando(64);  //posicion de memoria donde esta el enemigo
  lcd_comando(dec);
  lcd_dato(0);
  delay(5);
  dec=dec-0x01;
  if(puerto)
  {
  break;
  }
  lcd_comando(72); 
  lcd_comando(dec+0x01);
  lcd_dato(1);
  delay(5);
  }
  
}
	      

 void IntExt()interrupt 0	   //funcion de la interrupcion
{	 
delay(5);	
}

void graficos()
{

  lcd_comando(64);  //direccion del enemigo
  lcd_dato(14);
  lcd_dato(31);
  lcd_dato(21);
  lcd_dato(31);
  lcd_dato(31);
  lcd_dato(14);
  lcd_dato(10);
  lcd_dato(0);
  lcd_comando(0x89); //direccion en pantalla
  lcd_dato(0);     //matriz numero 0
  
  lcd_comando(72);  // direccion del clear
  lcd_dato(0);
  lcd_dato(0);
  lcd_dato(0);
  lcd_dato(0);
  lcd_dato(0);
  lcd_dato(0);
  lcd_dato(0);
  lcd_dato(0);
  lcd_comando(0x81);
  lcd_dato(1);
  

  lcd_comando(80);  //direccion de disparo
  lcd_dato(0);
  lcd_dato(4);
  lcd_dato(2);
  lcd_dato(31);
  lcd_dato(2);
  lcd_dato(4);
  lcd_dato(0);
  lcd_dato(0);
  lcd_comando(0x81);
  lcd_dato(2);
  
 	 
  lcd_comando(88);  // direccion de nave
  lcd_dato(31);
  lcd_dato(0);
  lcd_dato(31);
  lcd_dato(31);
  lcd_dato(0);
  lcd_dato(31);
  lcd_dato(0);
  lcd_dato(0);
  lcd_comando(0x80);
  lcd_dato(3);
 
    lcd_comando(96);  //direccion de explosion
  	lcd_dato(0);
  	lcd_dato(4);
  	lcd_dato(14);
 	lcd_dato(31);
 	lcd_dato(14);
 	lcd_dato(4);
	lcd_dato(0);
 	lcd_dato(0);
 	lcd_comando(0x90);
  	lcd_dato(4);
 
}

void main()
{
			//interrupciones
	IT0=1;
	EA=1;
	EX0=1;
	puerto=0;
			   //se inicializa el lcd y se cargan los graficos
	lcd_ini();
	graficos();
		
while(1){			   //ciclo infinito

	   enemigo();		//corre el enemigo

	if (puerto){			//verificacion para ver si se el puerto esta en 1 (activacion del push boton)
		
		for(e;e>1;e--)
 		{
			 
			dispdir=dispdir+0x01;

 			 lcd_comando(80); 
  		  	lcd_comando(dispdir);
  			lcd_dato(2);
	  		delay(5);  

			lcd_comando(72); 
  			lcd_comando(dec+0x01);
	  		lcd_dato(1);
  			delay(5);
	
  			lcd_comando(64); 
  			lcd_comando(dec);
  			lcd_dato(0);
  			delay(5);

		 	if (dispdir==dec)
			{
				lcd_comando(54); 
  				lcd_comando(dispdir);
  				lcd_dato(4);
  				delay(50);
		
				lcd_comando(72); 
  				lcd_comando(dispdir);
  				lcd_dato(1);
  				delay(5);
			break;	
			}
  			
			dec=dec-0x01;	
					
			lcd_comando(72); 
  			lcd_comando(dispdir);
  			lcd_dato(1);
  			delay(5);
		
			lcd_comando(72); 
  			lcd_comando(dec+0x01);
  			lcd_dato(1);
  			delay(5);
			
 			}	
  
	   }
	}
}

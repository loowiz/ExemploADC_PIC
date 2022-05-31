/*=======================================================
					SENAI A. Jacob Lafer
					====================

Nome do projeto:	Conversor Analógico-Digital (ADC)
Versão:				1.0x
Última revisão:		01/06/2020
Cliente:			SENAI
Desenvolvimento:	Luiz Ricardo Bitencourt

Descritivo Funcional:
Teste do módulo ADC.

Inputs:
- RA0 - Entrada analógica

Outputs:
- RB2 - Display RS
- RB3 - Display E
- RB4-RB7 - Display Data
=========================================================*/

//======================================================
// Bibliotecas
//======================================================
#include <xc.h>
#include "lcd_4vias.h"
#include "adc.h"

// ==========================================================
// CONFIGURAÇÕES DO MICROCONTROLADOR
// ==========================================================
#pragma config  FOSC    = HS
#pragma config  PLLDIV  = 1
#pragma config  CPUDIV  = OSC1_PLL2
#pragma config  USBDIV  = 1
#pragma config  BORV    = 0
#pragma config  WDTPS   = 1
#pragma config  MCLRE   = ON
#pragma config	PWRT=ON, LVP=OFF, IESO=OFF, WDT=OFF, PBADEN=OFF, BOR=OFF
#pragma config  CCP2MX=ON, LPT1OSC=OFF, ICPRT=OFF, XINST=OFF, VREGEN=OFF
#pragma config  CP0=OFF, CP1=OFF, CP2=OFF, CP3=OFF, CPB=OFF, CPD=OFF, WRTD = OFF
#pragma config  WRT0=OFF, WRT1=OFF, WRT2=OFF, WRT3=OFF, WRTC = OFF, WRTB = OFF
#pragma config  EBTR0=OFF, EBTR1=OFF, EBTR2=OFF, EBTR3=OFF, EBTRB=OFF
// ==========================================================


//======================================================
// Programa Principal
//======================================================
void main (void){
    // -------------------------------------------------
	// Declaração de variáveis locais
	// -------------------------------------------------
	unsigned int	ValorADC;
    unsigned int    ValorTemp;
    // ------------------------------------------------------
    
    // -------------------------------------------------
	// Configurações iniciais
	// -------------------------------------------------
    TRISB = 0b00000011;     // Port B, saídas do RB2 até RB7

	IniciaLCD();            // Inicializa Display
	LimpaLCD();             // Limpa Display
    Inicializa_ADC();		// Inicializa ADC
    // ------------------------------------------------------

    // ------------------------------------------------------
    // LOOP PRINCIPAL
    // ------------------------------------------------------
	while(1){
		ValorADC = LerADC();        // Lê entrada analógica e grava em uma variável
       
        PosicionaLCD(1,1);
        StringLCD("Valor ADC: ");
        PosicionaLCD(1,13);
		EscreveLCD((ValorADC/1000)%10 + 48);    // Separa e escreve digito "milhares"
		EscreveLCD((ValorADC/100)%10 + 48);     // Separa e escreve digito "centenas"
		EscreveLCD((ValorADC/10)%10 + 48);      // Separa e escreve digito "dezenas"
		EscreveLCD(ValorADC%10 + 48);           // Separa e escreve digito "unidades"
       
        PosicionaLCD(2,1);
        StringLCD("Convertido: ");
        PosicionaLCD(2,13);
        
        ValorTemp = ((ValorADC*5.0)/1024)*200;  // Converte para escala de 0.0 a 99.0
        
        EscreveLCD((ValorTemp/100)%10 + 48);    // Dígito das "centenas" vira "dezenas"
		EscreveLCD((ValorTemp/10)%10 + 48);     // Dígito das "dezenas" vira "unidades"
        EscreveLCD('.');                        // Ponto de separação decimal
		EscreveLCD(ValorTemp%10 + 48);          // Dígito das "unidades" vira "decimal"
	}
    // ------------------------------------------------------
}

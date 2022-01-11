/*
 * menu.h
 *
 * Created: 11.01.2022 09:41:09
 *  Author: Mekon
 */ 


#ifndef MENU_H_
#define MENU_H_

#include <avr/pgmspace.h>
#include "uart.h"
#include "functions.h"
#include "init.h"

//Forward declaration
void AusgabeBetriebsablaufliste();
void mainmenu_func();
void configuration_func();
void install_func();
void error_func();
void firmware_func();

volatile char g;
volatile char id_crossroad;

enum MainMenu{configuration = 1, install = 2, errors = 3, firmware = 4}mainmenu;

enum ConfigurationMenu{id_change = 1, state_request, state_change, operational_flow_read, operational_flow_change, date_read, date_change, return_to_main_menu1 = 0 }configmenu;
enum InstallationMenu{lights_install = 1, lights_deinstall, return_to_main_menu2 = 0}installmenu;
enum ErrorMenu{no_error = 1, red_light_mr, red_light_sr, flash_error, sram_error, stack_error, sw_error, time_error, return_to_main_menu3 = 0}errormessage;
enum FirmwareMenu{firmware_version = 1, firmware_update}firmwaremenu;

//**************************************************************************************************************************************//
//UART_Ausgaben
//Hauptmenü
const char mainMenu_message_menu[] PROGMEM = "\n\tAmpel-Leitsystemmenue\n1. Ampel-Konfiguration\n2. Ampel installieren\\deinstallieren\n3. Fehlermeldungen auslesen\n4. Firmware\n\nWaehlen Sie eine Nummer aus: ";

//Konfigurations-Menü
const char configuration_message_menu[] PROGMEM = "\tAmpel-Konfiguration\n\n1. Kennung aendern\n2. Zustandsabfrage\n3. Zustand aendern\n4. Betriebsablauf auslesen\n5. Betriebsablauf aendern\n6. Datum\\Uhrzeit auslesen\n7. Datum\\Uhrzeit aendern\n8. Zurueck zum Hauptmenue\n\nWaehlen Sie eine Nummer aus: ";

const char id_changes_message_menu[] PROGMEM = "\n\tAmpelkennung aendern\n3. Zurueck zum Hauptmenue\n\nWaehlen Sie eine Nummer aus: ";

//Installtion/Deinstalltion
const char install_message_menu[] PROGMEM = "\t Ampel installieren\\deinstallieren\n\n1. Ampel installieren\n2. Ampel deinstallieren\n3. Zurueck zum Hauptmenue\n\nWaehlen Sie eine Nummer aus: ";
const char change_successfull_message[] = "\nDie Kennung wurde erfolgreich geändert\n";
//Fehlermeldungen
const char errors_message_menu[] PROGMEM = "\tFehlermeldungen\n\nFehlername\tCode\n1. No_error\t0x00\n2. Red_light_MR\t0x10\n3. Red_light_SR\t0x11\n4. Flash_error\t0x20\n5. SRAM_error\t0x21\n6. Stack_error\t0x22\n7. SW_Error\t0x80\n8. Time_error\t0x81\n9. Zurueck zum Hauptmenue\n\nWaehlen Sie eine Nummer aus: ";

// Fehlerbeschreibung
const char No_Error_Message[] PROGMEM = "\nKein Fehler diagnostiziert\n\nZurueck zu Fehlermeldungen mit 0: ";
const char Red_Light_MR_Message[] PROGMEM = "\nUeberwachungsfehler auf dem spannungsfuehrenden\nTeil des roten Lichtes auf der Hauptstrasse\n\nZurueck zu Fehlermeldungen mit 0: ";
const char Red_Light_SR_Message[] PROGMEM = "\nUeberwachungsfehler auf dem spannungsfuehrenden\nTeil des roten Lichtes auf der Nebenstrasse\n\nZurueck zu Fehlermeldungen mit 0: ";
const char Flash_Error_Message[] PROGMEM = "\nFehler bei der Ueberpruefung des Flash-Speichers\ndiagnostiziert\n\nZurueck zu Fehlermeldungen mit 0: ";
const char SRAM_Error_Message[] PROGMEM = "\nFehler bei der Ueberpruefung des SRAM diagnostiziert\n\nZurueck zu Fehlermeldungen mit 0: ";
const char Stack_Error_Message[] PROGMEM = "\nStack-Overflow diagnostiziert\n\nZurueck zu Fehlermeldungen mit 0: ";
const char SW_Error_Message[] PROGMEM = "\nReset durch software-Fehler ausgefuehrt\n\nZurueck zu Fehlermeldungen mit 0: ";
const char Time_Error_Message[] PROGMEM = "\nFehler beim Auslesen von Uhrzeit und Datum\n\nZurueck zu Fehlermeldungen mit 0: ";

//Firmware
const char firmware_message_menu[] PROGMEM = "\tFirmware\n1. Firmware-Version auslesen\n2. Firmware-Update\n3. Zurueck zum Hauptmenue\n\nWaehlen Sie eine Nummer aus: ";

//Für Betriebsablaufliste
const char OutputOperationlist[] PROGMEM = "\nDie Betriebsablaufliste des gewaehlten Ampelsystems ist: \n";

const char HighOp[] PROGMEM = "\nHigh_frequency_modus:\n";
const char LowOp[] PROGMEM = "\n\nLow_frequency modus:\n";
const char RemoteOp[] PROGMEM = "\n\nRemote_frequency modus:\n";

const char OutputTo[] PROGMEM = " to ";
const char OutputAnd[] PROGMEM= " and ";


const char OutputWeekday[] PROGMEM = "\tMonday - Friday: ";
const char OutputSaturday[] PROGMEM = "\n\tSaturday: ";
const char OutputSunday[] PROGMEM = "\n\tSunday: ";

//**************************************************************************************************************************************//

void mainmenu_func() {
		printMenu(mainMenu_message_menu);
		g = USART_Receive();
		USART_Transmit(g);
		uint8_t c = g - 48;
	switch(c){
		case configuration:
			configuration_func();
		break;
		case install:
			install_func();
		break;
		case errors:
			error_func();
		break;
		case firmware:
			firmware_func();
		break;
		default:
		break;
		//Fehler
	}
}

void configuration_func(){
	printMenu(configuration_message_menu);
	g = USART_Receive();
	USART_Transmit(g);
	uint8_t c = g - 48;
	switch(c){
		case id_change:
		break;
		case state_request:
		break;
		case state_change:
		break;
		case operational_flow_read:
			AusgabeBetriebsablaufliste();
		break;
		case operational_flow_change:
		break;
		case date_read:
		break;
		case date_change:
		break;
		case return_to_main_menu1:
			mainmenu_func();
		break;
		default:
		break;
	}
}

void install_func(){
	printMenu(install_message_menu);
	g = USART_Receive();
	USART_Transmit(g);
	uint8_t c = g - 48;
	switch(c){
		case lights_install:
		break;
		case lights_deinstall:
		break;
		case return_to_main_menu2:
			mainmenu_func();
		default:
		break;
	}
}

void error_func(){
	printMenu(errors_message_menu);
	g = USART_Receive();
	USART_Transmit(g);
	uint8_t c = g - 48;
	switch(c){
		case no_error:
			printMenu(No_Error_Message);
		break;
		case red_light_mr:
			printMenu(Red_Light_MR_Message);
		break;
		case red_light_sr:
			printMenu(Red_Light_SR_Message);
		break;
		case flash_error:
			printMenu(Flash_Error_Message);
		break;
		case sram_error:
			printMenu(SRAM_Error_Message);
		break;
		case stack_error:
			printMenu(Stack_Error_Message);
		break;
		case sw_error:
			printMenu(SW_Error_Message);
		break;
		case time_error:
			printMenu(Time_Error_Message);
		break;
		case return_to_main_menu3:
			mainmenu_func();
		break;
		default:
		break;
	}
}

void firmware_func(){
	printMenu(firmware_message_menu);
	g = USART_Receive();
	USART_Transmit(g);
	uint8_t c = g - 48;
	switch(c){
		case firmware_version:
		break;
		case firmware_update:
		break;
		default:
		break;
	}
}

//------------------------------------------------------


void AusgabeBetriebsablaufliste(){
	
	printMenu(OutputOperationlist);
	
	//High Freq Operation
	printMenu(HighOp);
	printMenu(OutputWeekday);
	printUI(werktag_starttime_high);
	printMenu(OutputTo);
	printUI(werktag_endtime_high+1);
	printMenu(OutputSaturday);
	printUI(saturday_starttime_high);
	printMenu(OutputTo);
	printUI(saturday_endtime_high+1);
	printMenu(OutputSunday);
	printUI(sunday_starttime_high);
	printMenu(OutputTo);
	printUI(sunday_endtime_high+1);
	
	//Low Feq Op
	printMenu(LowOp);
	printMenu(OutputWeekday);
	printUI(werktag_starttime_low);
	printMenu(OutputTo);
	printUI(werktag_endtime_low+1);
	printMenu(OutputSaturday);
	printUI(saturday_starttime_low1);
	printMenu(OutputTo);
	printUI(saturday_endtime_low1+1);
	printMenu(OutputAnd);
	printUI(saturday_starttime_low2);
	printMenu(OutputTo);
	printUI(saturday_endtime_low2+1);
	printMenu(OutputSunday);
	printUI(sunday_starttime_low1);
	printMenu(OutputTo);
	printUI(sunday_endtime_low1+1);
	printMenu(OutputAnd);
	printUI(sunday_starttime_low2);
	printMenu(OutputTo);
	printUI(sunday_endtime_low2+1);
	
	//remote freq op
	printMenu(RemoteOp);
	printMenu(OutputWeekday);
	printUI(werktag_starttime_remote);
	printMenu(OutputTo);
	printUI(werktag_endtime_remote+1);
	printMenu(OutputSaturday);
	printUI(saturday_starttime_remote);
	printMenu(OutputTo);
	printUI(saturday_endtime_remote+1);
	printMenu(OutputSunday);
	printUI(sunday_starttime_remote);
	printMenu(OutputTo);
	printUI(sunday_endtime_remote+1);
	
}


#endif /* MENU_H_ */
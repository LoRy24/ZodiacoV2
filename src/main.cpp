//
// Zodiaco V2.0 by Lorenzo Rocca
// Descrizione: 
// Questo programma permette di calcolare il segno zodiacale di una persona in base alla data di nascita.
// La UI sembra volutamente quella di un videogame degli anni 80, più o meno ;3
//

// Inclusioni
#include <iostream>
#include <graphics.h>
#include <unistd.h>

// Namespace STD
using namespace std;

#pragma region Definizioni

// Impostazioni finestra
// Per evitare problemi, non modificare le seguenti impostazioni
#define WIDTH                                   1300
#define HEIGHT                                  800
#define WINDOW_TITLE                            "Zodiaco V2.0"

// Press Enter To Continue
#define PRESS_ENTER_TO_CONTINUE_CLOCK_MS        300
#define PRESS_ENTER_TO_CONTINUE_Y               600

// Ascii
#define ESCAPE                                  27
#define ENTER                                   13

// Immagini
#define INTRO_IMAGE                             "./img/intestazione.jpg"
#define PRESS_ENTER_IMAGE                       "./img/premi_invio.jpg"
#define DATA_NASCITA_IMAGE                      "./img/data_nascita_titolo.jpg"
#define PULSANTI_MENU_DATA_NASCITA_IMAGE        "./img/pulsanti_menu_nascita.jpg"

#pragma endregion

#pragma region Utilità immagini

/**
 * @brief Calcola l'altezza in base alla nuova larghezza
 * 
 * @param oldWidth Larghezza originale
 * @param oldHeight Altezza originale
 * @param newWidth Nuova larghezza
 */
int computeBasedOnNewWidth(int oldWidth, int oldHeight, int newWidth) {
    return (oldHeight * newWidth) / oldWidth;
}

#pragma endregion

#pragma region Strutture dati

/**
 * @brief Struttura per la data di nascita
 */
struct BirthDate
{
    int day;
    int month;
    int year;
};

/**
 * @brief Enum per la selezione della data
 */
enum DateSelection {
    DAY,
    MONTH
};


#pragma endregion

#pragma region Funzioni Grafiche - Menu Principale

/**
 * @brief Inizializza la schermata principale
 */
void setupScreen() {
    // Inizializza la schermata
    initwindow(WIDTH, HEIGHT, WINDOW_TITLE);
    setbkcolor(WHITE);
    cleardevice();

    // Calcola le dimensioni dell'immagine
    int imageWidth = 640;
    int imageHeight = computeBasedOnNewWidth(1920, 1080, imageWidth);
    
    // In base alla dimensione dello schermo, decidi lo spazio per centrarla
    int x = (WIDTH - imageWidth) / 2;

    // Stampa l'immagine a schermo
    int y = 160;
    readimagefile(INTRO_IMAGE, x, y, x + imageWidth, y + imageHeight);
}

/**
 * @brief Stampa l'immagine "Premi invio per continuare"
 * @param y Coordinata Y
 */
void drawPressEnterToContinue(int y) {
    // Calcola le dimensioni dell'immagine
    int imageWidth = 400;
    int imageHeight = computeBasedOnNewWidth(1200, 220, imageWidth);

    // In base alla dimensione dello schermo, decidi lo spazio per centrarla
    int x = (WIDTH - imageWidth) / 2;

    // Stampa l'immagine
    readimagefile(PRESS_ENTER_IMAGE, x, y, x + imageWidth, y + imageHeight);
}

/**
 * @brief Cancella l'immagine "Premi invio per continuare"
 * @param y Coordinata Y
 */
void clearPressEnterToContinue(int y) {
    // Calcola le dimensioni dell'immagine
    int imageWidth = 400;
    int imageHeight = computeBasedOnNewWidth(1200, 220, imageWidth);

    // In base alla dimensione dello schermo, decidi lo spazio per centrarla
    int x = (WIDTH - imageWidth) / 2;

    // Cancella l'immagine
    setfillstyle(SOLID_FILL, WHITE);
    bar(x, y, x + imageWidth, y + imageHeight);
}

/**
 * @brief Aspetta che venga premuto invio. Questa funzione avvia anche un'animazione
 */
void waitForPressEnterToContinue() {
    // Definisco le variabili per lo stato
    int clock = 0;
    int print = true;

    // Loop per l'animazione
    while (true) {
        // Incrementa il clock
        clock++;

        // Vedi se nel buffer ci sono caratteri da leggere
        if (kbhit()) {
            // Vedi che carattere è stato premuto
            char key = getch();
            
            // Se è uguale a invio, esci
            if (key == ENTER) {
                break;
            }
        }

        // Se il clock arriva al valore impostato
        if (clock == PRESS_ENTER_TO_CONTINUE_CLOCK_MS) {
            // Resetta il clock
            clock = 0;

            // Stampa o cancella l'immagine
            if (print) {
                drawPressEnterToContinue(PRESS_ENTER_TO_CONTINUE_Y);
            } else {
                clearPressEnterToContinue(PRESS_ENTER_TO_CONTINUE_Y);
            }

            // Cambia lo stato
            print = !print;
        }

        // Attendi 1ms
        usleep(1);
    }
}

#pragma endregion

#pragma region Funzioni Grafiche - Menu Selezione data di nascita

/**
 * @brief Stampa l'header per la selezione della data di nascita
 */
void printBirthDateFormHeader(int y) {
    // Calcola le dimensioni dell'immagine
    int imageWidth = 450;
    int imageHeight = computeBasedOnNewWidth(1200, 400, imageWidth);

    // In base alla dimensione dello schermo, decidi lo spazio per centrarla
    int x = (WIDTH - imageWidth) / 2;

    // Stampa l'immagine
    readimagefile(DATA_NASCITA_IMAGE, x, y, x + imageWidth, y + imageHeight);
}

/**
 * @brief Stampa i pulsanti in basso a destra
 */
void printRightBottomButtons(int rightDistance, int bottomDistance) {
    // Calcola le dimensioni dell'immagine
    int imageWidth = 550;
    int imageHeight = computeBasedOnNewWidth(850, 100, imageWidth);

    // In base alla dimensione dello schermo, decidi lo spazio per posizionarlo in basso a destra
    int x = WIDTH - rightDistance - imageWidth;
    int y = HEIGHT - bottomDistance - imageHeight;

    // Stampa l'immagine
    readimagefile(PULSANTI_MENU_DATA_NASCITA_IMAGE, x, y, x + imageWidth, y + imageHeight);
}

/**
 * @brief Stampa lo sfondo del prompt della data di nascita. In base al selected, evidenzierà uno
 *        dei due campi. Opzioni: 1 = giorno, 2 = mese
 */
void printDateSelectionBackground(DateSelection highlighted) {
    
}

/**
 * @brief Importa la pagina per la richiesta della data di nascita
 */
void setupBirtDateForm() {
    // Scrivi il titolo
    printBirthDateFormHeader(100);

    // Scrivi i pulsanti in basso a destra
    printRightBottomButtons(55, 18);
}

#pragma endregion

#pragma region Menu Selezione data di nascita

/**
 * @brief Richiedi la data di nascita
 */
BirthDate requestBirthDateForm() {
    // Definisco anticipatamente l'esito della funzione
    BirthDate birthDate;

    // Preimposta il form
    setupBirtDateForm();

    // Attendi che venga premuto un tasto
    getch();

    // Ritorna 
    return birthDate;
}

#pragma endregion

// Main

int main() {
    // Inizializza lo schermo
    setupScreen();

    // Aspetta che venga premuto invio
    waitForPressEnterToContinue();

    // Pulisci lo schermo
    cleardevice();

    // Richiedi la data di nascita
    BirthDate birthDate = requestBirthDateForm();

    // Esci
    return 0;
}
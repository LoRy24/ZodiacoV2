//
// Zodiaco V2.0 by Lorenzo Rocca
//
// Descrizione: 
// Questo programma permette di calcolare il segno zodiacale di una persona in base alla data di nascita.
// La UI sembra volutamente quella di un videogame arcade, per dare un tocco di originalità.
//

// Inclusioni
#include <iostream>
#include <graphics.h>
#include <unistd.h>
#include <string>

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
#define UP_ARROW                                72
#define DOWN_ARROW                              80
#define LEFT_ARROW                              75
#define RIGHT_ARROW                             77

// Immagini
#define INTRO_IMAGE                             "./img/intestazione.jpeg"
#define PRESS_ENTER_IMAGE                       "./img/premi_invio.jpeg"
#define DATA_NASCITA_IMAGE                      "./img/data_nascita_titolo.jpeg"
#define PULSANTI_MENU_DATA_NASCITA_IMAGE        "./img/pulsanti_menu_nascita.jpeg"
#define SELEZIONE_DATA_GIORNO_IMAGE             "./img/data/selezione_data_giorno.jpeg"
#define SELEZIONE_DATA_MESE_IMAGE               "./img/data/selezione_data_mese.jpeg"

#pragma endregion

#pragma region Variabili e Costanti Globali

// Variabili globali per la selezione della data
int giornoSelezionato = 1;
int meseSelezionato = 1;

// Numero di giorni per mese
int giorniPerMese[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Nomi dei mesi
string nomiMesi[12] = {
    "Gennaio",
    "Febbraio",
    "Marzo",
    "Aprile",
    "Maggio",
    "Giugno",
    "Luglio",
    "Agosto",
    "Settembre",
    "Ottobre",
    "Novembre",
    "Dicembre"
};

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

// Ottiene i numeri da 1 a 31
char* getNumberFileName(int number, bool selected) {
    // Nel non sia selezionato, applica quello non selezionato
    if (!selected) {
        switch (number) {
            case 1:
                return "./img/numbers/notSelected/1.jpeg";
            case 2:
                return "./img/numbers/notSelected/2.jpeg";  
            case 3:
                return "./img/numbers/notSelected/3.jpeg";
            case 4:
                return "./img/numbers/notSelected/4.jpeg";  
            case 5:
                return "./img/numbers/notSelected/5.jpeg";  
            case 6:
                return "./img/numbers/notSelected/6.jpeg";  
            case 7:
                return "./img/numbers/notSelected/7.jpeg";  
            case 8:
                return "./img/numbers/notSelected/8.jpeg";  
            case 9:
                return "./img/numbers/notSelected/9.jpeg";  
            case 10:
                return "./img/numbers/notSelected/10.jpeg";  
            case 11:
                return "./img/numbers/notSelected/11.jpeg";  
            case 12:
                return "./img/numbers/notSelected/12.jpeg";  
            case 13:
                return "./img/numbers/notSelected/13.jpeg";  
            case 14:
                return "./img/numbers/notSelected/14.jpeg";  
            case 15:
                return "./img/numbers/notSelected/15.jpeg";  
            case 16:
                return "./img/numbers/notSelected/16.jpeg";  
            case 17:
                return "./img/numbers/notSelected/17.jpeg";  
            case 18:
                return "./img/numbers/notSelected/18.jpeg";  
            case 19:
                return "./img/numbers/notSelected/19.jpeg";  
            case 20:
                return "./img/numbers/notSelected/20.jpeg";  
            case 21:
                return "./img/numbers/notSelected/21.jpeg";  
            case 22:
                return "./img/numbers/notSelected/22.jpeg";  
            case 23:
                return "./img/numbers/notSelected/23.jpeg";  
            case 24:
                return "./img/numbers/notSelected/24.jpeg";  
            case 25:
                return "./img/numbers/notSelected/25.jpeg";  
            case 26:
                return "./img/numbers/notSelected/26.jpeg";  
            case 27:
                return "./img/numbers/notSelected/27.jpeg";  
            case 28:
                return "./img/numbers/notSelected/28.jpeg";  
            case 29:
                return "./img/numbers/notSelected/29.jpeg";  
            case 30:
                return "./img/numbers/notSelected/30.jpeg";  
            case 31:
                return "./img/numbers/notSelected/31.jpeg";    
            default:
                return "\0";
        }
    }
    else {
        switch (number) {
            case 1:
                return "./img/numbers/selected/1.jpeg";
            case 2:
                return "./img/numbers/selected/2.jpeg";  
            case 3:
                return "./img/numbers/selected/3.jpeg";
            case 4:
                return "./img/numbers/selected/4.jpeg";  
            case 5:
                return "./img/numbers/selected/5.jpeg";  
            case 6:
                return "./img/numbers/selected/6.jpeg";  
            case 7:
                return "./img/numbers/selected/7.jpeg";  
            case 8:
                return "./img/numbers/selected/8.jpeg";  
            case 9:
                return "./img/numbers/selected/9.jpeg";  
            case 10:
                return "./img/numbers/selected/10.jpeg";  
            case 11:
                return "./img/numbers/selected/11.jpeg";  
            case 12:
                return "./img/numbers/selected/12.jpeg";  
            case 13:
                return "./img/numbers/selected/13.jpeg";  
            case 14:
                return "./img/numbers/selected/14.jpeg";  
            case 15:
                return "./img/numbers/selected/15.jpeg";  
            case 16:
                return "./img/numbers/selected/16.jpeg";  
            case 17:
                return "./img/numbers/selected/17.jpeg";  
            case 18:
                return "./img/numbers/selected/18.jpeg";  
            case 19:
                return "./img/numbers/selected/19.jpeg";  
            case 20:
                return "./img/numbers/selected/20.jpeg";  
            case 21:
                return "./img/numbers/selected/21.jpeg";  
            case 22:
                return "./img/numbers/selected/22.jpeg";  
            case 23:
                return "./img/numbers/selected/23.jpeg";  
            case 24:
                return "./img/numbers/selected/24.jpeg";  
            case 25:
                return "./img/numbers/selected/25.jpeg";  
            case 26:
                return "./img/numbers/selected/26.jpeg";  
            case 27:
                return "./img/numbers/selected/27.jpeg";  
            case 28:
                return "./img/numbers/selected/28.jpeg";  
            case 29:
                return "./img/numbers/selected/29.jpeg";  
            case 30:
                return "./img/numbers/selected/30.jpeg";  
            case 31:
                return "./img/numbers/selected/31.jpeg";    
            default:
                return "\0";
        }
    }
}

#pragma endregion

#pragma region Strutture dati

/**
 * @brief Struttura per la data di nascita
 */
struct BirthDate
{
    int day; // 1 a 31
    int month; // 0 a 11
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

// Tieni sott'occhio il valore della data selezionato
DateSelection highlightedDateSelection = DAY;

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
void printDateSelectionBackground(int y) {
    // Calcola le dimensioni dell'immagine
    int imageWidth = 400;
    int imageHeight = computeBasedOnNewWidth(600, 240, imageWidth);

    // In base alla dimensione dello schermo, posizionalo centrato
    int x = (WIDTH - imageWidth) / 2;

    // Stampa l'immagine
    readimagefile(highlightedDateSelection == DAY ? SELEZIONE_DATA_GIORNO_IMAGE : SELEZIONE_DATA_MESE_IMAGE, x, y, x + imageWidth, y + imageHeight);
}

/**
 * @brief Stampa la data inserita nelle variabili globali
 */
void printDate() {
    // Offset verticale
    int y = 402;

    // Calcola le dimensioni dell'immagine del numero
    int imageWidth = 80;
    int imageHeight = computeBasedOnNewWidth(400, 300, imageWidth);

    // Coordinata centrata nello schermo
    int x = (WIDTH - imageWidth) / 2;

    // Stampa il numero del giorno
    int xGiorno = x - 100;
    readimagefile(getNumberFileName(giornoSelezionato, highlightedDateSelection == DAY ? true : false), xGiorno, y, xGiorno + imageWidth, y + imageHeight);

    // Stampa il numero del mese
    int xMese = x + 100;
    readimagefile(getNumberFileName(meseSelezionato, highlightedDateSelection == MONTH ? true : false), xMese, y, xMese + imageWidth, y + imageHeight);
}

/**
 * @brief Cambia l'evidenziazione del campo selezionato
 */
void changeHighlight() {
    // Se il campo selezionato è il giorno, cambialo in mese
    if (highlightedDateSelection == DAY) {
        highlightedDateSelection = MONTH;
    } else {
        highlightedDateSelection = DAY;
    }

    // Stampa l'immagine
    printDateSelectionBackground(350);

    // Stampa la data
    printDate();
}

/**
 * @brief Importa la pagina per la richiesta della data di nascita
 */
void setupBirtDateForm() {
    // Scrivi il titolo
    printBirthDateFormHeader(100);

    // Scrivi i pulsanti in basso a destra
    printRightBottomButtons(55, 18);

    // Scrivi il prompt della data
    printDateSelectionBackground(350);

    // Scrivi la data iniziale
    printDate();
}

#pragma endregion

#pragma region Menu Selezione data di nascita

/**
 * @brief Incrementa il giorno selezionato
 */
void increaseDay() {
    // Se il giorno selezionato è minore del numero di giorni per il mese selezionato
    if (giornoSelezionato < giorniPerMese[meseSelezionato - 1]) {
        // Incrementa il giorno selezionato
        giornoSelezionato++;
    }
    else {
        // Altrimenti, se il giorno selezionato è uguale al numero di giorni per il mese selezionato, imposta il giorno selezionato a 1
        giornoSelezionato = 1;
    }

    // Aggiorna la data su schermo
    printDate();
}

/**
 * @brief Decrementa il giorno selezionato
 */
void decreaseDay() {
    // Se il giorno selezionato è 1, imposta il giorno selezionato al numero di giorni per il mese selezionato
    if (giornoSelezionato == 1) {
        giornoSelezionato = giorniPerMese[meseSelezionato - 1];
    } else {
        giornoSelezionato--;
    }

    // Aggiorna la data su schermo
    printDate();
}

/**
 * @brief Aggiorna il limite del giorno basandosi sul mese selezionato
 */
void updateDayLimitBasingOnMonth() {
    // Se il giorno selezionato è maggiore del numero di giorni per il mese selezionato, sistemalo
    if (giornoSelezionato > giorniPerMese[meseSelezionato - 1]) {
        giornoSelezionato = giorniPerMese[meseSelezionato - 1];
    }

    // Aggiorna la data su schermo
    printDate();
}

/**
 * @brief Incrementa il mese selezionato
 */
void increaseMonth() {
    // Se il mese selezionato è minore di 12, incrementalo
    if (meseSelezionato < 12) {
        meseSelezionato++;
    } else {
        meseSelezionato = 1;
    }

    // Aggiorna la data su schermo
    updateDayLimitBasingOnMonth();
}

/**
 * @brief Decrementa il mese selezionato
 */
void decreaseMonth() {
    // Se il mese selezionato è 1, imposta il mese selezionato a 12
    if (meseSelezionato == 1) {
        meseSelezionato = 12;
    } else {
        meseSelezionato--;
    }

    // Aggiorna la data su schermo
    updateDayLimitBasingOnMonth();
}

/**
 * @brief Richiedi la data di nascita
 */
BirthDate requestBirthDateForm() {
    // Definisco anticipatamente l'esito della funzione
    BirthDate birthDate;

    // Debug
    std::cout << "[DEBUG] Configurazione form di richiesta della data" << std::endl;

    // Preimposta il form
    setupBirtDateForm();

    // Debug
    std::cout << "[DEBUG] Schermo configurato" << std::endl;

    // Loop per la gestione dell'input
    while (true) {
        // Attendi per un carattere da inserire
        char input = getch();

        // Debug
        std::cout << "[DEBUG] Tasto premuto"<< std::endl;

        // Se viene premuto invio, esci
        if (input == ENTER) {
            std::cout << "[DEBUG] Invio premuto" << std::endl;
            break;
        }

        // Se viene premuta la freccia su, aumenta il valore del mese o del giorno
        if (input == UP_ARROW) {
            std::cout << "[DEBUG] Freccia su premuta" << std::endl;
            
            // Se si sta modificando il giorno, incrementalo, altrimenti incrementa il mese
            if (highlightedDateSelection == DAY) {
                increaseDay();
            } else {
                increaseMonth();
            }

            // Continua
            continue;
        }

        // Se viene premuta la freccia giù, aumenta il valore del mese o del giorno
        if (input == DOWN_ARROW) {
            std::cout << "[DEBUG] Freccia giù premuta" << std::endl;

            // Se si sta modificando il giorno, decrementalo, altrimenti decrementa il mese
            if (highlightedDateSelection == DAY) {
                decreaseDay();
            } else {
                decreaseMonth();
            }

            // Continua
            continue;
        }

        // Se viene premuta la freccia destra o sinistra, cambia il campo selezionato
        if (input == RIGHT_ARROW || input == LEFT_ARROW) {
            std::cout << "[DEBUG] Freccia destra o sinistra premuta" << std::endl;
            changeHighlight();

            // Continua
            continue;
        }
    }

    // Imposta la data di nascita
    birthDate.day = giornoSelezionato;
    birthDate.month = meseSelezionato - 1;

    // Debug
    std::cout << "[DEBUG] Data di Nascita: " << birthDate.day << " " << nomiMesi[birthDate.month] << std::endl;

    // Ritorna 
    return birthDate;
}

#pragma endregion

#pragma region Funzioni Grafiche - Menu Segno Zodiacale

#pragma endregion

#pragma region Routine Programma

// Main

int main() {
    // Inizializza lo schermo
    setupScreen();

    // Debug
    std::cout << "[DEBUG] Schermo configurato, in attesa del tasto invio" << std::endl;

    // Aspetta che venga premuto invio
    waitForPressEnterToContinue();

    // Debug
    std::cout << "[DEBUG] Tasto invio premuto" << std::endl;

    // Pulisci lo schermo
    cleardevice();

    // Debug
    std::cout << "[DEBUG] Schermo pulito" << std::endl;

    // Richiedi la data di nascita
    BirthDate birthDate = requestBirthDateForm();

    // Debug
    std::cout << "[DEBUG] Data di nascita inserita" << std::endl;

    // Pulisci lo schermo
    cleardevice();

    // Attendi un input
    getch();

    // Chiudi lo schermo
    closegraph();

    // Esci
    return 0;
}

#pragma endregion

//
// Zodiaco V2.0 by Lorenzo Rocca
//
// Descrizione: 
// Questo programma permette di calcolare il segno zodiacale di una persona in base alla data di nascita.
// La UI sembra volutamente quella di un videogame arcade, per dare un tocco di originalità.
//

#pragma region Inclusioni

// Inclusioni
#include <iostream>
#include <graphics.h>
#include <unistd.h>
#include <string>
#include <cstdio>
#include <time.h>

#pragma endregion

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
#define PREMI_Q_PER_USCIRE_IMAGE                "./img/premi_q_per_uscire.jpeg"

#pragma endregion

#pragma region Variabili e Costanti Globali

// Variabili globali per la selezione della data
int giornoSelezionato = 1;
int meseSelezionato = 1;

// Numero di giorni per mese
int giorniPerMese[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Nomi dei mesi
std::string nomiMesi[12] = {
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

// Enum dei segni zodiacali
enum ZodiacalSign {
    CAPRICORNO,
    ACQUARIO,
    PESCI,
    ARIETE,
    TORO,
    GEMELLI,
    CANCRO,
    LEONE,
    VERGINE,
    BILANCIA,
    SCORPIONE,
    SAGITTARIO
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

/**
 * @brief Ottiene il nome del file per il numero
 */
char* getNumberFileName(int number, bool selected) {
    // Creiamo il buffer
    static char buffer[100] = {0};
    sprintf(buffer, "./img/numbers/%s/%d.jpeg", selected ? "selected" : "notSelected", number);

    // Ritorna il buffer
    return buffer;
}

/**
 * @brief Ottiene il nome del file per il segno zodiacale
 */
char* getSignFileName(int sign) {
    // Creiamo il buffer
    static char buffer[100] = {0};
    sprintf(buffer, "./img/sign/%d.jpeg", sign);

    // Ritorna il buffer
    return buffer;
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
        struct timespec ts;
        ts.tv_nsec = 1000 * 1000 * 1;
        ts.tv_sec = 0;
        nanosleep(&ts, NULL);
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

#pragma region Calcolo Segno Zodiacale

// Costanti per i segni zodiacali
ZodiacalSign segniZodiacaliPrimaMeta[12] = {
    CAPRICORNO, ACQUARIO, PESCI, ARIETE, TORO, GEMELLI, CANCRO, LEONE, VERGINE, BILANCIA, SCORPIONE, SAGITTARIO
};

ZodiacalSign segniZodiacaliSecondaMeta[12] = {
    ACQUARIO, PESCI, ARIETE, TORO, GEMELLI, CANCRO, LEONE, VERGINE, BILANCIA, SCORPIONE, SAGITTARIO, CAPRICORNO
};

/**
 * @brief Ottieni il segno zodiacale in base alla data di nascita. Considera del segno della prima metà fino al giorno 
 *        di scambio. Quindi, se ci si trova in condizione di cuspide, bisogna considerare il segno della seconda metà \
 *        per l'unione. Es: 19 Gennaio, Capricorno-Acquario (0-1), dove 0 è Capricorno e 1 è Acquario. La funzione ritornerà 
 *        0 quindi bisogna prendere 0 + 1.
 */
ZodiacalSign getZodiacalSign(BirthDate birthDate, bool* cuspide) {
    // Definisco il limite e il giorno di scambio
    int limit = 0, changeDay = 0;

    // Definisco il mese
    int month = birthDate.month + 1;

    // In base al mese, imposto il limite di giorni
    switch (month) {
        case 4:
        case 6:
        case 9:
        case 11: {
            limit = 30;
            break;
        }

        case 2: {
            limit = 29;
            break;
        }

        default: {
            limit = 31;
            break;
        }
    }
    
    // Sempre in base al mese, imposto il giorno di scambio
    switch (month) {
        case 4:
        case 1:
        case 2: {
            changeDay = 19;
            break;
        }

        case 3:
        case 5:
        case 6: {
            changeDay = 20;
            break;
        }

        case 11:
        case 12: {
            changeDay = 21;
            break;
        }

        case 8: {
            changeDay = 23;
            break;
        }

        default: {
            changeDay = 22;
            break;
        }
    }

    // Verifica se è in cuspide
    *cuspide = birthDate.day == changeDay || birthDate.day == changeDay + 1;

    // Ritorno il segno
    return birthDate.day <= changeDay ? segniZodiacaliPrimaMeta[birthDate.month] : segniZodiacaliSecondaMeta[birthDate.month];
}

#pragma endregion

#pragma region Funzioni Grafiche - Menu Segno Zodiacale

/**
 * @brief Avvia l'animazione per il segno zodiacale
 */
void playZodiacalSignAnimation(ZodiacalSign zodiacalSign) {
    // Definisco le schermate da cambiare
    int frames = 24;

    // Il programma inizierà a rallentare 6 schermate prima, dunque dobbiamo calcoalre il segno a quanto dista.
    // Esempio: se il segno è 0, non aggiungiamo nulla a 18, se è 6, aggiungiamo 6 a 18, se è 12, aggiungiamo 12 a 18.
    frames += zodiacalSign;

    // Dimensioni immagine schermata
    int initialWidth = 1300;
    int initialHeight = 800;

    // Va piazzata al centro totale dello schermo, dunque:
    int x = (WIDTH - initialWidth) / 2;
    int y = (HEIGHT - initialHeight) / 2;

    // L'immagine non va ridimensionata, quindi procediamo con l'animazione
    int frame = 0;
    for (frame = 0; frame < frames; frame++) {
        // Stampa l'immagine
        readimagefile(getSignFileName(frame % 12), x, y, x + initialWidth, y + initialHeight);

        // Debug
        std::cout << "Frame attuale: " << frame << std::endl;

        // Attendi il tempo dell'animazione (500ms)
        struct timespec ts;
        ts.tv_nsec = 1000 * 1000 * 50;
        ts.tv_sec = 0;
        nanosleep(&ts, NULL);
    }

    // Debug
    std::cout << "Stampa ultimi 12 frame: " << std::endl;

    // Definiamo i tempi di attesa per i frame
    int framesSleepMs[12] = {75, 100, 125, 150, 200, 250, 300, 400, 500, 650, 850, 1000};

    // Stampa gli ultimi 12 frame
    for (int fA = 0; frame < frames + 12; frame++, fA++) {
        // Stampa l'immagine
        readimagefile(getSignFileName(frame % 12), x, y, x + initialWidth, y + initialHeight);

        // Debug
        std::cout << "Frame attuale: " << frame << std::endl;

        // Attendi il tempo dell'animazione che cresce
        struct timespec ts;
        ts.tv_nsec = 1000 * 1000 * (framesSleepMs[fA] - ((framesSleepMs[fA] / 1000) * 1000));
        ts.tv_sec = framesSleepMs[fA] / 1000;
        nanosleep(&ts, NULL);
    }

    // Aspetta 2 secondi
    sleep(2);
}

/**
 * @brief Stampa la schermata del segno zodiacale
 */
void showZodiacalSign(BirthDate birthDate) {
    // Calcola il segno zodiacale
    bool cuspide = false;
    ZodiacalSign zodiacalSign = getZodiacalSign(birthDate, &cuspide);

    // Debug
    std::cout << "[DEBUG] Segno Zodiacale: " << zodiacalSign << std::endl;
    std::cout << "[DEBUG] Configurazione schermata segno zodiacale" << std::endl;

    // Avvia l'animazione
    playZodiacalSignAnimation(zodiacalSign);

    // Scrivi il messaggio finale per uscire
    int width = 200, height = computeBasedOnNewWidth(1200, 240, width);
    readimagefile(PREMI_Q_PER_USCIRE_IMAGE, 291, 453, 291 + width, 453 + height);

    // Attendi un input
    while (true) {
        // Attendi per un carattere da inserire
        char input = getch();

        // Se viene premuto q, esci
        if (input == 'Q' || input == 'q') {
            break;
        }
    }
}

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

    // Debug
    std::cout << "[DEBUG] Schermo pulito, avvio schermata segno zodiacale" << std::endl;

    // Stampa la schermata del segno zodiacale
    showZodiacalSign(birthDate);

    // Debug
    std::cout << "[DEBUG] Schermata segno zodiacale completata, attesa pulsante di ritorno (esc)" << std::endl;

    // Chiudi lo schermo
    closegraph();

    // Esci
    return 0;
}

#pragma endregion

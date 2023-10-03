<<<<<<< HEAD
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>

using namespace std;

const int ptsTD = 6, ptsFG = 3, ptsSFY = 2, ptsEP = 1, pts2pt = 2, baseFD = 10;
int yards, pointsTeamOne, pointsTeamTwo, withBall /*boolean 1 or 2*/, randYards;
int baseFirstDownLine, controlFD = 0;
int down = 1, PassI = 0;

void kickoff();

void define() {
    baseFirstDownLine = yards + baseFD;
    down = 1;
}

void touchback() {
    cout << "Function TOUCHBACK!" << endl;
    yards = 25;
    define();
}

int estouro() {
    if (down >= 5) {
        cout << "ESTOUROU" << endl;
        return 1;
    }
}

void statsPP() {
    cout << "Ball on line of " << yards << " it's a "<< down << " for " << baseFirstDownLine - yards;
    cout << endl;
}

void scorePoints(int points) {
    if (withBall == 1) {
        pointsTeamOne += points;
    } else {
        pointsTeamTwo += points;
    }
}

void touchdown(int withBall) {
    scorePoints(ptsTD);
    // Marca ponto pro 1 ou 2
    cout << "TOOOOOOUCHDOWN! SIX POINTS...";
    down = 1; //encerra o while
    kickoff(); //chama uma nova definição de jardas para o próximo time
}


void kickoff() {
    // Bola irá ser posicionada em alguma jarda podendo ter retorno, pós ExPoint ou 2ptCV
    int random = rand();
    //if (random < 0) {
   //     touchback();
        if (random % 13 == 1) { //rarissímo
            cout << "great" << endl;
            yards = 60 + (rand() % 60);
            if (yards > 100) {
                cout << "perfect" << endl;
                touchdown(withBall);
            }
            define();
            return;
        } else {
            if (random % 10 == 1 || random % 7 == 3) {
                cout << "very good" << endl;
                yards = 30 + (rand() % 30);
                define();
                return;
            }

            if (random % 10 == 1 || random % 5 == 3 || random % 8 == 0) {
                cout << "good" << endl;
                yards = 17 + (rand() % 33);
                define();
                return;
            }
            if (random % 2 == 0) {
                cout << "Touchback" << endl;
                touchback();
            } else {
                cout << "normal return" << endl;
                yards = 5 + (rand() % 20);
                define();
            }
        }
}




void verify() {
    if (randYards + yards > 100) {
        touchdown(withBall);
        return;
    } else {
        cout << "BALL ON " << (randYards + yards) << " yards " << endl;
        yards = yards + randYards;
        if (yards >= baseFirstDownLine) {
            cout << "FIRST DOWN" << endl;
            down = 1;
            define();
        } else {
            cout << "Trying to renove the downs..." << endl;
            down++;

        }
    }
    cout << endl;
}

void passIncomplete() {
    down++;
}

void pass() {
    cout <<"It's a pass situation..."<<endl;
    int random = rand();
    //cout << random <<endl;

    if (random % 10 == 0) {
        randYards = 45 + (rand() % 70);
        if (randYards > 100) {
            randYards = 100;
        }
        cout<<"OHHH, it's a big play for "<< randYards <<" yards"<<endl;
        verify();
        return;
    } else {
        if (random % 10 == 1 || random % 10 == 2) {
            randYards = 15 + (rand() % 30);
            cout <<"Good play, medium gain yards, was " << randYards << endl;
            verify();
            return;
        } else {
            if (random % 10 == 3 || random % 10 == 4) {
                randYards = 1 + (rand() % 14);
            cout <<"Pass complete but it's a little gain for " << randYards <<endl;
            verify();
            return;
            } else {
                passIncomplete();
                cout<<"Pass incomplete"<<endl;
                //verify();
            }
        }

    }
    cout << endl;
}

void run () {
    cout <<"Running with the ball..."<<endl;
    int random = rand();

    if (random % 10 == 9) {
        randYards = 40 + (rand() % 60);
        cout << "A MASSIVE RUN FOR " << randYards << " yards"<<endl;
        verify();
        return;
    } else {
        if (random % 10 == 8 || random % 10 == 7) {
            randYards = 15 + (rand() % 25);
            cout << "GREAT RUNNING FOR ATTACKER TEAM, RESULTS IN " << randYards << " yds"<< endl;
            verify();
            return;
        } else {
            if (random % 10 == 0 || random % 10 == 5 || random % 10 == 3) {
                randYards = 1 + (rand() % 14);
                cout << "Good advance for " << randYards << " yds" << endl;
                verify();
                return;
            } else {
                cout << "It's a bad call for run, not advance" << endl;
                down++;
            }
        }

    }
    cout << endl;
}


void changePossesion() {
    if (withBall == 1) {
        withBall = 2;
    } else {
        withBall = 1;
    }
}

void punt(){
    // Bola irá ser posicionada em alguma jarda podendo ter retorno
    int puntD;
    puntD = 40 + (rand() % 27);
    yards = 100 - (yards + puntD);
    if (yards < 0) {
        touchback();
    }
    cout << "The punt flies for " << puntD << " yards" << endl;
    changePossesion();
    define();

}

void interception(){
    // Bola muda de posse
    cout << "INTERCEPTION! INTERCEPTION! The ball changes possession..." << endl;
    changePossesion();
    yards = 100 - yards;
    down = 1;
    define();
}
void fumble(){
    changePossesion();
    define();
}

//void reception(){
    //Bola mantém a posse e avança jardas
//}

void flag() {
    // Falta na jogada, aumento ou diminuição de jardas, pode ser de defesa ou ataque
}

void safety(){
    // Tackle na endzone, 2 pontos e troca a posse
    changePossesion();
    scorePoints(ptsSFY);
    kickoff();
}

void fieldGoal(){
    // Acertar ou errar, 3 pontos pro time 1 ou 2
    scorePoints(ptsFG);
    changePossesion();
}

void extraPoint(){
    scorePoints(ptsEP);
    changePossesion();
    // Acertar ou errar pós TD, 1 pontos pro time
}

void twoConversion(){
    // Converter ou não pós TD, 2 pontos pro time
    scorePoints(pts2pt);
    changePossesion();
}



void AttackPlay() {
    statsPP();
    cout << endl;
    cout << "Choose your play: " << endl;
    cout << "[1] PASS // [2] RUN // [3] FIELD GOAL // [4] PUNT" << endl;
    int option = 0;
    scanf("%i", &option);
    switch (option) {
        case 1:
            pass();
            break;
        case 2:
            run();
            break;
        case 3:
            fieldGoal();
            break;
        case 4:
            punt();
            break;
        default:
            AttackPlay();
            break;
    }
}

int endGame() {
    return 0;
}

int main() {

    srand(time(NULL));
    int control = 1;
    while (control != 0) {
        kickoff();
        while (down < 5) {
            AttackPlay();
        }
        //control = endGame();
    }
}

/*
int main () {
    srand(time(NULL));
    int control = 1;
    while (control != 0) {
            AttackPlay();//Jogo total
        kickoff();
        while (down < 5) { //Campanha de ataque
            int i=0;
            statsPP(down);
            pass();
            int testa = estouro();
            if (testa == 1) {
                //testa = 0;
                break;
            }
            cout << i << endl;
            i++;
            statsPP(down);
            pass();
            cout << i << endl;
            i++;
            statsPP(down);
            pass();
            cout << i << endl;
            i++;
            //pass();
            //interception();

            //pass();
            //statsPP(down);

        }
    control = 0;
    }
}
*/


/*
int main () {
    srand(time(NULL));
    int control = 1;
    while (control != 0) { //Jogo total
        touchback();
        while (down < 5) { //Campanha de ataque
            statsPP(down);
            pass();
        }
    control = 0;
    }

    //cout << baseFirstDownLine;

}
*/
=======
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>

using namespace std;

const int ptsTD = 6, ptsFG = 3, ptsSFY = 2, ptsEP = 1, pts2pt = 2, baseFD = 10;
int yards, pointsTeamOne, pointsTeamTwo, withBall /*boolean 1 or 2*/, randYards;
int baseFirstDownLine, controlFD = 0;
int down = 1, PassI = 0;

void kickoff();

void define() {
    baseFirstDownLine = yards + baseFD;
    down = 1;
}

void touchback() {
    cout << "Function TOUCHBACK!" << endl;
    yards = 25;
    define();
}

int estouro() {
    if (down >= 5) {
        cout << "ESTOUROU" << endl;
        return 1;
    }
}

void statsPP() {
    cout << "Ball on line of " << yards << " it's a "<< down << " for " << baseFirstDownLine - yards;
    cout << endl;
}

void scorePoints(int points) {
    if (withBall == 1) {
        pointsTeamOne += points;
    } else {
        pointsTeamTwo += points;
    }
}

void touchdown(int withBall) {
    scorePoints(ptsTD);
    // Marca ponto pro 1 ou 2
    cout << "TOOOOOOUCHDOWN! SIX POINTS...";
    down = 1; //encerra o while
    kickoff(); //chama uma nova definição de jardas para o próximo time
}


void kickoff() {
    // Bola irá ser posicionada em alguma jarda podendo ter retorno, pós ExPoint ou 2ptCV
    int random = rand();
    //if (random < 0) {
   //     touchback();
        if (random % 13 == 1) { //rarissímo
            cout << "great" << endl;
            yards = 60 + (rand() % 60);
            if (yards > 100) {
                cout << "perfect" << endl;
                touchdown(withBall);
            }
            define();
            return;
        } else {
            if (random % 10 == 1 || random % 7 == 3) {
                cout << "very good" << endl;
                yards = 30 + (rand() % 30);
                define();
                return;
            }

            if (random % 10 == 1 || random % 5 == 3 || random % 8 == 0) {
                cout << "good" << endl;
                yards = 17 + (rand() % 33);
                define();
                return;
            }
            if (random % 2 == 0) {
                cout << "Touchback" << endl;
                touchback();
            } else {
                cout << "normal return" << endl;
                yards = 5 + (rand() % 20);
                define();
            }
        }
}




void verify() {
    if (randYards + yards > 100) {
        touchdown(withBall);
        return;
    } else {
        cout << "BALL ON " << (randYards + yards) << " yards " << endl;
        yards = yards + randYards;
        if (yards >= baseFirstDownLine) {
            cout << "FIRST DOWN" << endl;
            down = 1;
            define();
        } else {
            cout << "Trying to renove the downs..." << endl;
            down++;

        }
    }
    cout << endl;
}

void passIncomplete() {
    down++;
}

void pass() {
    cout <<"It's a pass situation..."<<endl;
    int random = rand();
    //cout << random <<endl;

    if (random % 10 == 0) {
        randYards = 45 + (rand() % 70);
        if (randYards > 100) {
            randYards = 100;
        }
        cout<<"OHHH, it's a big play for "<< randYards <<" yards"<<endl;
        verify();
        return;
    } else {
        if (random % 10 == 1 || random % 10 == 2) {
            randYards = 15 + (rand() % 30);
            cout <<"Good play, medium gain yards, was " << randYards << endl;
            verify();
            return;
        } else {
            if (random % 10 == 3 || random % 10 == 4) {
                randYards = 1 + (rand() % 14);
            cout <<"Pass complete but it's a little gain for " << randYards <<endl;
            verify();
            return;
            } else {
                passIncomplete();
                cout<<"Pass incomplete"<<endl;
                //verify();
            }
        }

    }
    cout << endl;
}

void run () {
    cout <<"Running with the ball..."<<endl;
    int random = rand();

    if (random % 10 == 9) {
        randYards = 40 + (rand() % 60);
        cout << "A MASSIVE RUN FOR " << randYards << " yards"<<endl;
        verify();
        return;
    } else {
        if (random % 10 == 8 || random % 10 == 7) {
            randYards = 15 + (rand() % 25);
            cout << "GREAT RUNNING FOR ATTACKER TEAM, RESULTS IN " << randYards << " yds"<< endl;
            verify();
            return;
        } else {
            if (random % 10 == 0 || random % 10 == 5 || random % 10 == 3) {
                randYards = 1 + (rand() % 14);
                cout << "Good advance for " << randYards << " yds" << endl;
                verify();
                return;
            } else {
                cout << "It's a bad call for run, not advance" << endl;
                down++;
            }
        }

    }
    cout << endl;
}


void changePossesion() {
    if (withBall == 1) {
        withBall = 2;
    } else {
        withBall = 1;
    }
}

void punt(){
    // Bola irá ser posicionada em alguma jarda podendo ter retorno
    int puntD;
    puntD = 40 + (rand() % 27);
    yards = 100 - (yards + puntD);
    if (yards < 0) {
        touchback();
    }
    cout << "The punt flies for " << puntD << " yards" << endl;
    changePossesion();
    define();

}

void interception(){
    // Bola muda de posse
    cout << "INTERCEPTION! INTERCEPTION! The ball changes possession..." << endl;
    changePossesion();
    yards = 100 - yards;
    down = 1;
    define();
}
void fumble(){
    changePossesion();
    define();
}

//void reception(){
    //Bola mantém a posse e avança jardas
//}

void flag() {
    // Falta na jogada, aumento ou diminuição de jardas, pode ser de defesa ou ataque
}

void safety(){
    // Tackle na endzone, 2 pontos e troca a posse
    changePossesion();
    scorePoints(ptsSFY);
    kickoff();
}

void fieldGoal(){
    // Acertar ou errar, 3 pontos pro time 1 ou 2
    scorePoints(ptsFG);
    changePossesion();
}

void extraPoint(){
    scorePoints(ptsEP);
    changePossesion();
    // Acertar ou errar pós TD, 1 pontos pro time
}

void twoConversion(){
    // Converter ou não pós TD, 2 pontos pro time
    scorePoints(pts2pt);
    changePossesion();
}



void AttackPlay() {
    statsPP();
    cout << endl;
    cout << "Choose your play: " << endl;
    cout << "[1] PASS // [2] RUN // [3] FIELD GOAL // [4] PUNT" << endl;
    int option = 0;
    scanf("%i", &option);
    switch (option) {
        case 1:
            pass();
            break;
        case 2:
            run();
            break;
        case 3:
            fieldGoal();
            break;
        case 4:
            punt();
            break;
        default:
            AttackPlay();
            break;
    }
}

int endGame() {
    return 0;
}

int main() {

    srand(time(NULL));
    int control = 1;
    while (control != 0) {
        kickoff();
        while (down < 5) {
            AttackPlay();
        }
        //control = endGame();
    }
}

/*
int main () {
    srand(time(NULL));
    int control = 1;
    while (control != 0) {
            AttackPlay();//Jogo total
        kickoff();
        while (down < 5) { //Campanha de ataque
            int i=0;
            statsPP(down);
            pass();
            int testa = estouro();
            if (testa == 1) {
                //testa = 0;
                break;
            }
            cout << i << endl;
            i++;
            statsPP(down);
            pass();
            cout << i << endl;
            i++;
            statsPP(down);
            pass();
            cout << i << endl;
            i++;
            //pass();
            //interception();

            //pass();
            //statsPP(down);

        }
    control = 0;
    }
}
*/


/*
int main () {
    srand(time(NULL));
    int control = 1;
    while (control != 0) { //Jogo total
        touchback();
        while (down < 5) { //Campanha de ataque
            statsPP(down);
            pass();
        }
    control = 0;
    }

    //cout << baseFirstDownLine;

}
*/
>>>>>>> 8917871c21a676cc56da6aaaf67df118a4957319

#include "curlBkps.hpp"

size_t write_data(char *buffer, size_t size, size_t nitems, void *outstream){
    return fwrite(buffer, size, nitems, (FILE*)outstream);
}

int progress_callback(void *clientp,
                    curl_off_t dltotal, curl_off_t dlnow,
                    curl_off_t ultotal, curl_off_t ulnow)
{
    HANDLE cO(GetStdHandle(STD_OUTPUT_HANDLE));
    COORD winSize;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(cO, &csbi);
    winSize=COORD{csbi.srWindow.Right-csbi.srWindow.Left, csbi.srWindow.Bottom-csbi.srWindow.Top};
    winSize.X++;
    winSize.Y++;

    short total(winSize.X+winSize.Y); // Total à parcourir
    static short lastDraw(0);

    if(!(dlnow||ulnow)){
        system("CLS");
        lastDraw=0;
    }

    //std::cout << "Opérations sur un écran de " << winSize.X << " par " << winSize.Y << std::endl;
    //std::cout << "DL : tot " << dltotal << " / now : " << dlnow << " / Upload : tot : " << ultotal << " / now : " << ulnow << std::endl;
    //FillConsoleOutputAttribute(cO, BACKGROUND_GREEN|BACKGROUND_INTENSITY, winSize.X*winSize.Y, COORD{0,0}, NULL);
    if(dltotal){
        short fillNbr(total*dlnow/dltotal);
        for(short diag=lastDraw;diag<fillNbr;diag++){
            for(short posY=diag;posY>=0;posY--){
                COORD charPos;
                charPos.Y=posY;
                charPos.X=diag-posY;
                if(posY<winSize.Y && charPos.X<winSize.X)
                    FillConsoleOutputAttribute(cO, BACKGROUND_GREEN|BACKGROUND_INTENSITY, 1, charPos, NULL);
                    //FillConsoleOutputCharacter(cO, ' ', 1, charPos, NULL);

            }
        }
    }else{ // C'est un upload mon capitaine !

    }
}

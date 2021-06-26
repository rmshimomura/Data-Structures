#include "qry.h"
#include "elemento.h"
#include "flags.h"


//Evitar sets indevidos
void setBBIDexecutado(flag checkers, bool state);
void setBBIexecutado(flag checkers, bool state);
void setTPExecutado(flag checkers, bool state);
void setTPRExecutado(flag checkers, bool state);
void setiidExecutado(flag checkers, bool state);

int intersec(double x1, double y1, double p1Largura, double p1Altura, double x2, double y2, double p2Largura, double p2Altura) {
    if ((x2 >= x1 && x2 <= x1 + p1Largura && y2 >= y1 && y2 <= y1 + p1Altura) || (x1 >= x2 && x1 <= x2 + p2Largura && y2 > y1 && y2 <= y1 + p1Altura) || (x2 >= x1 && x2 <= x1 + p1Largura && y1 > y2 && y1 <= y2 + p2Altura) || (x1 >= x2 && x1 <= x2 + p2Largura && y1 > y2 && y1 <= y2 + p2Altura) || (x1 == x2 && y1 == y2)) {
        return 1;
    } else {
        return 0;
    }
}

int inside(double x1, double y1, double p1Largura, double p1Altura, double x2, double y2, double p2Largura, double p2Altura) {
    if ((x1 >= x2 && x1 <= x2 + p2Largura && y1 >= y2 && y1 <= y2 + p2Altura && x1 + p1Largura <= x2 + p2Largura && y1 + p1Altura <= y2 + p2Altura)) {
        return 1;
    } else {
        return 0;
    }
}

void tp(lista sequence, FILE* results, flag checkers){
    int tamanho = getSize(sequence);
    if(tamanho == 0){
        return;
    }
    celula pos1 = getHead(sequence);
    celula pos2 = getHead(sequence);
    item aux1;
    item aux2;
    fprintf(results, "tp\n");
    int quantPair = 0;
    int IndexOfColors = 0;
    char colors[10][50] = {"blue", "gold", "yellow", "green", "red", "purple", "pink", "orange", "tan", "indigo"};
    FILE* testeTP = fopen("testeTP.txt", "a+");  
    for (int i = 0; i < tamanho; i++) {
        pos2 = getNext(sequence, pos1);
        if(pos1 != NULL){
            aux1 = getItem(sequence, pos1);
        }
        if(pos2 != NULL){
            aux2 = getItem(sequence, pos2);
            raiseVisitas(sequence);
        }
        for (int j = i + 1; j < tamanho; j++) {
            if (intersec(getX(aux1), getY(aux1), getLargura(aux1), getAltura(aux1), getX(aux2), getY(aux2), getLargura(aux2), getAltura(aux2))) {
                fprintf(results, "%s %s\n", getId(aux1), getId(aux2));
                if (!getMarcadoTP(aux1)) {
                    fprintf(testeTP, "%s\n", getId(aux1));
                    setMarcadoTP(aux1, true);
                }
                if (!getMarcadoTP(aux2)) {
                    fprintf(testeTP, "%s\n", getId(aux2));
                    setMarcadoTP(aux2, true);
                }
                setPreenchimento(aux1, colors[IndexOfColors]);
                setPreenchimento(aux2, colors[IndexOfColors]);
                IndexOfColors++;
                if (IndexOfColors == 10) {
                    IndexOfColors = 0;
                }
                quantPair++;
            }
            pos2 = getNext(sequence, pos2);
            if(pos2 != NULL){
                aux2 = getItem(sequence, pos2);
            }
        }
        pos1 = getNext(sequence, pos1);
        if(pos1 != NULL){
            aux1 = getItem(sequence, pos1);
        }
    }
    fclose(testeTP);
    fprintf(results, "-----------\n");
    setTPExecutado(checkers, true);
}

void tpr(double x, double y, double largura, double altura, lista sequence, FILE* results, flag checkers) {
    int tamanho = getSize(sequence);
    if(tamanho == 0){
        return;
    }
    celula posaux1 = getHead(sequence);
    item aux1 = getItem(sequence, posaux1);
    celula posaux2 = getNext(sequence, posaux1);
    item aux2 = getItem(sequence, posaux2);
    fprintf(results, "tpr\n");
    char colors[10][50] = {"blue", "gold", "yellow", "green", "red", "purple", "pink", "orange", "tan", "indigo"};
    int indexOfColors = 0;
    FILE* tempTPRAppend = fopen("tempTPR.txt", "a+");  
    for (int i = 0; i < tamanho; i++) {
        posaux2 = getNext(sequence, posaux1);
        if(posaux2){
            aux2 = getItem(sequence, posaux2);
        }
        for(int j = i + 1; j < tamanho; j++){
            if (inside(getX(aux1), getY(aux1), getLargura(aux1), getAltura(aux1), x, y, largura, altura) && inside(getX(aux2), getY(aux2), getLargura(aux2), getAltura(aux2), x, y, largura, altura) && intersec(getX(aux1), getY(aux1), getLargura(aux1), getAltura(aux1), getX(aux2), getY(aux2), getLargura(aux2), getAltura(aux2))) { //  
                fprintf(results, "%s %s\n", getId(aux1), getId(aux2));
                if(!getMarcadoTPR(aux1)){
                    fprintf(tempTPRAppend, "%s\n", getId(aux1));
                    setMarcadoTPR(aux1, true);
                }
                if(!getMarcadoTPR(aux2)){
                    fprintf(tempTPRAppend, "%s\n", getId(aux2));
                    setMarcadoTPR(aux2, true);
                }
                setPreenchimento(aux1, colors[indexOfColors]);
                setPreenchimento(aux2, colors[indexOfColors]);
                indexOfColors++;
                if (indexOfColors == 10) {
                    indexOfColors = 0;
                }
            }
            posaux2 = getNext(sequence, posaux2);
            if(posaux2){
                aux2 = getItem(sequence, posaux2);
            }
        }
        posaux1 = getNext(sequence, posaux1);
        if(posaux1){
            aux1 = getItem(sequence, posaux1);
        }
    }
    fclose(tempTPRAppend);
    setTPRExecutado(checkers, true);
    fprintf(results, "-----------\n");
}

void dpi(double x, double y, lista sequence, FILE* results, flag checkers) {
    int tamanho = getSize(sequence);
    if(tamanho == 0){
        return;
    }
    celula posaux1 = getHead(sequence);
    item aux1 = getItem(sequence, posaux1);
    int k = 0;
    char idToRemove[50];
    fprintf(results, "dpi\n");
    FILE* dpiToRemove = fopen("tempDPI.txt", "a+");

    for (int i = 0; i < tamanho; i++) {
        if (inside(x, y, 0.0, 0.0, getX(aux1), getY(aux1), getLargura(aux1), getAltura(aux1))) {
            fprintf(results, "%s\n", getId(aux1));
            fprintf(dpiToRemove, "%s\n", getId(aux1));
            k++;
        }
        posaux1 = getNext(sequence, posaux1);
        if(posaux1){
            aux1 = getItem(sequence, posaux1);
        }
    }
    fclose(dpiToRemove);
    FILE* a = fopen("tempDPI.txt", "r");
    //Achar por nome porque o index muda quando se remove retangulos
    for (int i = 0; i < k; i++) {
        fscanf(a, "%s", idToRemove);
        posaux1 = getHead(sequence);
        if(posaux1){
            aux1 = getItem(sequence, posaux1);
        }
        while (1) {
            if (!strcmp(idToRemove, getId(aux1))) {
                break;
            } else {
                posaux1 = getNext(sequence, posaux1);
                if(posaux1){
                    aux1 = getItem(sequence, posaux1);
                }
            }
            if (posaux1 == NULL) {
                fprintf(results, "-----------\n");
                fclose(a);
                return;
            }
        }
        removeNode(sequence, posaux1);
    }
    fclose(a);
    fprintf(results, "-----------\n");
}

void dr(char* id, lista sequence, FILE* results, flag checkers) {
    int tamanho = getSize(sequence);
    if(tamanho == 0){
        return;
    }
    celula posaux1 = getHead(sequence);
    celula posaux2 = getHead(sequence);
    item aux1 = getItem(sequence, posaux1);
    item aux2 = getItem(sequence, posaux2);
    bool found = false;
    int k = 0;
    char idToRemove[50];
    fprintf(results, "dr\n");

    for (int i = 0; i < tamanho; i++) { //Achar id do primeiro
        if (!strcmp(id, getId(aux1))) {
            found = true;
            break;
        } else {
            posaux1 = getNext(sequence, posaux1);
            if(posaux1){
                aux1 = getItem(sequence, posaux1);
            }
        }
    }

    if (!found) {
        fprintf(results, "id de argumento passado inexistente na lista\n");
        fprintf(results, "-----------\n");
        return;
    }
    FILE* tempDR = fopen("tempDR.txt", "a+");
    for (int i = 0; i < tamanho; i++) {
        if (inside(getX(aux2), getY(aux2), getLargura(aux2), getAltura(aux2), getX(aux1), getY(aux1), getLargura(aux1), getAltura(aux1)) && (strcmp(id, getId(aux2)))) {
            fprintf(results, "%s\n", getId(aux2));
            fprintf(tempDR, "%s\n", getId(aux2));
            //Escrever retangulos para remover
            k++;
        }
        posaux2 = getNext(sequence, posaux2);
        if(posaux2){
            aux2 = getItem(sequence, posaux2);
        }
    }
    fclose(tempDR);

    FILE* a = fopen("tempDR.txt", "r");
    for (int i = 0; i < k; i++) {

        fscanf(a, "%s", idToRemove);
        posaux1 = getHead(sequence);
        if(posaux1){
            aux1 = getItem(sequence, posaux1);
            raiseVisitas(sequence);
        }
        while (1) {
            //Achar os indexs dos retangulos que foram marcados para serem removidos
            if (!strcmp(idToRemove, getId(aux1))) {
                break;
            } else {
                posaux1 = getNext(sequence, posaux1);
                if(posaux1){
                    aux1 = getItem(sequence, posaux1);
                }
            }
            if (posaux1 == NULL) {
                fprintf(results, "-----------\n");
                fclose(a);
                return;
            }
        }
        removeNode(sequence, posaux1);
    }
    fclose(a);

    fprintf(results, "-----------\n");
}

void bbi(double x, double y, lista sequence, FILE* results, flag checkers) {
    int tamanho = getSize(sequence);
    if(tamanho == 0){
        return;
    }
    celula posaux1 = getHead(sequence);
    celula posp1;
    celula posp2;

    item aux1 = getItem(sequence, posaux1);
    item p1;

    fprintf(results, "bbi\n");
    int rec = 0;
    int vectorOfRectanglesInTheBBI[tamanho];
    double menorX, menorY, mAlt, mLarg;
    double xBBI, yBBI, alturaBoundingBox, larguraBoundingBox;
    menorX = 10000000000000000.00;
    menorY = 10000000000000000.00;
    mAlt = 0.0;
    mLarg = 0.0;
    xBBI = yBBI = alturaBoundingBox = larguraBoundingBox = 0.0;

    for (int i = 0; i < tamanho; i++) {
        if (inside(x, y, 0.0, 0.0, getX(aux1), getY(aux1), getLargura(aux1), getAltura(aux1))) {
            fprintf(results, "%s %s %s\n", getId(aux1), getPreenchimento(aux1), getContorno(aux1));
            vectorOfRectanglesInTheBBI[rec] = i;
            rec++;
        }
        posaux1 = getNext(sequence, posaux1);
        if(posaux1){
            aux1 = getItem(sequence, posaux1);
        }
    }

    for (int i = 0; i < rec; i++) {
        posp1 = atPos(sequence, vectorOfRectanglesInTheBBI[i]);
        if(posp1){
            p1 = getItem(sequence, posp1);
        }
        if (getX(p1) < menorX) menorX = getX(p1);
        if (getY(p1) < menorY) menorY = getY(p1);
        
    }
    for (int i = 0; i < rec; i++) {
        posp1 = atPos(sequence, vectorOfRectanglesInTheBBI[i]);
        if(posp1){
            p1 = getItem(sequence, posp1);
        }
        if (getX(p1) + getLargura(p1) - menorX > mLarg) mLarg = getX(p1) + getLargura(p1) - menorX;
        if (getY(p1) + getAltura(p1) - menorY > mAlt) mAlt = getY(p1) + getAltura(p1) - menorY;
    }
    xBBI = menorX;
    yBBI = menorY;
    larguraBoundingBox = mLarg;
    alturaBoundingBox = mAlt;

    if (rec) {  //Existe Bouding box
        FILE* tempDataBBICoordenadas = fopen("tempBBICoordinates.txt", "a+");
        FILE* tempDataBBIPoint = fopen("tempBBIPoints.txt", "a+");
        fprintf(tempDataBBICoordenadas, "%.3lf %.3lf %.3lf %.3lf\n", xBBI, yBBI, larguraBoundingBox, alturaBoundingBox);
        fprintf(tempDataBBIPoint, "%.3lf %.3lf\n", x, y);
        fclose(tempDataBBICoordenadas);
        fclose(tempDataBBIPoint);
    } else if (!rec) {  //Nao existe bouding box
        FILE* tempDataBBIPoint = fopen("tempBBIPoints.txt", "a+");
        fprintf(tempDataBBIPoint, "%.3lf %.3lf\n", x, y);
        fclose(tempDataBBIPoint);
    }
    setBBIexecutado(checkers, true);
    if (rec) {
        char tempColor[50];
        for (int i = 0; i < rec; i++) {
            posaux1 = atPos(sequence, vectorOfRectanglesInTheBBI[i]);
            if(posaux1){
                aux1 = getItem(sequence, posaux1);
            }
            strcpy(tempColor, getPreenchimento(aux1));
            setPreenchimento(aux1, getContorno(aux1));
            setContorno(aux1, tempColor);
        }
    }
    fprintf(results, "-----------\n");
}

void bbid(char* id, lista sequence, FILE* results, flag checkers) {
    int tamanho = getSize(sequence);
    if(tamanho == 0){
        return;
    }
    celula posaux1 = getHead(sequence);
    celula posaux2 = getHead(sequence);
    celula posp1;
    item aux1 = getItem(sequence, posaux1);
    item aux2 = getItem(sequence, posaux2);
    item p1;
    fprintf(results, "bbid\n");
    int rec = 0;
    bool found = false;
    int vectorOfRectanglesInTheBBID[tamanho];
    double menorX, menorY, mAlt, mLarg;
    double xBBI, yBBI, alturaBoundingBox, larguraBoundingBox;
    menorX = 10000000000000000.00;
    menorY = 10000000000000000.00;
    mAlt = 0.0;
    mLarg = 0.0;
    xBBI = yBBI = alturaBoundingBox = larguraBoundingBox = 0.0;
    for (int i = 0; i < tamanho; i++) {
        if (!strcmp(id, getId(aux1))) {
            found = true;
            break;
        } else {
            posaux1 = getNext(sequence, posaux1);
            if(posaux1){
                aux1 = getItem(sequence, posaux1);
            }
        }
    }
    if (posaux1 == NULL && !found) {
        fprintf(results, "id passado nao existe\n");
        return;
    }
    //Aux1 vai estar guardando informacoes do id passado se existir.
    for (int i = 0; i < tamanho; i++) {
        if (inside(getX(aux2), getY(aux2), getLargura(aux2), getAltura(aux2), getX(aux1), getY(aux1), getLargura(aux1), getAltura(aux1)) && (strcmp(id, getId(aux2)))) {
            //Segunda condicao serve para que evite comparacoes com o mesmo retangulo passado no id
            fprintf(results, "%s %s %s\n", getId(aux2), getPreenchimento(aux2), getContorno(aux2));
            vectorOfRectanglesInTheBBID[rec] = i;
            rec++;
        }
        posaux2 = getNext(sequence, posaux2);
        if(posaux2){
            aux2 = getItem(sequence, posaux2);
        }
    }

    for (int i = 0; i < rec; i++) {  //Altura da bbi = menor x ate maior x;
        posp1 = atPos(sequence, vectorOfRectanglesInTheBBID[i]);
        if(posp1){
            p1 = getItem(sequence, posp1);
        }
        if (getX(p1) < menorX) menorX = getX(p1);
        if (getY(p1) < menorY) menorY = getY(p1);
    }
    for (int i = 0; i < rec; i++) {
        posp1 = atPos(sequence, vectorOfRectanglesInTheBBID[i]);
        if(posp1){
            p1 = getItem(sequence, posp1);
        }
        if (getX(p1) + getLargura(p1) - menorX > mLarg) mLarg = getX(p1) + getLargura(p1) - menorX;
        if (getY(p1) + getAltura(p1) - menorY > mAlt) mAlt = getY(p1) + getAltura(p1) - menorY;
    }
    xBBI = menorX;
    yBBI = menorY;
    larguraBoundingBox = mLarg;
    alturaBoundingBox = mAlt;

    if (rec) {  //Primeira vez do bbid considerando que existe uma bouding box
        FILE* tempDataBBIDCoordenadas = fopen("tempBBIDCoordinates.txt", "a+");
        fprintf(tempDataBBIDCoordenadas, "%.3lf %.3lf %.3lf %.3lf\n", xBBI, yBBI, larguraBoundingBox, alturaBoundingBox);
        fclose(tempDataBBIDCoordenadas);
    }
    setBBIDexecutado(checkers, true);
    if (rec) {
        char tempColor[40];
        for (int i = 0; i < rec; i++) {
            posaux1 = atPos(sequence, vectorOfRectanglesInTheBBID[i]);
            if(posaux1){
                aux1 = getItem(sequence, posaux1);
            }
            strcpy(tempColor, getPreenchimento(aux1));
            setPreenchimento(aux1, getContorno(aux1));
            setContorno(aux1, tempColor);
        }
    }

    fprintf(results, "-----------\n");
}

void iid(char* id, int k, lista sequence, FILE* results, flag checkers) {
    int tamanho = getSize(sequence);
    if(tamanho == 0){
        return;
    }
    celula posaux1 = getHead(sequence);
    celula posaux2;
    item aux1 = getItem(sequence, posaux1);
    item aux2;
    int index;
    bool found = false;
    for (int i = 0; i < tamanho; i++) {
        if (!strcmp(id, getId(aux1))) {
            index = i;
            found = true;
            break;
        } else {
            posaux1 = getNext(sequence, posaux1);
            if(posaux1){
                aux1 = getItem(sequence, posaux1);
            }
        }
    }
    if (posaux1 == NULL && !found) {
        fprintf(results, "id passado nao existe\n");
        return;
    }

    fprintf(results, "iid\n");
    if (k > 0) {
        posaux2 = atPos(sequence, index);
        if(posaux2){
            aux2 = getItem(sequence, posaux2);
        }
        for (int i = 0; i < k + 1; i++) {
            if (i == tamanho) {
                break;
            }
            fprintf(results, "[id = %s] [ancora (x,y) = (%.3lf, %.3lf)][largura = %.3lf] [altura = %.3lf] [cc = %s] [cp = %s]\n", getId(aux2), getX(aux2), getY(aux2), getLargura(aux2), getAltura(aux2), getContorno(aux2), getPreenchimento(aux2));
            posaux2 = getNext(sequence, posaux2);
            if(posaux2){
                aux2 = getItem(sequence, posaux2);
            }
            if (posaux2 == NULL) {
                break;
            }
        }

    } else if (k < 0) {
        posaux2 = atPos(sequence, index);
        if(posaux2){
            aux2 = getItem(sequence, posaux2);
        }
        for (int i = 0; i < -k + 1; i++) {
            fprintf(results, "[id = %s] [ancora (x,y) = (%.3lf, %.3lf)] [largura = %.3lf] [altura = %.3lf] [cc = %s] [cp = %s]\n", getId(aux2), getX(aux2), getY(aux2), getLargura(aux2), getAltura(aux2), getContorno(aux2), getPreenchimento(aux2));
            posaux2 = getPrevious(sequence, posaux2);
            if(posaux2){
                aux2 = getItem(sequence, posaux2);
            }

            if (posaux2 == NULL) {
                break;
            }
        }
    }
    setiidExecutado(checkers, true);
    
    fprintf(results, "-----------\n");
}

void diid(char* id, int k, lista sequence, FILE* results, flag checkers) {
    int tamanho = getSize(sequence);
    if(tamanho == 0){
        return;
    }
    celula posaux1 = getHead(sequence);
    celula posaux2;
    item aux1 = getItem(sequence, posaux1);
    item aux2;
    bool found = false;
    int p = 0;
    int index;
    for (int i = 0; i < tamanho; i++) {
        if (!strcmp(id, getId(aux1))) {
            index = i;
            found = true;
            break;
        } else {
            posaux1 = getNext(sequence, posaux1);
            if(posaux1){
                aux1 = getItem(sequence, posaux1);
            }
        }
    }
    if (posaux1 == NULL && !found) {
        fprintf(results, "id passado nao existe\n");
        return;
    }
    
    fprintf(results, "diid\n");
    FILE* tempDiidAppend = fopen("tempDIID.txt", "a+");
    FILE* tempDiidRemoveAppend = fopen("tempDIIDRemove.txt", "a+");
    if (k > 0) {
        posaux2 = atPos(sequence, index);
        if(posaux2){
            aux2 = getItem(sequence, posaux2);
        }
        for (int i = 0; i < k + 1; i++) {
            if (i == tamanho) {
                break;
            }
            fprintf(results, "[id = %s] [ancora (x,y) = (%.3lf, %.3lf)][largura = %.3lf] [altura = %.3lf] [cc = %s] [cp = %s]\n",  getId(aux2), getX(aux2), getY(aux2), getLargura(aux2), getAltura(aux2), getContorno(aux2), getPreenchimento(aux2));
            fprintf(tempDiidAppend, "%s\n", getId(aux2));
            if (strcmp(id, getId(aux2))) {
                fprintf(tempDiidRemoveAppend, "%s\n", getId(aux2));
                p++;
            }
            posaux2 = getNext(sequence, posaux2);
            if(posaux2){
                aux2 = getItem(sequence, posaux2);
            }
            if (posaux2 == NULL) {
                break;
            }
        }
    } else if (k < 0) {
        posaux2 = atPos(sequence, index);
        if(posaux2){
            aux2 = getItem(sequence, posaux2);
        }
        for (int i = 0; i < -k + 1; i++) {
            fprintf(results, "[id = %s] [ancora (x,y) = (%.3lf, %.3lf)] [largura = %.3lf] [altura = %.3lf] [cc = %s] [cp = %s]\n", getId(aux2), getX(aux2), getY(aux2), getLargura(aux2), getAltura(aux2), getContorno(aux2), getPreenchimento(aux2));
            fprintf(tempDiidAppend, "%s\n", getId(aux2));
            if (strcmp(id, getId(aux2))) {
                fprintf(tempDiidRemoveAppend, "%s\n", getId(aux2));
                p++;
            }
            posaux2 = getPrevious(sequence, posaux2);
            if(posaux2){
                aux2 = getItem(sequence, posaux2);
            }
            if (posaux2 == NULL) {
                break;
            }
        }
    }
    fclose(tempDiidAppend);
    fclose(tempDiidRemoveAppend);
    FILE* tempDiidRead = fopen("tempDIIDRemove.txt", "r");
    celula pospointer;
    item pointer;
    char idToRmv[100] = "";
    int posToRmv;
    for (int i = 0; i < p; i++) {
        while (fscanf(tempDiidRead, "%s", idToRmv) != -1) {
            pospointer = getHead(sequence);
            if(pospointer){
                pointer = getItem(sequence, pospointer);
            }
            for (int k = 0; k < tamanho; k++) {
                if (strcmp(getId(pointer), idToRmv)) {
                    pospointer = getNext(sequence, pospointer);
                    if(pospointer){
                        pointer = getItem(sequence, pospointer);
                    }
                } else {
                    break;
                }
            }
            removeNode(sequence, pospointer);
        }
    }

    fclose(tempDiidRead);
    fprintf(results, "-----------\n");
}
#include "bibliotecas.h"
#include "elemento.h"
#include "system.h"


//Constroi o grafico apos um -fb executado com a coleta previamente iniciada
void buildGraphic(lista sequence, path paths);

//Constroi o svg com as informacoes provenientes do getArguments e a execucao do programa
void writeOnSvg(FILE* svg_source, lista sequence, flag checkers);
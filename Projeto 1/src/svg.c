#include "svg.h"
#include "flags.h"
#include "paths.h"

void writeOnSvg(FILE* svg_source, lista sequence, flag checkers) {
    int tamanho = getSize(sequence);
    if(tamanho == 0){
        fprintf(svg_source, "<svg>\n ");
        fprintf(svg_source, "</svg>");
        return;
    }
    celula posaux = getHead(sequence); //posicao
    celula postp1 = getHead(sequence); //posicao
    celula postp2 = getHead(sequence); //posicao
    celula postpr1 = getHead(sequence); //posicao
    item aux = getItem(sequence, posaux); //data
    item tp1 = getItem(sequence, postp1); //data
    item tp2 = getItem(sequence, postp2); //data
    item tpr1 = getItem(sequence, postpr1); //data
    fprintf(svg_source, "<svg>\n ");
    if (getTPRExecutado(checkers)) {
        if(!postp1){
            return;
        }
        char id[100];
        int found = 1;
        FILE* tprData = fopen("tempTPR.txt", "r");
        while (fscanf(tprData, "%s", id) != -1) {
            postpr1 = getHead(sequence);
            raiseVisitas(sequence);
            while (strcmp(getId(tpr1), id)) {
                postpr1 = getNext(sequence, postpr1);
                if(postpr1 != NULL){
                    tpr1 = getItem(sequence, postpr1);
                }
                if(!postpr1){
                    found = 0;
                    break;
                }
            }
            if(found){
                if (!strcmp(getPreenchimento(tpr1), "@")) {
                    fprintf(svg_source, "<rect x=\"%.3lf\" y=\"%.3lf\" width=\"%.3lf\" height=\"%.3lf\"\n  style=\"fill:white;stroke:%s;stroke-width:1;fill-opacity:0;stroke-opacity:1\" />\n", getX(tpr1), getY(tpr1), getLargura(tpr1), getAltura(tpr1), getContorno(tpr1));
                } else if (!strcmp(getContorno(tpr1), "@")) {
                    fprintf(svg_source, "<rect x=\"%.3lf\" y=\"%.3lf\" width=\"%.3lf\" height=\"%.3lf\"\n  style=\"fill:%s;stroke:white;stroke-width:1;fill-opacity:1;stroke-opacity:0\" />\n", getX(tpr1), getY(tpr1), getLargura(tpr1), getAltura(tpr1), getPreenchimento(tpr1));

                } else if (!strcmp(getPreenchimento(tpr1), "@") && !strcmp(getContorno(tpr1), "@")) {
                    fprintf(svg_source, "<rect x=\"%.3lf\" y=\"%.3lf\" width=\"%.3lf\" height=\"%.3lf\"\n  style=\"fill:white;stroke:white;stroke-width:1;fill-opacity:0;stroke-opacity:0\" />\n", getX(tpr1), getY(tpr1), getLargura(tpr1), getAltura(tpr1));
                } else {
                    fprintf(svg_source, "<rect x=\"%.3lf\" y=\"%.3lf\" width=\"%.3lf\" height=\"%.3lf\"\n  style=\"fill:%s;stroke:%s;stroke-width:1;fill-opacity:1;stroke-opacity:1\" />\n", getX(tpr1), getY(tpr1), getLargura(tpr1), getAltura(tpr1), getPreenchimento(tpr1), getContorno(tpr1));
                }
            }
        }
        fclose(tprData);
    } else if (getTPExecutado(checkers)) {
        if(!postp1){
            return;
        }
        char retangulo[50];
        int found = 1;
        FILE* tps = fopen("testeTP.txt", "r");
        while (fscanf(tps, "%s", retangulo) != -1) {
            postp1 = getHead(sequence);
            raiseVisitas(sequence);
            while (strcmp(getId(tp1), retangulo)) {
                postp1 = getNext(sequence, postp1);
                if(postp1 != NULL){
                    tp1 = getItem(sequence, postp1);
                }
                if(!postp1){
                    found = 0;
                    break;
                }
            }
            if(found){
                if (!strcmp(getPreenchimento(tp1), "@")) {
                    fprintf(svg_source, "<rect x=\"%.3lf\" y=\"%.3lf\" width=\"%.3lf\" height=\"%.3lf\"\n  style=\"fill:white;stroke:%s;stroke-width:1;fill-opacity:0;stroke-opacity:1\" />\n", getX(tp1), getY(tp1), getLargura(tp1), getAltura(tp1), getContorno(tp1));
                } else if (!strcmp(getContorno(tp1), "@")) {
                    fprintf(svg_source, "<rect x=\"%.3lf\" y=\"%.3lf\" width=\"%.3lf\" height=\"%.3lf\"\n  style=\"fill:%s;stroke:white;stroke-width:1;fill-opacity:1;stroke-opacity:0\" />\n", getX(tp1), getY(tp1), getLargura(tp1), getAltura(tp1), getPreenchimento(tp1));

                } else if (!strcmp(getPreenchimento(tp1), "@") && !strcmp(getContorno(tp1), "@")) {
                    fprintf(svg_source, "<rect x=\"%.3lf\" y=\"%.3lf\" width=\"%.3lf\" height=\"%.3lf\"\n  style=\"fill:white;stroke:white;stroke-width:1;fill-opacity:0;stroke-opacity:0\" />\n", getX(tp1), getY(tp1), getLargura(tp1), getAltura(tp1));
                } else {
                    fprintf(svg_source, "<rect x=\"%.3lf\" y=\"%.3lf\" width=\"%.3lf\" height=\"%.3lf\"\n  style=\"fill:%s;stroke:%s;stroke-width:1;fill-opacity:1;stroke-opacity:1\" />\n", getX(tp1), getY(tp1), getLargura(tp1), getAltura(tp1), getPreenchimento(tp1), getContorno(tp1));
                }
            }
        }
        fclose(tps);
    } else {
        if(!posaux){
            return;
        }
        for (int i = 0; i < tamanho; i++) {
            if (!strcmp(getPreenchimento(aux), "@")) {
                fprintf(svg_source, "<rect x=\"%.3lf\" y=\"%.3lf\" width=\"%.3lf\" height=\"%.3lf\"\n  style=\"fill:white;stroke:%s;stroke-width:1;fill-opacity:0;stroke-opacity:1\" />\n", getX(aux), getY(aux), getLargura(aux), getAltura(aux), getContorno(aux));
            } else if (!strcmp(getContorno(aux), "@")) {
                fprintf(svg_source, "<rect x=\"%.3lf\" y=\"%.3lf\" width=\"%.3lf\" height=\"%.3lf\"\n  style=\"fill:%s;stroke:white;stroke-width:1;fill-opacity:1;stroke-opacity:0\" />\n", getX(aux), getY(aux), getLargura(aux), getAltura(aux), getPreenchimento(aux));

            } else if (!strcmp(getPreenchimento(aux), "@") && !strcmp(getContorno(aux), "@")) {
                fprintf(svg_source, "<rect x=\"%.3lf\" y=\"%.3lf\" width=\"%.3lf\" height=\"%.3lf\"\n  style=\"fill:white;stroke:white;stroke-width:1;fill-opacity:0;stroke-opacity:0\" />\n", getX(aux), getY(aux), getLargura(aux), getAltura(aux));
            } else {
                fprintf(svg_source, "<rect x=\"%.3lf\" y=\"%.3lf\" width=\"%.3lf\" height=\"%.3lf\"\n  style=\"fill:%s;stroke:%s;stroke-width:1;fill-opacity:1;stroke-opacity:1\" />\n", getX(aux), getY(aux), getLargura(aux), getAltura(aux), getPreenchimento(aux), getContorno(aux));
            }
            posaux = getNext(sequence, posaux);
            if(posaux){
                aux = getItem(sequence, posaux);
            }
        }
    }
    if (getBBIexecutado(checkers)) {
        double xPoint, yPoint;
        double xB, yB, widthB, heightB;

        FILE* boudingBoxes = fopen("tempBBICoordinates.txt", "r");
        while (fscanf(boudingBoxes, "%lf %lf %lf %lf", &xB, &yB, &widthB, &heightB) != -1) {
            fprintf(svg_source, "<rect x=\"%.3lf\" y=\"%.3lf\" width=\"%.3lf\" height=\"%.3lf\"\n  style=\"fill:black;stroke:red;stroke-width:2;fill-opacity:0;stroke-opacity:1;stroke-dasharray:5\" />\n", xB, yB, widthB, heightB);
        }
        fclose(boudingBoxes);

        FILE* pontos = fopen("tempBBIPoints.txt", "r");
        while (fscanf(pontos, "%lf %lf", &xPoint, &yPoint) != -1) {
            fprintf(svg_source, "<circle cx=\"%.3lf\" cy=\"%.3lf\" r=\"1\" stroke=\"black\" stroke-width=\"0.5\" fill=\"white\" /> \n", xPoint, yPoint);
        }
        fclose(pontos);
    }
    if (getBBIDexecutado(checkers)) {
        double xB, yB, widthB, heightB;

        FILE* boudingBoxes = fopen("tempBBIDCoordinates.txt", "r");
        while (fscanf(boudingBoxes, "%lf %lf %lf %lf", &xB, &yB, &widthB, &heightB) != -1) {
            fprintf(svg_source, "<rect x=\"%.3lf\" y=\"%.3lf\" width=\"%.3lf\" height=\"%.3lf\"\n  style=\"fill:black;stroke:red;stroke-width:2;fill-opacity:0;stroke-opacity:1;stroke-dasharray:5\" />\n", xB, yB, widthB, heightB);
        }
        fclose(boudingBoxes);
    }
    fprintf(svg_source, "</svg>");
}

void buildGraphic(lista sequence, path paths) {
    FILE* grafico = fopen(getPathSVGFinalGrafico(paths), "w+");
    FILE* consultas = fopen("visitasDoQryAtual.txt", "r");
    long int n_visitas, n_elementos_na_lista, maiorVisita, maiorTamanho;
    int quantidadeDeQrys = 0;
    double divHorT, divVerT;
    n_visitas = 0;
    n_elementos_na_lista = 0;
    maiorVisita = 0;
    maiorTamanho = 0;
    divHorT = 0.0;
    divVerT = 0.0;
    fprintf(grafico, "<svg viewBox = \"0 0 3000 1700\">\n\t<rect width=\"100%%\" height=\"100%%\" fill=\"white\"/>\n");
    fprintf(grafico, "\t<text x=\"70\" y=\"850\" font-size=\"30px\" >Visitas</text>\n\t<line x1=\"200\" x2=\"200\" y1=\"100\" y2=\"1610\" style=\"stroke:black;stroke-width:2\"/>\n\t<text x=\"1500\" y=\"1660\" font-size=\"30px\" text-anchor=\"middle\">Tamanho</text>\n\t<line x1=\"200\" x2=\"2700\" y1=\"1600\" y2=\"1600\" style=\"stroke:black;stroke-width:2\"/>\n\t<text x=\"1500\" y=\"1690\" font-size=\"30px\" text-anchor=\"middle\">%s</text>\n", getTituloGrafFinal(paths));
    for (int i = 0; i < 16; i++) {
        fprintf(grafico, "\t<line x1=\"190\" x2=\"210\" y1=\"%d\" y2=\"%d\" style=\"stroke:black;stroke-width:2\"/>\n", (i + 1) * 100, (i + 1) * 100);
    }
    for (int i = 0; i < 25; i++) {
        fprintf(grafico, "\t<line x1=\"%d\" x2=\"%d\" y1=\"1590\" y2=\"1600\" style=\"stroke:black;stroke-width:2\"/>\n", 300 + (i * 100), 300 + (i * 100));
    }
    while (fscanf(consultas, "%ld %ld", &n_visitas, &n_elementos_na_lista) != -1) {
        quantidadeDeQrys++;
        if (n_visitas >= maiorVisita) maiorVisita = n_visitas;
        if (n_elementos_na_lista >= maiorTamanho) maiorTamanho = n_elementos_na_lista;
    }
    divHorT = maiorTamanho / 25.0;
    divVerT = maiorVisita / 15.0;
    rewind(consultas);
    for (int i = 0; i < 15; i++) {
        fscanf(consultas, "%ld %ld", &n_visitas, &n_elementos_na_lista);
        fprintf(grafico, "\t<text x=\"100\" y=\"%d\" font-size=\"20px\">%.2lf</text>\n", 105 + (100 * i), (maiorVisita / 15.0) * (15 - i));
    }
    rewind(consultas);
    for (int i = 0; i < 25; i++) {
        fscanf(consultas, "%ld %ld", &n_visitas, &n_elementos_na_lista);
        fprintf(grafico, "\t<text x=\"%d\" y=\"1630\" font-size=\"20px\">%.2lf</text>\n", 290 + (100 * i), (maiorTamanho / 25.0) * (i + 1));
    }
    rewind(consultas);
    for (int i = 0; i < quantidadeDeQrys; i++) {
        fscanf(consultas, "%ld %ld", &n_visitas, &n_elementos_na_lista);
        fprintf(grafico, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"6\"></circle>\n", (double)200 + (100 * (n_elementos_na_lista / divHorT)), (double)1600 - (100 * (n_visitas / divVerT)));
        //Horizontal
        fprintf(grafico, "\t<line x1=\"200\" x2=\"%.2lf\" y1=\"%.2lf\" y2=\"%.2lf\" style=\"stroke:black;stroke-width:2;stroke-dasharray:4\"/>\n", (double)200 + (100 * (n_elementos_na_lista / divHorT)), (double)1600 - (100 * (n_visitas / divVerT)), (double)1600 - (100 * (n_visitas / divVerT)));
        //Vertical
        fprintf(grafico, "\t<line x1=\"%.2lf\" x2=\"%.2lf\" y1=\"1600\" y2=\"%.2lf\" style=\"stroke:black;stroke-width:2;stroke-dasharray:4\"/>\n", (double)200 + (100 * (n_elementos_na_lista / divHorT)), (double)200 + (100 * (n_elementos_na_lista / divHorT)), (double)1600 - (100 * (n_visitas / divVerT)));
    }

    fprintf(grafico, "</svg>");
    fclose(grafico);
    fclose(consultas);
}
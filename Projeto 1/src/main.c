#include "bibliotecas.h"
#include "lista.h"
#include "system.h"
#include "flags.h"
#include "paths.h"
#include "svg.h"

int main(int argc, char** argv){
    flag checkers = createFlags();
    path paths = createPathsGerais();
    getArguments(argc, argv, checkers, paths);
    if(getFail(checkers) || !getFileGeo(checkers) || !getPathSaida(checkers) || !getFileQryValido(checkers)){
        freePaths(paths);
        free(checkers);
        return -1;
    }
    FILE* SvgSemAlteracao = fopen(getPathDoSvgDoGeoSemMudanca(paths), "w+");
    FILE* geo_source = fopen(getPathArquivoGeoInicial(paths), "r");
    int espaco = nxFind(paths);
    lista sequence = createList(espaco);
    getData(sequence, paths);
    writeOnSvg(SvgSemAlteracao, sequence, checkers);
    if(getConsultafeita(checkers)){
        createTempFiles();
        getFunctions(sequence, getPathArquivoQryAtual(paths), checkers, paths);
        checarColetas(sequence, checkers, paths);
        removeTempFiles();
    }
    freeList(sequence, espaco);
    freePaths(paths);
    free(checkers);
    CloseFiles(geo_source, SvgSemAlteracao);
}
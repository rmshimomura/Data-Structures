#include "flags.h"

typedef struct flags{
    bool BBIDexecutado;
    bool BBIexecutado;
    bool CbExecutado;
    bool Consultafeita;
    bool Fail;
    bool FbExecutado;
    bool FileQryValido;
    bool FileGeo;
    bool IbExecutado;
    bool iidExecutado;
    bool PathSaida;
    bool TPExecutado;
    bool TPRExecutado;
}flags;

flag createFlags(){
    flags* aux = calloc(1, sizeof(flags));
    return aux;
}

void setFlags(flag checkers){
    flags* aux = checkers;
    aux->BBIDexecutado = false;
    aux->BBIexecutado = false;
    aux->CbExecutado = false;
    aux->Consultafeita = false;
    aux->Fail = false;
    aux->FbExecutado = false;
    aux->FileGeo = false;
    aux->IbExecutado = false;
    aux->iidExecutado = false;
    aux->PathSaida = false;
    aux->TPExecutado = false;
    aux->TPRExecutado = false;
    aux->FileQryValido = false;
}

void setBBIDexecutado(flag checkers, bool state){
    flags* aux = checkers;
    aux->BBIDexecutado = state;
}

void setBBIexecutado(flag checkers, bool state){
    flags* aux = checkers;
    aux->BBIexecutado = state;
}

void setCbExecutado(flag checkers, bool state){
    flags* aux = checkers;
    aux->CbExecutado = state;
}

void setConsultafeita(flag checkers, bool state){
    flags* aux = checkers;
    aux->Consultafeita = state;
}

void setFail(flag checkers, bool state){
    flags* aux = checkers;
    aux->Fail = state;
}

void setFbExecutado(flag checkers, bool state){
    flags* aux = checkers;
    aux->FbExecutado = state;
}

void setFileGeo(flag checkers, bool state){
    flags* aux = checkers;
    aux->FileGeo = state;
}

void setIbExecutado(flag checkers, bool state){
    flags* aux = checkers;
    aux->IbExecutado = state;
}

void setiidExecutado(flag checkers, bool state){
    flags* aux = checkers;
    aux->iidExecutado = state;
}

void setPathSaida(flag checkers, bool state){
    flags* aux = checkers;
    aux->PathSaida = state;
}

void setTPExecutado(flag checkers, bool state){
    flags* aux = checkers;
    aux->TPExecutado = state;
}

void setTPRExecutado(flag checkers, bool state){
    flags* aux = checkers;
    aux->TPRExecutado = state;
}

void setFileQryValido(flag checkers, bool state){
    flags* aux = checkers;
    aux->FileQryValido = state;
}

//-------------------------------------------------//

bool getBBIDexecutado(flag checkers){
    flags* aux = checkers;
    return aux->BBIDexecutado;
}

bool getBBIexecutado(flag checkers){
    flags* aux = checkers;
    return aux->BBIexecutado;
}

bool getCbExecutado(flag checkers){
    flags* aux = checkers;
    return aux->CbExecutado;
}

bool getConsultafeita(flag checkers){
    flags* aux = checkers;
    return aux->Consultafeita;
}

bool getFail(flag checkers){
    flags* aux = checkers;
    return aux->Fail;
}

bool getFileGeo(flag checkers){
    flags* aux = checkers;
    return aux->FileGeo;
}

bool getFbExecutado(flag checkers){
    flags* aux = checkers;
    return aux->FbExecutado;
}

bool getIbExecutado(flag checkers){
    flags* aux = checkers;
    return aux->IbExecutado;
}

bool getiidExecutado(flag checkers){
    flags* aux = checkers;
    return aux->iidExecutado;
}

bool getPathSaida(flag checkers){
    flags* aux = checkers;
    return aux->PathSaida;
}

bool getTPExecutado(flag checkers){
    flags* aux = checkers;
    return aux->TPExecutado;
}

bool getTPRExecutado(flag checkers){
    flags* aux = checkers;
    return aux->TPRExecutado;
}

bool getFileQryValido(flag checkers){
    flags* aux = checkers;
    return aux->FileQryValido;
}
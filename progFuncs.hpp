#ifndef PROGFUNCS_HPP_INCLUDED
#define PROGFUNCS_HPP_INCLUDED

#include "mainStructs.hpp"



ReturnedError executeInside(string name){
    ReturnedError retErr;
    if(name.find('/')!=string::npos || name.find('\\')!=string::npos || name.find('.')!=string::npos || name.find('|')!=string::npos){ // Ne marche pas...
        retErr.isError=true;
        retErr.errorMsg="Le nom ne doit pas contiendre |, /, \\ ou ..";
        return retErr;
    }
    GetLastError(); // on vide si jamais
    STARTUPINFO sti;
    GetStartupInfo(&sti);
    SECURITY_ATTRIBUTES secu;
    secu.nLength=sizeof(SECURITY_ATTRIBUTES);
    secu.bInheritHandle=true;
    PROCESS_INFORMATION proci;
    if(CreateProcess(
        string("preaugram/ksh/"+name+".exe").c_str(), NULL,
        NULL, NULL, true, 0,// https://msdn.microsoft.com/en-us/library/windows/desktop/ms684863(v=vs.85).aspx
        NULL, NULL, &sti, &proci
    )){
        WaitForSingleObject(proci.hProcess, INFINITE);
        CloseHandle(proci.hProcess);
        CloseHandle(proci.hThread);
    }

    DWORD newErr;
    if(newErr=GetLastError()){
        retErr.isError=true;
        retErr.winId=newErr;
        retErr.errorMsg="Windows est pas content. Il dit : ";
    }else
        retErr.isError=false;
    return retErr;
}

ReturnedError executeOutside(string name){
    ReturnedError retErr;
    if(name.find('/')!=string::npos || name.find('\\')!=string::npos || name.find('.')!=string::npos || name.find('|')!=string::npos){
        retErr.isError=true;
        retErr.errorMsg="Le nom ne doit pas contiendre |, /, \\ ou ..";
        return retErr;
    }
    GetLastError(); // on vide si jamais
    STARTUPINFO sti;
    GetStartupInfo(&sti);
    SECURITY_ATTRIBUTES secu;
    secu.nLength=sizeof(SECURITY_ATTRIBUTES);
    secu.bInheritHandle=true;
    PROCESS_INFORMATION proci;
    if(CreateProcess(
        string("preaugram/windob/"+name+"/"+name+".exe").c_str(), NULL,
        NULL, NULL, false, DETACHED_PROCESS,// https://msdn.microsoft.com/en-us/library/windows/desktop/ms684863(v=vs.85).aspx
        NULL, string("preaugram/windob/"+name+"/").c_str(), &sti, &proci
    )){
        retErr.isError=false;
        return retErr;
    }

    DWORD newErr;
    if(newErr=GetLastError()){
        retErr.isError=true;
        retErr.winId=newErr;
        retErr.errorMsg="Windows est pas content. Il dit : ";
    }else
        retErr.isError=false;
    return retErr;
}

void launchNav(string address){ // J'avais vraiment pas déjà fait ?
    ShellExecute(HWND_DESKTOP, "open", string("http://"+address).c_str(),NULL, NULL, NULL);
}

#endif // PROGFUNCS_HPP_INCLUDED

#include <iostream>
#include <windows.h>
#include <commctrl.h>
#include <richedit.h>
#include "resource.h"

using namespace std;

HINSTANCE hInst;
HBRUSH brush;
HPEN greenPen;
COLORREF actual;

char *CONCATENAR(char *A,char *B){
    char *C;
    int i=0;for(;*(A+i);i++);
    int j=0;for(;*(B+j);j++);
    int S=i+j;C=new char[S];
    for(i=0;*(A+i);i++){
        *(C+i)=*(A+i);
    }for(j=0;*(B+j);j++,i++){
        *(C+i)=*(B+j);
    }*(C+i)='\0';
    return C;
}

bool ValBase(char *NUM){
    bool Valido=1;
    for(int i=0;*(NUM+i);i++){
        if(*(NUM+i)>'/'&&*(NUM+i)<':'){
        }else{
            Valido=0;
            break;
        }
    }
    cout<<Valido<<"BB ";
    return Valido;
}
bool EntradaCad(HWND hwndDlg,char *NUM,int Base){
    bool Valido=1;bool Bs=0;
    if(Base>1&&Base<=10){
    }else if(Base>10&&Base<=36){Bs=1;
    }else{
        SetDlgItemText(hwndDlg,EDIT8,"La Base Exede el Rango");
        SetDlgItemText(hwndDlg,EDIT11,"");
        cout<<"La Base Exede el Rango\n";
        return Valido;
    }
    for(int i=0;*(NUM+i);i++){
        if(Bs==0){
            if(*(NUM+i)>'/'&&*(NUM+i)<(char)(Base+48)){

            }else{
                Valido=0;
                SetDlgItemText(hwndDlg,EDIT8,"Error El Numero No Corresponde a La Base...");
                SetDlgItemText(hwndDlg,EDIT11,"");
                cout<<"Error El Numero No Corresponde a La Base...\n";
                return Valido;
            }
        }
        if(Bs==1){
            if((*(NUM+i)>'/'&&*(NUM+i)<':')||(*(NUM+i)>='A'&&*(NUM+i)<=(char)(Base+54))){

            }else{
                Valido=0;
                SetDlgItemText(hwndDlg,EDIT8,"Error El Numero No Corresponde a La Base...");
                SetDlgItemText(hwndDlg,EDIT11,"");
                cout<<"Error El Numero No Corresponde a La Base...\n";
                return Valido;
            }
        }

    }
    return Valido;
}

char *InverTIR(char *N,int C){
    char *N1=new char[C+1];*(N1+C+1)='\0';
    int j=0;for(;C;C--,j++){
        int interMedia=(int)*(N+C-1);
        if(interMedia>57){
            interMedia+=7;
            *(N1+j)=(char)(interMedia);
        }else{
            *(N1+j)=*(N+C-1);
        }
    }*(N1+j)='.';
    cout<<endl<<N1;
    return N1;
}
void ConverBase(HWND hwndDlg,unsigned long long CadNum,double CadNumDecimal,int Bini,int Bfin){
    char *CadFINAL=new char[100];int i=0;


    if(Bini!=10){
        unsigned long long Resu=0;
        unsigned long long DBas=CadNum;
        int BiniIN=1;
        for(int j=0;DBas>0;j++){

            for(int s=j;s>0;s--){
                BiniIN*=Bini;
            }
            cout<<(DBas%10)<<" "<<BiniIN<<endl;
            Resu+=(DBas%10)*BiniIN;
            DBas/=10;BiniIN=1;
        }
        cout<<Resu<<"RR"<<endl;CadNum=Resu;
    }

    for(;;){
        if((CadNum/Bfin)<(Bfin)){
            *(CadFINAL+i)=(char)(CadNum%Bfin+48);i++;
            *(CadFINAL+i)=(char)(CadNum/Bfin+48);i++;
            cout<<"->"<<(char)(CadNum%Bfin+48)<<" ";
            cout<<"->"<<CadNum/Bfin<<" Fin\n";
            break;
        }else{
            cout<<CadNum/Bfin<<" ";
            *(CadFINAL+i)=(CadNum%Bfin+48);i++;
            cout<<"->"<<(char)(CadNum%Bfin+48)<<endl;
        }CadNum=CadNum/Bfin;
    }*(CadFINAL+i)='\0';

    cout<<endl<<i<<endl<<CadFINAL<<endl<<"RESULTADO:"<<endl;

    long PInt=CadNumDecimal;
    double PDcm=CadNumDecimal-PInt;

    char *Flotantes=new char[11];
    int j=0;for(;PDcm&&j<5;j++){
        PDcm*=Bfin;
        PInt=PDcm;
        if(PInt>9){
            *(Flotantes+j)=(char)(PInt+55);
        }else{
            *(Flotantes+j)=(char)(PInt+48);
        }
        PDcm=PDcm-PInt;
    }*(Flotantes+j)='\0';

    SetDlgItemText(hwndDlg,EDIT11,CONCATENAR(InverTIR(CadFINAL,i),Flotantes));

}

void CONVERBASE_D(HWND hwndDlg,unsigned long long NumInt,double PuntFloat,int BaseInicial,int BaseFinal)
{
    cout<<NumInt<<"\n";
    cout<<PuntFloat<<"\n";
    cout<<BaseInicial<<"\n";
    cout<<BaseFinal<<"\n";
    ConverBase(hwndDlg,NumInt,PuntFloat,BaseInicial,BaseFinal);
}


BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    switch(uMsg)
    {
        case WM_PAINT:
        {   HDC hdc;
            PAINTSTRUCT ps;
            hdc=BeginPaint(hwndDlg,&ps);
            greenPen=CreatePen(PS_SOLID, 2, RGB(51, 204, 255));
            SelectObject(hdc,greenPen);
            Rectangle(hdc,5,5,695,240);
            DeleteObject(greenPen);
            EndPaint(hwndDlg,&ps);
        }
        case WM_INITDIALOG:
        {
        }
        return TRUE;

        case WM_CLOSE:
        {   EndDialog(hwndDlg, 0);
        }
        return TRUE;

        case WM_COMMAND:
        {   switch(LOWORD(wParam))
            {
                case BTN_LIMPIAR:
                    SetDlgItemText(hwndDlg,EDIT1,"");
                    SetDlgItemText(hwndDlg,EDIT2,"");
                    SetDlgItemText(hwndDlg,EDIT11,"");
                    SetDlgItemText(hwndDlg,EDIT8,"----------------");
                    InvalidateRect(hwndDlg,NULL,true);
                    return TRUE;
                case BTN_INSERTAR:

                    char Cad[20],Cad1[10],Cad2[20],Cad3[20],Cad4[10];
                    unsigned long long NumInt;
                    double PuntFloat;
                    int BaseInicial;
                    int BaseFinal;

                    GetDlgItemText(hwndDlg,EDIT1,Cad,20);//capturar evento
                    NumInt=atoll(Cad);
                    GetDlgItemText(hwndDlg,EDIT2,Cad1,10);
                    PuntFloat=atof(Cad1);
                    GetDlgItemText(hwndDlg,EDIT3,Cad2,20);
                    BaseInicial=atoi(Cad2);
                    GetDlgItemText(hwndDlg,EDIT4,Cad3,20);
                    BaseFinal=atoi(Cad3);

                    int M=0,N=0;bool ABRE=0;for(;*(Cad1+M);M++){
                        if(*(Cad1+M)=='.'){ABRE=1;M++;
                        }if(ABRE==1){
                            *(Cad4+N)=*(Cad1+M);
                            N++;
                        }
                    }*(Cad4+N)='\0';

                    if(ValBase(Cad2)){
                        int Base=atoi(Cad2);
                        if(Base>1&&Base<=36){
                            if(EntradaCad(hwndDlg,Cad,Base)){
                            if(EntradaCad(hwndDlg,Cad4,Base)){
                                if(ValBase(Cad3)){
                                    int BaseFIN=atoi(Cad3);
                                    if(BaseFIN>1&&BaseFIN<=36){
                                        if(Base!=BaseFIN){
                                            cout<<"CORRECTO";
                                            SetDlgItemText(hwndDlg,EDIT8,"CORRECTO");
                                            CONVERBASE_D(hwndDlg,NumInt,PuntFloat,BaseInicial,BaseFinal);
                                        }else{
                                            SetDlgItemText(hwndDlg,EDIT8,"La Base es la misma");
                                            SetDlgItemText(hwndDlg,EDIT11,"");
                                        }
                                    }else{
                                        SetDlgItemText(hwndDlg,EDIT8,"Error Base Destino");
                                        SetDlgItemText(hwndDlg,EDIT11,"");
                                        cout<<"Error Base Destino";
                                    }
                                }else{
                                    SetDlgItemText(hwndDlg,EDIT8,"Error Base Destino");
                                    SetDlgItemText(hwndDlg,EDIT11,"");
                                }
                            }}
                        }else{
                            SetDlgItemText(hwndDlg,EDIT8,"Error Base Destino");
                            SetDlgItemText(hwndDlg,EDIT11,"");
                            cout<<"Error Base Destino";
                        }
                    }else{
                        SetDlgItemText(hwndDlg,EDIT8,"Base Incorrecta...");
                        SetDlgItemText(hwndDlg,EDIT11,"");
                        cout<<"Base Incorrecta...";
                    }
                    InvalidateRect(hwndDlg,NULL,true);
                    return TRUE;
            }
        }return TRUE;
    }
    return FALSE;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}

//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include <stdio.h>
#include <stdlib.h>
#include "genopt.h"
#include "wsetup.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TGenOptBox *GenOptBox;
//---------------------------------------------------------------------------
__fastcall TGenOptBox::TGenOptBox(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

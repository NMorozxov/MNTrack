#include "xsetapp.h"
#include "xsetapp.moc"

extern int ConfigChanged;

XSetupApp::XSetupApp( int &argc, char **argv)
 :QApplication(argc,argv)
{
}

void XSetupApp::quit()
{
disconnect(SIGNAL(lastWindowClosed()));
if (ConfigChanged && !QMessageBox::information(NULL,"MNTrack Setup","Save MNTrack configuration ?","Yes","No",0,0,1))
 SaveConfig();
unlink("mntrack.bsy");
}

#include "mntrq.h"
void exit_mntrack(int retcode)
{
unlink("mntrack.bsy");
exit(retcode);
}

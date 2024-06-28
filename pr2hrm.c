#include "pr2hrm.h"
#include "linked_list.h"
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LEN 256
#define empty (-1)

typedef struct HrMgmt_s
{
    LinkedList list;
}HrMgmt_t,*HrMgmt;

typedef struct Workers_s
{
    char name[MAX_NAME_LEN];
    int id;
    HrmWorkerRole role;
    float wage;
    int numOfShifts;
}worker_t,*Worker;
/*worker_t type , Worker is pointer */

static ListElement copyworker(ListElement element){
    Worker worker  = (Worker)element;
    Worker new_worker = NULL;
    if (element == NULL)
        return NULL;
    new_worker = (Worker)malloc(sizeof(worker_t));
    if(new_worker == NULL)
        return NULL;

    strncpy(new_worker->name,worker->name,MAX_NAME_LEN);
    new_worker->id = worker->id;
    new_worker->role = worker->role;
    new_worker->wage = worker->wage;
    new_worker->numOfShifts = worker->numOfShifts;

    return new_worker;
}
static void freeWorker(ListElement element){
    if (element)
        free(element);
}

static void printWorker(FILE *out, ListElement element)
{
    Worker worker = (Worker)element;
    if (worker == NULL)
        return;
    fprintf(out, "\t[%09d] %s %d %d %f\n", worker->id,worker->name,worker->numOfShifts,worker->role,worker->wage);
}

HrMgmt HrMgmtCreate() {
    HrMgmt new_hr = (HrMgmt)malloc(sizeof(HrMgmt_t));
    if (new_hr == NULL)
        return NULL;
    if(linkedListCreate(&(new_hr->list),copyworker,freeWorker,printWorker) != LIST_SUCCESS)
    {
        free(NULL);
        return HRM_OUT_OF_MEMORY;
    }
    return HRM_SUCCESS;
}

void HrMgmtDestroy(HrMgmt hrm){
    if(hrm){
        
        free(hrm);
    }
}
HrmResult HrMgmtAddWorker(HrMgmt hrm,const char *name, int id, HrmWorkerRole role, float wage, int numOfShifts){

}
HrmResult HrMgmtRemoveWorker(HrMgmt hrm, int id){

}
HrmResult HrMgmtAddShiftToWorker(HrMgmt hrm, int id, HrmShiftDay day,HrmShiftType type){

}
HrmResult HrMgmtRemoveShiftFromWorker(HrMgmt hrm, int id, HrmShiftDay day,HrmShiftType type){

}
HrmResult HrMgmtTransferShift(HrMgmt hrm, int fromId, int toId,HrmShiftDay day, HrmShiftType type){

}
HrmResult HrMgmtReportWorkers (HrMgmt hrm, HrmWorkerRole role, FILE *outStream){

}
HrmResult HrMgmtReportShiftsOfWorker (HrMgmt hrm, int id, FILE *outStream){

}
HrmResult HrMgmtReportWorkersInShift (HrMgmt hrm, HrmShiftDay day,HrmShiftType type, FILE *outStream){

}
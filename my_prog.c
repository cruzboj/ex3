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

static int matchWorkerById(ListElement element, KeyForListElement key){
    if(element == NULL || key == NULL)
        return 0;
    Worker wo = (Worker)element;
    int id = *(int*)key;
    return wo->id == id;
}

HrMgmt HrMgmtCreate() {
    HrMgmt new_hr = (HrMgmt)malloc(sizeof(HrMgmt_t));
    if (new_hr == NULL)
        return NULL;
    if(linkedListCreate(&(new_hr->list),copyworker,freeWorker,printWorker) != LIST_SUCCESS)
    {
        free(NULL);
        return NULL;
    }
    return new_hr;
}

void HrMgmtDestroy(HrMgmt hrm){
    if(hrm)
        free(hrm);
    if(linkedListDestroy(hrm->list) == LIST_SUCCESS)
        free(hrm);
    return;
}
HrmResult HrMgmtAddWorker(HrMgmt hrm,const char *name, int id, HrmWorkerRole role, float wage, int numOfShifts){
    Worker add_worker;
    add_worker->id = id;
    strncpy(add_worker->name,name,MAX_NAME_LEN);
    add_worker->role = role;
    add_worker->wage = wage;

    if (hrm == NULL)
        return HRM_NULL_ARGUMENT;
    else if(linkedListInsertFirst(hrm->list,&add_worker) != LIST_SUCCESS)
        return HRM_NULL_ARGUMENT;
    else if(add_worker->id < 0 )
        return HRM_INVALID_WORKER_ID;
    else if(add_worker->wage < 9)
        return HRM_INVALID_WAGE;
    else if(add_worker->numOfShifts < 0 && add_worker->numOfShifts %2 == 0)
        return HRM_INVALID_NUM_OF_SHIFTS;
    else if(linkedListFind(hrm->list,&id,matchWorkerById) == LIST_SUCCESS)
        return HRM_WORKER_ALREADY_EXISTS;
    else
    return HRM_SUCCESS;
}
HrmResult HrMgmtRemoveWorker(HrMgmt hrm, int id){
    Worker rem_wo ;

    linkedListGoToHead(hrm->list);
    rem_wo->id = id;
    if(rem_wo->id < 0)
        return HRM_INVALID_WORKER_ID;
    else if(linkedListFind(hrm->list,&id,matchWorkerById) != LIST_SUCCESS){
        if(linkedListRemoveCurrent(hrm->list) != LIST_SUCCESS)
            return HRM_WORKER_DOES_NOT_EXIST;
    }
    
    

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
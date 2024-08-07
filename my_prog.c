#include "pr2hrm.h"
#include "linked_list.h"

#include <string.h>
#include <stdlib.h>
#define MAX_NAME_LEN 256
#define MAX_SHIFT 100
#define empty (-1)

typedef struct HrMgmt_s
{
    LinkedList list;

}HrMgmt_t,*HrMgmt;

typedef struct shift_s
{
    HrmShiftDay day;
    HrmShiftType shift_type;
    int shift_count;
}shift_t,*shift;

typedef struct Workers_s
{
    char name[MAX_NAME_LEN];
    int id;
    HrmWorkerRole role;
    float wage;
    int numOfShifts;
    shift_t *Shifts;
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

    for (int i = 0; i < worker->numOfShifts; i++) {
        new_worker->Shifts[i].day = worker->Shifts[i].day;
        new_worker->Shifts[i].shift_type = worker->Shifts[i].shift_type;
    }
    
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
    add_worker->Shifts->shift_count = 0;

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
    if(hrm == NULL)
        return HRM_NULL_ARGUMENT;

    linkedListGoToHead(hrm->list);
    
    
    if(linkedListFind(hrm->list,&id,matchWorkerById) == LIST_SUCCESS){
        if(linkedListRemoveCurrent(hrm->list) != LIST_SUCCESS)
            return HRM_INVALID_WORKER_ID;
    }
    else
    {
        return HRM_WORKER_DOES_NOT_EXIST;
    }
    return HRM_SUCCESS;

}
HrmResult HrMgmtAddShiftToWorker(HrMgmt hrm, int id, HrmShiftDay day,HrmShiftType type){
    if(hrm == NULL)
        return HRM_NULL_ARGUMENT; 

    linkedListGoToHead(hrm->list);
    if(id < 0)
        return HRM_INVALID_WORKER_ID;
    if(linkedListFind(hrm->list,&id,matchWorkerById) == LIST_SUCCESS){
        Worker worker_shift;  
        
        if(linkedListGetCurrent(hrm->list,(ListElement *)&worker_shift))
        {
            for (int i = 0; i < worker_shift->numOfShifts; i++) {
                if(day == worker_shift->Shifts[i].day && type == worker_shift->Shifts[i].shift_type)
                    return HRM_SHIFT_ALREADY_EXISTS;
            }
            shift_t* newShifts = realloc(worker_shift->Shifts, (worker_shift->numOfShifts + 1) * sizeof(shift_t));
            if (newShifts == NULL) {
                free(newShifts);
                return HRM_OUT_OF_MEMORY;
            }
            if(newShifts->shift_count > worker_shift->numOfShifts)
                return HRM_SHIFTS_OVERFLLOW;
            else{
                worker_shift->Shifts = newShifts;
                worker_shift->Shifts[worker_shift->Shifts->shift_count].day = day;
                worker_shift->Shifts[worker_shift->Shifts->shift_count].shift_type = type;
                worker_shift->Shifts->shift_count++;
                return HRM_SUCCESS;
            }
        }
    }
    else
        return HRM_WORKER_DOES_NOT_EXIST;

}

HrmResult HrMgmtRemoveShiftFromWorker(HrMgmt hrm, int id, HrmShiftDay day,HrmShiftType type){
     if(hrm == NULL)
        return HRM_NULL_ARGUMENT;

    linkedListGoToHead(hrm->list);
    if(id < 0)
        return HRM_INVALID_WORKER_ID;
    if(linkedListFind(hrm->list,&id,matchWorkerById) == LIST_SUCCESS){
        Worker remove_worker_shift;  
         
        if(linkedListGetCurrent(hrm->list,(ListElement *)&remove_worker_shift))
        {
            for (int i = 0; i < remove_worker_shift->numOfShifts; i++) {
                if(day == remove_worker_shift->Shifts[i].day && type == remove_worker_shift->Shifts[i].shift_type)
                {
                    for (int j = i; j < remove_worker_shift->numOfShifts - 1; j++) {
                        remove_worker_shift->Shifts[j] = remove_worker_shift->Shifts[j + 1];
                    }
                remove_worker_shift->numOfShifts--;
                
                remove_worker_shift->Shifts[remove_worker_shift->numOfShifts].day = (HrmShiftDay)0;
                remove_worker_shift->Shifts[remove_worker_shift->numOfShifts].shift_type = (HrmShiftType)0;  
                return HRM_SUCCESS;
                }    
            }
            return HRM_SHIFT_DOES_NOT_EXIST;
        }
    }
    else
        return HRM_WORKER_DOES_NOT_EXIST;
}
HrmResult HrMgmtTransferShift(HrMgmt hrm, int fromId, int toId,HrmShiftDay day, HrmShiftType type){

}
HrmResult HrMgmtReportWorkers (HrMgmt hrm, HrmWorkerRole role, FILE *outStream){

}
HrmResult HrMgmtReportShiftsOfWorker (HrMgmt hrm, int id, FILE *outStream){

}
HrmResult HrMgmtReportWorkersInShift (HrMgmt hrm, HrmShiftDay day,HrmShiftType type, FILE *outStream){

}

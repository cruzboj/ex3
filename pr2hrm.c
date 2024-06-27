#include "pr2hrm.h"
#include "linked_list.h"

typedef struct node_s{
    size_t index;
    struct node_s * next;
}node_t;

typedef struct HrMgmt_s
{
    size_t size;
    //size_t capacity;
    node_t * head;
}HrMgmt_t;

HrMgmt HrMgmtCreate() {
    HrMgmt hrm = (HrMgmt)malloc(sizeof(HrMgmt_t));
    if (hrm == NULL) {
        return NULL;
    }
    hrm->size = 0;
    hrm->head = (node_t *)malloc(sizeof(node_t));
    if(hrm->head == NULL)
    {
        free(hrm);
        return NULL;
    }
    hrm->head->index = NULL;
    hrm->head->next = NULL;

    return hrm;
}
void HrMgmtDestroy(HrMgmt hrm){
    if(hrm){
        
        free(hrm);
    }
}
HrmResult HrMgmtAddWorker(HrMgmt hrm,
const char *name, int id, HrmWorkerRole role, float wage, int numOfShifts){

}
HrmResult HrMgmtRemoveWorker(HrMgmt hrm, int id){

}
HrmResult HrMgmtAddShiftToWorker(HrMgmt hrm, int id, HrmShiftDay day,
HrmShiftType type){

}
HrmResult HrMgmtRemoveShiftFromWorker(HrMgmt hrm, int id, HrmShiftDay day,
HrmShiftType type){

}
HrmResult HrMgmtTransferShift(HrMgmt hrm, int fromId, int toId,
HrmShiftDay day, HrmShiftType type){

}
HrmResult HrMgmtReportWorkers (HrMgmt hrm, HrmWorkerRole role, FILE *outStream){

}
HrmResult HrMgmtReportShiftsOfWorker (HrMgmt hrm, int id, FILE *outStream){

}
HrmResult HrMgmtReportWorkersInShift (HrMgmt hrm, HrmShiftDay day,
HrmShiftType type, FILE *outStream){

}
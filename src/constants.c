#include <stdio.h>
#include "constants.h"
void clean_stdin(void)
{
    int c;

    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int initFlowList()
{
    extern int FLOWS[];
    FILE *flowFile = NULL;
    flowFile = fopen(FLOWFILE, "r");
    int i;
    if (flowFile != NULL)
    {
        char *line = NULL;
        size_t lineSize = 0;
        getline(&line, &lineSize, flowFile);
        line[strcspn(line, "\n")] = 0;
        for (i = 0; i < 16; i++)
        {
            line = NULL;
            lineSize = 0;
            getline(&line, &lineSize, flowFile);
            FLOWS[i] = atoi(line);
        }
        return 1;
    }
    printf("error when reading  flow database\n");
    return 0;
}

int writeFlowList(char *flowfilename)
{
    extern int FLOWS[];
    FILE *flowFile;
    flowFile = fopen(flowfilename, "w");
    if (flowFile == NULL)
    {
        printf("error when trying to open file %s \n ", flowfilename);
        return 0;
    }
    else
    {
        fprintf(flowfilename, "--- the flow here is the time needed in sec to empty one liter\n");
        int i;
        for (i = 0; i < 16; i++)
        {
            fprintf(flowFile, "%d\n", FLOWS[i]);
        }
        fclose(flowFile);
    }
    return 1;
}

int saveFlowList()
{
    extern int FLOWS[];
    extern int FLOWSCHANGED;
    if (FLOWSCHANGED)
    {
        char *temporaryName = "temporaryflow.txt";
        if (writeFlowList(temporaryName))
        {
            remove(FLOWFILE);
            rename(temporaryName, FLOWFILE);
            FLOWSCHANGED = 0;
            return 1;
        }
        else
        {
            printf("error when writing flows  in a new file \n");
            remove(temporaryName);
            return 0;
        }
    }
    return 1;
}

void readAllFlows()
{
    extern int FLOWS[];
    int i;
    for (i = 0; i < 16; i++)
    {
        printf("emplacement %d , flow = %d \n", i, FLOWS[i]);
    }
}

int editFlow(int servoAdress, int Flow)
{
    if (servoAdress < 16)
    {
        extern int FLOWS[];
        FLOWS[servoAdress] = Flow;
        return 1;
    }
    else
        return 0;
}

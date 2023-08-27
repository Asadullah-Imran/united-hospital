
#include <stdio.h>
#define N 50
int num,sum=0,a=0,counter=0,i,n,j;
struct patient
{
    char name[N], disease[N],phone[15],gender[8];
    int cabin,age,sl;
};

int option;
void menu();
void read();
void add();
void view();
void search();
void searchBySerial(FILE *fp, struct patient *info);
void searchByName(FILE *fp, struct patient *info);
void searchByAge(FILE *fp, struct patient *info);
void searchByGender(FILE *fp, struct patient *info);
void searchByPhone(FILE *fp, struct patient *info);
void printPatientInfo(struct patient *info);
void edit();
void del();
// main function start
int main()
{
    read();
    printf("\n\t\t\tUnited Hospital\n\n");
    menu();

while(1){
    switch(option){
case 1:
    system("cls");
    add();
    system("cls");
    menu();
    break;
case 2:
    system("cls");
    view();
    system("cls");
    menu();
    break;
case 3:
    system("cls");
    search();
    system("cls");
    menu();
    break;
case 4:
    system("cls");
    edit();
    getch();
    system("cls");
    menu();
    break;
case 5:
    system("cls");
    del();
    getch();
    system("cls");
    menu();
    break;
case 6:
    system("cls");
    printf("\n\n\t\t\tThank you :)\n");
     getch();
    exit(1);
    break;

default:
    system("cls");
    printf("\n\n\n\t\t\t try between 1 to 6\n");
    printf("\t\t\t________________________");    getch();
    menu();
    getch();
    }

    }

getch();
return 0;}

void read(){
    FILE *fp;
    struct patient info[100];
    fp=fopen("patient_info.txt","r");

    num = fread(&info, sizeof(struct patient),100, fp);
    fclose(fp);
}

void menu(){
    printf("\n\t\t\t\t**Enter your choice**\n\n\t\t1. Add Information\n\t\t2. View all Information\n\t\t3. Search Information\n\t\t4. Edit Information\n\t\t5. Delete Information\n\t\t6. Exit\n\n\t\tOption = ");
    scanf("%d",&option);

};

void add(){
    char another;
    FILE *fp;
    struct patient info[100];

    fp=fopen("patient_info.txt","a");
    printf("\n\tTotal Patients in the Database = %d\n\n",num);
    printf("\n\t\t**Add new patient**\n\n");
    printf("\n\tHow many entry do you want to add: ");
    scanf("%d",&n);
    sum=num+n;
    for(i=num;i<sum;i++){
        info[i].sl=i+1;
        fflush(stdin);
        printf("\n\tEnter patient's Name = ");
        gets(info[i].name);
        fflush(stdin);
        printf("\n\tEnter patient's disease = ");
        gets(info[i].disease);
        printf("\n\tEnter patient's Gender = ");
        fflush(stdin);
        gets(info[i].gender);
        printf("\n\tEnter patient's age = ");
        scanf("%d",&info[i].age);
        printf("\n\tEnter patient's cabin no = ");
        scanf("%d",&info[i].cabin);
        printf("\n\tEnter patient's phone number = ");
        fflush(stdin);
        gets(info[i].phone);
        printf("\n");
        num++;
        fwrite(&info[i],sizeof(struct patient),1,fp);

    }

    fclose(fp);
}

void view(){
    FILE *fp;
    struct patient info[100];
    fp=fopen("patient_info.txt","r");
    if(fp == NULL)
    {
        printf("\n\t\tCan't Open File\n\n");

    }
    printf("\n\tTotal Patients in the Database = %d\n\n",num);
     printf("\n\t\t**View patient record**\n");


    i=0;
    while(fread(&info,sizeof(struct patient),1,fp)){
        printf("\n\t__________________________________________\n");
        printf("\n\tSerial number:      %d",info[i].sl);
        printf("\n\tPatient's Name:     %s",info[i].name);
        printf("\n\tPatient's Disease:  %s",info[i].disease);
        printf("\n\tPatient's Gender:   %s",info[i].gender);
        printf("\n\tPatient's Age:      %d",info[i].age);
        printf("\n\tPatient's Cabin:    %d",info[i].cabin);
        printf("\n\tPatient's Phone no: %s",info[i].phone);

    }
    fclose(fp);
    getch();
}

void search() {
    FILE *fp;
    struct patient info[100];
    int searchOption, found = 0;

    fp = fopen("patient_info.txt", "r");
    if (fp == NULL) {
        printf("Can't Open File\n");
        return;
    }

    printf("\n\t\t\tPatient Search\n");
    printf("\tSearch by:\n");
    printf("\t1. Serial number\n");
    printf("\t2. Name\n");
    printf("\t3. Age\n");
    printf("\t4. Gender\n");
    printf("\t5. Phone number\n");
    printf("\tEnter your choice: ");
    scanf("%d", &searchOption);

    switch (searchOption) {
        case 1:
            printf("Enter serial number: ");
            searchBySerial(fp, info);
            break;
        case 2:
            printf("Enter name: ");
            searchByName(fp, info);
            break;
        case 3:
            printf("Enter disease: ");
            searchByDisease(fp, info);
            break;
        case 4:
            printf("Enter gender: ");
            searchByGender(fp, info);
            break;
        case 5:
            printf("Enter age: ");
            searchByAge(fp, info);
            break;
        case 6:
            printf("Enter cabin: ");
            searchByCabin(fp, info);
            break;
        case 7:
            printf("Enter phone number: ");
            searchByPhone(fp, info);
            break;
        default:
            printf("Invalid option\n");
    }

    fclose(fp);

    getch();
}

void searchBySerial(FILE *fp, struct patient *info) {
    int serial, found = 0;
    printf("Serial number: ");
    scanf("%d", &serial);

    while (fread(info, sizeof(struct patient), 1, fp)) {
        if (info->sl == serial) {
            printPatientInfo(info);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Record not found\n");
    }
}

void searchByName(FILE *fp, struct patient *info) {
    char searchName[N];
    int found = 0;
    fflush(stdin);
    gets(searchName);

    while (fread(info, sizeof(struct patient), 1, fp)) {
        if (strcmp(info->name, searchName) == 0) {
            printPatientInfo(info);
            found = 1;
        }
    }

    if (!found) {
        printf("Record not found\n");
    }
}

void searchByDisease(FILE *fp, struct patient *info) {
    char searchDisease[N];
    int found = 0;
    fflush(stdin);
    gets(searchDisease);

    while (fread(info, sizeof(struct patient), 1, fp)) {
        if (strcmp(info->disease, searchDisease) == 0) {
            printPatientInfo(info);
            found = 1;
        }
    }

    if (!found) {
        printf("Record not found\n");
    }
}

void searchByGender(FILE *fp, struct patient *info) {
    char searchGender[8];
    int found = 0;
    fflush(stdin);

    gets(searchGender);

    while (fread(info, sizeof(struct patient), 1, fp)) {
        if (strcmp(info->gender, searchGender) == 0) {
            printPatientInfo(info);
            found = 1;
        }
    }

    if (!found) {
        printf("Record not found\n");
    }
}

void searchByAge(FILE *fp, struct patient *info) {
    int searchAge, found = 0;
    scanf("%d", &searchAge);

    while (fread(info, sizeof(struct patient), 1, fp)) {
        if (info->age == searchAge) {
            printPatientInfo(info);
            found = 1;
        }
    }

    if (!found) {
        printf("Record not found\n");
    }
}

void searchByCabin(FILE *fp, struct patient *info) {
    int searchCabin, found = 0;
    scanf("%d", &searchCabin);

    while (fread(info, sizeof(struct patient), 1, fp)) {
        if (info->cabin == searchCabin) {
            printPatientInfo(info);
            found = 1;
        }
    }

    if (!found) {
        printf("Record not found\n");
    }
}

void searchByPhone(FILE *fp, struct patient *info) {
    char searchPhone[15];
    int found = 0;
    fflush(stdin);
    gets(searchPhone);

    while (fread(info, sizeof(struct patient), 1, fp)) {
        if (strcmp(info->phone, searchPhone) == 0) {
            printPatientInfo(info);
            found = 1;
        }
    }

    if (!found) {
        printf("Record not found\n");
    }
}

void printPatientInfo(struct patient *info) {
    printf("Serial number:      %d\n", info->sl);
    printf("Patient's Name:     %s\n", info->name);
    printf("Patient's Disease:  %s\n", info->disease);
    printf("Patient's Gender:   %s\n", info->gender);
    printf("Patient's Age:      %d\n", info->age);
    printf("Patient's Cabin:    %d\n", info->cabin);
    printf("Patient's Phone no: %s\n", info->phone);
    printf("__________________________________________\n");
}


void del() {
    FILE *fp;
    struct patient info[100];
    int serial, found = 0;
    fp = fopen("patient_info.txt", "r");

    if (fp == NULL) {
        printf("Can't Open File\n");
        return;
    }


    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(fp);
        return;
    }

    printf("\n\t\t\tpatient search\n");
    printf("serial no: ");
    scanf("%d", &serial);

    int i = 0;
    while (fread(&info[i], sizeof(struct patient), 1, fp)) {
        if (info[i].sl == serial) {
            found = 1;
            num--;
        } else {
            fwrite(&info[i], sizeof(struct patient), 1, tempFile);
        }
        i++;

    }

    fclose(fp);
    fclose(tempFile);

    if (found) {
        system("cls");
        remove("patient_info.txt");
        rename("temp.txt", "patient_info.txt");
        printf("\n\n\t\tRecord deleted successfully.\n");



        FILE *updatedFile = fopen("patient_info.txt", "r");
        if (updatedFile == NULL) {
            printf("Can't Open File\n");
            return;
        }

        FILE *tempUpdateFile = fopen("temp_update.txt", "w");
        if (tempUpdateFile == NULL) {
            printf("Error creating temporary file.\n");
            fclose(updatedFile);
            return;
        }

        i = 0;
        while (fread(&info[i], sizeof(struct patient), 1, updatedFile)) {
            info[i].sl = i + 1; // Update serial number
            fwrite(&info[i], sizeof(struct patient), 1, tempUpdateFile);
            i++;
        }

        fclose(updatedFile);
        fclose(tempUpdateFile);

        remove("patient_info.txt");
        rename("temp_update.txt", "patient_info.txt");

    } else {
        system("cls");
        printf("\n\n\t\tRecord not found.\n");
    }


}


void edit() {
    FILE *fp;
    struct patient info[100];
    int serialNumber, found = 0;
    fp = fopen("patient_info.txt", "r+");

    if (fp == NULL) {
        printf("Can't Open File\n");
        return;
    }

    printf("\n\n\t\t\tEdit Patient Information\n");
    printf("\n\tEnter serial number to edit: ");
    scanf("%d", &serialNumber);

    int i = 0;
    while (fread(&info[i], sizeof(struct patient), 1, fp)) {
        if (info[i].sl == serialNumber) {
            found = 1;
        printf("\n\tPatient %d's information:\n", serialNumber);
        printf("\n\tPatient's Name:     %s",info[i].name);
        printf("\n\tPatient's Disease:  %s",info[i].disease);
        printf("\n\tPatient's Gender:   %s",info[i].gender);
        printf("\n\tPatient's Age:      %d",info[i].age);
        printf("\n\tPatient's Cabin:    %d",info[i].cabin);
        printf("\n\tPatient's Phone no: %s",info[i].phone);
        printf("\n\t_____________________________________");

            int editOption;
            printf("\n\n\n\tSelect field to edit %d's information:",serialNumber);
            printf("\n\t1. Name\n\t2. Disease\n\t3. Gender\n\t4. Age\n\t5. Cabin\n\t6. Phone\n");
            printf("\n\tChoose any field to edit:");
            scanf("%d", &editOption);

            switch (editOption) {
                case 1:
                    fflush(stdin);
                    printf("\n\tEnter new Name = ");
                    gets(info[i].name);
                    break;
                case 2:
                    fflush(stdin);
                    printf("\n\tEnter new Disease: ");
                    gets(info[i].disease);
                    break;
                case 3:
                    fflush(stdin);
                    printf("\n\tEnter new Gender: ");
                    gets(info[i].gender);
                    break;
                case 4:
                    printf("\n\tEnter new Age: ");
                    scanf("%d", &info[i].age);
                    break;

                case 5:
                    printf("\n\tEnter new Cabin number: ");
                    scanf("%d", &info[i].cabin);
                    break;

                case 6:
                    fflush(stdin);
                    printf("\n\tEnter new Phone number: ");
                    gets(info[i].phone);
                    break;
                default:
                    system("cls");
                    printf("\n\n\t\tInvalid option.\n");

                    fclose(fp);
                    return;
            }

            fseek(fp, i * sizeof(struct patient), SEEK_SET);
            fwrite(&info[i], sizeof(struct patient), 1, fp);
            break;
        }
        i++;
    }

    fclose(fp);
    system("cls");
    if (found) {
        printf("\n\n\t\tRecord edited successfully.\n");
    } else {
        printf("\n\n\t\tRecord not found.\n");
    }
}


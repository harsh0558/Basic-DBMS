#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_COLUMNS 10
#define MAX_ROWS 100
#define MAX_STRING_LENGTH 128
#define MAX_LINE_LENGTH 512


char columnNames[MAX_COLUMNS][MAX_STRING_LENGTH];
char data[MAX_ROWS][MAX_COLUMNS][MAX_STRING_LENGTH];


int columnCount = 0;
int rowCount = 0;
int unsavedChanges = 0;

int readCSVFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file %s\n", filename);
        return -1;
    }

    char line[MAX_LINE_LENGTH];


    if (fgets(line, MAX_LINE_LENGTH, file)) {
        char *token = strtok(line, ",\n");
        while (token != NULL && columnCount < MAX_COLUMNS) {
            strncpy(columnNames[columnCount], token, MAX_STRING_LENGTH);
            columnCount++;
            token = strtok(NULL, ",\n");
        }
    }

    
    while (fgets(line, MAX_LINE_LENGTH, file) && rowCount < MAX_ROWS) {
        char *token = strtok(line, ",\n");
        for (int i = 0; i < columnCount && token != NULL; i++) {
            strncpy(data[rowCount][i], token, MAX_STRING_LENGTH);
            token = strtok(NULL, ",\n");
        }
        rowCount++;
    }

    fclose(file);
    return 0;
}


int saveCSVToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Could not open file %s\n", filename);
        return -1;
    }

    
    for (int i = 0; i < columnCount; i++) {
        fprintf(file, "%s", columnNames[i]);
        if (i < columnCount - 1) {
            fprintf(file, ",");
        }
    }
    fprintf(file, "\n");

    
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < columnCount; j++) {
            fprintf(file, "%s", data[i][j]);
            if (j < columnCount - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
    unsavedChanges = 0; 
    printf("Data saved successfully.\n");
    return 0;
}


void printCSVData() {
    
    for (int i = 0; i < columnCount; i++) {
        printf("%-20s", columnNames[i]);
    }
    printf("\n");

    
    for (int i = 0; i < columnCount; i++) {
        printf("--------------------");
    }
    printf("\n");

    
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < columnCount; j++) {
            printf("%-20s", data[i][j]);
        }
        printf("\n");
    }
}


void updateRecord() {
    char columnName[MAX_STRING_LENGTH];
    int columnIndex = -1, rowIndex;
    char newValue[MAX_STRING_LENGTH];

    
    printf("Enter the column name to update: ");
    fgets(columnName, MAX_STRING_LENGTH, stdin);
    columnName[strcspn(columnName, "\n")] = '\0';

    
    for (int i = 0; i < columnCount; i++) {
        if (strcmp(columnNames[i], columnName) == 0) {
            columnIndex = i;
            break;
        }
    }
    if (columnIndex == -1) {
        printf("Column not found.\n");
        return;
    }

    
    printf("Enter the row number to update (1 to %d): ", rowCount);
    scanf("%d", &rowIndex);
    getchar(); 

    if (rowIndex < 1 || rowIndex > rowCount) {
        printf("Invalid row number.\n");
        return;
    }

    
    printf("Enter the new value: ");
    fgets(newValue, MAX_STRING_LENGTH, stdin);
    newValue[strcspn(newValue, "\n")] = '\0';

    
    strncpy(data[rowIndex - 1][columnIndex], newValue, MAX_STRING_LENGTH);
    unsavedChanges = 1; 
    printf("Record updated successfully.\n");
    printCSVData();
}


void addRecord() {
    if (rowCount >= MAX_ROWS) {
        printf("Cannot add more rows. Maximum limit reached.\n");
        return;
    }

    printf("Enter the values for the new record:\n");
    for (int i = 0; i < columnCount; i++) {
        printf("Enter value for '%s': ", columnNames[i]);
        fgets(data[rowCount][i], MAX_STRING_LENGTH, stdin);
        data[rowCount][i][strcspn(data[rowCount][i], "\n")] = '\0';
    }

    rowCount++;
    unsavedChanges = 1; 
    printf("New record added successfully.\n");
    printCSVData();
}

void deleteRecord() {
    int recordID;

    printf("Enter the record number to delete (1 to %d): ", rowCount);
    scanf("%d", &recordID);
    getchar(); 

    if (recordID < 1 || recordID > rowCount) {
        printf("Invalid record number.\n");
        return;
    }

    
    for (int i = recordID - 1; i < rowCount - 1; i++) {
        for (int j = 0; j < columnCount; j++) {
            strncpy(data[i][j], data[i + 1][j], MAX_STRING_LENGTH);
        }
    }
    rowCount--;
    unsavedChanges = 1;
    printf("Record deleted successfully.\n");
    printCSVData();
}


void sortDataByColumn() {
    char columnName[MAX_STRING_LENGTH];
    int columnIndex = -1;

    printf("Enter the column name to sort by: ");
    fgets(columnName, MAX_STRING_LENGTH, stdin);
    columnName[strcspn(columnName, "\n")] = '\0';


    for (int i = 0; i < columnCount; i++) {
        if (strcmp(columnNames[i], columnName) == 0) {
            columnIndex = i;
            break;
        }
    }
    if (columnIndex == -1) {
        printf("Column not found.\n");
        return;
    }

    
    char sortOrder;
    printf("Enter 'A' for ascending or 'D' for descending order: ");
    scanf(" %c", &sortOrder);
    getchar(); 
    
    
    for (int i = 0; i < rowCount - 1; i++) {
        for (int j = i + 1; j < rowCount; j++) {
            int comparison = strcmp(data[i][columnIndex], data[j][columnIndex]);
            if ((sortOrder == 'A' || sortOrder == 'a') ? (comparison > 0) : (comparison < 0)) {
                
                for (int k = 0; k < columnCount; k++) {
                    char temp[MAX_STRING_LENGTH];
                    strncpy(temp, data[i][k], MAX_STRING_LENGTH);
                    strncpy(data[i][k], data[j][k], MAX_STRING_LENGTH);
                    strncpy(data[j][k], temp, MAX_STRING_LENGTH);
                }
            }
        }
    }

    unsavedChanges = 1; 
    printf("Data sorted by column '%s' in %s order.\n", columnName,
           (sortOrder == 'A' || sortOrder == 'a') ? "ascending" : "descending");
    printCSVData();
}


void searchData() {
    char columnName[MAX_STRING_LENGTH], searchValue[MAX_STRING_LENGTH];
    int columnIndex = -1;

    
    printf("Enter the column name to search in: ");
    fgets(columnName, MAX_STRING_LENGTH, stdin);
    columnName[strcspn(columnName, "\n")] = '\0';

    
    for (int i = 0; i < columnCount; i++) {
        if (strcmp(columnNames[i], columnName) == 0) {
            columnIndex = i;
            break;
        }
    }
    if (columnIndex == -1) {
        printf("Column not found.\n");
        return;
    }


    printf("Enter the value to search for: ");
    fgets(searchValue, MAX_STRING_LENGTH, stdin);
    searchValue[strcspn(searchValue, "\n")] = '\0';

    
    printf("Matching records:\n");
    for (int i = 0; i < columnCount; i++) {
        printf("%-20s", columnNames[i]);
    }
    printf("\n");

    for (int i = 0; i < columnCount; i++) {
        printf("--------------------");
    }
    printf("\n");

    for (int i = 0; i < rowCount; i++) {
        if (strcmp(data[i][columnIndex], searchValue) == 0) {
            for (int j = 0; j < columnCount; j++) {
                printf("%-20s", data[i][j]);
            }
            printf("\n");
        }
    }
}


int main() {
    char filename[MAX_STRING_LENGTH];
    int choice;

    printf("Enter the name of the CSV file: ");
    fgets(filename, MAX_STRING_LENGTH, stdin);
    filename[strcspn(filename, "\n")] = '\0';

    if (readCSVFromFile(filename) != 0) {
        return 1;
    }

    printf("File loaded successfully.\n");
    printCSVData();

    do {
        printf("\nMenu:\n");
        printf("1. Add a record\n");
        printf("2. Update a record\n");
        printf("3. Delete a record\n");
        printf("4. Sort data by column\n");
        printf("5. Search data\n");
        printf("6. Save data\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                updateRecord();
                break;
            case 3:
                deleteRecord();
                break;
            case 4:
                sortDataByColumn();
                break;
            case 5:
                searchData();
                break;
            case 6:
                saveCSVToFile(filename);
                break;
            case 7:
                if (unsavedChanges) {
                    char saveChoice;
                    printf("You have unsaved changes. Do you want to save them before exiting? (Y/N): ");
                    scanf(" %c", &saveChoice);
                    if (saveChoice == 'Y' || saveChoice == 'y') {
                        saveCSVToFile(filename);
                    }
                }
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 7);

    return 0;
}

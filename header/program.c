#include "./program.h"

const char *filename = "./files/orders.dat";

FILE *openFile(){
    FILE *fptr;

    if((fptr =  fopen(filename, "rb+")) == NULL) {
        fptr = fopen(filename, "wb+");
    } else {
        fclose(fptr);
        fptr = fopen(filename, "rb+");
    }

    system("cls");

    return fptr;
}

List getList(FILE* fptr){
    List head = NULL;
    List *curr = &head;
    Order temp;

    rewind(fptr);

    while(fread(&temp, sizeof(Order), 1, fptr) != 0){
        (*curr) = (List)malloc(sizeof(struct node));
        if(*curr != NULL){
            (*curr)->order = temp;
            curr = &(*curr)->next;
        }
    }

    (*curr) = NULL;

    return head;
}

Option landingScreen(){
    int num;
    Option option;

    printf("Welcome to Rale.co Clothing Merchandise\n");
    printf("[1] Read Order/s\n");
    printf("[2] Add Order\n");
    printf("[3] Edit Order\n");
    printf("[4] Delete Order\n");
    printf("[?] Save & Exit\n");
    printf("Enter Option Number: ");
    flush;
    scanf("%d", &num);

    switch(num){
        case 1: option = READ; break;
        case 2: option = ADD; break;
        case 3: option = EDIT; break;
        case 4: option = DELETE; break;
        default: option = CLOSE; break;
    }
    return option;
}

void doOption(Option option, List* head, FILE** file){
    switch(option){
        case READ: displayOrder(*head); break;
        case ADD: addOrder(head); break;
        case EDIT: editOrder(*head); break;
        case DELETE: deleteOrder(head); break;
    }
}

void displayOrder(List head){
    system("cls");
    if(head != NULL){
        printf("%-5s%-20s%-40s%-15s%-10s%-15s%-10s%-20s\n","ID", "Customer", "Email", "Design", "Color", "Size", "Qty", "Status");

        for(int i = 0; i < 135; i++) {
            printf("-");
        }
        printf("\n");

        for(List curr = head; curr != NULL; curr = curr->next){
            char design[20], color[20], size[15], status[20] = "";
            switch(curr->order.design){
                case RANDOM: strcpy(design, "Random"); break;
                case RESIST: strcpy(design, "Resist"); break;
                case DEVOTION: strcpy(design, "Devotion"); break;
                case PANTONE: strcpy(design, "Pantone"); break;
                case HAPPYH: strcpy(design, "Happy Human"); break;
                case EXEMPLIFY: strcpy(design, "Exemplify"); break;
                case TEACHP: strcpy(design, "Teach Peace"); break;
                case DQUIT: strcpy(design, "Don't Quit"); break;
                case SINULOG: strcpy(design, "Sinulog"); break;
            }

            switch(curr->order.color){
                case RANDOMIZE: strcpy(color, "Randomized"); break;
                case WHITE: strcpy(color, "White"); break;
                case BLACK: strcpy(color, "Black"); break;
                case PURPLE: strcpy(color, "Purple"); break;
                case GREEN: strcpy(color, "Green"); break;
                case RED: strcpy(color, "Red"); break;
                case BLUE: strcpy(color, "Blue"); break;
            }

            switch(curr->order.size){
                case Small: strcpy(size, "Small"); break;
                case Medium: strcpy(size, "Medium"); break;
                case Large: strcpy(size, "Large"); break;
                case XLarge: strcpy(size, "X-Large"); break;
                case XXLarge: strcpy(size, "XX-Large"); break;
                case XXXLarge: strcpy(size, "XXX-Large"); break;
            }

            switch(curr->order.status){
                case UNFINISHED: strcpy(status, "Deciding"); break;
                case PENDING: strcpy(status, "In the making"); break;
                case DONE: strcpy(status, "Done"); break;
                case OTW: strcpy(status, "On the way"); break;
                case DELIVERED: strcpy(status, "Delivered"); break;
            }

            printf("%-5d%-20s%-40s%-15s%-10s%-15s%-10d%-20s\n",curr->order.cust_id,curr->order.cust.Name, curr->order.email, design, color, size, curr->order.quantity, status);
        }
        printf("\n");
        for(int i = 0; i < 135; i++) {
            printf("-");
        }
    }else{
        printf("There are orders  in the List. Order Rale merch now!\n");
    }
    
    printf("\n\n");
}

int isGmail(char *email) {
    char *check = "@gmail.com";
    return strstr(email, check) != NULL;
}

void capital(char* Name){
    Name[0] = toupper(Name[0]);
    for(int i = 1; Name[i] != '\0'; i++) {
        if(isspace(Name[i - 1])) {
            Name[i] = toupper(Name[i]);
        } else {
            Name[i] = tolower(Name[i]);
        }
    }
}

Order createOrder(List* head){
    int count;
    List* trav;
    for(trav = head; *trav !=NULL && (*trav)->next !=NULL;trav = &(*trav)->next){}
    if(*trav == NULL){
        count = 1;
    }else{
        count = (*trav)->order.cust_id + 1;
    }

    Order temp = {count,{"XXXX","XXXX","XXXX"},"XXXX@gmail.com",RANDOM,RANDOMIZE,Large,-1,UNFINISHED};

    // User input name
    char Fname[24];
    char Lname[16];
    int length;

    system("cls");
    do{
        printf("Enter First Name: ");
        flush;
        scanf("%[^\n]", Fname);
        printf("Enter Last Name: ");
        flush;
        scanf("%[^\n]", Lname);
        length = strlen(Fname);
        if(length >= 26){
            printf("Name exceeds maximum of %d letters.\n", 26 - 1);
        }
    } while (length >= 26);

    capital(Fname); capital(Lname);
    strcpy(temp.cust.Fname, Fname);
    strcpy(temp.cust.Lname, Lname);
    strcpy(temp.cust.Name, Fname);
    strcat(temp.cust.Name, " ");   // Add a space between the names
    strcat(temp.cust.Name, Lname); // Concatenate Lname to Name

    system("cls");

    char email[50];
    do {
        printf("Email Address: ");
        flush;
        scanf("%[^\n]", email);
        if (!isGmail(email)) {
            printf("Please enter a valid Gmail address ending with '@gmail.com'\n");
        }
    } while (!isGmail(email));
    strcpy(temp.email, email);

    system("cls");

    int design = 0;
    printf("What would be the design?\n");
    printf("[1] Resist\n");
    printf("[2] Devotion\n");
    printf("[3] Pantone\n");
    printf("[4] Happy Human\n");
    printf("[5] Exemplify\n");
    printf("[6] Teach Peace\n");
    printf("[7] Don't Quit\n");
    printf("[8] Sinulog\n");
    printf("[?] Random\n");
    printf("Design Number: \n");
    flush;
    scanf("%d", &design);

    switch(design){
        case 1: temp.design = RESIST; break;
        case 2: temp.design = DEVOTION; break;
        case 3: temp.design = PANTONE; break;
        case 4: temp.design = HAPPYH; break;
        case 5: temp.design = EXEMPLIFY; break;
        case 6: temp.design = TEACHP; break;
        case 7: temp.design = DQUIT; break;
        case 8: temp.design = SINULOG; break;
        default: temp.design = RANDOM;
    }
    system("cls");

    int color = 0;
    printf("And the color of your T-Shirt?\n");
    printf("[1] White\n");
    printf("[2] Black\n");
    printf("[3] Purple\n");
    printf("[4] Green\n");
    printf("[5] Red\n");
    printf("[6] Blue\n");
    printf("[?] Random\n");
    printf("Color Number: \n");
    flush;
    scanf("%d", &color);

    switch(color){
        case 1: temp.color = WHITE; break;
        case 2: temp.color = BLACK; break;
        case 3: temp.color = PURPLE; break;
        case 4: temp.color = GREEN; break;
        case 5: temp.color = RED; break;
        case 6: temp.color = BLUE; break;
        default: temp.color = RANDOMIZE;
    }
    system("cls");

    int size = 0;
    printf("The size?\n");
    printf("[1] Small\n");
    printf("[2] Medium\n");
    printf("[3] Large\n");
    printf("[4] X-Large\n");
    printf("[5] 2X-Large\n");
    printf("[6] 3X-Large\n");
    printf("[?] Random\n");
    printf("Size Number: \n");
    flush;
    scanf("%d", &size);

    switch(size){
        case 1: temp.size = Small; break;
        case 2: temp.size = Medium; break;
        case 3: temp.size = Large; break;
        case 4: temp.size = XLarge; break;
        case 5: temp.size = XXLarge; break;
        case 6: temp.size = XXXLarge; break;
        default: temp.size = Large;
    }
    system("cls");
    int quantity = 1;
    printf("How many of this order do you want?: ");
    flush;
    scanf("%d", &quantity);
    temp.quantity = quantity;
    system("cls");
    return temp;
}

void addOrder(List* head){
    Order new_order = createOrder(head); 
    

    List* trav;
    for(trav = head;*trav != NULL;trav=&(*trav)->next){}
    *trav= (List)malloc(sizeof(struct node));
    if(*trav != NULL) {
        (*trav)->order = new_order;
        (*trav)->next = NULL;
    } else {
        printf("Memory allocation failed. Unable to add new order.\n");
    }
}

List tobeEdited(List head, int id){
    List trav;
    for(trav = head; trav != NULL && trav->order.cust_id != id;trav= trav->next){}
    return trav;
}

void editOrder(List head){
    int id;
    List edit;

    system("cls");
    displayOrder(head);
    printf("Whose order do you want to edit?\n");
    printf("(Enter customer ID): ");
    flush;
    scanf("%d", &id);

    edit = tobeEdited(head,id);
    if(edit == NULL){
        printf("Couldn't find order with that id.\n\n");
    }else{
        char con = 'y';
        while(con == 'y'){
            int option;
            system("cls");
            printf("Enter area to edit:\n\n");
            printf("[1] Name\n");
            printf("[2] Email\n");
            printf("[3] Design\n");
            printf("[4] Color\n");
            printf("[5] Size\n");
            printf("[6] Quantity\n");
            printf("[7] Status\n");

            printf("Choice: ");
            flush;
            scanf("%d",&option);

            switch(option){
                case 1: editName(edit);break;
                case 2: editEmail(edit);break;
                case 3: editDesign(edit);break;
                case 4: editColor(edit);break;
                case 5: editSize(edit);break;
                case 6: editQuantity(edit);break;
                case 7: editStatus(edit);break;
            }
            printf("Do you want to contiue editing this customer?[Y/N]: ");
            flush;
            scanf("%c",&con);
            if(con == 'Y'){
                con = 'y';
            }
        }
        
    }
    system("cls");
}

void editName(List edit){
    char Fname[24];
    char Lname[16];
    int length;

    system("cls");
    do{
        printf("Enter NEW First Name: ");
        flush;
        scanf("%[^\n]", Fname);
        printf("Enter NEW Last Name: ");
        flush;
        scanf("%[^\n]", Lname);
        length = strlen(Fname);
        if(length >= 26){
            printf("Name exceeds maximum of %d letters.\n", 26 - 1);
        }
    } while (length >= 26);

    capital(Fname); capital(Lname);
    strcpy(edit->order.cust.Fname, Fname);
    strcpy(edit->order.cust.Lname, Lname);
    strcpy(edit->order.cust.Name, Fname);
    strcat(edit->order.cust.Name, " ");   // Add a space between the names
    strcat(edit->order.cust.Name, Lname); // Concatenate Lname to Name
    system("cls");
}

void editEmail(List edit){
    char email[50];
    system("cls");
    do {
        printf("NEW Email Address: ");
        flush;
        scanf("%[^\n]", email);
        if (!isGmail(email)){
            printf("Please enter a valid Gmail address ending with '@gmail.com'\n");
        }
    } while (!isGmail(email));
    strcpy(edit->order.email, email);
    system("cls");
}

void editDesign(List edit){
    int design = 0;
    system("cls");
    printf("What would be the NEW design?\n");
    printf("[1] Resist\n");
    printf("[2] Devotion\n");
    printf("[3] Pantone\n");
    printf("[4] Happy Human\n");
    printf("[5] Exemplify\n");
    printf("[6] Teach Peace\n");
    printf("[7] Don't Quit\n");
    printf("[8] Sinulog\n");
    printf("[?] Random\n");
    printf("Design Number: \n");
    flush;
    scanf("%d", &design);

    switch(design){
        case 1: edit->order.design = RESIST; break;
        case 2: edit->order.design = DEVOTION; break;
        case 3: edit->order.design = PANTONE; break;
        case 4: edit->order.design = HAPPYH; break;
        case 5: edit->order.design = EXEMPLIFY; break;
        case 6: edit->order.design = TEACHP; break;
        case 7: edit->order.design = DQUIT; break;
        case 8: edit->order.design = SINULOG; break;
        default: edit->order.design = RANDOM;
    }
    system("cls");

}

void editColor(List edit){
    int color = 0;
    system("cls");
    printf("The NEW color of your T-Shirt?\n");
    printf("[1] White\n");
    printf("[2] Black\n");
    printf("[3] Purple\n");
    printf("[4] Green\n");
    printf("[5] Red\n");
    printf("[6] Blue\n");
    printf("[?] Random\n");
    printf("Color Number: \n");
    flush;
    scanf("%d", &color);

    switch(color){
        case 1: edit->order.color = WHITE; break;
        case 2: edit->order.color = BLACK; break;
        case 3: edit->order.color = PURPLE; break;
        case 4: edit->order.color = GREEN; break;
        case 5: edit->order.color = RED; break;
        case 6: edit->order.color = BLUE; break;
        default: edit->order.color = RANDOMIZE;
    }
    system("cls");
}

void editSize(List edit){
    system("cls");

    int size = 0;
    printf("The NEW size?\n");
    printf("[1] Small\n");
    printf("[2] Medium\n");
    printf("[3] Large\n");
    printf("[4] X-Large\n");
    printf("[5] 2X-Large\n");
    printf("[6] 3X-Large\n");
    printf("[?] Random\n");
    printf("Size Number: \n");
    flush;
    scanf("%d", &size);

    switch(size){
        case 1: edit->order.size = Small; break;
        case 2: edit->order.size = Medium; break;
        case 3: edit->order.size = Large; break;
        case 4: edit->order.size = XLarge; break;
        case 5: edit->order.size = XXLarge; break;
        case 6: edit->order.size = XXXLarge; break;
        default: edit->order.size = Large;
    }
    system("cls");
}

void editQuantity(List edit){
    system("cls");
    int quantity = 1;
    printf("How many of this order do you want?: ");
    flush;
    scanf("%d", &quantity);
    edit->order.quantity = quantity;
    system("cls");
}

void editStatus(List edit){
    system("cls");
    int option;
    printf("What would you like to change the status to?\n");
    printf("[1] Deciding\n");
    printf("[2] In the making\n");
    printf("[3] Done\n");
    printf("[4] On the way\n");
    printf("[5] Delivered\n");
    printf("Option: ");
    scanf("%d", &option);

    

    switch(option) {
        case 1: edit->order.status = UNFINISHED; break;
        case 2: edit->order.status = PENDING; break;
        case 3: edit->order.status = DONE; break;
        case 4: edit->order.status = OTW; break;
        case 5: edit->order.status = DELIVERED; break;
    }
    system("cls");
}

void deleteOrder(List* head){
    int id;
    int delete = 0;

    system("cls");
    displayOrder(*head);
    printf("Whose order do you want to delete?\n");
    printf("(Enter customer ID): ");
    flush;
    scanf("%d", &id);
    
    if(*head != NULL){
        List* trav = head;
        while(*trav != NULL){
            if((*trav)->order.cust_id == id){
                List temp = *trav;
                *trav = (*trav)->next;
                free(temp);
                delete = 1;
            } else {
                trav = &(*trav)->next;
            }
        }
    }

    if(delete == 1){
        printf("Deleted.\n\n");
    } else {
        printf("Could not find order in the list.\n\n");
    }
}

void freeAll(List head){
    while(head !=NULL){
        List temp = head;
        head = head->next;
        free(temp);
    }
}

void save(FILE** file, List head){
    FILE* newFile = fopen("./files/temp.dat", "wb+");

    while(head != NULL){
        fwrite(&(head)->order,sizeof(Order),1,newFile);
        head = head->next;
    }

    fclose(newFile); 
    fclose(*file);

    remove(filename);
    rename("./files/temp.dat", filename);
}
char* toCSV(Order order, char* container){
    system("cls");
    char design[20], color[20], size[15], status[20] = "";
    switch(order.design){
        case RANDOM: strcpy(design, "Random"); break;
        case RESIST: strcpy(design, "Resist"); break;
        case DEVOTION: strcpy(design, "Devotion"); break;
        case PANTONE: strcpy(design, "Pantone"); break;
        case HAPPYH: strcpy(design, "Happy Human"); break;
        case EXEMPLIFY: strcpy(design, "Exemplify"); break;
        case TEACHP: strcpy(design, "Teach Peace"); break;
        case DQUIT: strcpy(design, "Don't Quit"); break;
        case SINULOG: strcpy(design, "Sinulog"); break;
    }

    switch(order.color){
        case RANDOMIZE: strcpy(color, "Randomized"); break;
        case WHITE: strcpy(color, "White"); break;
        case BLACK: strcpy(color, "Black"); break;
        case PURPLE: strcpy(color, "Purple"); break;
        case GREEN: strcpy(color, "Green"); break;
        case RED: strcpy(color, "Red"); break;
        case BLUE: strcpy(color, "Blue"); break;
    }

    switch(order.size){
        case Small: strcpy(size, "Small"); break;
        case Medium: strcpy(size, "Medium"); break;
        case Large: strcpy(size, "Large"); break;
        case XLarge: strcpy(size, "X-Large"); break;
        case XXLarge: strcpy(size, "XX-Large"); break;
        case XXXLarge: strcpy(size, "XXX-Large"); break;
    }

    switch(order.status){
        case UNFINISHED: strcpy(status, "Deciding"); break;
        case PENDING: strcpy(status, "In the making"); break;
        case DONE: strcpy(status, "Done"); break;
        case OTW: strcpy(status, "On the way"); break;
        case DELIVERED: strcpy(status, "Delivered"); break;
    }
        /*Since it is a CSV file, the format specifiers should be
        comma-seperated*/
    sprintf(container,"%d,%s,%s,%s,%s,%s,%d,%s\n",order.cust_id,order.cust.Name, order.email, design, color, size, order.quantity, status);
        
    
    return container;
}

void savetoCSV(List head,const char* filename){
    FILE* fptr = fopen(filename, "w");
    if(fptr == NULL){
        printf("Failed to open file\n\n");
        return;
    }

    /*Note to self: when dealing with csv file remember to use comma in seperating
        values like ID,Customer and etc. Because it will go crazy when you open the 
        csv file in excel*/

    // Write CSV header
    fprintf(fptr, "ID,Customer,Email,Design,Color,Size,Qty,Status\n");

    char container[256];
    List curr = head;
    while(curr != NULL){
        fprintf(fptr,"%s",toCSV(curr->order,container));
        curr = curr->next;
    }

    fclose(fptr);
}

void end(FILE *fptr, List head) {
    freeAll(head);
    fclose(fptr);

    system("cls");
    printf("Thank you for using project Rale.co!!!\n\n");
    printf("This is an inspirational idea of Todo-List program.\n\n");
    printf("NOTE: you can open the \"orders.csv\" file in excel.\n\n");
    printf("\u00A9 Paul France M. Detablan\n\n");
}
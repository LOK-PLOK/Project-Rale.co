#include "./header/prjrale.h"

int main(){
    FILE *file = openFile();
    List head = getList(file);

    Option option = landingScreen();
    printf("%d",option);
    while(option != CLOSE){
        doOption(option,&head,&file);
        option = landingScreen();
    }
    save(&file,head);
    end(file, head);
    return 0; 
}
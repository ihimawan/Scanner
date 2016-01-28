//
//  main.c
//  LAB5
//
//  Created by Indri Himawan on 10/2/2015

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <array>
#include <cstring>

using namespace std;

void scan(char character);
void scanner(char character);
void thisIsId(char character);
void thisIsNum();
void thisIsNumWithPoint();
void thisIsComment();
void isRead();
void isWrite();
void fill(string outputs);

// struct output{
//     string data;
//     struct output *next;
// };

// typedef struct output node;

// node *head;
// node *tail;

string output[100];
int i = 0;
bool flag = true;

FILE *fp;

int main(int argc, const char * argv[]){
    
    if (argc != 2){
        cout << "Please enter a valid command with a file input.";
        return 0;
    }
    
    if ((fp = fopen(argv[1], "r")) == NULL) {
        cout << "File cannot be opened.";
        return 0;
    }else{
        cout << "File open successful.\n\n";
    }
    
    char startchar = fgetc(fp);
    scanner(startchar);
    
    
    
    fclose(fp);
    
}

void scanner(char character){
    
    // head=NULL;
    
    scan(character);
    
    
    if (flag) {
        
        // node *current;
        
        cout << "(";
        
        // for (current=head; current!=0; current=current->next) {
        //     cout << current->data;
        //     if ((current->next)!=0) {
        //         cout << ", ";
        //     }
        // }
        
        for (int j=0; j<i; j++){
            cout << output[j];
            
            if ((j+1)<i){
                cout << ",";
            }
        }
        
        cout << ")";
        
        
        
    }else{
        cout << "error.";
    }
}

void scan(char character){
    
    while (character!=EOF && flag){
        
        while (character==' ' || character == '\n') { //ignores new lines and spaces and tabs
            character=fgetc(fp);
        }
        
        if(character==EOF)
            return;
        
        if (character == 'r'){ //recognize "read"
            isRead();
        }
        
        else if (character == 'w') { //recognize "write"
            isWrite();
        }
        
        else if (('a'<=character && character<='z') || ('A'<=character && character<='Z')) { //if starts with letter
            thisIsId(character); //then this is an ID
        }
        
        else if (character == '.' || ('0'<= character && character <= '9')){ //if starts with . or 0-9
            if (character == '.') {
                char nextchar = fgetc(fp);
                if ('0' <= nextchar && nextchar <= '9') {
                    thisIsNumWithPoint();
                }else{
                    flag=0;
                }
            }else{
                thisIsNum(); //then this is a number
            }
        }
        
        else if (character == '('){
            fill("lparen");
        }
        
        else if (character == ')'){
            fill("rparen");
        }
        
        else if (character == '+'){
            fill ("plus");
        }
        
        else if (character == '-'){
            fill ("minus");
        }
        
        else if (character == '*'){
            fill ("times");
        }
        
        else if (character == ':'){ //if there is a ':', then the next one must be a '='
            char nextchar=fgetc(fp);
            if (nextchar == '=') {
                fill ("assign");
                
            }else{
                flag=0;
            }
        }
        
        else if (character == '/') {
            char nextchar = fgetc(fp);
            if (nextchar == '*'){
                thisIsComment();
            }else if(nextchar == '/'){
                while (nextchar!='\n') {
                    if (nextchar == EOF) {
                        flag = 0;
                        return;
                    }
                    nextchar=fgetc(fp);
                    
                }
            }else{
                fill("div");
                character=nextchar;
                continue;
            }
            
            
        }else{
            flag=0;
            //character=fgetc(fp); // <<<------DELETETHIS
        }
        
        character=fgetc(fp);
    }
    
}

void thisIsId(char character){
    
    while(('0'<= character && character <='9') || ('a'<=character && character<='z') || ('A'<=character && character<='Z')){
        character=fgetc(fp);
    }
    
    fill ("id");
    scan(character);
}

void thisIsNum(){
    char nextchar=fgetc(fp);
    while (('0' <= nextchar && nextchar <= '9')) {
        nextchar=fgetc(fp);
    }
    if(nextchar=='.'){
        char nextchar2 = fgetc(fp);
        if ('0' <= nextchar2 && nextchar2 <= '9'){
            thisIsNumWithPoint();
        }else{
            flag=0;
            //scan(nextchar2); //<----DELETETHIS
        }
    }else{
        fill ("number");
        scan(nextchar);
    }
}

void thisIsNumWithPoint(){
    char nextchar = fgetc(fp);
    while (('0' <= nextchar && nextchar <= '9'))
        nextchar=fgetc(fp);
    
    fill ("number");
    scan(nextchar);
    
}

void thisIsComment(){
    char nextchar = fgetc(fp);
    char nextchar2 = fgetc(fp);
    
    while (1){
        
        if (nextchar == '*'){
            if (nextchar2 == '/'){
                break;
            }
        }
        
        if (nextchar == EOF) {
            flag = 0;
            return;
        }
        
        nextchar = nextchar2;
        nextchar2 = fgetc(fp);
    }
    
    scan(fgetc(fp));
    
}

void isRead(){
    char character = fgetc(fp);
    if (character == 'e') {
        character = fgetc(fp);
        if (character == 'a'){
            character = fgetc(fp);
            if (character == 'd') {
                fill ("read");
                //scan(fgetc(fp));
            }else{
                thisIsId(character);
            }
        }else{
            thisIsId(character);
        }
    }else{
        thisIsId(character);
    }
}

void isWrite(){
    char character = fgetc(fp);
    if (character == 'r') {
        character = fgetc(fp);
        if (character == 'i'){
            character = fgetc(fp);
            if (character == 't') {
                character = fgetc(fp);
                if (character == 'e'){
                    fill("write");
                    //scan(fgetc(fp));
                }
            }else{
                thisIsId(character);
            }
        }else{
            thisIsId(character);
        }
    }else{
        thisIsId(character);
    }
}

void fill(string outputs){
    output[i] = outputs;
    i++;
    // node *temp;
    // cout << "1\n";
    // temp = (node *) malloc(sizeof(node));
    // cout << "2\n";
    // temp->data = outputs;
    // cout << "3\n";
    
    // if (head==NULL) {
    //     head=temp;
    //     cout << "4\n";
    //     head->next = NULL;
    //     cout << "5\n";
    //     tail=head;
    // }else{
    //     tail->next=temp;
    //     tail=temp;
    //     tail->next = NULL;
    // }
}

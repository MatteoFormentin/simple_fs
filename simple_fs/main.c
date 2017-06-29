//
//  main.c
//  simple_fs
//
//  Created by Matteo Formentin on 27/06/17.
//  Copyright © 2017 Matteo Formentin. All rights reserved.
//

#include <stdio.h>
#include <string.h>

//Prototipi
int check_path_format(char * path);
char * check_content_format(char content[]);
struct directory * go_to_path_directory(struct directory * current_path, char path_local[]);
struct directory * create_directory(struct directory * root, char path_local[]);

//STRUTTURE DATI IMPORTANTE: INIZIALIZZARE A NULL I PUNTATORI SE NECESSARIO

//Directory

struct directory {
    char * name;
    struct directory * left_child;
    struct directory * right_brother;
    struct file * file_tree;
} directory;

struct directory * root;

//File

struct file {
    struct file * file_brother;
} file;



int main(int argc, const char * argv[]) {
    
    //INIZIALIZZAZIONE STRUTTURE DATI
    root=(struct directory *)malloc(sizeof(directory));
    root->name="root";
    
    //DEBUG ONLY
    struct directory * temp0=(struct directory *)malloc(sizeof(directory));
    temp0->name="folder0";
    temp0->right_brother=NULL;
    root->right_brother=temp0;
    
    
    struct directory * temp2=(struct directory *)malloc(sizeof(directory));
    temp2->name="folder0-1";
    temp2->right_brother=NULL;
    temp0->right_brother=temp2;
    
    struct directory * temp3=(struct directory *)malloc(sizeof(directory));
    temp3->name="folder1";
    temp3->right_brother=NULL;
    temp0->left_child=temp3;
    
    struct directory * temp4=(struct directory *)malloc(sizeof(directory));
    temp4->name="folder2";
    temp4->right_brother=NULL;
    temp3->left_child=temp4;

    
    
    
    
    //Lettura Comando, Percorso, Contenuto e Inserimento in Array Corrisponente
    char temp[200];
    char * command;
    char * path;
    char * content;
    
    //IMPORTANTE:INSERIRE WHILE NELLA VERSIONE DEFINITIVA
    
    printf("inserire comando:\n ");
    gets(temp);
    command=strtok(temp," ");
    path=strtok(NULL," ");
    content=strtok(NULL," ");
    
   
    //Esecuzione del comando corretto
    
    
    //Conttrollo null ingresso
    if (command==NULL) return -1;
   
    
    //CREATE
    if(strcmp(command, "create")==0)
    {
        printf("comando: create\n");
        if(check_path_format(path)==1)
        {
            //Operazione Create
            
            struct directory * temp_dir=go_to_path_directory(root,path);
        }
    }
    
    //CREATE_DIR
    else if(strcmp(command, "create_dir")==0)
    {
        printf("comando: create_dir");
        if(check_path_format(path)==1)
        {
            //Operazione create_dir
            
            
            struct directory * temp_dir2=create_directory(root, path);
        }
    }
    
    //READ
    else if(strcmp(command, "read")==0)
    {
        printf("comando: read");
        if(check_path_format(path)==1)
        {
            //Operazione read
        }
    }
    
    //WRITE
    else if(strcmp(command, "write")==0)
    {
        printf("comando: write");
        if(check_path_format(path)==1)
        {
            content = check_content_format(content);
            if(content != NULL)
            {
                printf("\nc: %s|stop\n", content);
                return 1;
            }
        }
    }
    
    //DELETE
    else if(strcmp(command, "delete")==0)
    {
        printf("comando: delete");
        if(check_path_format(path)==1)
        {
            //Operazione delete
        }
    }
    
    //DELETE_R
    else if(strcmp(command, "delete_r")==0)
    {
        printf("comando: delete_r");
        if(check_path_format(path)==1)
        {
            //Operazione delete_r
        }
    }
    
    //FIND
    else if(strcmp(command, "find")==0)
    {
        printf("comando: find");
        if(check_path_format(path)==1)
        {
            //Operazione find
        }
    }
    
    //EXIT
    else if(strcmp(command, "exit")==0)
    {
        printf("comando: exit");
        return 1;
    }
    
    //ERRORE INPUT COMANDO
    else
    {
        printf("comando non valido");
    }

}


//FUNZIONI CONTROLLO CORRETTEZZA INPUT - IMPORTANTE: CONTROLLARE SE SERVE ESCLUDERE INPUT CON PATH O CONTENUTO DOVE NON PREVISTO

int check_path_format(char path[])
{
    if(path[0]!='/' || path==NULL)
    {
        printf("\nerrore nel formato del percorso!\n");
        return -1;
    }
    printf("\npercorso ok\n");
    return 1;
}

//Controlla se l'ingresso ha gli apici e li rimuove
char * check_content_format(char content[])
{
    //controlla lunghezza array
    int last_element=strlen(content);
    last_element--;
    
    //controlla gli apici
    if(content[0]!='"' || content==NULL || content[last_element]!='"')
    {
        printf("\nerrore nel formato del contenuto!\n");
        return NULL;
    }
    else //rimuovi gli apici
    {
        printf("\ncontenuto ok\n");
        char string_without_apices[last_element];
        int i=1;
        while(i<last_element)
        {
            string_without_apices[i-1]=content[i];
            i++;
        }
        return string_without_apices;
    }
}

//Funzione per raggiungere una directory (current path deve essere inizializzato come root)

struct directory * go_to_path_directory(struct directory * current_path, char path_local[])
{
    char * current_path_name=strtok(path_local,"/");
    while(current_path_name!=NULL)
    {
        while(strcmp(current_path_name, current_path->name)!=0 ) //Percorro i fratelli ramo destro
        {
            //directory non esistente o nome di un file
            current_path=current_path->right_brother;
            if(current_path==NULL)
            {
                printf("non trovato\n");
                return NULL;
            }
        }
        current_path_name=strtok(NULL,"/");
        if(current_path_name!=NULL) current_path=current_path->left_child;
    }
    printf("\ntrovato: %s\n", current_path->name);
    return current_path;
}


struct directory * create_directory(struct directory * root, char path_local[])
{
    struct directory * new_directory;
    struct directory * new_directory_path;

    int last_path_before_new=(int)(strrchr(path_local, '/')-path_local);
    char * path_where_create_dir;
    strncpy(path_where_create_dir,path_local,last_path_before_new);
    new_directory_path=go_to_path_directory(root, path_where_create_dir);
    if(new_directory_path==NULL) return NULL;
    new_directory=(struct directory *)malloc(sizeof(directory));
    new_directory_path->right_brother=new_directory;
    new_directory->name="test";
   
    
    return new_directory;
}

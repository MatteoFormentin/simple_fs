//
//  main.c
//  simple_fs
//
//  Created by Matteo Formentin on 27/06/17.
//  Copyright © 2017 Matteo Formentin. All rights reserved.
//


//!!!SISTEMARE CONTENT!!!




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Prototipi
int check_path_format(char * path, char command[]);
char * check_content_format(char content[]);

struct directory * go_to_path_directory(struct directory * current_path, char path_local[]);
struct directory * create_directory(struct directory * root, char path_local[]);

struct file * go_to_path_file(struct directory * current_path, char path_local[]);
struct file * create_file(struct directory * root, char path_local[]);
struct file * write_file(struct directory * root, char path_local[], char * content_local);
struct file * read_file(struct directory * root, char path_local[]);

void find(struct directory * root, char name[]);

//STRUTTURE DATI IMPORTANTE: INIZIALIZZARE A NULL I PUNTATORI SE NECESSARIO

//Directory

struct directory {
    char name[255];
    struct directory * left_child;
    struct directory * right_brother;
    struct file * file_tree;
} directory;

struct directory * root;

//File

struct file {
    char name[255];
    char content[255];
    struct file * file_brother;
} file;



int main(int argc, const char * argv[]) {
    
    //INIZIALIZZAZIONE STRUTTURE DATI
    root=(struct directory *)malloc(sizeof(directory));
    strcpy(root,"root");
    root->right_brother=NULL;
    root->left_child=NULL;
    root->file_tree=NULL;
    
    //DEBUG ONLY
    struct directory * temp0=(struct directory *)malloc(sizeof(directory));
    strcpy(temp0->name,"folder0");
    temp0->right_brother=NULL;
    root->left_child=temp0;
    temp0->file_tree=NULL;
    
    struct directory * temp1=(struct directory *)malloc(sizeof(directory));
    strcpy(temp1->name,"folder1");
    temp1->left_child=NULL;
    temp0->right_brother=temp1;
    temp1->file_tree=NULL;

    
    struct directory * temp2=(struct directory *)malloc(sizeof(directory));
    strcpy(temp2->name,"folder2");
    temp2->left_child=NULL;
    temp1->right_brother=temp2;
    
    struct directory * temp3=(struct directory *)malloc(sizeof(directory));
    strcpy(temp3->name,"folder3");;
    temp3->left_child=NULL;
    temp2->right_brother=temp3;
    
    struct directory * temp4=(struct directory *)malloc(sizeof(directory));
    strcpy(temp4->name,"folder4");;
    temp4->left_child=NULL;
     temp4->right_brother=NULL;
    temp3->right_brother=temp4;
    
    struct file * file0=(struct file *)malloc(sizeof(file));
    strcpy(file0->name,"file0");
    strcpy(file0->content,"test");
    temp0->file_tree=file0;
    

    
    
    
    
    //Lettura Comando, Percorso, Contenuto e Inserimento in Array Corrisponente
    char buffer[200];
    char * command;
    char * path;
    char * content;
    
  
    while (1) {
   
    printf("\n\n\n\ninserire comando:\n "); //DEBUG ONLY
        
        
    //Acquisizione comando-percorso-contenuto
    gets(buffer);
        
    command=strtok(buffer," ");
    if(command!=NULL) command[strlen(command)]='\0';
        
    path=strtok(NULL," ");
    if(path!=NULL) path[strlen(path)]='\0';
        
    content=strtok(NULL," ");
    if(content!=NULL) content[strlen(content)]='\0';
        
        
        
    //Esecuzione del comando corretto
    
    
    //Conttrollo null ingresso
    if (command==NULL)
    {
        printf("inserire un comando seguito da invio!"); //DEBUG ONLY
        continue;
    }
   
    
    //CREATE
    if(strcmp(command, "create")==0)
    {
        printf("comando: create\n");
        if(check_path_format(path, command)==1)
        {
            //Operazione Create
            
            struct file * temp_file=create_file(root,path);
        }
    }
    
    //CREATE_DIR
    else if(strcmp(command, "create_dir")==0)
    {
        printf("comando: create_dir\n");
        if(check_path_format(path, command)==1)
        {
            //Operazione create_dir
            
            
            struct directory * temp_dir2=create_directory(root, path);
        }
    }
    
    //READ
    else if(strcmp(command, "read")==0)
    {
        printf("comando: read");
        if(check_path_format(path, command)==1)
        {
            read_file(root, path);
        }
    }
    
    //WRITE
    else if(strcmp(command, "write")==0)
    {
        printf("comando: write");
        if(check_path_format(path, command)==1)
        {
            content = check_content_format(content);
            if(content!=NULL)
            {
                printf("\ncontent: %s\n", content);
                write_file(root, path, content);
            }
        }
    }
    
    //DELETE
    else if(strcmp(command, "delete")==0)
    {
        printf("comando: delete");
        if(check_path_format(path, command)==1)
        {
            //Operazione delete
        }
    }
    
    //DELETE_R
    else if(strcmp(command, "delete_r")==0)
    {
        printf("comando: delete_r");
        if(check_path_format(path, command)==1)
        {
            //Operazione delete_r
        }
    }
    
    //FIND
    else if(strcmp(command, "find")==0)
    {
        printf("comando: find");
        if(check_path_format(path, command)==1)
        {
            find(root, path);
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
        printf("comando non valido\n");
    }

    }
}

//FUNZIONI CONTROLLO CORRETTEZZA INPUT - IMPORTANTE: CONTROLLARE SE SERVE ESCLUDERE INPUT CON PATH O CONTENUTO DOVE NON PREVISTO

int check_path_format(char path[], char command[])
{
    if((path[0]!='/' || path==NULL) && strcmp(command, "find")!=0)
    {
        printf("\nerrore nel formato del percorso!\n");
        return -1;
    }
    return 1;
}

//Controlla se l'ingresso ha gli apici e li rimuove
char * check_content_format(char content[])
{
    
    //controlla lunghezza array
    int last_element=strlen(content);
    last_element--;
    if(last_element==0) return NULL;
    //controlla gli apici
    if(content[0]!='"' || content==NULL || content[last_element]!='"')
    {
        printf("\nerrore nel formato del contenuto!");
        if(content==NULL) printf("\ncontenuto null\n");
        return NULL;
    }
    else //rimuovi gli apici
    {
        char string_without_apices[last_element];
        int i=1;
        while(i<last_element)
        {
            string_without_apices[i-1]=content[i];
            i++;
        }
        string_without_apices[last_element-1]='\0';
        
        return string_without_apices;
    }
}

//Funzione per raggiungere una directory (current path deve essere inizializzato come root)

struct directory * go_to_path_directory(struct directory * current_path, char path_local[])
{
    
    current_path=current_path->left_child;
    if(current_path==NULL)
    {
        return root;
    }
    char * current_path_name=strtok(path_local,"/");
    while(current_path_name!=NULL) //percorro i livelli ramo sinistro
    {
        while(strcmp(current_path_name, current_path->name)!=0) //Percorro i fratelli ramo destro
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
        if(current_path_name!=NULL && current_path->left_child!=NULL) current_path=current_path->left_child;
        else
        {
            break;
        }
    }
    if(current_path==NULL)
    {
        printf("non trovato\n");
        return NULL;
    }
    return current_path;
}


struct directory * create_directory(struct directory * root, char path_local[])
{
    struct directory * new_directory_path=NULL;

    char * new_directory_name=NULL;
    char * path_where_create_dir=NULL;
    
    unsigned int last_path_before_new=(unsigned int)(strrchr(path_local, '/')-path_local); //Controllo se sono in root
   
    //Caso creazione non in root
    if (last_path_before_new!=0)
    {
        
        //Estrazione percorso dal parametro percorso
        path_where_create_dir = (char *)malloc(last_path_before_new);
        strncpy(path_where_create_dir,path_local,last_path_before_new);
        path_where_create_dir[last_path_before_new] = '\0';
        new_directory_path=go_to_path_directory(root, path_where_create_dir);
    
        if(new_directory_path==NULL)
        {
            printf("\nPercorso creazione non trovato, return\n");
            return NULL; //Percorso creazione non trovato
        }
        
        //Estrazione nome cratella dal parametro percorso
        new_directory_name=(char *)malloc(strlen(path_local)-last_path_before_new);
         for(int i=last_path_before_new; i<strlen(path_local); i++)
         {
             new_directory_name[i-last_path_before_new]=path_local[i+1];
         }
         new_directory_name[last_path_before_new+2]='\0';
    }
    
    //Caso creazione in root
    else
    {
        printf("\nCreazione in root\n"); //DEBUG ONLY
        new_directory_path=root;
        new_directory_name=(char *)malloc(strlen(path_local));
        int i;
        for(i=0; i<strlen(path_local); i++)
        {
            new_directory_name[i]=path_local[i+1];
        }
        new_directory_name[i+1]='\0';
    }
    
    //Creazione in memoria della cartella (non ancora nell'albero)
    struct directory * new_directory=malloc(sizeof(struct directory));
    new_directory->left_child=NULL;
    new_directory->right_brother=NULL;
    new_directory->file_tree=NULL;
    strcpy(new_directory->name, new_directory_name);
    
    //Caso 1: nessun figlio sinistro esistente
    if (new_directory_path->left_child==NULL)
    {
        new_directory_path->left_child=new_directory;
    }
    
    //Caso 2: figlio sinistro esistente
    else
    {
        new_directory_path=new_directory_path->left_child;
        
        //???POTREBBE ESSERE SUPERFLUO???
        if(strcmp(new_directory_path->name, new_directory_name)==0) //Controllo se esiste una directory con lo stesso nome come primo figlio
        {
            printf("directory già esistente, return\n"); //DEBUG ONLY
            free(new_directory);
            free(path_where_create_dir);
            free(new_directory_name);
            return NULL;
        }
        
        
        while (new_directory_path->right_brother!=NULL) //Caso 2: esistono dei figli->scorri fino alla prima posizione libera a destra
        {
            //printf("new_directory_path->name 2-2 (cartella attualmente controllata dal ciclo) %s\n", new_directory_path->name);
            if(strcmp(new_directory_path->name, new_directory_name)==0) //Directory con lo stesso nome come figli successivi
            {
                printf("directory già esistente, return\n");
                free(new_directory);
                free(path_where_create_dir);
                free(new_directory_name);
                return NULL;
            }
            new_directory_path=new_directory_path->right_brother;
        }
        
        new_directory_path->right_brother=new_directory;
    }
    
    free(path_where_create_dir);
    free(new_directory_name);
    printf("ok\n");
    return new_directory;
}

struct file * create_file(struct directory * root, char path_local[])
{
    
    char * new_file_name=NULL;
    char * path_where_create_file=NULL;
    
    struct directory * container_directory_path=NULL;

    
    unsigned int last_path_before_new=(unsigned int)(strrchr(path_local, '/')-path_local); //Controllo se sono in root
    
    //Caso creazione non in root
    if (last_path_before_new!=0)
    {
        
        //Estrazione percorso dal parametro percorso
        path_where_create_file = (char *)malloc(last_path_before_new);
        strncpy(path_where_create_file,path_local,last_path_before_new);
        path_where_create_file[last_path_before_new] = '\0';
        container_directory_path=go_to_path_directory(root, path_where_create_file);
        
        if(container_directory_path==NULL)
        {
            printf("\nPercorso creazione non trovato, return\n");
            return NULL; //Percorso creazione non trovato
        }
        
        //Estrazione nome file dal parametro percorso
        new_file_name=(char *)malloc(strlen(path_local)-last_path_before_new);
        for(int i=last_path_before_new; i<strlen(path_local); i++)
        {
            new_file_name[i-last_path_before_new]=path_local[i+1];
        }
        new_file_name[last_path_before_new+2]='\0';
    }
    
    //Caso creazione in root
    else
    {
        printf("\nCreazione in root\n"); //DEBUG ONLY
        container_directory_path=root;
        new_file_name=(char *)malloc(strlen(path_local)-last_path_before_new);
        int i;
        for(i=0; i<strlen(path_local); i++)
        {
            new_file_name[i]=path_local[i+1];
        }
        new_file_name[i+1]='\0';
    }
    
    
    struct file * new_file=malloc(sizeof(struct file));
    strcpy(new_file->name, new_file_name);
    new_file->file_brother=NULL;
    
    //Caso 1: nessun figlio esistente
    if (container_directory_path->file_tree==NULL)
    {
        container_directory_path->file_tree=new_file;
    }
    else
    {
        struct file * file_prec=container_directory_path->file_tree;
        
        if(strcmp(new_file->name, file_prec->name)==0) //Controllo se esiste una directory con lo stesso nome come primo figlio
        {
            printf("directory già esistente, return\n"); //DEBUG ONLY
            free(new_file_name);
            free(path_where_create_file);
            free(new_file);
            return NULL;
        }
        
        while (file_prec->file_brother!=NULL) {
            if(strcmp(new_file->name, file_prec->name)==0) //Controllo se esiste una directory con lo stesso nome come primo figlio
            {
                printf("directory già esistente, return\n"); //DEBUG ONLY
                free(new_file_name);
                free(path_where_create_file);
                free(new_file);
                return NULL;
            }
            file_prec=file_prec->file_brother;
        }
        file_prec->file_brother=new_file;
    }
    printf("ok\n");
    return new_file;
}


struct file * go_to_path_file(struct directory * current_path, char path_local[])
{
    char * file_name=NULL;
    char * container_directory_name=NULL;
    
    struct directory * container_directory_path=NULL;
    
    
    unsigned int last_path_before_new=(unsigned int)(strrchr(path_local, '/')-path_local); //Controllo se sono in root
    
    //Caso file non in root
    if (last_path_before_new!=0)
    {
        
        //Estrazione percorso dal parametro percorso
        container_directory_name = (char *)malloc(last_path_before_new);
        strncpy(container_directory_name,path_local,last_path_before_new);
        container_directory_name[last_path_before_new] = '\0';
        container_directory_path=go_to_path_directory(root, container_directory_name);
        
        if(container_directory_path==NULL)
        {
            printf("\nPercorso cartella container non trovato, return\n");
            return NULL; //Percorso creazione non trovato
        }
        
        //Estrazione nome file dal parametro percorso
        file_name=(char *)malloc(strlen(path_local)-last_path_before_new);
        for(int i=last_path_before_new; i<strlen(path_local); i++)
        {
            file_name[i-last_path_before_new]=path_local[i+1];
        }
        file_name[last_path_before_new+2]='\0';
    }
    
    //Caso file in root
    else
    {
        container_directory_path=root;
        file_name=(char *)malloc(strlen(path_local));
        int i;
        for(i=0; i<strlen(path_local); i++)
        {
            file_name[i]=path_local[i+1];
        }
        file_name[i+1]='\0';
    }
    
    //Ricerca del file nel sottoalbero file
    
    struct file * current_file=container_directory_path->file_tree;
    
    if(current_file==NULL)
    {
        printf("\nNessun file nella cartella\n");
        return NULL; //Percorso creazione non trovato
    }
    
    if(strcmp(current_file->name, file_name)==0) //Controllo se esiste una directory con lo stesso nome come primo figlio
    {
        printf("file trovato\n"); //DEBUG ONLY
        free(file_name);
        free(container_directory_name);
        return current_file;
    }
    
    while (current_file->file_brother!=NULL) {
        if(strcmp(current_file->name, file_name)==0) //Controllo se esiste una directory con lo stesso nome come primo figlio
        {
            printf("file trovato\n"); //DEBUG ONLY
            free(file_name);
            free(container_directory_name);
            return current_file;
        }
        current_file=current_file->file_brother;
    }
    
     printf("file NON trovato\n"); //DEBUG ONLY
    return NULL;

}





struct file * write_file(struct directory * root, char path_local[], char * content_local)
{
    struct file * file_to_write=go_to_path_file(root, path_local);
    printf("\ncontent local: %s\n", content_local);
    if(file_to_write==NULL)
    {
        printf("\nPercorso file non trovato, return\n");
        return NULL; //Percorso creazione non trovato
    }
    else
    {
        memset(file_to_write->content, '\0', 255);
        strcpy(file_to_write->content, content_local);
        printf("ok %d\n", strlen(content_local));
        return file_to_write;
    }
    
}


struct file * read_file(struct directory * root, char path_local[])
{
    struct file * file_to_read=go_to_path_file(root, path_local);
    if(file_to_read==NULL)
    {
        printf("no\n");
        return NULL; //Percorso creazione non trovato
    }
    else
    {
        printf("contenuto %s",file_to_read->content);
        return file_to_read;
    }
}

void find(struct directory * root, char name[])
{
    struct directory * current_level=root;
    struct directory * current_directory=root;
    struct directory * first_directory_level=root;
    struct file * current_file=NULL;
    
    char percorso[1024];
    strcpy(percorso,"/");

    
    while(current_level!=NULL)
    {
        first_directory_level=current_level;
        current_directory=first_directory_level;
        while (current_directory!=NULL)
        {
            if(strcmp(current_directory->name, name)==0)
            {
                strcat(percorso, current_directory->name);
                strcat(percorso, "/");
                printf("\ntrovato come directory");
                printf("\npercorso: %s", percorso);
                return;
            }
            current_file=current_directory->file_tree;
            while (current_file!=NULL) {
                if(strcmp(current_file->name, name)==0)
                {
                    strcat(percorso, current_directory->name);
                    strcat(percorso, "/");
                    strcat(percorso, current_file->name);
                    printf("\ntrovato come file\n");
                    printf("\npercorso: %s", percorso);
                    return;
                }
                current_file=current_file->file_brother;
            }
            
            current_directory=current_directory->right_brother;
        }
        
        current_level=current_level->left_child;

    }
    printf("NON trovato");
}


void delete(struct directory * root, char path_local[]){
    struct directory * directory_to_delete=go_to_path_file(root, path_local);
    if(directory_to_delete!=NULL && directory_to_delete->left_child==NULL){
        if(directory_to_delete->right_brother==NULL)
        {
            free(directory_to_delete);
        }
        if(
    }
}











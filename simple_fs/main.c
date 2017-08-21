//
//  main.c
//  simple_fs
//
//  Created by Matteo Formentin on 27/06/17.
//  Copyright © 2017 Matteo Formentin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Prototipi
int check_path_format(char * path);
char * check_content_format(char content[]);
struct directory * go_to_path_directory(struct directory * current_path, char path_local[]);
struct directory * create_directory(struct directory * root, char path_local[]);

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
    struct file * file_brother;
} file;



int main(int argc, const char * argv[]) {
    
    //INIZIALIZZAZIONE STRUTTURE DATI
    root=(struct directory *)malloc(sizeof(directory));
    strcpy(root,"root");
    root->right_brother=NULL;
    root->left_child=NULL;
    
    //DEBUG ONLY
    struct directory * temp0=(struct directory *)malloc(sizeof(directory));
    strcpy(temp0->name,"folder0");
    temp0->right_brother=NULL;
    root->left_child=temp0;
    
    struct directory * temp1=(struct directory *)malloc(sizeof(directory));
    strcpy(temp1->name,"folder1");
    temp1->left_child=NULL;
    temp0->right_brother=temp1;

    
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
    

    
    
    
    
    //Lettura Comando, Percorso, Contenuto e Inserimento in Array Corrisponente
    char buffer[200];
    char * command;
    char * path;
    char * content;
    
    //IMPORTANTE:INSERIRE WHILE NELLA VERSIONE DEFINITIVA
  
    while (1) {
   
    printf("\n\n\n\ninserire comando:\n ");
    gets(buffer);
    command=strtok(buffer," ");
    path=strtok(NULL," ");
    content=strtok(NULL," ");
    
    printf("command: %s path: %s content: %s\n",command, path, content);
   
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
        printf("comando: create_dir\n");
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
        printf("comando non valido\n");
    }

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
        
        //IMPORTANTE: CONTROLLARE USCITA DAL CICLO
        
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

    printf("trovato: %s\n", current_path->name);
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
        printf("\n CREAZIONE NON IN ROOT \n percorso dove creare la dir:%s\n", path_where_create_dir); //DEBUG ONLY
        new_directory_path=go_to_path_directory(root, path_where_create_dir);
    
        if(new_directory_path==NULL) return NULL; //Percorso creazione non trovato
               
        //Estrazione nome cratella dal parametro percorso
        new_directory_name=(char *)malloc(strlen(path_local)-last_path_before_new);
         for(int i=last_path_before_new; i<strlen(path_local); i++)
         {
             new_directory_name[i-last_path_before_new]=path_local[i+1];
         }
         new_directory_name[last_path_before_new]='\0';
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
    
    
    /*for(int i=0; i<strlen(new_directory_name); i++)
    {
        new_directory->name[i]=new_directory_name[i];
    }*/
   
    
    
    //Caso 1: nessun figlio sinistro esistente
    if (new_directory_path->left_child==NULL)
    {
        new_directory_path->left_child=new_directory; //Caso 1: nessun figlio esistente
        printf("\nCaso 1: nessun figlio esistente\n"); //DEBUG ONLY
    }
    
    //Caso 2: figlio sinistro esistente
    else
    {
        new_directory_path=new_directory_path->left_child;
        
        printf("\nCaso 2: figlio esistente\n"); //DEBUG ONLY
        printf("new_directory_path->name (cartella primo figlio) %s\n", new_directory_path->name); //DEBUG ONLY
        printf("new_directory_name %s\n", new_directory_name);
        
        
        //???POTREBBE ESSERE SUPERFLUO???
        if(strcmp(new_directory_path->name, new_directory_name)==0) //Controllo se esiste una directory con lo stesso nome come primo figlio
        {
            printf("directory già esistente 2-1\n"); //DEBUG ONLY
            printf("new_directory_path->name 2-1 %s\n", new_directory_path->name); //DEBUG ONLY
            printf("new_directory_name %s\n", new_directory_name); //DEBUG ONLY
            free(new_directory);
            return NULL;
        }
        
        
        while (new_directory_path->right_brother!=NULL) //Caso 2: esistono dei figli->scorri fino alla prima posizione libera a destra
        {
            //printf("new_directory_path->name 2-2 (cartella attualmente controllata dal ciclo) %s\n", new_directory_path->name);
            if(strcmp(new_directory_path->name, new_directory_name)==0) //Directory con lo stesso nome come figli successivi
            {
                printf("directory già esistente 2-2\n");
                free(new_directory);
                return NULL;
            }
            new_directory_path=new_directory_path->right_brother;
            printf("new_directory_path->name 2-2 (cartella attualmente controllata dal ciclo) %s\n", new_directory_path->name);
        }
        
        new_directory_path->right_brother=new_directory;
    }
    
    
    printf("\nnew directory name: %s\n", new_directory->name); //DEBUG ONLY
    // go_to_path_directory(root, path_local); //TEST CREAZIONE -- DEBUG ONLY
    
    free(path_where_create_dir);
    free(new_directory_name);
    printf("ok\n");
    return new_directory;
}

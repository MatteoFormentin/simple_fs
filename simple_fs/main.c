//
//  main.c
//  simple_fs
//
//  Created by Matteo Formentin on 27/06/17.
//  Copyright © 2017 Matteo Formentin. All rights reserved.
//


/*                !!!BUG NOTI!!!
 *  1-La creazione directory va a buon fine anche se si tenta la creazione in una subdirectory inesistente RISOLTO
 *  2-il contenuto della write viene troncato agli spazi
 *  3-Problemi nel passaggio del parametro "contenuto" nella write (contenuto errato) RISOLTO
 *  4-create_directory(root, "/folder0/folder0") crea /folder0 se non esiste invece di ritornare errore
 *
 *
 *
 */




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

int find(struct directory * current, char name[],char percorso[]);
void delete(struct directory * root, char path_local[], int flag);
void delete_child(struct directory * directory);

//STRUTTURE DATI IMPORTANTE: INIZIALIZZARE A NULL I PUNTATORI SE NECESSARIO

//Directory

struct directory {
    char name[255];
    struct directory * left_child;
    struct directory * right_brother;
    struct file * file_tree;
} directory;

struct directory * root;
struct directory * prec_folder;

struct file * prec_file;

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
    
    /*
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
    
*/
    create_directory(root, "/folder0");
    create_directory(root, "/folder1");
    create_directory(root, "/folder0/folder0");
    create_directory(root, "/folder0/folder1");
    create_directory(root, "/folder0/folder1/folder10");
    create_file(root,      "/folder0/folder1/folder10/file");
    create_directory(root, "/folder0/folder2");
    create_directory(root, "/folder0/folder3");
    create_directory(root, "/folder0/folder4");
    create_directory(root, "/folder0/folder0/folder10");
    create_directory(root, "/folder0/folder0/folder1");
    create_file(root, "/folder0/folder0/folder1/file");
    
    create_directory(root, "/folder0/folder0/folder0");
                                                        
    create_directory(root, "/folder0/folder0/folder2");
    create_directory(root, "/folder0/folder0/folder3");
    create_directory(root, "/folder0/folder0/folder10/folder20");
    create_file(root, "/folder0/folder0/folder10/folder20/file");
    create_directory(root, "/folder0/folder0/folder0/folder1");
    create_directory(root, "/folder0/folder0/folder0/folder2");
    create_directory(root, "/folder0/folder0/folder0/folder3");
    
    
    
    
    //Lettura Comando, Percorso, Contenuto e Inserimento in Array Corrisponente
    char buffer[200];
    char * command;
    char * path;
    char * content;
    
  
    while (1) {
   
    //printf("\n\n\n\ninserire comando:\n "); //DEBUG ONLY
        
        
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
        //printf("inserire un comando seguito da invio!"); //DEBUG ONLY
        continue;
    }
   
    
    //CREATE
    if(strcmp(command, "create")==0)
    {
        if(check_path_format(path, command)==1)
        {
            create_file(root,path);
        }
        else printf("no\n");
    }
    
    //CREATE_DIR
    else if(strcmp(command, "create_dir")==0)
    {
        if(check_path_format(path, command)==1)
        {
            create_directory(root, path);
        }
        else printf("no\n");
    }
    
    //READ
    else if(strcmp(command, "read")==0)
    {
        if(check_path_format(path, command)==1)
        {
            read_file(root, path);
        }
        else printf("no\n");
    }
    
    //WRITE
    else if(strcmp(command, "write")==0)
    {
        if(check_path_format(path, command)==1)
        {
            content = check_content_format(content);
            if(content!=NULL)
            {
                //printf("\ncontent: %s\n", content); //DEBUG ONLY
                write_file(root, path, content);
            }
            else printf("no\n");
        }
    }
    
    //DELETE
    else if(strcmp(command, "delete")==0)
    {
        if(check_path_format(path, command)==1)
        {
            delete(root, path, 0);
        }
        else printf("no\n");
    }
    
    //DELETE_R
    else if(strcmp(command, "delete_r")==0)
    {
        if(check_path_format(path, command)==1)
        {
            delete(root, path, 1);
        }
        else printf("no\n");
    }
    
    //FIND
    else if(strcmp(command, "find")==0)
    {
        if(check_path_format(path, command)==1)
        {
            char percorso[10240];
            memset(percorso, '/0', 10240);
            strcpy(percorso,"/");
            if(find(root, path, percorso)==0) printf("no\n");
            //printf("ok %s", percorso);
        }
        else printf("no\n");
    }
    
    //EXIT
    else if(strcmp(command, "exit")==0)
    {
        return 0;
    }
        
        
    else if(strcmp(command, "vai")==0) //DEBUG ONLY
    {
        if(check_path_format(path, command)==1)
        {
            struct directory * temp_dir=go_to_path_directory(root, path);
            if(temp_dir!=NULL)
                printf("\ntrovato: %s", temp_dir->name);
        }
    }
    
    //ERRORE INPUT COMANDO
    else
    {
        //printf("comando non valido\n"); //DEBUG ONLY
    }

    }
}

//FUNZIONI CONTROLLO CORRETTEZZA INPUT - IMPORTANTE: CONTROLLARE SE SERVE ESCLUDERE INPUT CON PATH O CONTENUTO DOVE NON PREVISTO

int check_path_format(char path[], char command[])
{
    if((path[0]!='/' || path==NULL) && strcmp(command, "find")!=0)
    {
        //printf("\nerrore nel formato del percorso!\n"); //DEBUG ONLY
        return -1;
    }
    return 1;
}

//Controlla se l'ingresso ha gli apici e li rimuove
char * check_content_format(char content[])
{
    if(content==NULL)
    {
        return NULL;
    }
    //controlla lunghezza array
    int last_element=strlen(content);
    last_element--;
    if(last_element==0) return NULL;
    //controlla gli apici
    if(content[0]!='"' || content==NULL || content[last_element]!='"')
    {
       // printf("\nerrore nel formato del contenuto!"); //DEBUG ONLY
        //if(content==NULL) printf("\ncontenuto null\n"); //DEBUG ONLY
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
    prec_folder=current_path;
    current_path=current_path->left_child;
    if(current_path==NULL) //Albero vuoto
    {
        return root;
    }
    char * current_path_name=strtok(path_local,"/");
    while(current_path_name!=NULL) //percorro i livelli ramo sinistro
    {
        while(strcmp(current_path_name, current_path->name)!=0) //Percorro i fratelli ramo destro
        {
            //directory non esistente o nome di un file
            prec_folder=current_path;
            current_path=current_path->right_brother;
            if(current_path==NULL) //Se una directory padre non c'è ritorna null
            {
                //printf("non trovato\n"); //DEBUG ONLY
                return NULL;
            }
        }
        
        current_path_name=strtok(NULL,"/");//leggi il nome della cartella successiva nel percorso
        if(current_path_name!=NULL && current_path->left_child!=NULL)
        {
            prec_folder=current_path;
            current_path=current_path->left_child;
        }
        else if(current_path_name!=NULL && current_path->left_child==NULL)
        {
            //printf("non trovato\n"); //DEBUG ONLY
            return NULL;
        }
        else //Se non ci sono più cartelle nel nome percorso ho trovato la cartella
        {
            break;
        }
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
            //printf("\nPercorso creazione non trovato, return\n"); //DEBUG ONLY
            printf("no\n");
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
        //printf("\nCreazione in root\n"); //DEBUG ONLY
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
        
        if(strcmp(new_directory_path->name, new_directory_name)==0) //Controllo se esiste una directory con lo stesso nome come primo figlio
        {
            //printf("directory già esistente, return\n"); //DEBUG ONLY
            printf("no\n");
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
                //printf("directory già esistente, return\n"); //DEBUG ONLY
                printf("no\n");
                free(new_directory);
                free(path_where_create_dir);
                free(new_directory_name);
                return NULL;
            }
            new_directory_path=new_directory_path->right_brother;
        }
        
        if(strcmp(new_directory_path->name, new_directory_name)==0) //Directory con lo stesso nome come ultimo figlio
        {
            //printf("directory già esistente, return\n"); //DEBUG ONLY
            printf("no\n");
            free(new_directory);
            free(path_where_create_dir);
            free(new_directory_name);
            return NULL;
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
            //printf("\nPercorso creazione non trovato, return\n"); //DEBUG ONLY
            printf("no\n");
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
        //printf("\nCreazione in root\n"); //DEBUG ONLY
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
        
        if(strcmp(new_file->name, file_prec->name)==0) //Controllo se esiste un file con lo stesso nome come primo figlio
        {
            //printf("directory già esistente, return\n"); //DEBUG ONLY
            printf("no\n");
            free(new_file_name);
            free(path_where_create_file);
            free(new_file);
            return NULL;
        }
        
        while (file_prec->file_brother!=NULL) {
            if(strcmp(new_file->name, file_prec->name)==0) //Controllo se esiste un file con lo stesso nome come altro figlio
            {
                //printf("directory già esistente, return\n"); //DEBUG ONLY
                printf("no\n");
                free(new_file_name);
                free(path_where_create_file);
                free(new_file);
                return NULL;
            }
            file_prec=file_prec->file_brother;
        }
        
        if(strcmp(new_file->name, file_prec->name)==0) //Controllo se esiste un file con lo stesso nome come ultimo figlio
        {
            //printf("directory già esistente, return\n"); //DEBUG ONLY
            printf("no\n");
            free(new_file_name);
            free(path_where_create_file);
            free(new_file);
            return NULL;
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
            //printf("\nPercorso cartella container non trovato, return\n");
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
        //printf("\nNessun file nella cartella\n"); //DEBUG ONLY
        return NULL; //Percorso creazione non trovato
    }
    
    if(strcmp(current_file->name, file_name)==0) //Controllo se esiste un file con lo stesso nome come primo figlio
    {
        //printf("file trovato\n"); //DEBUG ONLY
        free(file_name);
        free(container_directory_name);
        prec_folder=container_directory_path;
        return current_file;
    }
    
    while (current_file->file_brother!=NULL) {
        if(strcmp(current_file->name, file_name)==0) //Controllo se esiste una file con lo stesso nome come altro figlio
        {
            //printf("file trovato\n"); //DEBUG ONLY
            free(file_name);
            free(container_directory_name);
            prec_folder=container_directory_path;
            return current_file;
        }
        prec_file=current_file;
        current_file=current_file->file_brother;
    }
    
    if(strcmp(current_file->name, file_name)==0) //Controllo se esiste una file con lo stesso nome come ultimo figlio
    {
        //printf("file trovato\n"); //DEBUG ONLY
        free(file_name);
        free(container_directory_name);
        prec_folder=container_directory_path;
        return current_file;
    }
    
    //printf("file NON trovato\n"); //DEBUG ONLY
    return NULL;

}


struct file * write_file(struct directory * root, char path_local[], char * content_local)
{
    struct file * file_to_write=go_to_path_file(root, path_local);
    //printf("\ncontent local: %s\n", content_local); //DEBUG ONLY
    if(file_to_write==NULL)
    {
        //printf("\nPercorso file non trovato, return\n"); //DEBUG ONLY
        printf("no\n");
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
        printf("contenuto %s\n",file_to_read->content);
        return file_to_read;
    }
}


int find(struct directory * current_directory, char name[], char percorso[])
{
    int flag_trovato=0;
   
    if(current_directory->left_child!=NULL)
    {
        if(current_directory!=root)
        {
            if(strcmp(percorso, "/")!=0) strcat(percorso,"/");
            strcat(percorso, current_directory->name);
        }
        
        flag_trovato=find(current_directory->left_child, name, percorso);
        
        for(int i=(strlen(percorso)-strlen(current_directory->name))-1;i<strlen(percorso);i++) percorso[i]='\0';
    }
    if(current_directory->right_brother!=NULL)
    {
        flag_trovato=find(current_directory->right_brother, name, percorso);
    }
    
    if(strcmp(current_directory->name, name)==0)
    {

        printf("ok %s/%s\n", percorso,current_directory->name);
        return 1;
    }
    else if(current_directory->file_tree!=NULL)
    {
        struct file * current_file=current_directory->file_tree;
        while (current_file!=NULL) {
            if(strcmp(current_file->name, name)==0)
            {
                printf("ok %s/%s/%s\n", percorso,current_directory->name,current_file->name);
                return 1;
            }
            current_file=current_file->file_brother;
        }
        
    }
    
    return 0;
}


void delete(struct directory * root, char path_local[], int flag)
{
    prec_folder=NULL;
    prec_file=NULL;
    char * path_local2 = (char *)malloc(strlen(path_local));
    strcpy(path_local2,path_local);
    struct directory * directory_to_delete=go_to_path_directory(root, path_local);
    
    
    //Delete directory
    if(directory_to_delete!=NULL) //Necessario per escludere il ricorsivo
    {
        if((directory_to_delete->left_child==NULL || directory_to_delete->file_tree==NULL) && flag==0 )
        {
            //printf("\nfile nella cartella"); //DEBUG ONLY
            printf("no\n");
            return;
        }
        
        if(prec_folder->right_brother==directory_to_delete) //Casi directory fratelli
        {
            if(directory_to_delete->right_brother==NULL)
            {
                prec_folder->right_brother=NULL;
            }
            else
            {
                prec_folder->right_brother=directory_to_delete->right_brother;
            }
        }
        
        else if(prec_folder->left_child==directory_to_delete) //Casi directory figlie
        {
            if(directory_to_delete->right_brother==NULL)
            {
                prec_folder->left_child=NULL;
            }
        
            else
            {
                prec_folder->left_child=directory_to_delete->right_brother;
            }
            
        }
        
        if(flag==1 && directory_to_delete->left_child!=NULL) //Delete ricorsiva
        {
            delete_child(directory_to_delete->left_child);
        }
        
        free(directory_to_delete);
        
        free(path_local2);
        printf("ok\n");
        return;
    }
    
    //Delete file
    struct file * file_to_delete=go_to_path_file(root, path_local2);
    if(file_to_delete !=NULL )
    {
        if(file_to_delete!=NULL)
        {
            if(prec_folder->file_tree==file_to_delete) //Casi file fratelli
            {
                if(file_to_delete->file_brother==NULL)
                {
                    prec_folder->file_tree=NULL;
                }
                else
                {
                    prec_folder->file_tree=file_to_delete->file_brother;
                }
            }
            
            else if(prec_folder->file_tree!=file_to_delete) //Casi directory figlie
            {
                if(file_to_delete->file_brother==NULL)
                {
                    prec_file->file_brother=NULL;
                }
                
                else
                {
                    prec_file->file_brother=file_to_delete->file_brother;
                }
            }
            
            free(file_to_delete);
            printf("ok\n");
        }
    }
    else printf("no\n");
    free(path_local2);
}
  /*
void delete_child(struct directory * father){
    
    struct directory * first=father->left_child;
    struct directory * current=first;
    struct directory * prec=current;
    
    while (current!=NULL)
    {
        if (current->left_child!=NULL) delete_child(current);
        prec=current;
        if(current->right_brother!=NULL) current=current->right_brother;
        free(prec);
    }
}*/


void delete_child(struct directory * directory)
{
    if(directory->left_child!=NULL)
    {
        delete_child(directory->left_child);
    }
    if(directory->right_brother!=NULL)
    {
        delete_child(directory->right_brother);
    }
    
    /*
    if(directory->file_tree!=NULL)
    {
        struct file * file=directory->file_tree;
        struct file * prec=file;
        
        while(file!=NULL);
        {
            prec=file;
            file=file->file_brother;
            free(prec);
        }
    }*/
    
    free(directory);

}


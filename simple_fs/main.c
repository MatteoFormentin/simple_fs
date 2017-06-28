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


//STRUTTURE DATI





int main(int argc, const char * argv[]) {
    
    //INIZIALIZZAZIONE STRUTTURE DATI
    
    
    
    
    
    //Lettura Comando, Percorso, Contenuto e Inserimento in Array Corrisponente
    char temp[50];
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
    
    
    //CREATE
    if(strcmp(command, "create")==0)
    {
        printf("comando: create\n");
        if(check_path_format(path)==1)
        {
            //Operazione Create
            printf("percorso ok\n");
        }
    }
    
    //CREATE_DIR
    else if(strcmp(command, "create_dir")==0)
    {
        printf("comando: create_dir");
        if(check_path_format(path)==1)
        {
            //Operazione create_dir
            printf("percorso ok");

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
                //eseguo write
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



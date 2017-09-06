//
//  main.c
//
//  simple_fs - Simple File System
//  Progetto API - Algoritmi e Strutture Dati 2017
//
//  Created by Matteo Formentin on 27/06/17.
//  Copyright © 2017 Matteo Formentin. All rights reserved.
//


/*                !!!BUG NOTI!!!
 *
 */

/*                !!!DA FARE!!!
 *  1-Max figli 255 e risorse nella stessa cartella 1024
 *  2-ordine lessicografico find
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_ALTEZZA 255
#define MAX_AMPIEZZA 1024
#define BUFFER_DIM 10000
#define CONTENT_DIM 1000
#define PERCORSO_N 700 //N massimo stringhe
#define PERCORSO_SIZE 30000 //Lunghezza massima stringa

//Prototipi
int check_path_format(char * path, char command[]);
int check_content_format(char content[]);

struct directory * go_to_path_directory(struct directory * current_path, char path_local[]);
struct directory * create_directory(struct directory * root, char path_local[]);


struct file * go_to_path_file(struct directory * current_path, char path_local[]);
struct file * create_file(struct directory * root, char path_local[]);
struct file * write_file(struct directory * root, char path_local[], char * content_local);
struct file * read_file(struct directory * root, char path_local[]);

int find(struct directory * current, char name[], char percorso[][PERCORSO_SIZE], char temp_percorso[]);
void delete(struct directory * root, char path_local[], int flag);
void delete_child(struct directory * directory);

//STRUTTURE DATI IMPORTANTE: INIZIALIZZARE A NULL I PUNTATORI SE NECESSARIO

//Directory

struct directory {
    char name[255];
    struct directory * left_child;
    struct directory * right_brother;
    struct file * file_tree;
    int n_file;
    int n_dir;
} directory;

struct directory * root;
struct directory * prec_folder;
struct directory * father_folder;
int altezza=0;

struct file * prec_file;

//File

struct file {
    char name[255];
    char content[255];
    struct file * file_brother;
} file;

//Comando, Percorso, Contenuto
char buffer[BUFFER_DIM];
char * command = NULL;
char * path = NULL;
char content[CONTENT_DIM];

int k;
int comp(const void * a, const void * b)
{
    return strcmp((char*)a, (char*)b);
}

int main(int argc, const char * argv[]) {
    
    //INIZIALIZZAZIONE STRUTTURE DATI
    root=(struct directory *)malloc(sizeof(directory));
    strcpy(root->name,"root");
    root->right_brother=NULL;
    root->left_child=NULL;
    root->file_tree=NULL;
    root->n_dir=0;
    root->n_file=0;
    
    
    //DEBUG ONLY
    /*
     create_directory(root, "/dir0rid");
     create_directory(root, "/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    
     create_file(root, "/dir0rid/dir0rid/dir0rid/file");
     create_file(root, "/dir0rid/dir0rid/dir0rid/file1");
     create_file(root, "/dir0rid/dir0rid/dir0rid/file2");
    
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_directory(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
     create_file(root, "/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/file");
    create_directory(root, "/dir1rid");
    create_directory(root, "/dir1rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid");
    create_file(root, "/dir1rid/dir0rid/dir0rid/file");
    create_file(root, "/dir1rid/dir0rid/dir0rid/file1");
    create_file(root, "/dir1rid/dir0rid/dir0rid/file2");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_directory(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid");
    create_file(root, "/dir1rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/dir0rid/file");
    
     printf("tutte create\n");
    */
    
    
    while (1) {
        
        // printf("\n\n\n\ninserire comando:\n "); //DEBUG ONLY
        
        
        //Acquisizione comando-percorso-contenuto
        
        fgets(buffer, BUFFER_DIM, stdin);
        buffer[strlen(buffer)-1]='\0';
        
        
        //!!!DOPO UN PO SI BLOCCA QUI
        
        //Split buffer
        command=strtok(buffer," \n");
        if(command!=NULL) command[strlen(command)]='\0';
        
        path=strtok(NULL," \n");
        if(path!=NULL) path[strlen(path)]='\0';
        
        memset(content, '\0', CONTENT_DIM);
        strcpy(content, "\0");
        char * temp;
        temp=strtok(NULL," \n");
        if(temp!=NULL)
        {
            strcpy(content, temp);
            
            while((temp=strtok(NULL, " \n"))!=NULL)
            {
                strcat(content, " ");
                strcat(content, temp);
            }
        }
        //if(content!=NULL) content[strlen(content)-1]='\0';
        //printf("%s", temp);
        //printf("\n%s\n", content);
        
        //Esecuzione del comando corretto
        
        //Controllo NULL ingresso
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
                if(check_content_format(content)!=0)
                {
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
                char percorso[PERCORSO_N][PERCORSO_SIZE];
                char temp_percorso[PERCORSO_SIZE];
               /* for(int i=0; i<PERCORSO_N; i++)
                {
                    strcpy(percorso[i], "\0");
                }*/
                k=0;
                if(find(root, path, percorso, temp_percorso)==0) printf("no\n");
                else
                {
                    qsort(percorso, k, sizeof(percorso[0]), comp);
                    for(int i=0; i<k; i++)
                    {
                        printf("ok %s\n",percorso[i]);
                    }
                }
            }
            else printf("no\n");
        }
        
        //EXIT
        else if(strcmp(command, "exit")==0)
        {
            return 0;
        }
        
        /*
         else if(strcmp(command, "vai")==0) //DEBUG ONLY
         {
         if(check_path_format(path, command)==1)
         {
         struct directory * temp_dir=go_to_path_directory(root, path);
         if(temp_dir!=NULL)
         printf("\ntrovato: %s", temp_dir->name);
         }
         }*/
        
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
    if(path==NULL) return -1;
    if((path[0]!='/') && strcmp(command, "find")!=0)
    {
        //printf("\nerrore nel formato del percorso!\n"); //DEBUG ONLY
        return -1;
    }
    return 1;
}

//Controlla se l'ingresso ha gli apici e li rimuove
int check_content_format(char content_local[])
{
    if(content_local==NULL)
    {
        return 0;
    }
    //controlla lunghezza array
    int last_element=(int)strlen(content_local);
    last_element--;
    if(last_element==0) return 0;
    //controlla gli apici
    if(content_local[0]!='"' || content_local==NULL || content_local[last_element]!='"')
    {
        // printf("\nerrore nel formato del contenuto!"); //DEBUG ONLY
        //if(content==NULL) printf("\ncontenuto null\n"); //DEBUG ONLY
        return 0;
    }
    else //rimuovi gli apici
    {
        char string_without_apices[last_element+1];
        int i=1;
        while(i<last_element)
        {
            string_without_apices[i-1]=content_local[i];
            i++;
        }
        string_without_apices[last_element-1]='\0';
        memset(content, '\0', 255);
        strcpy(content, string_without_apices);
        //printf("%s\n", string_without_apices);
    }
    return 1;
}

//Funzione per raggiungere una directory (current path deve essere inizializzato come root)

struct directory * go_to_path_directory(struct directory * current_path, char path_local[])
{
    
    prec_folder=current_path;
    current_path=current_path->left_child;
    altezza=1;
    if(current_path==NULL) //Albero vuoto
    {
        return NULL;
    }
    
    struct directory * first_level=current_path;
    
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
                //printf("non trovato1 "); //DEBUG ONLY
                prec_folder=first_level;
                return NULL;
            }
        }
        
        current_path_name=strtok(NULL,"/");//leggi il nome della cartella successiva nel percorso
        if(current_path_name!=NULL && current_path->left_child!=NULL)
        {
            first_level=current_path;
            prec_folder=current_path;
            current_path=current_path->left_child;
            altezza++;
        }
        else if(current_path_name!=NULL && current_path->left_child==NULL)
        {
            //printf("non trovato 2 "); //DEBUG ONLY
            prec_folder=first_level->left_child;
            return NULL;
        }
        else //Se non ci sono più cartelle nel nome percorso ho trovato la cartella
        {
            break;
        }
    }
    //printf("altezza: %d", altezza);
    father_folder=first_level;
    return current_path;
}


struct directory * create_directory(struct directory * root, char path_local[])
{
    struct directory * new_directory_path=NULL;
    struct directory * new_directory_father=NULL;
    struct directory * prec=NULL;
    char new_directory_name[strlen(path_local)+1];
    
    unsigned int last_path_before_new=(unsigned int)(strrchr(path_local, '/')-path_local); //Controllo se sono in root
    
    //Caso creazione non in root
    if (last_path_before_new!=0)
    {
        //Estrazione percorso dal parametro percorso
        char path_where_create_dir[strlen(path_local)+1];
        strncpy(path_where_create_dir,path_local,last_path_before_new);
        path_where_create_dir[last_path_before_new] = '\0';
        new_directory_path=go_to_path_directory(root, path_where_create_dir);
        new_directory_father=new_directory_path;

        if(altezza+1>MAX_ALTEZZA)
        {
            printf("no\n");
            return NULL; //Troppe directory nell'albero
        }
        
        if(new_directory_path==NULL)
        {
            //printf("\nPercorso creazione non trovato, return "); //DEBUG ONLY
            printf("no\n");
            //printf("\n"); //DEBUG ONLY
            return NULL; //Percorso creazione non trovato
        }
        
        //Estrazione nome cratella dal parametro percorso
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
        new_directory_father=new_directory_path;
        int i=0;
        for(i=0; i<strlen(path_local); i++)
        {
            new_directory_name[i]=path_local[i+1];
        }
        new_directory_name[i+1]='\0';
    }
    
    if(strlen(new_directory_name)>255)
    {
        printf("no\n");
        return NULL;
    }
    
    if((new_directory_father->n_dir+new_directory_father->n_file)+1>MAX_AMPIEZZA)
    {
        printf("no\n"); //Troppe risorse nella stessa cartella
        return NULL;
    }
    
    
    //Creazione in memoria della cartella (non ancora nell'albero)
    struct directory * new_directory=malloc(sizeof(struct directory));
    new_directory->left_child=NULL;
    new_directory->right_brother=NULL;
    new_directory->file_tree=NULL;
    new_directory->n_dir=0;
    new_directory->n_file=0;
    strcpy(new_directory->name, "\0");
    strcpy(new_directory->name, new_directory_name);
    
    /* //DEBUG ONLY
     if (strcmp(new_directory->name,"")==0) {
     printf(" errore nella copia del nome");
     }*/
    
    //Caso 1: nessun figlio sinistro esistente
    if (new_directory_path->left_child==NULL)
    {
        new_directory_path->left_child=new_directory;
    }
    
    //Caso 2: figlio sinistro esistente
    else
    {
        prec=new_directory_path;
        new_directory_path=new_directory_path->left_child;
        
        if(strcmp(new_directory_path->name, new_directory_name)==0) //Controllo se esiste una directory con lo stesso nome come primo figlio
        {
            //printf("directory già esistente, return\n"); //DEBUG ONLY
            printf("no\n");
            free(new_directory);
            return NULL;
        }
        
        
        while (strcmp(new_directory_path->name, new_directory_name)<=0) //Caso 2: esistono dei figli->scorri fino alla prima posizione libera a destra
        {

            if(strcmp(new_directory_path->name, new_directory_name)==0) //Directory con lo stesso nome come figli successivi
            {
                //printf("directory già esistente, return\n"); //DEBUG ONLY
                printf("no\n");
                free(new_directory);
                return NULL;
            }
            
            if(new_directory_path->right_brother!=NULL)
            {
                prec=new_directory_path;
                new_directory_path=new_directory_path->right_brother;
            }
            else break;
        }
        
        /*
        if(strcmp(new_directory_path->name, new_directory_name)==0) //Directory con lo stesso nome come ultimo figlio
        {
            //printf("directory già esistente, return\n"); //DEBUG ONLY
            printf("no\n");
            free(new_directory);
            return NULL;
        }*/
        if(prec->left_child==new_directory_path)
        {
            if(strcmp(new_directory_path->name, new_directory_name)>0)
            {
                prec->left_child=new_directory;
                new_directory->right_brother=new_directory_path;
            }
            else
            {
                new_directory_path->right_brother=new_directory;
            }
        }
        else if(strcmp(new_directory_path->name, new_directory_name)>0)
        {
            new_directory->right_brother=new_directory_path;
            prec->right_brother=new_directory;
        }
        else new_directory_path->right_brother=new_directory;
        
        
        
        /*
        if(new_directory_path->right_brother->right_brother!=NULL)
        {
            new_directory->right_brother=new_directory_path->right_brother->right_brother;
        }
        
        new_directory_path->right_brother=new_directory;*/
    }
    
    printf("ok\n");
    new_directory_father->n_dir++;
    return new_directory;
}

struct file * create_file(struct directory * root, char path_local[])
{
    char new_file_name[1000];
    
    struct directory * container_directory_path=NULL;
    
    unsigned int last_path_before_new=(unsigned int)(strrchr(path_local, '/')-path_local); //Controllo se sono in root
    
    //Caso creazione non in root
    if (last_path_before_new!=0)
    {
        
        //Estrazione percorso dal parametro percorso
        char path_where_create_file[strlen(path_local)+1];
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
        int i;
        for(i=0; i<strlen(path_local); i++)
        {
            new_file_name[i]=path_local[i+1];
        }
        new_file_name[i+1]='\0';
    }
    
    
    if(strlen(new_file_name)>255)
    {
        printf("no\n");
        return NULL;
    }
    
    if((container_directory_path->n_dir+container_directory_path->n_file)+1>MAX_AMPIEZZA)
    {
        printf("no\n"); //Troppe risorse nella stessa cartella
        return NULL;
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
        //ampiezza++;
        struct file * file_prec=container_directory_path->file_tree;
        
        if(strcmp(new_file->name, file_prec->name)==0) //Controllo se esiste un file con lo stesso nome come primo figlio
        {
            //printf("directory già esistente, return\n"); //DEBUG ONLY
            printf("no\n");
            free(new_file);
            return NULL;
        }
        
        
        while (file_prec->file_brother!=NULL) {
            if(strcmp(new_file->name, file_prec->name)==0) //Controllo se esiste un file con lo stesso nome come altro figlio
            {
                //printf("directory già esistente, return\n"); //DEBUG ONLY
                printf("no\n");
                free(new_file);
                return NULL;
            }
            file_prec=file_prec->file_brother;
         /*   ampiezza++;
            printf("\nampiezza dir+file: %d\n", ampiezza);
            
            if(ampiezza>MAX_AMPIEZZA-1)
            {
                printf("no\n");
                return NULL;
            }*/
        }
        
        if(strcmp(new_file->name, file_prec->name)==0) //Controllo se esiste un file con lo stesso nome come ultimo figlio
        {
            //printf("directory già esistente, return\n"); //DEBUG ONLY
            printf("no\n");
            free(new_file);
            return NULL;
        }
        
        file_prec->file_brother=new_file;
    }
    container_directory_path->n_file++;
    printf("ok\n");
    return new_file;
}


struct file * go_to_path_file(struct directory * current_path, char path_local[])
{
    char file_name[strlen(path_local)+1];
    struct directory * container_directory_path=NULL;
    
    unsigned int last_path_before_new=(unsigned int)(strrchr(path_local, '/')-path_local); //Controllo se sono in root
    
    //Caso file non in root
    if (last_path_before_new!=0)
    {
        //Estrazione percorso dal parametro percorso
        char container_directory_name[strlen(path_local)+1];
        strncpy(container_directory_name,path_local,last_path_before_new);
        container_directory_name[last_path_before_new] = '\0';
        container_directory_path=go_to_path_directory(root, container_directory_name);
        
        if(container_directory_path==NULL)
        {
            //printf("\nPercorso cartella container non trovato, return\n");
            return NULL; //Percorso creazione non trovato
        }
        
        //Estrazione nome file dal parametro percorso
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
        prec_folder=container_directory_path;
        return current_file;
    }
    
    while (current_file->file_brother!=NULL) {
        if(strcmp(current_file->name, file_name)==0) //Controllo se esiste una file con lo stesso nome come altro figlio
        {
            //printf("file trovato\n"); //DEBUG ONLY
            prec_folder=container_directory_path;
            return current_file;
        }
        prec_file=current_file;
        current_file=current_file->file_brother;
    }
    
    if(strcmp(current_file->name, file_name)==0) //Controllo se esiste una file con lo stesso nome come ultimo figlio
    {
        //printf("file trovato\n"); //DEBUG ONLY
        prec_folder=container_directory_path;
        return current_file;
    }
    
    //printf("file NON trovato\n"); //DEBUG ONLY
    return NULL;
    
}


struct file * write_file(struct directory * root, char path_local[], char * content_local)
{
    if(strlen(content_local)>255)
    {
        printf("no\n");
        return NULL;
    }
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
        strcpy(file_to_write->content, "\0");
        strcpy(file_to_write->content, content_local);
        printf("ok %d\n", (int)strlen(content_local));
        //printf(" %s \n", file_to_write->content); //DEBUG ONLY
        return file_to_write;
    }
    
}


struct file * read_file(struct directory * root, char path_local[])
{
    struct file * file_to_read=go_to_path_file(root, path_local);
    if(file_to_read==NULL)
    {
        printf("no\n");
        return NULL; //Percorso file non trovato
    }
    else
    {
        if(strcmp(file_to_read->content,"")==0) printf("contenuto \n");
        else printf("contenuto %s\n", file_to_read->content);
        return file_to_read;
    }
}



int find(struct directory * current_directory, char name[], char percorso[][PERCORSO_SIZE], char temp_percorso[])
{
    int flag_trovato=0;

    //Prima in profondità
    if(current_directory->left_child!=NULL)
    {
        if(current_directory!=root)
        {
            if(strcmp(temp_percorso, "/")!=0) strcat(temp_percorso,"/");
            strcat(temp_percorso, current_directory->name);
            
        }
        
        flag_trovato=find(current_directory->left_child, name, percorso,temp_percorso);
        
        for(int i=((int)strlen(temp_percorso)-(int)strlen(current_directory->name))-1;i<(int)strlen(temp_percorso);i++) temp_percorso[i]='\0';
    }

    //Se non ci sono figli
    if(strcmp(current_directory->name, name)==0)
    {
        sprintf(percorso[k],"%s/%s", temp_percorso,current_directory->name);
        k++;
        flag_trovato=1;
    }
    
    //Cerca tra i file
    if(current_directory->file_tree!=NULL)
    {
        struct file * current_file=current_directory->file_tree;
        while (current_file!=NULL)
        {
            if(strcmp(current_file->name, name)==0)
            {
                if(current_directory==root) sprintf(percorso[k],"/%s", current_file->name);
                else sprintf(percorso[k],"%s/%s/%s", temp_percorso,current_directory->name,current_file->name);
                flag_trovato=1;
                k++;
            }
            current_file=current_file->file_brother;
        }
        
    }
    
    //Vai al fratello
    if(current_directory->right_brother!=NULL)
    {
        flag_trovato=find(current_directory->right_brother, name, percorso, temp_percorso);
    }
   
    
    if(flag_trovato==1)return 1;
    else return 0;
}


void delete(struct directory * root, char path_local[], int flag)
{
    prec_folder=NULL;
    prec_file=NULL;
    char path_local2[strlen(path_local)+1];
    strcpy(path_local2,path_local);
    struct directory * directory_to_delete=go_to_path_directory(root, path_local);
    
    //Delete directory
    if(directory_to_delete!=NULL) //Necessario per escludere il ricorsivo
    {
        if((directory_to_delete->left_child!=NULL || directory_to_delete->file_tree!=NULL) && flag==0 )
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
        father_folder->n_dir--;
        printf("ok\n");
        return;
    }
    
    //Delete file
    else if(prec_folder!=NULL)
    {
        // if(prec_folder!=root) prec_folder=prec_folder->left_child;
        if(prec_folder->file_tree!=NULL)
        {
            
            struct file * file_to_delete=prec_folder->file_tree;
            
            char * p=strrchr(path_local2, '/');
            p++;
            char file_name[255];
            int i=0;
            while(*p!='\0')
            {
                file_name[i]=*p;
                p++;
                i++;
            }
            file_name[i]='\0';
            
            /*
             printf("\nprec dir: %s", prec_folder->name);
             
             printf("\n\nfile: %s\n", file_name);
             */
            int trovato=0;
            if(strcmp(file_to_delete->name, file_name)==0) //Controllo se esiste un file con lo stesso nome come primo figlio
            {
                trovato=1;
            }
            else
            {
                while (file_to_delete->file_brother!=NULL)
                {
                    if(strcmp(file_to_delete->name, file_name)==0) //Controllo se esiste una file con lo stesso nome come altro figlio
                    {
                        trovato=1;
                        break;
                    }
                    prec_file=file_to_delete;
                    file_to_delete=file_to_delete->file_brother;
                }
                
                if(strcmp(file_to_delete->name, file_name)==0) //Controllo se esiste una file con lo stesso nome come ultimo figlio
                {
                    trovato=1;
                }
            }
            
            if(trovato==1)
            {
                if(file_to_delete!=NULL)
                {
                    if(prec_folder->file_tree==file_to_delete) //Casi primo file
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
                    
                    else if(prec_folder->file_tree!=file_to_delete) //Casi file intermedio
                    {
                        if(file_to_delete->file_brother==NULL) //Caso ultimo file
                        {
                            prec_file->file_brother=NULL;
                        }
                        
                        else
                        {
                            prec_file->file_brother=file_to_delete->file_brother;
                        }
                    }
                    
                    //free(file_to_delete->name);
                    memset(file_to_delete->content, '\0', 255);
                    strcpy(file_to_delete->content, "\0");
                    free(file_to_delete);
                    prec_folder->n_file--;
                    printf("ok\n");
                    return;
                }
            }
        }
    }
    
    printf("no\n");
}


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
    
    
    if(directory->file_tree!=NULL)
    {
        struct file * file=directory->file_tree;
        struct file * prec=file;
        
        while(file!=NULL)
        {
            prec=file;
            file=file->file_brother;
            free(prec);
        }
    }
    
    free(directory);
    
}


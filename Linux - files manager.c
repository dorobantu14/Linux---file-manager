#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LINE_SIZE 300

struct Dir;
struct File;


typedef struct Dir {
    char *name;
    struct Dir *parent;
    struct File *head_children_files;
    struct Dir *head_childrens_dirs;
    struct Dir *next;
} Dir;

typedef struct File {
    char *name;
    struct Dir *parent;
    struct File *next;
} File;


void touch(Dir *parent, char *name) {
    File *tmp = parent->head_children_files;
    File *newfile = (File *) malloc(sizeof(File));
    newfile->parent = parent;
    newfile->next = NULL;
    newfile->name = (char *) malloc((strlen(name) + 1) * sizeof(char));
    strcpy(newfile->name, name);

    if (tmp == NULL) {
        parent->head_children_files = newfile;
        return;
    }

    if (tmp->next == NULL) {
        if (strcmp(tmp->name, newfile->name) == 0) {
            printf("File already exists\n");
            free(newfile->name);
            free(newfile);
            return;
        }
        tmp->next = newfile;
        return;
    }
    while (tmp->next != NULL) {
        if (strcmp(tmp->name, newfile->name) == 0) {
            printf("File already exists\n");
            return;
        }
        tmp = tmp->next;
        if (strcmp(tmp->name, newfile->name) == 0) {
            printf("File already exists\n");
            return;
        }
    }
    tmp->next = newfile;
}


void mkdir(Dir *parent, char *name) {
    Dir *tmp = parent->head_childrens_dirs;
    Dir *newdir = (Dir *) malloc(sizeof(Dir));
    newdir->name = (char *) malloc((strlen(name) + 1) * sizeof(char));
    newdir->head_children_files = NULL;
    newdir->head_childrens_dirs = NULL;
    newdir->parent = parent;
    strcpy(newdir->name, name);
    newdir->next = NULL;

    if (tmp == NULL) {
        parent->head_childrens_dirs = newdir;    
        return;
    }

    if (tmp->next == NULL) {
        if (strcmp(tmp->name, name) == 0) {
            printf("Directory already exists\n");
            free(newdir->name);
            free(newdir);
            return;
        }
        tmp->next = newdir;
        return;
    }

    while (tmp->next != NULL) {
        if (strcmp(tmp->name, name) == 0) {
            printf("Directory already exists\n");
            return;
        }
        tmp = tmp->next;
    }
    if (strcmp(tmp->name, name) == 0) {
            printf("Directory already exists\n");
            return;
        }

    tmp->next = newdir;

}

void ls(Dir *parent) {
    Dir *directories = parent->head_childrens_dirs;
    File *files = parent->head_children_files;

    while (directories) {
        printf("%s\n", directories->name);
        directories = directories->next;
    }

    while (files) {
        printf("%s\n", files->name);
        files = files->next;
    }

}

void rm(Dir *parent, char *name) {
    File *tmp = parent->head_children_files;

    if (tmp == NULL) {
        printf("Could not find the file\n");      
        return;
    }

    if (strcmp(tmp->name, name) == 0) {
        parent->head_children_files = parent->head_children_files->next;
        free(tmp->name);
        free(tmp);
        return;
    } else {
        File *current = parent->head_children_files;
        while (current->next != NULL) {
            if (strcmp(current->next->name, name) == 0) {
                tmp = current->next;
                if (current->next->next == NULL) {
                    current->next = NULL;
                    free(tmp->name);
                    free(tmp);
                    return;
                }
                current->next = current->next->next;
                free(tmp->name);
                free(tmp);
                return;
            }
            current = current->next;
        }
        printf("Could not find the file\n");
    }
}

void removeFiles(Dir *target) {
    File *files = target->head_children_files;

    if (files == NULL)
    {
        return;
    }
    
    if (files->next == NULL)
    {
        free(files->name);
        free(files);
        files = NULL;
        return;
    } 
    
    while (files->next != NULL)
    {
        File *tmp = files;
        files = files->next;
        free(tmp->name);
        free(tmp);
        
        if (files->next == NULL)
        {
            free(files->name);
            free(files);
            files = NULL;
            return;
        }
    }       
}

void removeDirs(Dir *target) {
    Dir *dirs = target->head_childrens_dirs;

    if (dirs == NULL)
    {
        return;
    }
    
    if (dirs->next == NULL)
        {
            free(dirs->name);
            free(dirs);
            return;
        } 
    else 
    {
        while (dirs->next != NULL)
        {
            Dir *tmp = dirs;
            dirs = dirs->next;
            free(tmp->name);
            free(tmp);
            
            if (dirs->next == NULL)
            {
                free(dirs->name);
                free(dirs);
                return;
            }
        }
    }       
}


void removeAll(Dir *target) {
    Dir *directories = target->head_childrens_dirs;
    File *files = target->head_children_files;

    if (files != NULL)
    {
        removeFiles(target);
        files = NULL;
    }
    else
    {
        if (directories == NULL)
        {
            return;
        }

        if (directories->next == NULL)
        {
            if (directories->head_childrens_dirs)
            {
                removeAll(directories);
            }

            if (directories->head_children_files)
            {
                removeFiles(directories);
            }
            
            Dir *tmp = directories;
            free(tmp->name);
            free(tmp);       
            tmp = NULL; 
           return;
        }

        else
        {
            Dir *tmp2 = directories;
            while (tmp2->next)
            {
                if (tmp2->head_children_files)
                {
                    removeFiles(tmp2);
                }
                
                if (tmp2->head_childrens_dirs)
                {
                    removeAll(tmp2);
                }

                tmp2 = tmp2->next;

                if (tmp2->next == NULL)
                {
                    if (tmp2->head_children_files)
                    {
                        removeFiles(tmp2);
                    }
                
                    if (tmp2->head_childrens_dirs)
                    {
                        removeAll(tmp2);
                    }
                }
                       
            }
            
        }
       
    }

    if (directories)
    {
        removeDirs(target);
    }

    if (files)
    {
        removeFiles(target);
    }
    
}

void rmdir(Dir *parent, char *name) {
    Dir *tmp = parent->head_childrens_dirs;

    if (tmp == NULL) {
        printf("Could not find the dir\n");
        return;
    }

    if (strcmp(tmp->name, name) == 0) {   
        parent->head_childrens_dirs = parent->head_childrens_dirs->next;
        removeAll(tmp);
        free(tmp->name);
        free(tmp);
        return;
    } else {
        Dir *current = parent->head_childrens_dirs;
        while (current->next != NULL) {
            if (strcmp(current->next->name, name) == 0) {
                tmp = current->next;
                if (current->next->next == NULL) {
                    current->next = NULL;
                    removeAll(tmp);
                    free(tmp->name);
                    free(tmp);
                    return;
                }
                current->next = current->next->next;
                removeAll(tmp);
                free(tmp->name);
                free(tmp);
                return;
            }
            current = current->next;
            if (current->next == NULL)
            {
                if (strcmp(current->name, name) == 0)
                {
                    removeAll(current);
                    free(current->name);
                    free(current);
                }
                else
                {
                    printf("Could not find the dir\n");
                    return;
                }               
                
            }
            
        }

    }
}

void cd(Dir **target, char *name) {
    Dir *curr_directory = (*target)->head_childrens_dirs;

    if (strcmp(name, "..") == 0) {
        if ((*target)->parent != NULL)
            (*target) = (*target)->parent;
        return;
    }

    if (curr_directory == NULL) {
        printf("No directories found!\n");
        return;
    }

    while (curr_directory->next == NULL) {
        if (strcmp(curr_directory->name, name) == 0) {
            (*target) = curr_directory;
        } else
            printf("No directories found!\n");
        return;
    }

    while (curr_directory->next != NULL) {
        if (strcmp(curr_directory->name, name) == 0) {
            (*target) = curr_directory;
        } else {
            printf("No directories found!\n");
            return;
        }
        curr_directory = curr_directory->next;
    }
}

char *pwd(Dir *target) {
    Dir *parent = target->parent;
    char *path = (char *)malloc(MAX_INPUT_LINE_SIZE);
    strcpy(path, target->name);
    strcat(path, "/");
    while (parent != NULL) {
        strcat(path, parent->name);
        strcat(path, "/");
        parent = parent->parent;

    }

    char *token = strtok(path, "/");
    char **array = (char **) malloc(MAX_INPUT_LINE_SIZE);
    char *finalPath = (char *) malloc(100 * sizeof(char));
    int i = 0;
    while (token != NULL) {
        array[i++] = token;
        token = strtok(NULL, "/");
    }

    strcpy(finalPath, "/");

    for (int j = i - 1; j >= 0; j--) {
        if (j != 0) {
            strcat(finalPath, array[j]);
            strcat(finalPath, "/");
        } else {
            strcat(finalPath, array[j]);
        }
    }
    free(path);
    free(array);
    return finalPath;
}

void stop(Dir *target) {

    removeAll(target);
    free(target->name);
    free(target);       

    exit(0);
}

void tree(Dir *target, int level) {
    Dir *directories = target->head_childrens_dirs;
    File *files = target->head_children_files;

    if (directories->next == NULL) {
        printf("%s\n", directories->name);
        if (files->next == NULL) {
            printf("%s\n", files->name);
            return;
        }
    }

    return;
}

void mv(Dir *parent, char *oldname, char *newname) {
    Dir *directories = parent->head_childrens_dirs;
    File *files = parent->head_children_files;
    Dir *newDir = (Dir *) malloc(sizeof(Dir));
    File *newFile = (File *) malloc(sizeof(File));
    newDir->name = (char *) malloc((strlen(newname) + 1) * sizeof(char));
    strcpy(newDir->name, newname);
    newDir->next = NULL;
    newDir->parent = parent;
    newDir->head_children_files = NULL;
    newDir->head_childrens_dirs = NULL;
    newFile->name = (char *) malloc((strlen(newname) + 1) * sizeof(char));
    strcpy(newFile->name, newname);
    newFile->next = NULL;
    newFile->parent = parent;

    if (directories == NULL) {
        goto file;
    }

    int ok1 = 0;   // nu exista directorul old name
    int ok2 = 0;   // exista directorul new name
    if (directories->next == NULL) {
        if (strcmp(directories->name, oldname) == 0) {
            ok1 = 1;
        } else {                        //cazul in care am doar
            ok1 = 0;                    //un director
        }
        if (strcmp(directories->name, newname) == 0) {
            ok2 = 0;
        } else {
            ok2 = 1;
        }
    }

    int ok21 = 0;   // nu exista new name in fisiere
    File *fil2 = parent->head_children_files;
    if (ok1 == 1 && ok2 == 1 && fil2 != NULL) {
        while (fil2->next != NULL) {
            if (strcmp(newname, fil2->name) == 0) {
                ok21 = 1;
                printf("File/Director already exists\n");
                free(newDir->name);
                free(newDir);
                free(newFile->name);
                free(newFile);
                return;
            }
            fil2 = fil2->next;
        }
        if (strcmp(newname, fil2->name) == 0) {
            ok21 = 1;
            printf("File/Director already exists\n");
            free(newDir->name);
            free(newDir);
            free(newFile->name);
            free(newFile);
    
            return;
        }
    }


    if (ok1 == 1 && ok2 == 1 && ok21 == 0 && directories->next == NULL) {
        Dir *d1 = parent->head_childrens_dirs;
        rmdir(parent, d1->name);
        parent->head_childrens_dirs = newDir;
        free(newFile->name);
        free(newFile);
        return;
    }

    if (ok1 == 1 && ok2 == 0 && directories->next == NULL) {
        printf("File/Director already exists\n");
        return;
    }


    int ok3 = 0;        // nu exista old name in directoare 
    int ok4 = 0;        // exista new name in directoare
    Dir *d5 = parent->head_childrens_dirs;
    while (d5->next != NULL) {
        if (strcmp(d5->name, oldname) == 0) {
            ok3 = 1;
        } else {                               //verific daca vechiul
            ok3 = 0;                           // nume se afla in list
        }
        d5 = d5->next;
    }


    Dir *d2 = parent->head_childrens_dirs;
    while (d2->next != NULL) {
        if (strcmp(d2->name, newname) == 0) {
            ok4 = 0;
        }                                   //verific daca noul nume
        else {                              //se afla in lista 
            ok4 = 1;
        }
        d2 = d2->next;
    }


    if (d2->next == NULL) {
        if (strcmp(d2->name, newname) == 0) {
            ok4 = 0;
        }
        else
        {
            ok4 = 1;
        }
        
    }

    int ok20 = 0;           // new name nu se afla in fisiere          
    File *fil1 = parent->head_children_files;
    if (ok3 == 1 && ok4 == 1 && fil1 != NULL) {
        while (fil1->next != NULL) {
            if (strcmp(newname, fil1->name) == 0) {
                ok20 = 1;
                printf("File/Director already exists\n");
                free(newDir->name);
                free(newDir);
                free(newFile->name);
                free(newFile);
                return;                                             // verific daca new name se afla in fisiere
            }
            fil1 = fil1->next;
        }
        if (strcmp(newname, fil1->name) == 0) {
            ok20 = 1;
            printf("File/Director already exists\n");
            free(newDir->name);
            free(newDir);
            free(newFile->name);
            free(newFile);
            return;
        }
    }

    Dir *d3 = parent->head_childrens_dirs;
    if (ok3 == 1 && ok4 == 1 && ok20 == 0) {
        while (d3->next != NULL) {
            d3 = d3->next;
        }
        d3->next = newDir;

        Dir *d = parent->head_childrens_dirs;
        while (d->next != NULL)
        {      
            if (strcmp(d->name, oldname) == 0) {
                rmdir(parent, d->name);
                free(newFile->name);
                free(newFile);
                return;
            }
            d = d->next;       
        }        

    }

    if (ok3 == 1 && ok4 == 0 && directories->next != NULL) {
        printf("File/Director already exists\n");
        free(newDir->name);
        free(newDir);
        free(newFile->name);
        free(newFile);
        return;
    }


    int ok7 = 0;        // old name nu se afla in fisiere
    int ok8 = 0;        // new name se afla in fisiere
    int ok9 = 0;        // old name nu se afla in fisiere
    int ok10 = 0;       // new name se afla in fisiere
    file:
        if (files == NULL) {
            if (ok1 == 0 && directories->next == NULL)
            {
                printf("File/Director not found\n");
                free(newDir->name);
                free(newDir);
                free(newFile->name);
                free(newFile);
                return;
            }
            if (ok3 == 0 && directories->next != NULL)
            {
                printf("File/Director not found\n");
                return;
            }
            return;
        
        }


        if (files->next == NULL) {
            if (strcmp(files->name, oldname) == 0) {
                ok7 = 1;
            } else {                        //cazul in care am doar
                ok7 = 0;                    //un director
            }
            if (strcmp(files->name, newname) == 0) {
                ok8 = 0;
            } else {
                ok8 = 1;
            }
        }

        int ok23 = 0;               // new name nu se afla in directoare
        Dir *dir1 = parent->head_childrens_dirs;
        if (ok7 == 1 && ok8 == 1 && dir1 != NULL) {
            while (directories->next != NULL) {
                if (strcmp(newname, dir1->name) == 0) {
                    ok23 = 1;
                    printf("File/Director already exists\n");
            
                    return;
                }
                dir1 = dir1->next;
            }
            if (strcmp(newname, dir1->name) == 0) {
                ok23 = 1;
                printf("File/Director already exists\n");
                
                return;
            }
        }


        if (ok7 == 1 && ok8 == 1 && ok23 == 0 && files->next == NULL) {
            File *f1 = parent->head_children_files;
            rm(parent, f1->name);
            parent->head_children_files = newFile;       
            free(newDir->name);
            free(newDir);
            return;
        }

        if (ok7 == 1 && ok8 == 0 && files->next == NULL) {
            printf("File/Director already exists\n");
            
            return;
        }

        File *f5 = parent->head_children_files;
        while (f5->next != NULL) {
            if (strcmp(f5->name, oldname) == 0) {
                ok9 = 1;
            } else {                               //verific daca vechiul
                ok9 = 0;                           // nume se afla in lista
            }
            f5 = f5->next;
        }

        File *f2 = parent->head_children_files;
        while (f2->next != NULL) {
            if (strcmp(f2->name, newname) == 0) {
                ok10 = 0;
            }                                   //verific daca noul nume
            else {                              //se afla in lista
                ok10 = 1;
            }
            f2 = f2->next;
        }

        if (f2->next == NULL) {
            if (strcmp(f2->name, newname) == 0) {
                ok10 = 0;
            }
        }

        int ok22 = 0;           // new name nu se afla in directoare
        Dir *dir2 = parent->head_childrens_dirs;
        if (ok9 == 1 && ok10 == 1 && dir2 != NULL) {
            while (dir2->next != NULL) {
                if (strcmp(newname, dir2->name) == 0) {
                    ok22 = 1;
                    printf("File/Director already exists\n");
        
                    return;
                }
                dir2 = dir2->next;
            }
            if (strcmp(newname, dir2->name) == 0) {
                ok22 = 1;
                printf("File/Director already exists\n");
                free(newDir->name);
                free(newDir);
                free(newFile->name);
                free(newFile);
                return;
            }
        }


        File *f3 = parent->head_children_files;
        if (ok9 == 1 && ok10 == 1 && ok22 == 0) {
            File *f = parent->head_children_files;
            while (f->next != NULL)
            {
                f = f->next;
            }
            f->next = newFile;
        
            File *f6 = parent->head_children_files;
            while (f3->next != NULL) {
                if (strcmp(f3->name, oldname) == 0) {
                    rm(parent, f3->name);
                    free(newDir->name);
                    free(newDir);
                    return;
                }
                f3 = f3->next;
            }
        }

        if (ok9 == 1 && ok10 == 0 && files->next != NULL) {
                printf("File/Director already exists\n");
                free(newDir->name);
                free(newDir);
                free(newFile->name);
                free(newFile);
                return;
        }


    if (directories == NULL) {
        if (ok7 == 0 && files->next == NULL)
            printf("File/Director not found\n");
        
            return;

        if (ok9 == 0 && files->next != NULL)
            printf("File/Director not found\n");
            free(newDir->name);
            free(newDir);
            free(newFile->name);
            free(newFile);
            return;
    }


    if (ok1 == 0 && directories->next == NULL && ok7 == 0  || ok1 == 0 && ok7 == 0 && files->next == NULL) {
        printf("File/Director not found\n");

        return;
    }

    if (ok3 == 0 && directories->next != NULL && ok9 == 0 || ok9 == 0 && ok3 == 0 && files->next != NULL) {
        printf("File/Director not found\n");

        return;
    }

}

int main() {
    Dir *home = (Dir *) malloc(sizeof(Dir));
    home->parent = NULL;
    home->head_childrens_dirs = NULL;
    home->head_children_files = NULL;
    home->name = (char *) malloc(50 * sizeof(char));
    strcpy(home->name, "home");
    char *comanda = (char *) malloc(MAX_INPUT_LINE_SIZE * sizeof(char));
    gets(comanda);
    char *sir1;
    char *sir2;
    char *sir3;
    char *path;
    Dir *current = home;

    if (comanda != NULL) {
        sir1 = strtok(comanda, " ");
        sir2 = strtok(NULL, " ");
        sir3 = strtok(NULL, " ");
    }

    do {
        if (sir1) {
            if (strcmp(comanda, "ls") == 0) {
                ls(current);
            }

            if (strcmp(comanda, "pwd") == 0) {
                path = pwd(current);
                printf("%s\n", path);
                free(path);
            }

            if (strcmp(comanda, "tree") == 0) {
                tree(home, 0);
            }
            
            if (strcmp(sir1, "stop") == 0) {
                free(sir1);
                free(sir2);
                free(sir3);
                stop(home);
            }

            if (sir2) {

                if (strcmp(sir1, "touch") == 0) {
                    touch(current, sir2);
                }

                if (strcmp(sir1, "mkdir") == 0) {
                    mkdir(current, sir2);
                }

                if (strcmp(sir1, "rm") == 0) {
                    rm(current, sir2);
                }

                if (strcmp(sir1, "rmdir") == 0) {
                    rmdir(current, sir2);

                }

                if (strcmp(sir1, "cd") == 0) {
                    cd(&current, sir2);
                }

                if (sir3) {
                    if (strcmp(sir1, "mv") == 0) {
                        mv(current, sir2, sir3);
                    }
                }
            }
        }
        
        gets(comanda);
        sir1 = strtok(comanda, " ");
        sir2 = strtok(NULL, " ");
        sir3 = strtok(NULL, " ");

    } while (comanda);

    return 0;
}
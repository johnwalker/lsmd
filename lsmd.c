#include <argp.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>

#include <vlc/vlc.h>

#include "arguments.h"
#include "node.h"
#include "pretty.h"

const char *lsmd_version = "lsmd 0.1.0";
const char *lsmd_bugs    = "http://github.com/johnwalker/lsmd";


/* Return 0 if there is a file at the given path. Return 1 if it's a 
   directory.  */
int is_file(char* path) {
        struct stat s;
        if (stat(path,&s) != 0) {
                perror("");
                return -1;
        }
        if( s.st_mode & S_IFREG )
        {
                return 0;
        }
        return 1;
}

/* Given two strings s1 and s2, concatenate them both into concat. */
int concat_paths(char** concat, char* s1, size_t s1_len, char* s2, size_t s2_len) {
        *concat = malloc(s1_len + s2_len + 2);

        if(*concat == NULL) {
                return -1;
        }

        memcpy(*concat,
               s1,
               s1_len);

        (*concat)[s1_len] = '/';

        memcpy(*concat + s1_len + 1,
               s2,
               s2_len + 1);

        return 0;
}

/* Set filenames to a list of files in the given directory. Ignores
   files that are directories. */
int list_filenames(Node** filenames, char* directory)
{
        struct dirent *ent;
        DIR *dir = opendir(directory);
        if(dir == NULL) {
                perror ("");
                return -1;
        }

        Node* curr;
        size_t name_length;
        size_t directory_length = strlen(directory);
        ent = readdir(dir);

        if (ent != NULL) {
                *filenames = malloc(sizeof(**filenames));
                curr = *filenames;
                (*filenames)->next = NULL;
        }
        char* tmp = NULL;
        Node* tmp_node = NULL;
        int err = 0;
        while (ent != NULL)
        {
                name_length = strlen(ent->d_name);
                err = concat_paths(&tmp, directory, directory_length, ent->d_name, name_length);
                if (err != 0) {
                        perror("");
                        exit(-1);
                }

                if (is_file(tmp) != 0) {
                        free(tmp);
                        ent = readdir(dir);
                        continue;
                }

                curr->data = malloc(name_length + 1);
                memcpy(curr->data, ent->d_name, name_length + 1);

                free(tmp);
                ent = readdir(dir);
                if (ent != NULL)
                {
                        tmp_node = curr;
                        curr = malloc(sizeof(*curr->next));
                        curr->next = tmp_node;
                }
                else
                {
                        break;
                }

        }
        *filenames = curr;
        closedir(dir);
        return 0;
}

int handle_directory(char* directory)
{
        Node* filenames = NULL;

        list_filenames(&filenames, directory);

        Node* head = filenames;
        char *full_path = NULL;
        size_t filename_length = 0;
        size_t directory_length = strlen(directory);
        int err = 0;

        libvlc_media_t *m = NULL;
        libvlc_instance_t *inst;
        int64_t duration = 0;


        inst = libvlc_new(0, NULL);
        while (head != NULL)
        {

                filename_length = strlen(head->data);
                err = concat_paths(&full_path, directory, directory_length, head->data, filename_length);

                if (err != 0)
                {
                        perror("");
                        exit(-1);
                }

                m = libvlc_media_new_path(inst, full_path);
                libvlc_media_parse(m);
                duration = libvlc_media_get_duration(m);
                if (duration != 0)
                        print_minutes_seconds(head->data, duration);
                head = head->next;
                free(full_path);
        }

        return 0;
}

/* Given the path of a media file, print its duration in minutes and
   seconds to STDOUT.

   handle_file(PATH_TO_FILE);
   ---

   FILENAME                 MINUTES:SECONDS */
int handle_file(char* filepath)
{
        libvlc_media_t *m = NULL;
        libvlc_instance_t *inst;
        int64_t duration = 0;

        inst = libvlc_new(0, NULL);

        m = libvlc_media_new_path(inst, filepath);
        libvlc_media_parse(m);
        duration = libvlc_media_get_duration(m);
        if (duration != 0)
                print_minutes_seconds(filepath, duration);
        return 0;
}


int main(int argc, char **argv)
{
        struct arguments arguments;

        arguments.version = 0;
        arguments.help = 0;
        arguments.args[0] = ".";

        argp_parse (&argp, argc, argv, 0, 0, &arguments);

        struct stat s;
        int err;

        if (arguments.version) {
                printf("%s\n", lsmd_version);
                return 0;
        }

        if( stat(arguments.args[0],&s) != 0 )
        {
                perror("");
                return -1;
        }

        if(s.st_mode & S_IFDIR )
        {
                err = handle_directory(arguments.args[0]);
                if (err != 0) perror("");
                return err;
        }
        else if( s.st_mode & S_IFREG )
        {

                err = handle_file(arguments.args[0]);
                if (err != 0) perror("");
                return err;
        }
        return (-1);
}

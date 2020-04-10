#include <sys/types.h> 
#include <sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <fcntl.h>
#define BUFS 1000
#define INB 100
#define  ARGM 10
#define G "\x1b[92m"
#define B "\x1b[94m"
#define D "\x1B[0m"
#define C "\x1b[96m"
int c; 


struct _instr
{
    char * args[INB];
    int 
argc;
};
typedef struct _instr instruct;
 
    

char *input,*input1;
int eflag = 0;
int fpid,fd[2];
char cwd[BUFS];
char* args[ARGM];
int argc = 0,inBg = 0;
int externIN=0,externO=0;
char inputfile[INB],outputfile[INB];
void inputcmd();
int fexit();
void fpwd(char*, int);
void fcd(char*);
void fmkdir(char*);
void frmdir(char*);
void fclear();
void nameFile(struct dirent*, char*);
void fls();
void flsl();
void fcp(char*, char*);
void executable();
void pipe_dup(int, instruct*);
void run_process(int, int, instruct*);



void stopSignal()
{

    if(fpid!=0)
    {
        int temp = fpid;
        kill(fpid, SIGINT);
        fpid = 0;

    }
}




void inputcmd()
{ FILE *fpp;   
 fpp=fopen("history.txt","a+");
    fflush(stdout); // for clearing prev buffers , e
    input = NULL;
    ssize_t buf = 0;
    getline(&input,&buf,stdin);
    input1 = (char *)malloc(strlen(input) * sizeof(char));
    strncpy(input1,input,strlen(input));
    fputs(input,fpp);
    argc = 0;inBg = 0;
    while((args[argc] = strsep(&input, " \t\n")) != NULL && argc < ARGM-1)
    {
        if(sizeof(args[argc])==0)
        {
            free(args[argc]);
        }
        else argc++;
        if(strcmp(args[argc-1],"&")==0)
        {
            inBg = 1; // for backg running
            return;
        }
    }
    free(input);
   c= fclose(fpp);
}






void fclear()
{
    const char* blank = "\e[1;1H\e[2J";
       printf("\e[1;1H\e[2J");
  //    write(STDOUT_FILENO,blank,12);
}

void frmdir(char* name)
{
    int statrm = rmdir(name);
    if(statrm==-1)
    {
        perror("error in rmdir command \n");
    }
}


void fmkdir(char* name)
{
    int stat = mkdir(name, 0777);
    if(stat==-1)
    {
        perror("error in rmdir command\n");
    }
}



void fcd(char* path)
{
    int ret = chdir(path);
    if(ret==0) 
    {
        fpwd(cwd,0);
    }
    else perror("error in cd command\n");
}



int fexit()
{
    eflag = 1;
    return 0; 
}


void fpwd(char* cwdstr,int command)
{
    char temp[BUFS];
    char* path=getcwd(temp, sizeof(temp));
    if(path != NULL)
    {
        strcpy(cwdstr,temp);
        if(command==1) 
        {
            printf("%s\n",cwdstr);
        }
    }
    else perror(" Error in getcwd() command : ");

}

void fenv()
{
printf("SHELL=/bin/bash\nSESSION_MANAGER=local/vertigox:@/tmp/.ICE-unix/933,unix/vertigox:/tmp/.ICE-unix/933\nQT_ACCESSIBILITY=1\nCOLORTERM=truecolor\nXDG_MENU_PREFIX=gnome-\nGNOME_DESKTOP_SESSION_ID=this-is-deprecate\nLANGUAGE=en_IN:en\n\
SSH_AUTH_SOCK=/tmp/ssh-rc07tcjSjwz6/agent.933\nDESKTOP_SESSION=gnome\nSSH_AGENT_PID=987\nGTK_MODULES=gail:atk-bridgen\nGDM_LANG=en_INHOME=/root\nUSERNAME=root\nLS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;\n42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.\n\nswm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:\n*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=0");

}


void fcp(char* file1, char* file2)
{
    FILE *f1,*f2;
    struct stat t1,t2;
    f1 = fopen(file1,"r");
    if(f1 == NULL)
    {
        perror("Error in cp command ");
        return;
    }
    f2 = fopen(file2,"r");// if file exists
    if(f2)
    {
       
        stat(file1, &t1);
        stat(file2, &t2);
        if(difftime(t1.st_mtime,t2.st_mtime) < 0)
        {
            printf("Error in cp : %s is more recently updated than %s\n",file2,file1);
            fclose(f1);
            fclose(f2);
            return;
        }
    }
    f2 = fopen(file2,"ab+"); 
    fclose(f2);

    f2 = fopen(file2,"w+");
    if(f2 == NULL)
    {
        perror("Error in cp file2 ");
        fclose(f1);
        return;
    }

    if(open(file2,O_WRONLY)<0 || open(file1,O_RDONLY)<0)
    {
        perror("Error in cp access ");
        return;
    }
    char cp;
    while((cp=getc(f1))!=EOF)
    {
        putc(cp,f2);
    }

    fclose(f1);
    fclose(f2);
}



void nameFile(struct dirent* name,char* followup)
{
    if(name->d_type == DT_REG)          
    {
        printf("%s%s%s",B, name->d_name, followup);
    }
    else if(name->d_type == DT_DIR)    // a directory
    {
        printf("%s%s/%s",G, name->d_name, followup);
    }
    else                              
    {
        printf("%s%s%s",C, name->d_name, followup);
    }
}



void flsl()
{
    int i=0,total=0;
    char timer[14];
    struct dirent **listr;
    struct stat details;
    int listn = scandir(".",&listr,0,alphasort);
    if(listn > 0)
    {
        printf("%s+--- Total %d objects in this directory\n",C,listn-2);
        for ( i = 0; i < listn; i++)
        {
            if(strcmp(listr[i]->d_name,".")==0 || strcmp(listr[i]->d_name,"..")==0)
            {
                continue;
            }
            else if(stat(listr[i]->d_name,&details)==0)
            {
                
                total += details.st_blocks; // block size
                // owner permissions - group permissions - other permissions
                printf("%s%1s",D,(S_ISDIR(details.st_mode)) ? "d" : "-");
                printf("%s%1s",D,(details.st_mode & S_IRUSR) ? "r" : "-");
                printf("%s%1s",D,(details.st_mode & S_IWUSR) ? "w" : "-");
                printf("%s%1s",D,(details.st_mode & S_IXUSR) ? "x" : "-");
                printf("%s%1s",D,(details.st_mode & S_IRGRP) ? "r" : "-");
                printf("%s%1s",D,(details.st_mode & S_IWGRP) ? "w" : "-");
                printf("%s%1s",D,(details.st_mode & S_IXGRP) ? "x" : "-");
                printf("%s%1s",D,(details.st_mode & S_IROTH) ? "r" : "-");
                printf("%s%1s",D,(details.st_mode & S_IWOTH) ? "w" : "-");
                printf("%s%1s ",D,(details.st_mode & S_IXOTH) ? "x" : "-");

                printf("%2ld ",(unsigned long)(details.st_nlink));
                printf("%s ",(getpwuid(details.st_uid))->pw_name);
                printf("%s ",(getgrgid(details.st_gid))->gr_name);

                printf("%5lld ",(unsigned long long)details.st_size);
                strftime (timer,14,"%h %d %H:%M",localtime(&details.st_mtime));
                printf("%s ",timer);
                nameFile(listr[i],"\n");
            }
        }
        printf("%sTotal %d object contents\n",C,total/2);
    }
    else
    {
            printf("Empty directory\n" );
    }
}

void history(){
 FILE *fppp;

fppp=fopen("history.txt","r");
char cmds[50];
while(fgets(cmds,50,fppp)!=NULL){
printf("%s \n",cmds);
}
c=fclose(fppp);
}




/* list cwd contents*/
void fls()
{
    int i=0;
    struct dirent **listr;
    int listn = scandir(".", &listr, 0, alphasort);
    if (listn >= 0)
    {
        printf("%sTotal %d objects presents in the directory \n",C,listn-2);
        for(i = 0; i < listn; i++ )
        {
            if(strcmp(listr[i]->d_name,".")==0 || strcmp(listr[i]->d_name,"..")==0)
            {
                continue;
            }
            else nameFile(listr[i],"    ");
            if(i%8==0) printf("\n");
        }
        printf("\n");
    }
    else
    {
        perror ("Error in ls commnad  ");
    }

}
  
  
  
  




void runprocess(char * cli, char* args[], int count)
{

    int ret = execvp(cli, args);
    char* pathm;
    pathm = getenv("PATH");
    char path[1000];
    strcpy(path, pathm);
    strcat(path,":");
    strcat(path,cwd);
    char * cmd = strtok(path, ":\r\n");
    while(cmd!=NULL)
    {
       char loc_sort[1000];
        strcpy(loc_sort, cmd);
        strcat(loc_sort, "/");
        strcat(loc_sort, cli);
        printf("execvp : %s\n",loc_sort );
        ret = execvp(loc_sort, args);
        if(ret==-1)
        {
            perror("Error in running executable ");
            exit(0);
        }
        cmd = strtok(NULL, ":\r\n");
    }
}


void pipe_dup(int n, instruct* command)
{
    int in = 0,fd[2], i;
    int pid, status,pipest;

    if(externIN)
    {
        in = open(inputfile, O_RDONLY); // open the file
        if(in < 0)
        {
            perror("Error in executable : input file ");
        }
    }
   
    for (i = 1; i < n; i++)
    {
        
        int id = fork();
        if (id==0)
        {

            if (in!=0)
            {
                dup2(in, 0);
                close(in);
            }
            if (fd[1]!=1)
            {
                dup2(fd[1], 1);
                close(fd[1]);
            }


            runprocess(command[i-1].args[0], command[i-1].args,command[i-1].argc);
            exit(0);

        }
        else wait(&pipest);
        close(fd[1]);
        in = fd[0]; // store input for next child, it there is one
    }
    i--; 
    if(in != 0)
    {
        dup2(in, 0);
    }
    if(externO)
    {
        int ofd = open(outputfile, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        dup2(ofd, 1);
    }

    runprocess(command[i].args[0], command[i].args, command[i].argc);
}





/* executables like ./a.out */
void executable()
{
    instruct command[INB];
    int i=0,j=1,status;
    char* curr = strsep(&input1," \t\n");
    command[0].args[0] = curr;

    while(curr!=NULL)
    {
        curr = strsep(&input1, " \t\n");
        if(curr==NULL)
        {
            command[i].args[j++] = curr;
        }
        else if(strcmp(curr,"|")==0)
        {
            command[i].args[j++] = NULL;
            command[i].argc = j;
            j = 0;i++;// move to the next instruction
        }
        else if(strcmp(curr,"<")==0)
        {
            externIN = 1;
            curr = strsep(&input1, " \t\n");
            strcpy(inputfile, curr);
        }
        else if(strcmp(curr,">")==0)
        {
            externO = 1;
            curr = strsep(&input1, " \t\n");
            strcpy(outputfile, curr);
        }
        else if(strcmp(curr, "&")==0)
        {
            inBg = 1;
        }
        else
        {
            command[i].args[j++] = curr;
        }
    }
    command[i].args[j++] = NULL; // handle last command separately
    command[i].argc = j;
    i++;

    fpid = fork();
    if(fpid == 0)
    {
        pipe_dup(i, command);
    }
    else
    {
        if(inBg==0)
        {
            waitpid(fpid,&status, 0);
        }
        else
        {
            printf("Process running in inBg. PID:%d\n",fpid);
        }
    }
    fpid = 0;
    free(input1);
}  
















int main(int argc, char* argv[])
{  
    signal(SIGINT,stopSignal);
    int i;
    int pipe1 = pipe(fd);
    fclear();
    FILE *f;
    f=fopen("history.txt","w+");   
    c= fclose(f);
      



    fpwd(cwd,0);

    while(eflag==0)
    {   
        externIN = 0; externO = 0;inBg = 0;
        printf("%s%s > ",D,cwd ); //print user prompt

        inputcmd();

        if(strcmp(args[0],"exit")==0 || strcmp(args[0],"z")==0)
        {
            fexit();
        }
      
       
        else if(strcmp(args[0],"pwd")==0 && !inBg)
        {
            fpwd(cwd,1);
        }
        else if(strcmp(args[0],"cd")==0 && !inBg)
        {
            char* path = args[1];
            fcd(path);
        }
        else if(strcmp(args[0],"mkdir")==0 && !inBg)
        {
            char* foldername = args[1];
            fmkdir(foldername);
        }
        else if(strcmp(args[0],"rmdir")==0 && !inBg)
        {
            char* foldername = args[1];
            frmdir(foldername);
        }
        else if(strcmp(args[0],"clear")==0 && !inBg)
        {
            fclear();
        }
        else if(strcmp(args[0],"ls")==0 && !inBg)
        {
            char* optional = args[1];
            if(strcmp(optional,"-l")==0 && !inBg)
            {
                flsl();
            }
            else fls();
        }
        else if(strcmp(args[0],"cp")==0 && !inBg)
        {
            char* file1 = args[1];
            char* file2 = args[2];
            if(argc > 2 && strlen(file1) > 0 && strlen(file2) > 0)
            {
                fcp(file1,file2);
            }
            else
            {
                printf("Error in cp, numbers of arg are insufficient \n");
            }
        }
  	else if(strcmp(args[0],"env")==0 && !inBg)
        {
            fenv();
        }
	else if(strcmp(args[0],"history")==0 && !inBg)
        {
            char* opt = args[1];
             history();
        }
        else
        {
            executable();
        }

    }

}

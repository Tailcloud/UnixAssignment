#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "unistd.h"
#include <sys/wait.h>
#define readline_size 1024;
#define delim "\t\n\r\a "

void tsh_loop(void);
int tshcd(char **args);
int tshpwd(char **args);
char *readline();
char **splitline(char* line);
int executefunc(char **args);
int runforeground(char **args);
int count = 0 ;
char cwd[1024];
char *builtin_str[] = {
	//put build-in fau in arr
	"cd",
	"pwd"
};

int (*buildin_fun[])(char**)={
	//function pointer with argument char**
	&tshcd,
	&tshpwd
};

int main(int argc, char **argv){
	tsh_loop();
	return EXIT_SUCCESS;
}

void tsh_loop(void){
	char *line;
	char **args;
	int status;

	do{
		printf("%s > ",getcwd(cwd,sizeof(cwd)));
		line = readline();
		args = splitline(line);
		status = executefunc(args);
	}while(status);
	
	free(line);
	free(args);

}
//readline
//parseline
//execute process: fork
//cd pwd

char *readline(){
	char *line = NULL;//init line
	ssize_t linebuf = 0;
	getline(&line,&linebuf,stdin);
	return line;
}

char **splitline(char* oriline){
	count=0;
	char** tokens;
	char* token;
	int bufsize = 64, pos = 0;
	tokens = malloc(bufsize * sizeof(char*));

	token = strtok(oriline,delim);
	if(!tokens){//no allocation
		exit(EXIT_FAILURE);
	}else{
		while(token != NULL){
			tokens[pos] = token;
			pos++;
			count++;
			if(pos>bufsize){
				bufsize += bufsize;
				tokens = realloc(tokens,bufsize * sizeof(char*));
				//realloc will release origin memory space
				if(!tokens){//no allocation
					exit(EXIT_FAILURE);
				}else{


				}
			}
			token = strtok(NULL,delim);
		}
		tokens[pos] = NULL;//iniit

		return tokens;
	}

}

//should it run background or not
int executefunc(char **args){
	int i;
	if(args[0] == NULL)//no command
		return 1;

	for(i = 0 ; i < 2 ; i++){
		if(strcmp(args[0],builtin_str[i]) == 0){//the same arg
			return (*buildin_fun[i])(args);
		}
	}
	return runforeground(args);
}

int runforeground(char **args){
	pid_t pid;
	int status;
	if((pid = fork())<0)
		fprintf(stderr,"tsh: fork failed");
	if(pid == 0){
		//child
		if(strcmp(args[count-1],"&")==0){
			args[count-1]=NULL;
			count--;
		}
		if(execvp(args[0],args) == -1){
			if((args[0][0]!='.')&&(args[0][1]!='/'))
				printf("%s: command not found\n",args[0]);
			else
				perror("tsh");
		}
		exit(EXIT_FAILURE);
	}else if(pid>0){
		if(strcmp(args[count-1],"&")!=0){
			do{
				waitpid(pid,&status,WUNTRACED);
			}while(!WIFEXITED(status)&&!WIFSIGNALED(status));//if child not stop, keep waiting
		}else{
			waitpid(-1,&status,WNOHANG);		
		}
		
		
	}else if(pid<0){
		//error
		perror("tsh");		
	}
	return 1;
}

void runbackground(){

}



int tshcd(char** args){

	char* tmp;	
	char c;
	char* path;

	if(args[1]==NULL){
		printf("in-null");
		chdir(getenv("HOME"));

	}else{
		tmp = args[1];
		c = tmp[0];
		if(args[0] == NULL){
			
			//no argument
			/*chdir(getenv("HOME"));*/
			fprintf(stderr, "tsh: expected argument to \"cd\"\n");
		}else{
			if(c=='~'){
				chdir(getenv("HOME"));
				memmove(args[1],args[1]+1,strlen(args[1]));
				memmove(args[1],args[1]+1,strlen(args[1]));
				chdir(args[1]);
			}else{
				if(chdir(args[1])!=0){//failed in chdir
					perror("tsh");
				}
			}
		}	
	}
	
	
	return 1;
}

int tshpwd(char** args){
	
    char buff[256];
    getcwd(buff,sizeof(buff));
    printf("%s\n",buff);
    return 1;
}

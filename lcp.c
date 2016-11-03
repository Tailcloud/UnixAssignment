#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libgen.h>
#include <sys/stat.h>
void writeFile(FILE* file1,FILE* file2);
int isDir(char *path);
struct stat s;
char *bname;
char *path2, *tarpath;
char lastc[256];

int main(int argc, char* argv[]){
	FILE *openOri, *openTar;

	if(fopen(argv[1],"r")!=NULL){
		openOri = fopen(argv[1],"r");
		path2 = strdup(argv[1]);
		bname = basename(path2);
		tarpath = argv[2];
		if(isDir(tarpath)){			
			int len = strlen(tarpath);
			strcpy(lastc,tarpath);
			if(lastc[len-1]!='/'){
				tarpath = strcat(tarpath,"/");
				tarpath = strcat(tarpath,bname);
			}else{
				tarpath = strcat(tarpath,bname);
			}
		}else{
			tarpath = tarpath;
		}
	 }else{
		printf("cp: %s: No such file or directory\n", argv[1]);
	}

	if(fopen(tarpath,"w")!=NULL){
	 	openTar = fopen(tarpath,"w");
	  }else{
	 	printf("cp: cannot copy to\n");		
	 }

	 writeFile(openOri,openTar);

	 fclose(openOri);
	 fclose(openTar);
	return 0;
}

void writeFile(FILE* fileOri, FILE* fileTar){
	int orifd = fileno(fileOri);
	int tarfd = fileno(fileTar);
	int x;
	int size=lseek(orifd,0,SEEK_END);   //to find the size of the file
	char *buffer = malloc(size);
	lseek(orifd,0,SEEK_SET);
	for(x = 0 ; x<size ; x++){
		int rd=read(orifd,buffer,1);    //read one char at a time from file1 (use fd1)
		int wr;
		if(*buffer==0)
			*buffer = '\0';
		wr=write(tarfd,buffer,1);

	}
}

int isDir(char *path){
	if( stat(path,&s) == 0 )
	{
	    if( s.st_mode & S_IFDIR )
	    	return 1;
	    else if( s.st_mode & S_IFREG )
	    	return 0;
	}
	else
		return 0;
}

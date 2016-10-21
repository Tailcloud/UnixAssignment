#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define BUFFER_MAX 200
int main(int argc, char *argv[]){
	FILE *inputFile;
	char *filename;
	char num;
	int line=0,word=0,byt=0;
	char lineChar[256]={'\0'},wordChar[256]={'\0'},bytChar[256]={'\0'},tmpbChar[256]={'\0'},tmpwChar[256]={'\0'},tmplChar[256]={'\0'},*tmpFilename[256]={"\0"};
	const char* iter;
	int inword = 0;
	int optarr[]= {0,0,0} ;
	int count=0;
	int err=1;
	int i;
	char *files[128];
	int fileCount=0;
	int wTotal[128],lTotal[128],bTotal[128];
	int tw=0,tl=0,tb=0;
	int spacelen;
	int cunt=0;
	int isFiles = 0;
	int isTotal=0;
	for (i = 1 ; i < argc ; i++){
		if(strstr(argv[i],"-")!=NULL){
			//options
			int j;
			for(j = 1 ; j < strlen(argv[i]);j++){
				switch(argv[i][j]){
				case 'l':
					optarr[0] = 1;
					count++;
				break;
				case 'w':
					optarr[1] = 1;
					count++;
				break;
				case 'c':
					optarr[2] = 1;
					count++;
				break;
				default:
					err=0;
					fprintf(stderr,"wc: invalid option -- '-%c'\nTry 'wc --help' for more information.\n",argv[i][j]);
				}
				cunt = count;
			}
	 	}else{
			isTotal++;
			if((fopen(argv[i],"r")!=NULL)&&(i!=0)){
				//valid filename
				//filename = argv[i];
				files[fileCount] = argv[i];
				fileCount++;
			 }else{
			 	// invalid filename	
				fprintf(stderr,"wc: %s: No such file or directory\n",argv[i]);
			 	isFiles++;
			 }	
		}
	 }
//	讀檔 全部讀過
	int filscount;
	for(filscount = 0 ; filscount < fileCount ; filscount++){
	 	word = 0;
	 	line = 0;
	 	byt = 0;
	 	filename = files[filscount];
	 	tmpFilename[filscount] = filename;
	 	if((fopen(files[filscount],"r")!=NULL)&&err==1){
	 	inputFile = fopen(filename,"r");
	 	while((num=fgetc(inputFile))!=EOF){//count
	 		switch(num){
	 			case '\0': case ' ': case '\t': case'\n': case '\r':
					if(inword){
						inword = 0;
						word++;
					}
					break;
		 		default:
	 				inword=1;
	 		}
	 		byt++;

	 		if(num =='\n')
	 		 	line = line+1;
	 	}	
	 	sprintf(lineChar,"%d",line);
	 	sprintf(wordChar,"%d",word);
	 	sprintf(bytChar,"%d",byt);
	 	wTotal[filscount] = word;
	 	lTotal[filscount] = line;
	 	bTotal[filscount] = byt;

	 	fclose(inputFile);
	 	
	 	// 計算並且存起來

	 	spacelen = strlen(bytChar);
		int tmplen = spacelen;
	 	//如果只有一個檔案，直接印。
	 	if((fileCount==1)&&(isTotal==1)){
	 		if(optarr[0]==0){
	 			//line
	 			lineChar[0] ='\0';
		 	}
		 	if(optarr[1]==0){
		 		//word
		 		wordChar[0]='\0';
		 	}
		 	if(optarr[2]==0){
		 		//count
		 		bytChar[0]='\0';
		 	}
		 	//如果只有一個option
		 	if(count==1){
		 		if(lineChar[0]!='\0'){
		 			printf("%s %s\n",lineChar,filename);
		 		}else if(wordChar[0]!='\0'){
		 			printf("%s %s\n",wordChar,filename);
		 		}else{
		 			printf("%s %s\n",bytChar,filename);
		 		}
		 	}else{//如果不只一個option

		 		for(i = 0 ; i <= count ; i++){
		 			//for(int x = 0 ; x <= spacelen ; x++){
		 				if(optarr[i]!=0){
		 					int x;
			 				if(i==0){
			 					spacelen = spacelen - strlen(lineChar);

			 					for(x = 0 ; x < spacelen ; x++){
			 						printf(" ");
			 					}
			 						printf("%s ",lineChar);
			 				}
			 				if(i==1){
			 					spacelen = spacelen - strlen(wordChar);
			 					for(x = 0 ; x < spacelen ; x++){
			 						printf(" ");
			 					}			 					
			 						printf("%s ",wordChar);
			 				}
			 				if(i==2){
			 					spacelen = spacelen - strlen(bytChar);
			 					for(x = 0 ; x < spacelen ; x++){
			 						printf(" ");
			 					}
			 						printf("%s ",bytChar);
			 				}
			 			}
		 			spacelen = tmplen; 
		 		}
		 		printf("%s\n",filename);
		 	}
		}	
	 	}
	}
	//如果不只一個檔案的印
	int finalCount;
	if((isTotal>1)&&(count>0)&&(err==1)){
	 	for (finalCount=0 ; finalCount < filscount ; finalCount++){
	 		tw = tw + wTotal[finalCount];
	 		tl = tl + lTotal[finalCount];
	 		tb = tb + bTotal[finalCount];
		}

		sprintf(tmplChar,"%d",tl);
	 	sprintf(tmpwChar,"%d",tw);
	 	sprintf(tmpbChar,"%d",tb);
		
		spacelen = strlen(tmpbChar);
		//
		if(optarr[0]==0){
	 		//line
	 		lineChar[0] ='\0';
	 	}
	 	if(optarr[1]==0){
	 		//word
	 		wordChar[0]='\0';
	 	}
	 	if(optarr[2]==0){
	 		//count
	 		bytChar[0]='\0';
	 	}
	 
	 	int tmpfile;
	 	for(tmpfile=0 ; tmpfile<fileCount ; tmpfile++){
	 		sprintf(lineChar,"%d",lTotal[tmpfile]);
	 		sprintf(wordChar,"%d",wTotal[tmpfile]);
	 		sprintf(bytChar,"%d",bTotal[tmpfile]);
	 		for(i = 0 ; i <= count ; i++){
	 				if(optarr[i]!=0){
	 					int x;
		 				if(i==0){
		 					spacelen = spacelen - strlen(lineChar);
		 					//printf("len - l %d\n",spacelen);

		 					for(x = 0 ; x < spacelen ; x++){
		 						printf(" ");
		 					}
		 						printf("%s ",lineChar);
		 				}
		 				if(i==1){
		 					spacelen = spacelen - strlen(wordChar);
		 					//printf("len - w %d\n",spacelen);

		 					for(x = 0 ; x < spacelen ; x++){
		 						printf(" ");
		 					}			 					
		 						printf("%s ",wordChar);
		 				}
		 				if(i==2){
		 					spacelen = spacelen - strlen(bytChar);
		 					//printf("len - b %d\n",spacelen);

		 					for(x = 0 ; x < spacelen ; x++){
		 						printf(" ");
		 					}
		 						printf("%s ",bytChar);
		 				}
		 			}
	 			spacelen = strlen(tmpbChar); 
	 		}
	 		printf("%s\n",tmpFilename[tmpfile]);


	 	}
	 	//}
		for(i = 0 ; i <= count ; i++){
	 				if(optarr[i]!=0){
	 					int x;
		 				if(i==0){
		 					spacelen = spacelen - strlen(tmplChar);

		 					for(x = 0 ; x < spacelen ; x++){
		 						printf(" ");
		 					}
		 						printf("%s ",tmplChar);
		 				}
		 				if(i==1){
		 					spacelen = spacelen - strlen(tmpwChar);
		 					for(x = 0 ; x < spacelen ; x++){
		 						printf(" ");
		 					}			 					
		 						printf("%s ",tmpwChar);
		 				}
		 				if(i==2){
		 					spacelen = spacelen - strlen(tmpbChar);
		 					for(x = 0 ; x < spacelen ; x++){
		 						printf(" ");
		 					}
		 						printf("%s ",tmpbChar);
		 				}
		 			}
	 			spacelen = strlen(tmpbChar); 
	 		}
	 		printf("total\n");

	 }
	 if(err==0||isFiles>0)
		return 1;
	else
		return 0;
}

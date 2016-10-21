#include "hw2.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int mydup2(int oldfd, int newfd){
 	int x,i;
 	int duped[1024];
 	int count = 0;
	char buffer[1024];
 	if(newfd>1023)
 		return -1;
 
	if (oldfd == newfd) {
		return newfd; 
	}

	if(isValid(oldfd)==-1){
		return -1;	
	}

	if(isValid(newfd))
		close(newfd);

	for(x = 0 ; x < 1024 ; x++){
		duped[count] = dup(oldfd);
		if(duped[count]==newfd){
			for(i = 0 ; i < count ; i++){
				close(duped[i]);
			}
			break;
		}
		count++;
	}
	return 0;
}

int isValid(int fd){
	int dupno = fd;
	if(dupno==0||dupno==1||dupno==2){
		return 1;
	}else{
		if(lseek(fd, 0, SEEK_CUR)>=0){
			return 1;
		}else{
			return -1;
		}
	}
	return 1;
}
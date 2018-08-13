#include<cstdio>
#include<cstring>
#define MAX 10010
int main(){
	char a[MAX];
	gets(a);
	int length=strlen(a);
	for(int i=0;i<length;i++){
		if(a[i]=='d'){
			i++;
			if(a[i]=='e'){
				i++;
				if(a[i]=='b'){
					i++;
					if(a[i]=='u'){
						i++;
						if(a[i]=='g'){
							printf("°üº¬");
							return 0;
						}
					}
				}
			}
		}		
	}
	printf("²»°üº¬");
	return 0;
}
